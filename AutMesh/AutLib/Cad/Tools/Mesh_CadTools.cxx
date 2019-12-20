#include <Mesh_CadTools.hxx>

#include <Entity2d_Box.hxx>
#include <MetricMap2d_ExactSurfaceLowerBounded.hxx>
#include <SizeMap3d_Uniform.hxx>
#include <SizeMap2d_Surface.hxx>
#include <SizeMap2d_FullIntSurface.hxx>
#include <Mesh2d_SizeMapAnIso.hxx>
#include <Mesh2d_SizeMapSurface.hxx>
#include <Numeric_AdaptIntegration.hxx>
#include <Mesh_LineIntegrand.hxx>
#include <Mesh_LineIntegrand_Function.hxx>
#include <Mesh_Info.hxx>
#include <Mesh_CurveEntity.hxx>
#include <Mesh_Curve.hxx>
#include <Cad_Tools.hxx>
#include <Numeric_AdaptIntegration.hxx>

#include <Geom2d_Curve.hxx>
#include <Geom_Surface.hxx>
#include <Geom_BoundedSurface.hxx>
#include <Geom_BSplineSurface.hxx>

Standard_Real AutLib::Mesh_CadTools::CalcLength
(
	const Pnt2d & theP0,
	const Pnt2d & theP1,
	const Entity2d_Box & theBoundingBox,
	const Handle(Geom_Surface) & theSurface,
	intgInfo& theInfo
)
{
	auto surfMetricInfo = std::make_shared<MetricMap2d_ExactSurfaceLowerBoundedInfo>();
	Debug_Null_Pointer(surfMetricInfo);

	auto metricMap = std::make_shared<MetricMap2d_ExactSurfaceLowerBounded>(theSurface, theBoundingBox, surfMetricInfo);
	Debug_Null_Pointer(metricMap);

	auto uniSize = std::make_shared<SizeMap3d_Uniform>(1.0);
	Debug_Null_Pointer(uniSize);

	auto surfaceSize = std::make_shared<SizeMap2d_Surface>(*uniSize, *theSurface);
	Debug_Null_Pointer(surfaceSize);

	auto fullAnIso = std::make_shared<SizeMap2d_FullIntSurface>(mesh_size_map2d_full_surface_info);
	Debug_Null_Pointer(fullAnIso);

	fullAnIso->LoadMetricMap(metricMap);
	fullAnIso->LoadSizeMap(surfaceSize);

	Mesh_LineIntegrand_FullIntSurface c0(theP0, theP1, *fullAnIso);
	Mesh_LineIntegrand_Function_FullIntSurface fun0(c0);

	Numeric_AdaptIntegration_FullIntSurface Intg(fun0, 0, 1, theInfo);

	Intg.Perform();
	return theInfo.Result();
}

Standard_Real 
AutLib::Mesh_CadTools::CalcLength
(
	const Geom2d_Curve & theCurve,
	const Standard_Real theFirst,
	const Standard_Real theLast,
	const Mesh2d_SizeMapAnIso & theSizeMap
)
{
	Mesh_CurveEntity<Geom2d_Curve, Mesh2d_SizeMapAnIso> 
		entity
		(
			theCurve, theSizeMap, 
			theFirst, theLast);

	Numeric_AdaptIntegrationInfo info;
	info.SetMaxNbIterations(100);
	info.SetNbInitIterations(4);
	info.SetTolerance(1.0E-4);

	return Mesh_Curve<Geom2d_Curve, Mesh2d_SizeMapAnIso>::CalcLength(entity, 10, info);
}

Standard_Real 
AutLib::Mesh_CadTools::CalcLength
(
	const Geom2d_Curve & theCurve,
	const Standard_Real theFirst, 
	const Standard_Real theLast, 
	const Mesh2d_SizeMapSurface & theSizeMap
)
{
	Mesh_CurveEntity<Geom2d_Curve, Mesh2d_SizeMapSurface>
		entity
		(
			theCurve, theSizeMap,
			theFirst, theLast);

	Numeric_AdaptIntegrationInfo info;
	info.SetMaxNbIterations(100);
	info.SetNbInitIterations(4);
	info.SetTolerance(1.0E-4);

	return Mesh_Curve<Geom2d_Curve, Mesh2d_SizeMapSurface>::CalcLength(entity, 10, info);
}

Standard_Real 
AutLib::Mesh_CadTools::CalcLengthOnSurface
(
	const Geom2d_Curve & theCurve,
	const Standard_Real theFirst, 
	const Standard_Real theLast, 
	const Entity2d_Box & theBoundingBox,
	const Handle(Geom_Surface)& theSurface
)
{
	auto surfMetricInfo = std::make_shared<MetricMap2d_ExactSurfaceLowerBoundedInfo>();
	Debug_Null_Pointer(surfMetricInfo);

	auto metricMap = std::make_shared<MetricMap2d_ExactSurfaceLowerBounded>(theSurface, theBoundingBox, surfMetricInfo);
	Debug_Null_Pointer(metricMap);

	auto uniSize = std::make_shared<SizeMap3d_Uniform>(1.0);
	Debug_Null_Pointer(uniSize);

	auto surfaceSize = std::make_shared<SizeMap2d_Surface>(*uniSize, *theSurface);
	Debug_Null_Pointer(surfaceSize);

	auto fullAnIso = std::make_shared<SizeMap2d_FullIntSurface>(mesh_size_map2d_full_surface_info);
	Debug_Null_Pointer(fullAnIso);

	fullAnIso->LoadMetricMap(metricMap);
	fullAnIso->LoadSizeMap(surfaceSize);

	return CalcLength(theCurve, theFirst, theLast, *fullAnIso);
}

namespace AutLib
{

	static Handle(Geom_Surface)
		Expand_U
	(
		const Geom_BSplineSurface & theSurface, 
		const Standard_Real multiply
	)
	{
		std::vector<Standard_Real> U;
		U.reserve(theSurface.UKnots().Size());

		for (const auto x : theSurface.UKnots())
		{
			U.push_back(multiply*x);
		}

		TColStd_Array1OfReal U1(1, (Standard_Integer)U.size());
		forThose(Index, 1, U1.Size()) U1.SetValue(Index, U[Index_Of(Index)]);

		if (theSurface.Weights())
		{
			Handle(Geom_BSplineSurface) copy =
				new Geom_BSplineSurface
				(
					theSurface.Poles(),
					*theSurface.Weights(),
					U1, theSurface.VKnots(), theSurface.UMultiplicities(),
					theSurface.VMultiplicities(),
					theSurface.UDegree(),
					theSurface.VDegree(),
					theSurface.IsUPeriodic(), theSurface.IsVPeriodic());

			return std::move(copy);
		}
		else
		{
			Handle(Geom_BSplineSurface) copy =
				new Geom_BSplineSurface
				(
					theSurface.Poles(),
					U1, theSurface.VKnots(), theSurface.UMultiplicities(),
					theSurface.VMultiplicities(),
					theSurface.UDegree(),
					theSurface.VDegree(),
					theSurface.IsUPeriodic(), theSurface.IsVPeriodic());

			return std::move(copy);
		}
	}

	static Handle(Geom_Surface)
		Expand_V
		(
			const Geom_BSplineSurface & theSurface,
			const Standard_Real multiply
		)
	{
		std::vector<Standard_Real> V;
		V.reserve(theSurface.VKnots().Size());

		for (const auto x : theSurface.VKnots())
		{
			V.push_back(multiply*x);
		}

		TColStd_Array1OfReal V1(1, (Standard_Integer)V.size());
		forThose(Index, 1, V1.Size()) V1.SetValue(Index, V[Index_Of(Index)]);

		if (theSurface.Weights())
		{
			Handle(Geom_BSplineSurface) copy =
				new Geom_BSplineSurface
				(
					theSurface.Poles(),
					*theSurface.Weights(),
					theSurface.UKnots(), V1, theSurface.UMultiplicities(),
					theSurface.VMultiplicities(),
					theSurface.UDegree(),
					theSurface.VDegree(),
					theSurface.IsUPeriodic(), theSurface.IsVPeriodic());

			return std::move(copy);
		}
		else
		{
			Handle(Geom_BSplineSurface) copy =
				new Geom_BSplineSurface
				(
					theSurface.Poles(),
					theSurface.UKnots(), V1, theSurface.UMultiplicities(),
					theSurface.VMultiplicities(),
					theSurface.UDegree(),
					theSurface.VDegree(),
					theSurface.IsUPeriodic(), theSurface.IsVPeriodic());

			return std::move(copy);
		}
	}

	static Handle(Geom_Surface) CopyGeometry
	(
		const Geom_BSplineSurface & theSurface,
		const gp_Trsf2d& theParamTransf
	)
	{
		std::vector<Pnt2d> U, V;
		U.reserve(theSurface.UKnots().Size());
		V.reserve(theSurface.VKnots().Size());

		for (const auto x : theSurface.UKnots())
		{
			U.push_back(Pnt2d(x, 0));
		}

		for (const auto x : theSurface.VKnots())
		{
			V.push_back(Pnt2d(0, x));
		}

		for (auto& x : U) x.Transform(theParamTransf);
		for (auto& x : V) x.Transform(theParamTransf);

		TColStd_Array1OfReal U1(1, (Standard_Integer)U.size());
		TColStd_Array1OfReal V1(1, (Standard_Integer)V.size());

		forThose(Index, 1, U1.Size()) U1.SetValue(Index, U[Index_Of(Index)].X());
		forThose(Index, 1, V1.Size()) V1.SetValue(Index, V[Index_Of(Index)].Y());

		if (theSurface.Weights())
		{
			Handle(Geom_BSplineSurface) copy =
				new Geom_BSplineSurface
				(
					theSurface.Poles(),
					*theSurface.Weights(),
					U1, V1, theSurface.UMultiplicities(),
					theSurface.VMultiplicities(),
					theSurface.UDegree(),
					theSurface.VDegree(),
					theSurface.IsUPeriodic(), theSurface.IsVPeriodic());

			return copy;
		}
		else
		{
			Handle(Geom_BSplineSurface) copy =
				new Geom_BSplineSurface
				(
					theSurface.Poles(),
					U1, V1, theSurface.UMultiplicities(),
					theSurface.VMultiplicities(),
					theSurface.UDegree(),
					theSurface.VDegree(),
					theSurface.IsUPeriodic(), theSurface.IsVPeriodic());

			return copy;
		}


	}
}

Handle(Geom_Surface) AutLib::Mesh_CadTools::GeomReParameterization
(
	const Handle(Geom_Surface)& theSurface, 
	const gp_Trsf2d & theParamTransf
)
{
	if (NOT Handle(Geom_BoundedSurface)::DownCast(theSurface))
	{
		return theSurface;
	}

	auto bspline = Handle(Geom_BSplineSurface)::DownCast(theSurface);
	if (bspline)
	{
		return CopyGeometry(*bspline, theParamTransf);
	}

	FatalErrorIn(FunctionSIG)
		<< "Invalid Surface type" << endl
		<< abort(FatalError);
	return 0;
}

Handle(Geom_Surface) AutLib::Mesh_CadTools::GeomReParameterization_uExpand
(
	const Handle(Geom_Surface)& theSurface, 
	const Standard_Real multiply
)
{
	if (NOT Handle(Geom_BoundedSurface)::DownCast(theSurface))
	{
		return theSurface;
	}

	auto bspline = Handle(Geom_BSplineSurface)::DownCast(theSurface);
	if (bspline)
	{
		auto expanded = Expand_U(*bspline, multiply);
		return std::move(expanded);
	}

	FatalErrorIn(FunctionSIG)
		<< "Invalid Surface type" << endl
		<< abort(FatalError);
	return 0;
}

Handle(Geom_Surface) 
AutLib::Mesh_CadTools::GeomReParameterization_vExpand
(
	const Handle(Geom_Surface)& theSurface,
	const Standard_Real multiply
)
{
	if (NOT Handle(Geom_BoundedSurface)::DownCast(theSurface))
	{
		return theSurface;
	}

	auto bspline = Handle(Geom_BSplineSurface)::DownCast(theSurface);
	if (bspline)
	{
		auto expanded = Expand_V(*bspline, multiply);
		return std::move(expanded);
	}

	FatalErrorIn(FunctionSIG)
		<< "Invalid Surface type" << endl
		<< abort(FatalError);
	return 0;
}

Handle(Geom_Surface)
AutLib::Mesh_CadTools::ConvertToBSpline
(
	const Handle(Geom_Surface)& theSurface,
	const Entity2d_Box& theTrimmed
)
{
	if (Handle(Geom_BSplineSurface)::DownCast(theSurface))
	{
		return theSurface;
	}

	auto surface = Cad_Tools::ConvertToBSpline(theSurface, theTrimmed);
	return std::move(surface);
}
#include <Mesh_PlnCurve.hxx>

#include <Entity2d_Chain.hxx>
#include <Mesh2d_CurveSurface.hxx>
#include <Mesh2d_CurveAnIso.hxx>
#include <Mesh2d_Curve.hxx>
#include <Mesh_CurveInfo.hxx>
#include <Geo2d_ApprxCurve.hxx>
#include <Aft2d_Edge.hxx>

#include <Geom2d_Curve.hxx>

std::shared_ptr<AutLib::Entity2d_Chain>
AutLib::Mesh_CadPlnCurveBase::Mesh
(
	const Standard_Real theFirst,
	const Standard_Real theLast,
	const Handle(Geom2d_Curve)& theCurve,
	const std::shared_ptr<Mesh2d_SizeMapSurface>& theSizeMap,
	const std::shared_ptr<Mesh_CurveInfo>& theInfo
)
{
	Mesh2d_CurveSurface Alg(theFirst, theLast, theCurve, theSizeMap, theInfo);

	if (NOT Alg.Curve())
	{
		FatalErrorIn(FunctionSIG)
			<< "No curve has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Alg.Map())
	{
		FatalErrorIn(FunctionSIG)
			<< "No size map has been loaded!" << endl
			<< abort(FatalError);
	}

	Alg.Perform();

	Debug_If_Condition_Message(NOT Alg.IsDone(), "the algorithm has not been performed!");

	auto mesh = Alg.Mesh();
	return std::move(mesh);
}

std::shared_ptr<AutLib::Entity2d_Chain> 
AutLib::Mesh_CadPlnCurveBase::Mesh
(
	const Standard_Real theFirst,
	const Standard_Real theLast,
	const Handle(Geom2d_Curve)& theCurve,
	const std::shared_ptr<Mesh2d_SizeMapAnIso>& theSizeMap,
	const std::shared_ptr<Mesh_CurveInfo>& theInfo
)
{
	Mesh2d_CurveAnIso Alg(theFirst, theLast, theCurve, theSizeMap, theInfo);

	if (NOT Alg.Curve())
	{
		FatalErrorIn(FunctionSIG)
			<< "No curve has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Alg.Map())
	{
		FatalErrorIn(FunctionSIG)
			<< "No size map has been loaded!" << endl
			<< abort(FatalError);
	}

	Alg.Perform();

	Debug_If_Condition_Message(NOT Alg.IsDone(), "the algorithm has not been performed!");

	auto mesh = Alg.Mesh();
	return std::move(mesh);
}

std::shared_ptr<AutLib::Entity2d_Chain>
AutLib::Mesh_CadPlnCurveBase::Mesh
(
	const Standard_Real theFirst,
	const Standard_Real theLast,
	const Handle(Geom2d_Curve)& theCurve,
	const std::shared_ptr<Mesh2d_SizeMap>& theSizeMap,
	const std::shared_ptr<Mesh_CurveInfo>& theInfo
)
{
	Mesh2d_Curve Alg(theFirst, theLast, theCurve, theSizeMap, theInfo);
	if (NOT Alg.Curve())
	{
		FatalErrorIn(FunctionSIG)
			<< "No curve has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Alg.Map())
	{
		FatalErrorIn(FunctionSIG)
			<< "No size map has been loaded!" << endl
			<< abort(FatalError);
	}

	Alg.Perform();
	Debug_If_Condition_Message(NOT Alg.IsDone(), "the algorithm has not been performed!");

	auto mesh = Alg.Mesh();
	return std::move(mesh);
}

std::shared_ptr<AutLib::Entity2d_Chain> 
AutLib::Mesh_CadPlnCurveBase::Discrete
(
	const Standard_Real theFirst,
	const Standard_Real theLast, 
	const Handle(Geom2d_Curve)& theCurve, 
	const std::shared_ptr<Geo_ApprxCurveInfo>& theInfo
)
{
	Geo2d_ApprxCurve Alg(theCurve, theFirst, theLast);

	Alg.Perform(*theInfo);
	Debug_If_Condition_Message(NOT Alg.IsDone(), "the algorithm has not been performed!");

	auto mesh = Alg.Chain();
	return std::move(mesh);
}
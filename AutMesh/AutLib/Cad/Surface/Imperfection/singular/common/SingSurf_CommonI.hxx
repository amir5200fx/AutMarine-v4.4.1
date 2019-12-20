#pragma once
#include <Singularity_TypeDetection.hxx>
#include <Singularity_PoleCurve.hxx>
#include <Mesh_CadTools.hxx>
namespace AutLib
{

	template<class SurfPln>
	std::shared_ptr<SurfPln> 
		SingSurf_Common<SurfPln>::GetPlane() const
	{
		auto This = std::dynamic_pointer_cast<SingSurf_Common<SurfPln>>(std::const_pointer_cast<typename SurfPln::surfType>(this->shared_from_this()));
		auto plane = ModifyPlane(This);
		return std::move(plane);
	}

	template<class SurfPln>
	std::shared_ptr<typename SurfPln::plnWire> 
		SingSurf_Common<SurfPln>::GetOuterWire
		(
			const typename surfType::wireType & theWire,
			const Geo_ColoringSurfMetric& theColors
		)
	{
		auto curves_ptr =
			std::make_shared<std::vector<std::shared_ptr<plnCurve>>>();
		auto& curves = *curves_ptr;
		curves.reserve(theWire.NbEdges());

		const auto& surface = theColors.Approx()->Surface();
		const auto& box = theColors.Approx()->BoundingBox();

		Standard_Integer K = 0;
		for (const auto& x : *theWire.Edges())
		{
			Debug_Null_Pointer(x);

			const auto& xCurve = x->Par();
			Debug_Null_Pointer(xCurve);

			auto midParam = MEAN(xCurve->FirstParam(), xCurve->LastParam());
			auto mPt = xCurve->Value(midParam);

			auto cLength = 
				Mesh_CadTools::CalcLengthOnSurface
				(
					*xCurve->Curve(), xCurve->FirstParam(),
					xCurve->LastParam(), box, surface);

			if (theColors.Value(mPt) AND cLength <= 1.0E-6)
			{
				auto curve =
					std::make_shared<Singularity_PoleCurve<plnCurve>>
					(
						xCurve->FirstParam(),
						xCurve->LastParam(),
						xCurve->Curve(), xCurve->Info());

				curves.push_back(curve);
			}
			else
			{
				curves.push_back(std::make_shared<plnCurve>(*xCurve));
			}
		}

		auto wire =
			std::make_shared<typename SurfPln::plnWire>(curves_ptr);

		return std::move(wire);
	}

	template<class SurfPln>
	std::shared_ptr<typename SurfPln::plnWire> 
		SingSurf_Common<SurfPln>::GetInnerWire
		(
			const typename surfType::wireType & theWire,
			const Geo_ColoringSurfMetric & theColors
		)
	{
		auto curves_ptr =
			std::make_shared<std::vector<std::shared_ptr<plnCurve>>>();
		auto& curves = *curves_ptr;
		curves.reserve(theWire.NbEdges());

		Standard_Integer K = 0;
		for (const auto& x : *theWire.Edges())
		{
			Debug_Null_Pointer(x);

			const auto& xCurve = x->Par();
			Debug_Null_Pointer(xCurve);

			auto midParam = MEAN(xCurve->FirstParam(), xCurve->LastParam());
			auto mPt = xCurve->Value(midParam);

			if (theColors.Value(mPt))
			{
				FatalErrorIn(FunctionSIG)
					<< " Invalid surface type: having any singularity curves for "
					<< " the common singularity surface has been forbidden!" << endl
					<< abort(FatalError);
			}
			else
			{
				curves.push_back(std::make_shared<plnCurve>(*xCurve));
			}
		}

		auto wire =
			std::make_shared<typename SurfPln::plnWire>(curves_ptr);

		return std::move(wire);
	}

	template<class SurfPln>
	std::shared_ptr<SurfPln> SingSurf_Common<SurfPln>::ModifyPlane
	(
		const std::shared_ptr<SingSurf_Common> & theSurface
	)
	{
		if (NOT theSurface->OuterWire())
		{
			FatalErrorIn(FunctionSIG)
				<< "Invalid Face : has no outer wire" << endl
				<< abort(FatalError);
		}

		Debug_Null_Pointer(theSurface->Type());
		Debug_Null_Pointer(theSurface->Type()->Colors());
		const auto& colors = theSurface->Type()->Colors();
		
		const auto& Outer = *theSurface->OuterWire();
		const auto& Inners = *theSurface->InnerWires();

		auto outer_wire =
			GetOuterWire(Outer, *colors);

		std::shared_ptr<std::vector<std::shared_ptr<typename SurfPln::plnWire>>> inner_wires;
		if (theSurface->InnerWires())
		{
			inner_wires = std::make_shared<std::vector<std::shared_ptr<typename SurfPln::plnWire>>>();
			inner_wires->reserve(Inners.size());

			for (const auto& x : Inners)
			{
				Debug_Null_Pointer(x);

				auto wire = GetInnerWire(*x, *colors);
				inner_wires->push_back(wire);
			}
		}

		auto plane =
			std::make_shared<SurfPln>(theSurface, outer_wire, inner_wires);
		return std::move(plane);
	}
}
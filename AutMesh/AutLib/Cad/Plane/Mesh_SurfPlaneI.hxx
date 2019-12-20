#pragma once
namespace AutLib
{

	template<class SurfType>
	void Mesh_SurfPlane<SurfType>::RetrieveWiresTo(wireList & theWires) const
	{
		theWires.push_back(theOutter_);
		if (theInner_)
		{
			for (const auto& x : *theInner_)
			{
				theWires.push_back(x);
			}
		}
	}

	template<class SurfType>
	std::shared_ptr<typename Mesh_SurfPlane<SurfType>::plnWire> 
		Mesh_SurfPlane<SurfType>::GetWire
		(
			const typename SurfType::wireType & theWire
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

			curves.push_back(std::make_shared<plnCurve>(*xCurve));
		}

		auto wire =
			std::make_shared<plnWire>(curves_ptr);

		return std::move(wire);
	}

	template<class SurfType>
	std::shared_ptr<Mesh_SurfPlane<SurfType>> 
		Mesh_SurfPlane<SurfType>::MakePlane
		(
			const std::shared_ptr<SurfType>& theFace
		)
	{
		if (NOT theFace->OuterWire())
		{
			FatalErrorIn(FunctionSIG)
				<< "Invalid Face : has no outer wire" << endl
				<< abort(FatalError);
		}

		const auto& Outer = *theFace->OuterWire();
		const auto& Inners = *theFace->InnerWires();

		auto outer_wire =
			GetWire(Outer);

		std::shared_ptr<std::vector<std::shared_ptr<plnWire>>> inner_wires;
		if (theFace->InnerWires())
		{
			inner_wires = std::make_shared<std::vector<std::shared_ptr<plnWire>>>();
			inner_wires->reserve(Inners.size());

			for (const auto& x : Inners)
			{
				Debug_Null_Pointer(x);

				auto wire = GetWire(*x);
				inner_wires->push_back(wire);
			}
		}

		auto plane =
			std::make_shared<Mesh_SurfPlane>(theFace, outer_wire, inner_wires);
		return std::move(plane);
	}
}
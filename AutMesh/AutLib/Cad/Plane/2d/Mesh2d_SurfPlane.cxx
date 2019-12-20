#include <Mesh2d_SurfPlane.hxx>

#include <Cad2d_Plane.hxx>
#include <Mesh2d_PlnWire.hxx>
#include <Mesh2d_PlnCurve.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>

void AutLib::Mesh_SurfPlane<AutLib::Cad2d_Plane>::RetrieveWiresTo(wireList& theWires) const
{
	theWires.push_back(theOuter_);
	if (theInner_)
	{
		for (const auto& x : *theInner_)
		{
			theWires.push_back(x);
		}
	}
}


//- Static functions and operators

std::shared_ptr<AutLib::Mesh2d_PlnWire> 
AutLib::Mesh_SurfPlane<AutLib::Cad2d_Plane>::GetWire
(
	const Pln_Wire& theWire
)
{
	auto curves_ptr =
		std::make_shared<std::vector<std::shared_ptr<Mesh2d_PlnCurve>>>();
	auto& curves = *curves_ptr;
	curves.reserve(theWire.NbEdges());

	Standard_Integer K = 0;
	for (const auto& x : *theWire.Edges())
	{
		Debug_Null_Pointer(x);

		const auto& xCurve = x->Curve();
		Debug_Null_Pointer(xCurve);

		curves.push_back(std::make_shared<Mesh2d_PlnCurve>(*xCurve));
	}

	auto wire =
		std::make_shared<Mesh2d_PlnWire>(curves_ptr);

	return std::move(wire);
}

std::shared_ptr<AutLib::Mesh2d_SurfPlane> 
AutLib::Mesh_SurfPlane<AutLib::Cad2d_Plane>::MakePlane
(
	const std::shared_ptr<Cad2d_Plane>& thePlane
)
{
	if (NOT thePlane->OuterWire())
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid Face : has no outer wire" << endl
			<< abort(FatalError);
	}

	const auto& Outer = *thePlane->OuterWire();
	const auto& Inners = *thePlane->InnerWires();

	auto outer_wire =
		GetWire(Outer);

	std::shared_ptr<std::vector<std::shared_ptr<Mesh2d_PlnWire>>> inner_wires;
	if (thePlane->InnerWires())
	{
		inner_wires = std::make_shared<std::vector<std::shared_ptr<Mesh2d_PlnWire>>>();
		inner_wires->reserve(Inners.size());

		for (const auto& x : Inners)
		{
			Debug_Null_Pointer(x);

			auto wire = GetWire(*x);
			inner_wires->push_back(wire);
		}
	}

	auto plane =
		std::make_shared<Mesh2d_SurfPlane>(thePlane, outer_wire, inner_wires);
	return std::move(plane);
}
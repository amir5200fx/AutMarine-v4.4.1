#include <TopoMesh2d_PlaneBoundaries.hxx>

#include <Mesh2d_PlnWire.hxx>
#include <Mesh2d_PlnCurve.hxx>
#include <Entity2d_Chain.hxx>

std::vector<std::shared_ptr<AutLib::Aft2d_Edge>>
AutLib::DownCastBoundaryEdges(const std::vector<std::shared_ptr<AutLib::Aft2d_SegmentEdge>>& theEdges)
{
	std::vector<std::shared_ptr<Aft2d_Edge>> edges;
	edges.reserve(theEdges.size());

	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		edges.push_back(x);
	}
	return std::move(edges);
}

Standard_Boolean
AutLib::TopoMesh_PlaneBoundaries
<
	AutLib::Mesh2d_SurfPlane,
	AutLib::Mesh2d_SizeMap,
	AutLib::Aft2d_SegmentEdge, true, false
>::IsTopologyValid() const
{
	if (NOT IsDone())
	{
		FatalErrorIn("Standard_Boolean IsValidTopology() const") << endl
			<< "the algorithm has not been performed!" << endl
			<< abort(FatalError);
	}

	const auto& boundaries = base::Boundaries();
	for (const auto& x : boundaries)
	{
		Debug_Null_Pointer(x);

		if (x->Node0()->NbFrontEdges() NOT_EQUAL 2) return Standard_False;
		if (x->Node1()->NbFrontEdges() NOT_EQUAL 2) return Standard_False;
	}
	return Standard_True;
}

void AutLib::TopoMesh_PlaneBoundaries
<
	AutLib::Mesh2d_SurfPlane,
	AutLib::Mesh2d_SizeMap,
	AutLib::Aft2d_SegmentEdge, true, false
>::Perform
(
	const std::shared_ptr<Mesh_CurveInfo>& theInfo
)
{
	if (NOT base::Map())
	{
		FatalErrorIn("void TopoMesh_PlaneBoundaries<PlaneType, SizeMap, BndType, WireChar>::Peform()")
			<< "the size map has not been loaded"
			<< abort(FatalError);
	}

	if (NOT base::Plane())
	{
		FatalErrorIn("void TopoMesh_PlaneBoundaries<PlaneType, SizeMap, BndType, WireChar>::Peform()")
			<< "the plane has not been loaded"
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<Mesh2d_PlnWire>> wires;
	base::Plane()->RetrieveWiresTo(wires);

	if (wires.empty())
	{
		FatalErrorIn("void TopoMesh_PlaneBoundaries<PlaneType, SizeMap, WireChar>::Peform()")
			<< "Invalid Plane: has no wire"
			<< abort(FatalError);
	}

	auto& boundaries = base::ChangeBoundaries();
	Standard_Integer Ke = 0;
	Standard_Integer Kn = 0;
	for (const auto& wire : wires)
	{
		Debug_Null_Pointer(wire);

		std::vector<std::shared_ptr<Aft2d_SegmentEdge>> Medges;

		const auto& curves = wire->Curves();
		for (const auto& x : curves)
		{
			Debug_Null_Pointer(x);

			auto mesh = 
				Mesh2d_PlnCurve::TopoMesh<Mesh2d_SizeMap, Aft2d_SegmentEdge>
				(
					x, base::Map(), 
					theInfo);

			for (const auto& edge : mesh)
			{
				Debug_Null_Pointer(edge);
				Medges.push_back(edge);
			}
		}

		for (auto& x : Medges)
		{
			Debug_Null_Pointer(x);
			x->SetIndex(++Ke);
		}

		Aft2d_SegmentEdge::MergeDangles(Medges, 1.0E-3);

		for (const auto& x : Medges)
		{
			Debug_Null_Pointer(x);
			boundaries.push_back(x);
		}

		for (auto& x : Medges)
		{
			Debug_Null_Pointer(x);
			auto& n0 = x->Node0();

			n0->SetIndex(++Kn);
		}
	}

	Aft2d_BndEdge::ActiveBoundaryEdges(Aft2d_SegmentEdge::UpCast(boundaries));

	Change_IsDone() = Standard_True;
}
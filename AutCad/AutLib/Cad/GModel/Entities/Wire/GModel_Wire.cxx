#include <GModel_Wire.hxx>

#include <GModel_parCurve.hxx>
#include <GModel_Edge.hxx>
#include <Entity2d_Box.hxx>

AutLib::Entity2d_Box
AutLib::GModel_Wire::CalcParametricBoundingBox() const
{
	Debug_Null_Pointer(theEdges_);

	const auto& edges = *theEdges_;

	if (edges.empty())
	{
		FatalErrorIn("Entity2d_Box CalcParametricBoundingBox() const")
			<< "the edge list is empty" << endl
			<< abort(FatalError);
	}

	auto box = edges[0]->Par()->BoundingBox();
	forThose(Index, 1, edges.size() - 1)
	{
		box = Entity2d_Box::Union(edges[Index]->Par()->BoundingBox(), box);
	}
	return std::move(box);
}

std::shared_ptr<AutLib::GModel_Wire> 
AutLib::GModel_Wire::ReParameterization
(
	const GModel_Wire & theWire, 
	const gp_Trsf2d & trans
)
{
	auto edges = std::make_shared<std::vector<std::shared_ptr<GModel_Edge>>>();
	edges->reserve(theWire.NbEdges());

	Debug_Null_Pointer(theWire.Edges());
	const auto& old = *theWire.Edges();
	for (const auto& x : old)
	{
		Debug_Null_Pointer(x);
		edges->push_back(GModel_Edge::ReParameterization(*x, trans));
	}

	auto wire = std::make_shared<GModel_Wire>(edges);
	return std::move(wire);
}

std::shared_ptr<AutLib::GModel_Wire> 
AutLib::GModel_Wire::BSplinePlaneEdges
(
	const GModel_Wire & theWire
)
{
	auto edges = std::make_shared<std::vector<std::shared_ptr<GModel_Edge>>>();
	edges->reserve(theWire.NbEdges());

	Debug_Null_Pointer(theWire.Edges());
	const auto& old = *theWire.Edges();
	for (const auto& x : old)
	{
		Debug_Null_Pointer(x);
		edges->push_back(GModel_Edge::BSplinePlaneEdge(x));
	}

	auto wire = std::make_shared<GModel_Wire>(edges);
	return std::move(wire);
}

std::shared_ptr<AutLib::GModel_Wire> 
AutLib::GModel_Wire::uPlaneExpand
(
	const GModel_Wire & theWire,
	const Standard_Real multiply
)
{
	auto edges = std::make_shared<std::vector<std::shared_ptr<GModel_Edge>>>();
	edges->reserve(theWire.NbEdges());

	Debug_Null_Pointer(theWire.Edges());
	const auto& old = *theWire.Edges();
	for (const auto& x : old)
	{
		Debug_Null_Pointer(x);
		edges->push_back(GModel_Edge::uPlaneExpand(*x, multiply));
	}

	auto wire = std::make_shared<GModel_Wire>(edges);
	return std::move(wire);
}

std::shared_ptr<AutLib::GModel_Wire>
AutLib::GModel_Wire::vPlaneExpand
(
	const GModel_Wire & theWire,
	const Standard_Real multiply
)
{
	auto edges = std::make_shared<std::vector<std::shared_ptr<GModel_Edge>>>();
	edges->reserve(theWire.NbEdges());

	Debug_Null_Pointer(theWire.Edges());
	const auto& old = *theWire.Edges();
	for (const auto& x : old)
	{
		Debug_Null_Pointer(x);
		edges->push_back(GModel_Edge::vPlaneExpand(*x, multiply));
	}

	auto wire = std::make_shared<GModel_Wire>(edges);
	return std::move(wire);
}
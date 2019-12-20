#include <Pln_Vertex.hxx>

#include <Pln_Ring.hxx>

void AutLib::Pln_Vertex::SetComparableFunction()
{
	theEdges_.SetComparableFunction(&Pln_Edge::IsLess);
}

Standard_Integer 
AutLib::Pln_Vertex::NbRings() const
{
	std::vector<std::weak_ptr<Pln_Edge>> edges;
	RetrieveEdgesTo(edges);

	Standard_Integer K = 0;
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x.lock());

		auto edge = x.lock();
		if (edge->IsRing()) ++K;
	}
	return K;
}

Standard_Boolean AutLib::Pln_Vertex::IsManifold() const
{
	if (NOT NbEdges())
		return Standard_False;
	else if (NbEdges() IS_EQUAL 1)
	{
		if (HasRing()) return Standard_True;
		else return Standard_False;
	}
	else if (NbEdges() IS_EQUAL 2)
	{
		if (HasRing()) return Standard_False;
		else return Standard_True;
	}
	return Standard_False;
}

Standard_Boolean AutLib::Pln_Vertex::HasRing() const
{
	std::vector<std::weak_ptr<Pln_Edge>> edges;
	RetrieveEdgesTo(edges);

	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x.lock());

		auto edge = x.lock();
		if (edge->IsRing()) return Standard_True;
	}
	return Standard_False;
}
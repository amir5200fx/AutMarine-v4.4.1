#pragma once
#include <error.hxx>
#include <OSstream.hxx>
namespace AutLib
{

	template<class BndEdgeTraits>
	void Aft_BndEdge<BndEdgeTraits>::ActiveBoundaryEdges
	(
		const std::vector<std::shared_ptr<typename BndEdgeTraits::edgeType>>& theEdges
	)
	{
		for (const auto& x : theEdges)
		{
			Debug_Null_Pointer(x);
			const auto n0 = std::dynamic_pointer_cast<typename Aft_BndEdge::bndNodeType>(x->Node0());
			const auto n1 = std::dynamic_pointer_cast<typename Aft_BndEdge::bndNodeType>(x->Node1());

			auto edge = std::dynamic_pointer_cast<Aft_BndEdge>(x);
			Debug_Null_Pointer(edge);

			n0->InsertToBoundaryEdges(x->Index(), edge);
			n1->InsertToBoundaryEdges(x->Index(), edge);
		}
	}

	template<class BndEdgeTraits>
	std::vector<std::shared_ptr<typename BndEdgeTraits::edgeType>> 
		Aft_BndEdge<BndEdgeTraits>::UpCast
		(
			const std::vector<std::shared_ptr<Aft_BndEdge>>& theEdges
		)
	{
		std::vector<std::shared_ptr<typename BndEdgeTraits::edgeType>> edges;
		edges.reserve(theEdges.size());

		for (const auto& x : theEdges)
		{
			Debug_Null_Pointer(x);
			edges.push_back(x);
		}
		return std::move(edges);
	}
}
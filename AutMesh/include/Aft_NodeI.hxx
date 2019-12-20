#pragma once
namespace AutLib
{

	template<class NodeTraits, class NodeIdentifier>
	std::vector<typename Aft_Node<NodeTraits, NodeIdentifier>::Point> 
		Aft_Node<NodeTraits, NodeIdentifier>::RetrieveGeometry
	(
		const std::vector<std::shared_ptr<aftNode>>& theNodes
	)
	{
		std::vector<Point> Pts;
		Pts.reserve(theNodes.size());
		for (const auto& x : theNodes)
		{
			Pts.push_back(x->Coord());
		}
		return std::move(Pts);
	}
}
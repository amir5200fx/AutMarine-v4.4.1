#pragma once
#include <Merge_StaticData.hxx>
namespace AutLib
{

	template<class NodeType>
	inline typename Knit_Chain<NodeType>::node_ptr 
		Knit_Chain<NodeType>::Next
		(
			const node_ptr & theNode
		)
	{
		if (theNode->Type() NOT_EQUAL Knit_ChainNodeType_REGULAR)
		{
			if (NOT theNode->NbEdges())
			{
				base::RemoveFromKnit_ChainNodes(theNode);		
			}
			return nullptr;
		}

		std::vector<std::weak_ptr<edge>> edges;
		theNode->RetrieveEdgesTo(edges);

		auto Edge = edges[0].lock();
		Debug_Null_Pointer(Edge);

		theNode->RemoveFromEdges(edges[0]);
		base::RemoveFromKnit_ChainEdges(Edge);

		const auto& left = Edge->Node0();
		const auto& right = Edge->Node1();

		std::shared_ptr<NodeType> next;
		if (left IS_EQUAL theNode) next = right;
		else if (right IS_EQUAL theNode) next = left;
		else
		{
			FatalErrorIn("node_ptr Next(const node_ptr& theNode)")
				<< "Unable to find the next node" << endl
				<< abort(FatalError);
		}
		
		if (edges.size() IS_EQUAL 1)
		{
			base::RemoveFromKnit_ChainNodes(theNode);
		}
		else
		{
			theNode->Type() = Knit_ChainNodeType_START;
		}

		next->RemoveFromEdges(Edge);
		return std::move(next);
	}

	template<class NodeType>
	inline typename Knit_Chain<NodeType>::node_ptr 
		Knit_Chain<NodeType>::FindStart
		(
			const Knit_ChainNodeType type
		) const
	{
		std::vector<node_ptr> nodes;
		base::RetrieveKnit_ChainNodesTo(nodes);

		for (const auto& x : nodes)
		{
			Debug_Null_Pointer(x);

			if (x->Type() IS_EQUAL type)
			{
				x->Type() = Knit_ChainNodeType_START;
				return x;
			}
		}
		return nullptr;
	}

	template<class NodeType>
	inline std::shared_ptr<Entity_Polygon<typename NodeType::ptType>> 
		Knit_Chain<NodeType>::GetPolygon
		(
			const node_ptr & theStart
		)
	{
		theStart->Type() = Knit_ChainNodeType_REGULAR;

		auto poly = std::make_shared<polygon>();
		Debug_Null_Pointer(poly);

		auto& Pts = poly->Points();

		Pts.push_back(theStart->Coord());
		auto next = Next(theStart);
		
		while (next)
		{
			Pts.push_back(next->Coord());
			next = Next(next);
		}

		return std::move(poly);
	}

	template<class NodeType>
	inline void Knit_Chain<NodeType>::SetTypes()
	{
		std::vector<node_ptr> nodes;
		base::RetrieveKnit_ChainNodesTo(nodes);

		for (const auto& x : nodes)
		{
			Debug_Null_Pointer(x);

			if (x->NbEdges() IS_EQUAL 1)
			{
				// start node
				x->Type() = Knit_ChainNodeType_START;
			}
			else
			{
				// regular node
				x->Type() = Knit_ChainNodeType_REGULAR;
			}
		}
	}

	template<class NodeType>
	inline void Knit_Chain<NodeType>::Perform()
	{
		// Create regular chains
		auto start = FindStart(Knit_ChainNodeType_START);
		while (start)
		{
			thePolygons_.push_back(GetPolygon(start));
			start = FindStart(Knit_ChainNodeType_START);
		}

		// Create cycle chain
		if (base::NbKnit_ChainEdges())
		{
			start = FindStart(Knit_ChainNodeType_REGULAR);
			while (start)
			{
				thePolygons_.push_back(GetPolygon(start));
				start = FindStart(Knit_ChainNodeType_REGULAR);
			}
		}

		if (base::NbKnit_ChainNodes())
		{
			FatalErrorIn("void Perform()")
				<< "The Nodes tree is not empty" << endl
				<< abort(FatalError);
		}

		if (base::NbKnit_ChainEdges())
		{
			FatalErrorIn("void Perform()")
				<< "The Edges tree is not empty" << endl
				<< abort(FatalError);
		}

		base::Change_IsDone() = Standard_True;
	}

	template<class NodeType>
	inline void Knit_Chain<NodeType>::Import
	(
		const Entity_StaticData<Point, connectivity::dual>& theChain
	)
	{
		/*Merge_StaticData<Entity_StaticData<Point, connectivity::dual>, Merge_PntAlg_Mean>
			merge;
		merge.Import(theChain);
		merge.Perform();
		
		Debug_If_Condition_Message(NOT merge.IsDone(), "Merging is not performed");

		const auto& merged = merge.Merged();
		Debug_Null_Pointer(merged);*/

		const auto& points = theChain.Points();
		const auto& indices = theChain.Connectivity();

		std::vector<node_ptr> nodes;
		nodes.reserve(points.size());

		Standard_Integer K = 0;
		for (const auto& x : points)
		{
			auto n = std::make_shared<NodeType>(++K, x);
			nodes.push_back(n);
			base::InsertToKnit_ChainNodes(n);
		}

		K = 0;
		for (const auto& x : indices)
		{
			auto v0 = x.Value(0);
			auto v1 = x.Value(1);

			auto e = std::make_shared<edge>(++K, nodes[Index_Of(v0)], nodes[Index_Of(v1)]);

			base::InsertToKnit_ChainEdges(e);

			nodes[Index_Of(v0)]->InsertToEdges(e);
			nodes[Index_Of(v1)]->InsertToEdges(e);
		}

		SetTypes();
	}
}
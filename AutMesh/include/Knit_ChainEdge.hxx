#pragma once
#ifndef _Knit_ChainEdge_Header
#define _Knit_ChainEdge_Header

#include <Mesh_Edge.hxx>
#include <Knit_ChainEdgeAdaptor.hxx>

namespace AutLib
{

	template<class NodeType, class FacetType = void>
	class Knit_ChainEdge
		: public Mesh_Edge<NodeType>
		, public Knit_ChainEdgeAdaptor<FacetType>
	{

		typedef std::shared_ptr<NodeType> node_ptr;
		typedef std::shared_ptr<Knit_ChainEdge<NodeType, FacetType>> edge_ptr;
		typedef std::weak_ptr<Knit_ChainEdge<NodeType, FacetType>> edge_weak;

		/*Private Data*/

	public:

		typedef NodeType nodeType;

		Knit_ChainEdge()
		{}

		Knit_ChainEdge
		(
			const Standard_Integer theIndex
		)
		{}

		Knit_ChainEdge
		(
			const Standard_Integer theIndex,
			const node_ptr& theNode0,
			const node_ptr& theNode1
		)
			: Mesh_Edge<NodeType>(theIndex, theNode0, theNode1)
		{}

		static Standard_Boolean IsLess
		(
			const edge_ptr& theEdge0, 
			const edge_ptr& theEdge1
		)
		{
			Debug_Null_Pointer(theEdge0);
			Debug_Null_Pointer(theEdge1);

			return theEdge0->Index() < theEdge1->Index();
		}

		static Standard_Boolean IsLess
		(
			const edge_weak& theEdge0,
			const edge_weak& theEdge1
		)
		{
			Debug_Null_Pointer(theEdge0.lock());
			Debug_Null_Pointer(theEdge1.lock());

			return theEdge0.lock()->Index() < theEdge1.lock()->Index();
		}
	};


	template<class NodeType>
	class Knit_ChainEdge<NodeType, void>
		: public Mesh_Edge<NodeType>
	{

		typedef std::shared_ptr<NodeType> node_ptr;
		typedef std::shared_ptr<Knit_ChainEdge<NodeType, void>> edge_ptr;
		typedef std::weak_ptr<Knit_ChainEdge<NodeType, void>> edge_weak;

		/*Private Data*/

	public:

		Knit_ChainEdge()
		{}

		Knit_ChainEdge
		(
			const Standard_Integer theIndex
		)
		{}

		Knit_ChainEdge
		(
			const Standard_Integer theIndex,
			const node_ptr& theNode0,
			const node_ptr& theNode1
		)
			: Mesh_Edge<NodeType>(theIndex, theNode0, theNode1)
		{}

		static Standard_Boolean IsLess
		(
			const edge_ptr& theEdge0,
			const edge_ptr& theEdge1
		)
		{
			Debug_Null_Pointer(theEdge0);
			Debug_Null_Pointer(theEdge1);

			return theEdge0->Index() < theEdge1->Index();
		}

		static Standard_Boolean IsLess
		(
			const edge_weak& theEdge0,
			const edge_weak& theEdge1
		)
		{
			Debug_Null_Pointer(theEdge0.lock());
			Debug_Null_Pointer(theEdge1.lock());

			return theEdge0.lock()->Index() < theEdge1.lock()->Index();
		}
	};
}

#endif // !_Knit_ChainEdge_Header

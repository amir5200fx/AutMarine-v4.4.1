#pragma once
#ifndef _Aft_Node_Header
#define _Aft_Node_Header

#include <Mesh_TypeTraits.hxx>
#include <Mesh_Node.hxx>
#include <Aft_NodeIdentifier.hxx>
#include <Aft_NodeAdaptor.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{

	// Forward Declarations
	template<class EdgeType, class ElementType, class FacetType = void>
	class Aft_NodeAdaptor;

	template
		<
		class NodeTraits,
		class NodeIdentifier
		>
	class Aft_Node
		: public Mesh_Node<typename NodeTraits::ptType>
		, public NodeIdentifier
		, public Aft_NodeAdaptor
		<
		typename NodeTraits::edgeType,
		typename NodeTraits::elementType, 
		typename NodeTraits::facetType
		>
	{

		typedef typename NodeTraits::ptType Point;
		typedef typename NodeTraits::edgeType edgeType;
		typedef typename NodeTraits::elementType elementType;
		typedef typename NodeTraits::facetType facetType;
		typedef Aft_NodeAdaptor<edgeType, elementType, facetType> nodeAdaptor;

		typedef Aft_Node<NodeTraits, NodeIdentifier> aftNode;

		/*template< bool cond, typename U >
		using resolvedType = typename std::enable_if< cond, U >::type;*/

		/*Private Data*/

	public:

		enum Merge_Alg
		{
			Merge_Alg_New = 0,
			Merge_Alg_FirstPreferred,
			Merge_Alg_SecondPreferred
		};

		typedef Pnt2d ptType;

		static const std::shared_ptr<Aft_Node> null_ptr;

		Aft_Node()
		{}

		Aft_Node
		(
			const Standard_Integer theIndex
		)
			: Mesh_Node<Point>(theIndex)
		{}

		Aft_Node
		(
			const Standard_Integer theIndex,
			const Point& theCoord
		)
			: Mesh_Node<Point>(theIndex, theCoord)
		{}		

		//- Static functions and operators

		static const Point& GetCoord(const std::shared_ptr<aftNode>& theNode)
		{
			Debug_Null_Pointer(theNode);
			return theNode->Coord();
		}

		static const Point& GetCoord(const std::weak_ptr<aftNode>& theNode)
		{
			const auto node = theNode.lock();
			Debug_Null_Pointer(node);

			return node->Coord();
		}

		static Standard_Boolean IsLess
		(
			const std::shared_ptr<Aft_Node>& theNode0,
			const std::shared_ptr<Aft_Node>& theNode1
		)
		{
			Debug_Null_Pointer(theNode0);
			Debug_Null_Pointer(theNode1);
			return theNode0->Index() < theNode1->Index();
		}

		static std::vector<Point> 
			RetrieveGeometry
			(
				const std::vector<std::shared_ptr<aftNode>>& theNodes
			);
	};
}

#include <Aft_NodeI.hxx>

#endif // !_Aft_Node_Header

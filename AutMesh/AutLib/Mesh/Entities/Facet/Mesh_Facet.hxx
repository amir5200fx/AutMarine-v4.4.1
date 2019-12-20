#pragma once
#ifndef _Mesh_Facet_Header
#define _Mesh_Facet_Header

#include <Mesh_Entity.hxx>
#include <Entity_Connectivity.hxx>
#include <Mesh_TypeTraits.hxx>

#include <memory>
#include <array>

namespace AutLib
{

	template
		<
		class FacetTraits,
		class FacetAdaptor
		>
	class Mesh_Facet
		: public Mesh_Entity
		, public FacetAdaptor
	{

	public:

		typedef typename FacetTraits::nodeType nodeType;
		typedef typename FacetTraits::edgeType edgeType;

		typedef typename FacetTraits::ptType Point;

		typedef std::shared_ptr<nodeType> nodePtr;
		typedef std::shared_ptr<edgeType> edgePtr;

	private:

		template< bool cond, typename U >
		using resolvedType = typename std::enable_if< cond, U >::type;

		typedef std::array<Standard_Real, 3>
			array3;

		/*Private Data*/

		nodePtr theNodes_[3];
		edgePtr theEdges_[3];

	public:

		/*typedef nodeType nodeType;
		typedef edgeType edgeType;*/

		typedef connectivity::triple connectType;

		enum
		{
			rank = 2,
			hierarchy = 0
		};

		Mesh_Facet()
		{}

		Mesh_Facet(const Standard_Integer theIndex)
			: Mesh_Entity(theIndex)
		{}

		Mesh_Facet
		(
			const Standard_Integer theIndex, 
			const nodePtr& theNode0,
			const nodePtr& theNode1,
			const nodePtr& theNode2
		)
			: Mesh_Entity(theIndex)
		{
			Node0() = theNode0;
			Node1() = theNode1;
			Node2() = theNode2;
		}

		const nodePtr& Node(const Standard_Integer theIndex) const
		{
			return theNodes_[theIndex];
		}

		nodePtr& Node(const Standard_Integer theIndex)
		{
			return theNodes_[theIndex];
		}

		const edgePtr& Edge(const Standard_Integer theIndex) const
		{
			return theEdges_[theIndex];
		}

		edgePtr& Edge(const Standard_Integer theIndex)
		{
			return theEdges_[theIndex];
		}

		const nodePtr& Node0() const
		{
			return theNodes_[0];
		}

		nodePtr& Node0()
		{
			return theNodes_[0];
		}

		const nodePtr& Node1() const
		{
			return theNodes_[1];
		}

		nodePtr& Node1()
		{
			return theNodes_[1];
		}

		const nodePtr& Node2() const
		{
			return theNodes_[2];
		}

		nodePtr& Node2()
		{
			return theNodes_[2];
		}

		const edgePtr& Edge0() const
		{
			return theEdges_[0];
		}

		edgePtr& Edge0()
		{
			return theEdges_[0];
		}

		const edgePtr& Edge1() const
		{
			return theEdges_[1];
		}

		edgePtr& Edge1()
		{
			return theEdges_[1];
		}

		const edgePtr& Edge2() const
		{
			return theEdges_[2];
		}

		edgePtr& Edge2()
		{
			return theEdges_[2];
		}

		Point Centre() const
		{
			Point pt = (Node0()->Coord() + Node1()->Coord() + Node2()->Coord()) / (Standard_Real)3.0;
			return std::move(pt);
		}

		template<int Sub>
		const std::shared_ptr<typename sub_type<Mesh_Facet, Sub>::type>& SubEntity
		(
			const Standard_Integer theIndex
		) const;

		template<>
		const std::shared_ptr<typename sub_type<Mesh_Facet, 0>::type>& SubEntity<0>
			(
				const Standard_Integer theIndex
				) const
		{
			return Node(theIndex);
		}

		template<>
		const std::shared_ptr<typename sub_type<Mesh_Facet, 1>::type>& SubEntity<1>
			(
				const Standard_Integer theIndex
				) const
		{
			return Edge(theIndex);
		}

		template<class U = array3>
		resolvedType<is_two_dimension<(int)Point::dim>::value, U> InterpWeights(const Point& theCoord) const;

		void SetNode(const Standard_Integer theIndex, const nodePtr& theNode)
		{
			theNodes_[theIndex] = theNode;
		}

		void SetEdge(const Standard_Integer theIndex, const edgePtr& theEdge)
		{
			theEdges_[theIndex] = theEdge;
		}

		static Standard_Boolean 
			IsLess
			(
				const std::shared_ptr<Mesh_Facet>& theF0,
				const std::shared_ptr<Mesh_Facet>& theF1
			)
		{
			Debug_Null_Pointer(theF0);
			Debug_Null_Pointer(theF1);

			return theF0->Index() < theF1->Index();
		}
	};
}

#endif // !_Mesh_Facet_Header

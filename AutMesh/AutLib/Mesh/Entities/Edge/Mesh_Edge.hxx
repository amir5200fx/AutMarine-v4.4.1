#pragma once
#ifndef _Mesh_Edge_Header
#define _Mesh_Edge_Header

#include <Mesh_Entity.hxx>
#include <Traits.hxx>

#include <memory>

namespace AutLib
{

	template<class NodeType>
	class Mesh_Edge
		: public Mesh_Entity
	{

	public:

		typedef std::shared_ptr<NodeType> node_ptr;
		typedef std::shared_ptr<Mesh_Edge> edge_ptr;
		typedef typename NodeType::ptType Point;

		template< bool cond, typename U >
		using resolvedType = typename std::enable_if< cond, U >::type;


	private:

		/*Private Data*/

		node_ptr theNodes_[2];

	public:

		enum
		{
			rank = 1,
			hierarchy = 0
		};

		Mesh_Edge()
		{}

		Mesh_Edge(const Standard_Integer theIndex)
			: Mesh_Entity(theIndex)
		{}

		Mesh_Edge
		(
			const Standard_Integer theIndex,
			const node_ptr& theNode0,
			const node_ptr& theNode1
		)
			: Mesh_Entity(theIndex)
		{
			theNodes_[0] = theNode0;
			theNodes_[1] = theNode1;
		}

		const node_ptr& Node0() const
		{
			return theNodes_[0];
		}

		node_ptr& Node0()
		{
			return theNodes_[0];
		}

		const node_ptr& Node1() const
		{
			return theNodes_[1];
		}

		node_ptr& Node1()
		{
			return theNodes_[1];
		}

		const node_ptr& Node(const Standard_Integer theIndex) const
		{
			return theNodes_[theIndex];
		}

		node_ptr& Node(const Standard_Integer theIndex)
		{
			return theNodes_[theIndex];
		}

		void SetNode(const Standard_Integer theIndex, const node_ptr& theNode)
		{
			theNodes_[theIndex] = theNode;
		}

		void SetNode0(const node_ptr& theNode)
		{
			theNodes_[0] = theNode;
		}

		void SetNode1(const node_ptr& theNode)
		{
			theNodes_[1] = theNode;
		}

		template<class U = Standard_Boolean>
		resolvedType<is_two_dimension<(int)Point::dim>::value, U> 
			IsRightSide
			(
				const Point& theCoord
			) const;

		template<class U = Standard_Boolean>
		resolvedType<is_two_dimension<(int)Point::dim>::value, U>
			IsLeftSide
			(
				const Point& theCoord
			) const;
	};
}

#endif // !_Mesh_Edge_Header
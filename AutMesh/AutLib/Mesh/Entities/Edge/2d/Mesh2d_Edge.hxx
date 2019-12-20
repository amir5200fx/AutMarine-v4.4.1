#pragma once
#ifndef _Mesh2d_Edge_Header
#define _Mesh2d_Edge_Header

#include <Mesh2d_Node.hxx>
#include <Mesh_Edge.hxx>
#include <Mesh_EdgeAdaptor.hxx>
#include <Mesh2d_ElementFwd.hxx>

namespace AutLib
{

	// Forward Declarations
	class Mesh2d_Node;

	typedef Mesh_Edge<Mesh2d_Node> Mesh_EdgeBase;

	template<>
	template<>
	Standard_Boolean Mesh_EdgeBase::IsRightSide<Standard_Boolean>
	(
		const Pnt2d& theCoord
	) const;

	template<>
	template<>
	Standard_Boolean Mesh_EdgeBase::IsLeftSide<Standard_Boolean>
		(
			const Pnt2d& theCoord
			) const;

	class Mesh2d_Edge
		: public Mesh_Edge<Mesh2d_Node>
		, public Mesh_EdgeAdaptor<Mesh2d_Element>
	{

		typedef std::shared_ptr<Mesh2d_Node> node_ptr;
		typedef std::shared_ptr<Mesh2d_Edge> edge_ptr;

		/*Private Data*/

	public:

		typedef Mesh2d_Node nodeType;

		Mesh2d_Edge()
		{}

		Mesh2d_Edge(const Standard_Integer theIndex)
			: Mesh_Edge<Mesh2d_Node>(theIndex)
		{}

		Mesh2d_Edge
		(
			const Standard_Integer theIndex,
			const node_ptr& theNode0,
			const node_ptr& theNode1
		)
			: Mesh_Edge<Mesh2d_Node>(theIndex, theNode0, theNode1)
		{}

		virtual ~Mesh2d_Edge()
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
			const std::weak_ptr<Mesh2d_Edge>& theEdge0,
			const std::weak_ptr<Mesh2d_Edge>& theEdge1
		)
		{
			Debug_Null_Pointer(theEdge0.lock());
			Debug_Null_Pointer(theEdge1.lock());
			return theEdge0.lock()->Index() < theEdge1.lock()->Index();
		}
	};
}

#endif // !_Mesh2d_Edge_Header
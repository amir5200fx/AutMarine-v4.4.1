#pragma once
#ifndef _Mesh3d_Edge_Header
#define _Mesh3d_Edge_Header

#include <Mesh_Edge.hxx>
#include <Mesh_EdgeAdaptor.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{

	// Forward Declarations
	class Mesh3d_Node;
	class Mesh3d_Element;
	class Mesh3d_Facet;

	class Mesh3d_Edge
		: public Mesh_Edge<Mesh3d_Node>
		, public Mesh_EdgeAdaptor<Mesh3d_Element, Mesh3d_Facet>
	{

		/*Private Data*/

	public:

		typedef Mesh3d_Node nodeType;
		typedef Mesh3d_Element elementType;
		typedef Mesh3d_Facet facetType;

		Mesh3d_Edge()
		{}

		Mesh3d_Edge(const Standard_Integer theIndex)
			: Mesh_Edge<Mesh3d_Node>(theIndex)
		{}

		Mesh3d_Edge
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<nodeType>& theNode0, 
			const std::shared_ptr<nodeType>& theNode1
		)
			: Mesh_Edge<Mesh3d_Node>(theIndex, theNode0, theNode1)
		{}

		static Standard_Boolean IsLess
		(
			const std::shared_ptr<Mesh3d_Edge>& theEdge0,
			const std::shared_ptr<Mesh3d_Edge>& theEdge1
		)
		{
			Debug_Null_Pointer(theEdge0);
			Debug_Null_Pointer(theEdge1);
			return theEdge0->Index() < theEdge1->Index();
		}

		static Standard_Boolean IsLess
		(
			const std::weak_ptr<Mesh3d_Edge>& theEdge0,
			const std::weak_ptr<Mesh3d_Edge>& theEdge1
		)
		{
			Debug_Null_Pointer(theEdge0.lock());
			Debug_Null_Pointer(theEdge1.lock());
			return theEdge0.lock()->Index() < theEdge1.lock()->Index();
		}
	};
}

#endif // !_Mesh3d_Edge_Header

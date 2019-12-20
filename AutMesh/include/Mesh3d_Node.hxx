#pragma once
#ifndef _Mesh3d_Node_Header
#define _Mesh3d_Node_Header

#include <Pnt3d.hxx>
#include <Mesh_Node.hxx>
#include <Mesh_NodeAdaptor.hxx>
#include <error.hxx>
#include <OSstream.hxx>


namespace AutLib
{

	// Forward Declarations
	class Mesh3d_Edge;
	class Mesh3d_Facet;
	class Mesh3d_Element;

	class Mesh3d_Node
		: public Mesh_Node<Pnt3d>
		, public Mesh_NodeAdaptor<Mesh3d_Edge, Mesh3d_Element, Mesh3d_Facet>
	{

		/*Private Data*/

	public:

		typedef Pnt3d ptType;

		Mesh3d_Node()
		{}

		Mesh3d_Node(const Standard_Integer theIndex)
			: Mesh_Node<Pnt3d>(theIndex)
		{}

		Mesh3d_Node
		(
			const Standard_Integer theIndex, 
			const Pnt3d& theCoord
		)
			: Mesh_Node<Pnt3d>(theIndex, theCoord)
		{}

		static Standard_Boolean IsLess
		(
			const std::shared_ptr<Mesh3d_Node>& theNode0,
			const std::shared_ptr<Mesh3d_Node>& theNode1
		)
		{
			Debug_Null_Pointer(theNode0);
			Debug_Null_Pointer(theNode1);

			return theNode0->Index() < theNode1->Index();
		}
	};
}

#endif // !_Mesh3d_Node_Header

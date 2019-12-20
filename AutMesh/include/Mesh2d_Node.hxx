#pragma once
#ifndef _Mesh2d_Node_Header
#define _Mesh2d_Node_Header

#include <Pnt2d.hxx>
#include <Mesh_Node.hxx>
#include <Mesh_NodeAdaptor.hxx>
#include <Mesh2d_ElementFwd.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{

	// Forward Declarations
	class Mesh2d_Edge;

	class Mesh2d_Node
		: public Mesh_Node<Pnt2d>
		, public Mesh_NodeAdaptor<Mesh2d_Edge, Mesh2d_Element>
	{

		/*Private Data*/

	public:

		Mesh2d_Node()
		{}

		Mesh2d_Node(const Standard_Integer theIndex)
			: Mesh_Node<Pnt2d>(theIndex)
		{}

		Mesh2d_Node
		(
			const Standard_Integer theIndex,
			const Pnt2d& theCoord
		)
			: Mesh_Node<Pnt2d>(theIndex, theCoord)
		{}

		static Standard_Boolean IsLess
		(
			const std::shared_ptr<Mesh2d_Node>& theNode0,
			const std::shared_ptr<Mesh2d_Node>& theNode1
		)
		{
			Debug_Null_Pointer(theNode0);
			Debug_Null_Pointer(theNode1);

			return theNode0->Index() < theNode1->Index();
		}
	};
}

#endif // !_Mesh2d_Node_Header

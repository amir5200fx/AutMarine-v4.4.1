#pragma once
#ifndef _Mesh3d_Element_Header
#define _Mesh3d_Element_Header

#include <Mesh_Element.hxx>
#include <Mesh_ElementAdaptor.hxx>

namespace AutLib
{

	// Forward Declarations
	class Mesh3d_Node;
	class Mesh3d_Edge;
	class Mesh3d_Facet;

	class Mesh3d_Element
		: public Mesh_Element<Mesh3d_Node, Mesh3d_Edge, Mesh_ElementAdaptor<Mesh3d_Element, 4>, Mesh3d_Facet>
	{

		/*Private Data*/

	public:

		typedef Mesh3d_Node nodeType;
		typedef Mesh3d_Edge edgeType;
		typedef Mesh3d_Facet facetType;

		Mesh3d_Element()
		{}

		Mesh3d_Element(const Standard_Integer theIndex)
			: Mesh_Element<Mesh3d_Node, Mesh3d_Edge, Mesh_ElementAdaptor<Mesh3d_Element, 4>, Mesh3d_Facet>(theIndex)
		{}

		Mesh3d_Element(const Standard_Integer theIndex)
			: Mesh_Element<Mesh3d_Node, Mesh3d_Edge, Mesh_ElementAdaptor<Mesh3d_Element, 4>, Mesh3d_Facet>(theIndex)
		{}

		Mesh3d_Element
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<nodeType>& theNode0,
			const std::shared_ptr<nodeType>& theNode1,
			const std::shared_ptr<nodeType>& theNode2,
			const std::shared_ptr<nodeType>& theNode3
		)
			: Mesh_Element<Mesh3d_Node, Mesh3d_Edge, Mesh_ElementAdaptor<Mesh3d_Element, 4>, Mesh3d_Facet>
			(
				theIndex,
				theNode0, 
				theNode1,
				theNode2, 
				theNode3
				)
		{}
	};
}

#endif // !_Mesh_Element_Header

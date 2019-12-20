#pragma once
#ifndef _Knit2d_ChainDirectedNode_Header
#define _Knit2d_ChainDirectedNode_Header

#include <Pnt2d.hxx>
#include <Knit_ChainNode.hxx>
#include <Knit_ChainNodeAdaptor.hxx>
#include <Mesh2d_ElementFwd.hxx>

namespace AutLib
{

	// Forward Declarations

	template<class NodeType, class FacetType>
	class Knit_ChainEdge;

	class Knit2d_ChainDirectedNode
		: public Knit_ChainNode<Pnt2d>
		, public Knit_ChainNodeAdaptor<Knit_ChainEdge<Knit2d_ChainDirectedNode, Mesh2d_Element>>
	{

		typedef std::shared_ptr<Knit2d_ChainDirectedNode> node_ptr;

		/*Private Data*/

	public:

		typedef Mesh2d_Element facetInfo;

		Knit2d_ChainDirectedNode()
		{}

		Knit2d_ChainDirectedNode
		(
			const Standard_Integer theIndex
		)
			: Knit_ChainNode<Pnt2d>(theIndex)
		{}

		Knit2d_ChainDirectedNode
		(
			const Standard_Integer theIndex,
			const Pnt2d& theCoord
		)
			: Knit_ChainNode<Pnt2d>(theIndex, theCoord)
		{}

		static Standard_Boolean IsLess
		(
			const node_ptr& theNode0,
			const node_ptr& theNode1
		)
		{
			Debug_Null_Pointer(theNode0);
			Debug_Null_Pointer(theNode1);

			return theNode0->Index() < theNode1->Index();
		}

	};
}

#endif // !_Knit2d_ChainDirectedNode_Header

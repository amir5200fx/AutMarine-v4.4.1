#pragma once
#ifndef _Knit2d_ChainNode_Header
#define _Knit2d_ChainNode_Header

#include <Pnt2d.hxx>
#include <Knit_ChainNode.hxx>
#include <Knit_ChainNodeAdaptor.hxx>

namespace AutLib
{

	// Forward Declarations
	template<class NodeType, class FacetType>
	class Knit_ChainEdge;

	class Knit2d_ChainNode
		: public Knit_ChainNode<Pnt2d>
		, public Knit_ChainNodeAdaptor<Knit_ChainEdge<Knit2d_ChainNode, void>>
	{

		/*Private Data*/

	public:

		typedef void facetInfo;
		typedef Pnt2d ptType;

		Knit2d_ChainNode()
		{}

		Knit2d_ChainNode
		(
			const Standard_Integer theIndex
		)
			: Knit_ChainNode<Pnt2d>(theIndex)
		{}

		Knit2d_ChainNode
		(
			const Standard_Integer theIndex, 
			const Pnt2d& theCoord
		)
			: Knit_ChainNode<Pnt2d>(theIndex, theCoord)
		{}

		std::shared_ptr<Knit2d_ChainNode> Copy() const
		{
			return std::make_shared<Knit2d_ChainNode>(Index(), Coord());
		}

		static Standard_Boolean IsLess
		(
			const std::shared_ptr<Knit2d_ChainNode>& n0,
			const std::shared_ptr<Knit2d_ChainNode>& n1
		)
		{
			Debug_Null_Pointer(n0);
			Debug_Null_Pointer(n1);

			return n0->Index() < n1->Index();
		}
	};
}

#endif // !_Knit2d_ChainNode_Header

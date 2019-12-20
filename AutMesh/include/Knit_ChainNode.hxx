#pragma once
#ifndef _Knit_ChainNode_Header
#define _Knit_ChainNode_Header

#include <Mesh_Node.hxx>

namespace AutLib
{

	enum Knit_ChainNodeType
	{
		Knit_ChainNodeType_START = 0,
		Knit_ChainNodeType_REGULAR,
		Knit_ChainNodeType_END
	};

	template<class Point>
	class Knit_ChainNode
		: public Mesh_Node<Point>
	{

		/*Private Data*/

		Knit_ChainNodeType theType_;

	public:

		Knit_ChainNode()
		{}

		Knit_ChainNode
		(
			const Standard_Integer theIndex
		)
			: Mesh_Node<Point>(theIndex)
		{}

		Knit_ChainNode
		(
			const Standard_Integer theIndex,
			const Point& theCoord
		)
			: Mesh_Node<Point>(theIndex, theCoord)
		{}

		Knit_ChainNodeType Type() const
		{
			return theType_;
		}

		Knit_ChainNodeType& Type()
		{
			return theType_;
		}
	};
}

#endif // !_Knit_ChainNode_Header

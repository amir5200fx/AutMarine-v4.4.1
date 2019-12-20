#pragma once
#ifndef _Aft2d_SegmentNodeFwd_Header
#define _Aft2d_SegmentNodeFwd_Header

#include <Mesh_BndNode_Position.hxx>

namespace AutLib
{

	// Forward Declarations
	template<class BndNodeTraits, Mesh_BndNode_Position POS>
	class Aft_TBndNode;

	struct Aft2d_SegmentNodeTraits;

	typedef Aft_TBndNode<Aft2d_SegmentNodeTraits, Mesh_BndNode_Position_Corner>
		Aft2d_SegmentNode;
}

#endif // !_Aft2d_SegmentNodeFwd_Header

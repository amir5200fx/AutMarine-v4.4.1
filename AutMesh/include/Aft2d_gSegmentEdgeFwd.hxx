#pragma once
#ifndef _Aft2d_gSegmentEdgeFwd_Header
#define _Aft2d_gSegmentEdgeFwd_Header

#include <Mesh_BndEdge_Position.hxx>

namespace AutLib
{

	// Forward Declarations
	template<class BndEdgeTraits, Mesh_BndEdge_Position POS>
	class Aft_TBndEdge;

	struct Aft2d_gBndEdgeTraits;

	typedef Aft_TBndEdge<Aft2d_gBndEdgeTraits, Mesh_BndEdge_Position_Segment>
		Aft2d_gSegmentEdge;
}

#endif // !_Aft2d_gSegmentEdgeFwd_Header

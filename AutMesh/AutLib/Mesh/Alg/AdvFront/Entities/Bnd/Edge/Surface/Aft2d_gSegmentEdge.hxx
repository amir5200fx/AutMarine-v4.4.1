#pragma once
#ifndef _Aft2d_gSegmentEdge_header
#define _Aft2d_gSegmentEdge_Header

#include <Aft_TBndEdge.hxx>
#include <Aft2d_gBndEdgeTraits.hxx>

namespace AutLib
{

	typedef Aft_TBndEdge<Aft2d_gBndEdgeTraits, Mesh_BndEdge_Position_Segment>
		Aft2d_gSegmentEdge;

	template<>
	static std::vector<std::shared_ptr<Aft2d_gSegmentEdge>>
		Aft2d_gSegmentEdge::GetTopology
		(
			const Entity2d_Chain& theChain,
			const std::shared_ptr<Mesh_PlnCurve<GModel_parCurve>>& theCurve
		);

	template<>
	static void
		Aft2d_gSegmentEdge::MergeDangles
		(
			const std::vector<std::shared_ptr<Aft2d_gSegmentEdge>>& theWire,
			const Standard_Real theTol
		);
}

#endif // !_Aft2d_gSegmentEdge_header

#pragma once
#ifndef _TopoMesh_PlaneBoundaryTraits_Header
#define _TopoMesh_PlaneBoundaryTraits_Header

#include <Aft2d_gSegmentEdgeFwd.hxx>
#include <Aft2d_SegmentEdgeFwd.hxx>

namespace AutLib
{

	// Forward Declarations
	template<class BndEdgeType>
	class Mesh2d_LineEdgeTemplate;

	template<class BndEdgeType>
	class Mesh2d_PoleEdgeTemplate;

	template<class BndType> struct base_boundary_edge_type {};

	template<> struct base_boundary_edge_type<Aft2d_gSegmentEdge> { typedef Aft2d_gSegmentEdge type; };
	template<> struct base_boundary_edge_type<Mesh2d_PoleEdgeTemplate<Aft2d_gSegmentEdge>> { typedef Aft2d_gSegmentEdge type; };
	template<> struct base_boundary_edge_type<Mesh2d_LineEdgeTemplate<Aft2d_gSegmentEdge>> { typedef Aft2d_gSegmentEdge type; };
}

#endif // !_TopoMesh_PlaneBoundaryTraits_Header

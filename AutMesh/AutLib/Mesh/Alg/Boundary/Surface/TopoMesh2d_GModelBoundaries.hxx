#pragma once
#ifndef _TopoMesh2d_GModelBoundaries_Header
#define _TopoMesh2d_GModelBoundaries_Header

#include <TopoMesh_PlaneBoundaries.hxx>
#include <Mesh2d_gSurfPlane.hxx>
#include <Mesh2d_SizeMapSurface.hxx>
#include <Mesh2d_gPlnWire.hxx>
#include <Aft2d_gSegmentEdge.hxx>

namespace AutLib
{

	typedef TopoMesh_PlaneBoundaries
		<
		Mesh2d_gSurfPlane,
		Mesh2d_SizeMapSurface,
		Aft2d_gSegmentEdge, true, true
		>
		TopoMesh2d_GModelBoundaries;

	template<>
	void TopoMesh2d_GModelBoundaries::UpdateFront();
}

#endif // !_TopoMesh2d_GModelBoundaries_Header

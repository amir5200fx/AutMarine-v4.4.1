#pragma once
#ifndef _MeshAPI_gBndCurvesAnalysis_Header
#define _MeshAPI_gBndCurvesAnalysis_Header

#include <MeshAPI_BndCurvesAnalysis.hxx>
#include <TopoMesh2d_GModelBoundaries.hxx>
#include <Mesh3d_SizeMap.hxx>

namespace AutLib
{

	typedef MeshAPI_BndCurvesAnalysis<TopoMesh2d_GModelBoundaries, Mesh3d_SizeMap>
		MeshAPI_gBndCurvesAnalysis;
}

#endif // !_MeshAPI_gBndCurvesAnalysis_Header

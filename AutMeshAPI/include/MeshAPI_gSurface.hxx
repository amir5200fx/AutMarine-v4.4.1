#pragma once
#ifndef _MeshAPI_gSurface_Header
#define _MeshAPI_gSurface_Header

#include <MeshAPI_Surface.hxx>
#include <GModel_Surface.hxx>
#include <Mesh3d_SizeMap.hxx>
#include <Aft2d_gSegmentEdge.hxx>

namespace AutLib
{
	typedef MeshAPI_Surface<GModel_Surface, Mesh3d_SizeMap>
		MeshAPI_gSurface;
}

#endif // !_MeshAPI_gSurface_Header

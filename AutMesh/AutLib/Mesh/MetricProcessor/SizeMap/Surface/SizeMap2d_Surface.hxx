#pragma once
#ifndef _SizeMap2d_Surface_Header
#define _SizeMap2d_Surface_Header

#include <Mesh_SurfaceSizeMap.hxx>
#include <Mesh3d_SizeMap.hxx>

namespace AutLib
{
	typedef Mesh_SurfaceSizeMap<Mesh3d_SizeMap>
		SizeMap2d_Surface;
}

#endif // !_SizeMap2d_Surface_Header

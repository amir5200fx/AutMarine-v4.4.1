#pragma once
#ifndef _Mesh2d_CurveSurface_Header
#define _Mesh2d_CurveSurface_Header

#include <Mesh_Curve.hxx>
#include <Mesh2d_SizeMapSurface.hxx>

#include <Geom2d_Curve.hxx>

namespace AutLib
{
	typedef Mesh_Curve<Geom2d_Curve, Mesh2d_SizeMapSurface>
		Mesh2d_CurveSurface;
}

#endif // !_Mesh2d_CurveSurface_Header

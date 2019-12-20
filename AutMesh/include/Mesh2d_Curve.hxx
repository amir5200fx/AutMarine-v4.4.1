#pragma once
#ifndef _Mesh2d_Curve_Header
#define _Mesh2d_Curve_Header

#include <Mesh_Curve.hxx>
#include <Mesh2d_SizeMap.hxx>

#include <Geom2d_Curve.hxx>

namespace AutLib
{
	typedef Mesh_Curve<Geom2d_Curve, Mesh2d_SizeMap>
		Mesh2d_Curve;
}

#endif // !_Mesh2d_Curve_Header

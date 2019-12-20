#pragma once
#ifndef _Mesh2d_CurveOptmPoint_Newton_Function_Header
#define _Mesh2d_CurveOptmPoint_Newton_Function_Header

#include <Mesh_CurveOptmPoint_Newton_Function.hxx>
#include <Mesh2d_SizeMap.hxx>
#include <Geom2d_Curve.hxx>

namespace AutLib
{
	typedef Mesh_CurveOptmPoint_Newton_Function<Geom2d_Curve, Mesh2d_SizeMap>
		Mesh2d_CurveOptmPoint_Newton_Function;
}

#endif // !_Mesh2d_CurveOptmPoint_Newton_Function_Header

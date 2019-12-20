#pragma once
#ifndef _Mesh2d_CurveOptmPoint_Newton_Derivation_Header
#define _Mesh2d_CurveOptmPoint_Newton_Derivation_Header

#include <Mesh_CurveOptmPoint_Newton_Derivation.hxx>
#include <Mesh2d_SizeMap.hxx>
#include <Geom2d_Curve.hxx>

namespace AutLib
{
	typedef Mesh_CurveOptmPoint_Newton_Derivation<Geom2d_Curve, Mesh2d_SizeMap>
		Mesh2d_CurveOptmPoint_Newton_Derivation;
}

#endif // !_Mesh2d_CurveOptmPoint_Newton_Derivation_Header

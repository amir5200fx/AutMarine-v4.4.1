#pragma once
#ifndef _Mesh2d_CurveAnIso_Header
#define _Mesh2d_CurveAnIso_Header

#include <Mesh_Curve.hxx>
#include <Mesh2d_SizeMapAnIso.hxx>

#include <Geom2d_Curve.hxx>

namespace AutLib
{
	typedef Mesh_Curve<Geom2d_Curve, Mesh2d_SizeMapAnIso>
		Mesh2d_CurveAnIso;
}

#endif // !_Mesh2d_CurveAnIso_Header

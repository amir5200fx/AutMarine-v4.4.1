#pragma once
#ifndef _Mesh2d_CurveEntity_Header
#define _Mesh2d_CurveEntity_Header

#include <Mesh_CurveEntity.hxx>
#include <Mesh2d_SizeMap.hxx>

#include <Geom2d_Curve.hxx>

namespace AutLib
{
	typedef Mesh_CurveEntity<Geom2d_Curve, Mesh2d_SizeMap>
		Mesh2d_CurveEntity;
}

#endif // !_Mesh2d_CurveEntity_Header

#pragma once
#ifndef _Mesh2d_Surface_Header
#define _Mesh2d_Surface_Header

#include <Mesh_Plane.hxx>
#include <Mesh2d_SizeMapSurface.hxx>
#include <Aft2d_CoreSurface.hxx>

namespace AutLib
{

	typedef Mesh_Plane<Mesh2d_SizeMapSurface, Mesh2d_SizeMapSurface>
		Mesh2d_Surface;

	template<>
	Standard_Boolean Mesh2d_Surface::CheckAngle(const frontType & theFront, const nodeType & theNode, const Standard_Real CosAngle) const;
}

#endif // !_Mesh2d_Surface_Header

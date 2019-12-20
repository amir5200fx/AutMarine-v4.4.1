#pragma once
#ifndef _Mesh2d_PlaneAnIso_Header
#define _Mesh2d_PlaneAnIso_Header

#include <Mesh_Plane.hxx>
#include <Mesh2d_SizeMapAnIso.hxx>
#include <Aft2d_CoreAnIso.hxx>

namespace AutLib
{

	typedef Mesh_Plane<Mesh2d_SizeMapAnIso, Mesh2d_SizeMapAnIso>
		Mesh2d_PlaneAnIso;
}

#endif // !_Mesh2d_PlaneAnIso_Header

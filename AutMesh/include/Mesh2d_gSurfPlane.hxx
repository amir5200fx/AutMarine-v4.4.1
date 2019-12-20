#pragma once
#ifndef _Mesh2d_gSurfPlane_Header
#define _Mesh2d_gSurfPlane_Header

#include <Mesh_SurfPlane.hxx>
#include <Mesh2d_gPlnCurve.hxx>
#include <Mesh2d_gPlnWire.hxx>
#include <GModel_Surface.hxx>
#include <GModel_Wire.hxx>
#include <GModel_Edge.hxx>

namespace AutLib
{
	typedef Mesh_SurfPlane<GModel_Surface>
		Mesh2d_gSurfPlane;
}

#endif // !_Mesh2d_gSurfPlane_Header

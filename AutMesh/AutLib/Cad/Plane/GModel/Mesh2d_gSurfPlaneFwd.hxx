#pragma once
#ifndef _Mesh2d_gSurfPlaneFwd_Header
#define _Mesh2d_gSurfPlaneFwd_Header

namespace AutLib
{

	// Forward Declarations

	template<class SurfType>
	class Mesh_SurfPlane;

	class GModel_Surface;

	typedef Mesh_SurfPlane<GModel_Surface>
		Mesh2d_gSurfPlane;
}

#endif // !_Mesh2d_gSurfPlaneFwd_Header

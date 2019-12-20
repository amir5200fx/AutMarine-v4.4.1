#pragma once
#ifndef _Aft2d_gBndNodeTraits_Header
#define _Aft2d_gBndNodeTraits_Header

#include <Aft2d_BndNodeSurfaceTraits.hxx>

namespace AutLib
{

	// Forward Declarations
	class GModel_parCurve;

	template<class CrvEntity>
	class Mesh_PlnCurve;

	struct Aft2d_gBndNodeTraits
	{

		typedef Aft2d_BndNodeSurfaceTraits bndNodeTraits;

		typedef Mesh_PlnCurve<GModel_parCurve> curveType;
		typedef void surfType;
	};
}

#endif // !_Aft2d_gBndNodeTraits_Header

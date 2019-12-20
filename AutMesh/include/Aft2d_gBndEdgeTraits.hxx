#pragma once
#ifndef _Aft2d_gBndEdgeTraits_Header
#define _Aft2d_gBndEdgeTraits_Header

#include <Aft2d_BndEdgeSurfaceTraits.hxx>
#include <Aft2d_gCornerNodeFwd.hxx>

namespace AutLib
{

	// Forward Declarations
	class GModel_parCurve;

	template<class CrvEntity>
	class Mesh_PlnCurve;

	struct Aft2d_gBndEdgeTraits
	{

		typedef Aft2d_BndEdgeSurfaceTraits bndEdgeTraits;
		typedef Aft2d_gCornerNode nodeType;

		typedef Mesh_PlnCurve<GModel_parCurve> curveType;
		typedef void surfType;
	};
}

#endif // !_Aft2d_gBndEdgeTraits_Header

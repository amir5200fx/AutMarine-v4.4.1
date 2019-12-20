#pragma once
#ifndef _Aft2d_TBndEdgeSurfaceTraits_Header
#define _Aft2d_TBndEdgeSurfaceTraits_Header

#include <Aft2d_BndEdgeSurfaceTraits.hxx>

namespace AutLib
{

	// Forward Declarations
	class Pln_Curve;

	template<class CrvEntity>
	class Mesh_PlnCurve;

	struct Aft2d_TBndEdgeSurfaceTraits
	{
		typedef Aft2d_BndEdgeSurfaceTraits bndEdgeTraits;

		typedef Mesh_PlnCurve<Pln_Curve> curveType;
		typedef void surfType;
	};
}

#endif // !_Aft2d_TBndEdgeSurfaceTraits_Header

#pragma once
#ifndef _Aft2d_TBndNodeSurfaceTraits_Header
#define _Aft2d_TBndNodeSurfaceTraits_Header

#include <Aft2d_BndNodeSurfaceTraits.hxx>

namespace AutLib
{

	// Forward Declarations
	class Pln_Curve;

	template<class CrvEntity>
	class Mesh_PlnCurve;

	struct Aft2d_TBndNodeSurfaceTraits
	{

		typedef Aft2d_BndNodeSurfaceTraits bndNodeTraits;

		typedef Mesh_PlnCurve<Pln_Curve> curveType;
		typedef void surfType;
	};
}

#endif // !_Aft2d_TBndNodeSurfaceTraits_Header

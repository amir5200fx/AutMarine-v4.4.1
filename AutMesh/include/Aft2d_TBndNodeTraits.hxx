#pragma once
#ifndef _Aft2d_TBndNodeTraits_Header
#define _Aft2d_TBndNodeTraits_Header

#include <Aft2d_BndNodeTraits.hxx>

namespace AutLib
{

	// Forward Declarations
	class Pln_Curve;

	template<class CrvEntity>
	class Mesh_PlnCurve;

	struct Aft2d_TBndNodeTraits
	{

		typedef Aft2d_BndNodeTraits bndNodeTraits;

		typedef Mesh_PlnCurve<Pln_Curve> curveType;
		typedef void surfType;
	};
}

#endif // !_Aft2d_TBndNodeTraits_Header

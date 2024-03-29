#pragma once
#ifndef _Aft2d_TBndEdgeAnIsoTraits_Header
#define _Aft2d_TBndEdgeAnIsoTraits_Header

#include <Aft2d_BndEdgeAnIsoTraits.hxx>

namespace AutLib
{

	// Forward Declarations
	class Pln_Curve;

	template<class CrvEntity>
	class Mesh_PlnCurve;

	struct Aft2d_TBndEdgeAnIsoTraits
	{
		typedef Aft2d_BndEdgeAnIsoTraits bndEdgeTraits;

		typedef Mesh_PlnCurve<Pln_Curve> curveType;
		typedef void surfType;
	};
}

#endif // !_Aft2d_TBndEdgeAnIsoTraits_Header

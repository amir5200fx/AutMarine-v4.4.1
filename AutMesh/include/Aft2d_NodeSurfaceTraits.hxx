#pragma once
#ifndef _Aft2d_NodeSurfaceTraits_Header
#define _Aft2d_NodeSurfaceTraits_Header

#include <Pnt2d.hxx>
#include <Aft2d_EdgeSurfaceFwd.hxx>
#include <Aft2d_ElementSurfaceFwd.hxx>

namespace AutLib
{

	// Forward Declarations

	struct Aft2d_NodeSurfaceTraits
	{

		typedef Aft2d_EdgeSurface edgeType;
		typedef Aft2d_ElementSurface elementType;
		typedef void facetType;

		typedef Pnt2d ptType;
	};
}

#endif // !_Aft2d_NodeSurfaceTraits_Header

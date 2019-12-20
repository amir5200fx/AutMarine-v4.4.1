#pragma once
#ifndef _Aft2d_EdgeSurfaceTraits_Header
#define _Aft2d_EdgeSurfaceTraits_Header

#include <Pnt2d.hxx>
#include <Aft2d_NodeSurface.hxx>
#include <Aft2d_ElementSurfaceFwd.hxx>

namespace AutLib
{

	// Forward Declarations

	struct Aft2d_EdgeSurfaceTraits
	{

		typedef Pnt2d ptType;
		typedef Aft2d_NodeSurface nodeType;
		typedef Aft2d_ElementSurface elementType;

		enum { geomInfo = 1 };
	};

}

#endif // !_Aft2d_EdgeSurfaceTraits_Header

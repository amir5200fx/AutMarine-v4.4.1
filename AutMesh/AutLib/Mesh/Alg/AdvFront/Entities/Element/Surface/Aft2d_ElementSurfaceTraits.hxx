#pragma once
#ifndef _Aft2d_ElementSurfaceTraits_Header
#define _Aft2d_ElementSurfaceTraits_Header

#include <Pnt2d.hxx>
#include <Aft2d_NodeSurfaceFwd.hxx>
#include <Aft2d_EdgeSurfaceFwd.hxx>
#include <Aft2d_ElementSurfaceAdaptor.hxx>

namespace AutLib
{

	struct Aft2d_ElementSurfaceTraits
	{

		typedef Aft2d_NodeSurface nodeType;
		typedef Aft2d_EdgeSurface edgeType;
		typedef Pnt2d ptType;

		typedef Aft2d_ElementSurfaceAdaptor adaptorType;

		enum
		{
			dim = 2
		};
	};
}

#endif // !_Aft2d_ElementSurfaceTraits_Header

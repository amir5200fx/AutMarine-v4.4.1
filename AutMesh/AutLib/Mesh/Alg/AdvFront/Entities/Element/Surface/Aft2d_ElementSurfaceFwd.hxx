#pragma once
#ifndef _Aft2d_ElementSurfaceFwd_Header
#define _Aft2d_ElementSurfaceFwd_Header

namespace AutLib
{

	// Forward Declarations
	struct Aft2d_ElementSurfaceTraits;

	template<class ElementTraits>
	class Aft_Element;

	typedef Aft_Element<Aft2d_ElementSurfaceTraits>
		Aft2d_ElementSurface;
}

#endif // !_Aft2d_ElementSurfaceFwd_Header

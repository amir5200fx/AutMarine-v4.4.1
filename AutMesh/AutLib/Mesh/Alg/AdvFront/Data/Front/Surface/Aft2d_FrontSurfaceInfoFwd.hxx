#pragma once
#ifndef _Aft2d_FrontSurfaceInfoFwd_Header
#define _Aft2d_FrontSurfaceInfoFwd_Header

#include <Aft2d_FrontSurfaceInfoAdaptorFwd.hxx>
#include <Aft2d_FrontTraits.hxx>

namespace AutLib
{

	// Forward Declarations
	template<class FrontTraits, class FrontAdaptor>
	class Aft2d_FrontInfoTemplate;

	typedef Aft2d_FrontInfoTemplate<Aft2d_FrontTraits<Aft2d_EdgeSurface>, Aft2d_FrontSurfaceInfoAdaptor>
		Aft2d_FrontSurfaceInfo;
}

#endif // !_Aft2d_FrontSurfaceInfoFwd_Header

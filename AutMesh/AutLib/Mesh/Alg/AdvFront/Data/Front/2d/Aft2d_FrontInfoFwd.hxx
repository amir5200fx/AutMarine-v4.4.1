#pragma once
#ifndef _Aft2d_FrontInfoFwd_Header
#define _Aft2d_FrontInfoFwd_Header

#include <Aft2d_FrontInfoAdaptorFwd.hxx>
#include <Aft2d_FrontTraits.hxx>

namespace AutLib
{

	// Forward Declarations
	template<class FrontTraits, class FrontAdaptor>
	class Aft2d_FrontInfoTemplate;

	typedef Aft2d_FrontInfoTemplate<Aft2d_FrontTraits<Aft2d_Edge>, Aft2d_FrontInfoAdaptor>
		Aft2d_FrontInfo;
}

#endif // !_Aft2d_FrontInfoFwd_Header

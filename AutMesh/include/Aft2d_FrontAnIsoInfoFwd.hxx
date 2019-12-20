#pragma once
#ifndef _Aft2d_FrontAnIsoInfoFwd_Header
#define _Aft2d_FrontAnIsoInfoFwd_Header

#include <Aft2d_FrontAnIsoInfoAdaptorFwd.hxx>
#include <Aft2d_FrontTraits.hxx>

namespace AutLib
{

	// Forward Declarations
	template<class FrontTraits, class FrontAdaptor>
	class Aft2d_FrontInfoTemplate;

	typedef Aft2d_FrontInfoTemplate<Aft2d_FrontTraits<Aft2d_EdgeAnIso>, Aft2d_FrontAnIsoInfoAdaptor>
		Aft2d_FrontAnIsoInfo;
}

#endif // !_Aft2d_FrontAnIsoInfoFwd_Header

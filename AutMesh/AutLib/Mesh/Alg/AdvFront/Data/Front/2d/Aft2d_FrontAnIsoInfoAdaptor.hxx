#pragma once
#ifndef _Aft2d_FrontAnIsoInfoAdaptor_Header
#define _Aft2d_FrontAnIsoInfoAdaptor_Header

#include <Aft2d_FrontInfoAdaptorTemplate.hxx>
#include <Aft2d_NodeAnIsoFwd.hxx>
#include <Aft2d_EdgeAnIsoFwd.hxx>
#include <Aft2d_ElementAnIsoFwd.hxx>
#include <Aft2d_FrontTraits.hxx>

namespace AutLib
{

	typedef Aft2d_FrontInfoAdaptorTemplate<Aft2d_FrontTraits<Aft2d_EdgeAnIso>>
		Aft2d_FrontAnIsoInfoAdaptor;
}

#endif // !_Aft2d_FrontAnIsoInfoAdaptor_Header

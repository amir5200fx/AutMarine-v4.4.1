#pragma once
#ifndef _Aft2d_FrontAnIsoInfo_Header
#define _Aft2d_FrontAnIsoInfo_Header

#include <Aft2d_FrontInfoTemplate.hxx>
#include <Aft2d_FrontTraits.hxx>
#include <Aft2d_FrontAnIsoInfoAdaptor.hxx>
#include <Aft2d_ElementAnIso.hxx>
#include <Aft2d_EdgeAnIso.hxx>
#include <Aft2d_NodeAnIso.hxx>

namespace AutLib
{

	typedef Aft2d_FrontInfoTemplate<Aft2d_FrontTraits<Aft2d_EdgeAnIso>, Aft2d_FrontAnIsoInfoAdaptor>
		Aft2d_FrontAnIsoInfo;
}

#endif // !_Aft2d_FrontAnIsoInfo_Header

#pragma once
#ifndef _Aft2d_Core_Header
#define _Aft2d_Core_Header

#include <Aft_Core.hxx>
#include <Aft2d_FrontInfo.hxx>
#include <Aft2d_FrontTraits.hxx>
#include <Aft_FrontGlobalData.hxx>
#include <Geom_AdTree.hxx>
#include <Geom_PriorityList.hxx>
#include <Mesh2d_SizeMap.hxx>

namespace AutLib
{

	typedef Aft_Core
		<
		Mesh2d_SizeMap,
		Aft2d_FrontInfoTemplate
		<
		Aft2d_FrontTraits<typename Mesh2d_SizeMap::frontType>,
		Aft2d_FrontInfoAdaptorTemplate<Aft2d_FrontTraits<typename Mesh2d_SizeMap::frontType>>
		>,
		Aft_FrontGlobalData<typename Mesh2d_SizeMap::frontType, Geom_AdTree, Geom_PriorityList>
		> Aft2d_Core;
}

#endif // !_Aft2d_Core_Header

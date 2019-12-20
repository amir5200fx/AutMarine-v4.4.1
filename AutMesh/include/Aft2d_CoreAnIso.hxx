#pragma once
#ifndef _Aft2d_CoreAnIso_Header
#define _Aft2d_CoreAnIso_Header

#include <Aft_Core.hxx>
#include <Aft2d_FrontAnIsoInfo.hxx>
#include <Aft2d_FrontTraits.hxx>
#include <Aft2d_FrontAnIsoGlobalData.hxx>
#include <Geom_AdTree.hxx>
#include <Geom_PriorityList.hxx>
#include <Mesh2d_SizeMapAnIso.hxx>

namespace AutLib
{

	typedef Aft_Core
		<
		Mesh2d_SizeMapAnIso,
		Aft2d_FrontInfoTemplate
		<
		Aft2d_FrontTraits<typename Mesh2d_SizeMapAnIso::frontType>,
		Aft2d_FrontInfoAdaptorTemplate<Aft2d_FrontTraits<typename Mesh2d_SizeMapAnIso::frontType>>
		>,
		Aft_FrontGlobalData<typename Mesh2d_SizeMapAnIso::frontType, Geom_AdTree, Geom_PriorityList>
		> Aft2d_CoreAnIso;
}

#endif // !_Aft2d_CoreAnIso_Header

#pragma once
#ifndef _Aft2d_CoreSurface_Header
#define _Aft2d_CoreSurface_Header

#include <Aft_Core.hxx>
#include <Aft2d_FrontSurfaceInfo.hxx>
#include <Aft2d_FrontTraits.hxx>
#include <Aft2d_FrontSurfaceGlobalData.hxx>
#include <Geom_AdTree.hxx>
#include <Geom_PriorityList.hxx>
#include <Mesh2d_SizeMapSurface.hxx>

namespace AutLib
{

	typedef Aft_Core
		<
		Mesh2d_SizeMapSurface,
		Aft2d_FrontInfoTemplate
		<
		Aft2d_FrontTraits<typename Mesh2d_SizeMapSurface::frontType>,
		Aft2d_FrontInfoAdaptorTemplate<Aft2d_FrontTraits<typename Mesh2d_SizeMapSurface::frontType>>
		>,
		Aft_FrontGlobalData<typename Mesh2d_SizeMapSurface::frontType, Geom_AdTree, Geom_PriorityList>
		> Aft2d_CoreSurface;

	template<>
	template<>
	void Aft2d_CoreSurface::UpdateFront<void>();
}

#endif // !_Aft2d_CoreSurface_Header

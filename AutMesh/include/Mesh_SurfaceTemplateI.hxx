#pragma once
#include <Mesh_CadTools.hxx>
namespace AutLib
{

	template<class SurfType>
	std::shared_ptr<Mesh_SurfPlane<SurfType>> 
		Mesh_SurfaceTemplate<SurfType>::GetPlane() const
	{
		auto This = std::dynamic_pointer_cast<Mesh_SurfaceTemplate<SurfType>>(std::const_pointer_cast<SurfType>(this->shared_from_this()));
		auto plane = Mesh_SurfPlane<SurfType>::MakePlane(This);
		return std::move(plane);
	}

	template<class SurfType>
	std::shared_ptr<SurfType> 
		Mesh_SurfaceTemplate<SurfType>::ReParameterization
		(
			const SurfType & theSurface,
			const Standard_Real theScale
		)
	{
		auto surface = 
			Mesh_CadTools::template ReParameterization<SurfType>(theSurface, theScale);
		return std::move(surface);
	}

	template<class SurfType>
	std::shared_ptr<SurfType> 
		Mesh_SurfaceTemplate<SurfType>::ReParameterization
	(
		const SurfType & theSurface, 
		intgInfo & theInfo
	)
	{
		auto surface = 
			Mesh_CadTools::template ReParameterization<SurfType>(theSurface, theInfo);
		return std::move(surface);
	}
}
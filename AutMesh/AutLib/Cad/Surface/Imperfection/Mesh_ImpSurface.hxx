#pragma once
#ifndef _Mesh_ImpSurface_Header
#define _Mesh_ImpSurface_Header

#include <Mesh_SurfaceTemplate.hxx>

namespace AutLib
{

	template<class SurfType>
	class Mesh_ImpSurface
		: public Mesh_SurfaceTemplate<SurfType>
	{

		/*Private Data*/

	protected:

		typedef Mesh_SurfaceTemplate<SurfType> base;

		Mesh_ImpSurface(const SurfType& theSurface)
			: SurfType(theSurface)
		{}

		Mesh_ImpSurface
		(
			const Handle(typename SurfType::geomType)& theGeom,
			const typename base::outer& theOuter,
			const typename base::inner& theInner
		)
			: Mesh_SurfaceTemplate<SurfType>(theGeom, theOuter, theInner)
		{}
	};
}

#endif // !_Mesh_ImpSurface_Header

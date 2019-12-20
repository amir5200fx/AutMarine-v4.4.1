#pragma once
#ifndef _ImpSurf_defect_Header
#define _ImpSurf_defect_Header

#include <Mesh_ImpSurface.hxx>
#include <word.hxx>

namespace AutLib
{

	template<class SurfType>
	class ImpSurf_defect
		: public Mesh_ImpSurface<SurfType>
	{

		/*Private Data*/

	protected:

		typedef Mesh_ImpSurface<SurfType> base;

		ImpSurf_defect(const SurfType& theSurface)
			: Mesh_ImpSurface<SurfType>(theSurface)
		{}

		ImpSurf_defect
		(
			const Handle(typename SurfType::geomType)& theGeom,
			const typename base::outer& theOuter,
			const typename base::inner& theInner
		)
			: Mesh_ImpSurface<SurfType>(theGeom, theOuter, theInner)
		{}

	public:

		virtual const word& TypeName() const = 0;
	};
}

#endif // !_ImpSurf_defect_Header

#pragma once
#ifndef _SingSurf_General_Header
#define _SingSurf_General_Header

#include <ImpSurf_singular.hxx>

namespace AutLib
{

	template<class SurfPln>
	class SingSurf_General
		: public ImpSurf_singular<SurfPln>
	{

		/*Private Data*/

	public:

		typedef ImpSurf_singular<SurfPln> base;

		SingSurf_General
		(
			const typename SurfPln::surfType& theSurface,
			std::shared_ptr<Singularity_TypeDetection<SurfPln>>& theType
		)
			: ImpSurf_singular<SurfPln>(theSurface, theType)
		{}

		SingSurf_General
		(
			const Handle(typename SurfPln::surfType::geomType)& theGeom,
			const typename base::outer& theOuter,
			const typename base::inner& theInner,
			const std::shared_ptr<Singularity_TypeDetection<SurfPln>>& theType
		)
			: ImpSurf_singular<SurfPln>(theGeom, theOuter, theInner, theType)
		{}
	};
}

#endif // !_SingSurf_General_Header

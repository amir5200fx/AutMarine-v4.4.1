#pragma once
#ifndef _ImpSurf_defectWire_Header
#define _ImpSurf_defectWire_Header

#include <ImpSurf_defect.hxx>

namespace AutLib
{

	template<class SurfType>
	class ImpSurf_defectWire
		: public ImpSurf_defect<SurfType>
	{

		/*Private Data*/

	protected:

		typedef ImpSurf_defect<SurfType> base;

		ImpSurf_defectWire(const SurfType& theSurface)
			: SurfType(theSurface)
		{}


		ImpSurf_defectWire
		(
			const Handle(typename SurfType::geomType)& theGeom,
			const typename base::outer& theOuter,
			const typename base::inner& theInner
		)
			: ImpSurf_defect<SurfType>(theGeom, theOuter, theInner)
		{}

	public:


	};
}

#endif // !_ImpSurf_defectWire_Header

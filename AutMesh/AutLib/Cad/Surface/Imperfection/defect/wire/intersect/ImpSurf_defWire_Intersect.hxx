#pragma once
#ifndef _ImpSurf_defWire_Intersect_Header
#define _ImpSurf_defWire_Intersect_Header

#include <ImpSurf_defectWire.hxx>

//#include "GModel_Wire.hxx"

namespace AutLib
{

	template<class SurfType>
	class ImpSurf_defWire_Intersect
		: public ImpSurf_defectWire<SurfType>
	{

		/*Private Data*/

	public:

		static const word typeName;

		typedef ImpSurf_defectWire<SurfType> base;

		ImpSurf_defWire_Intersect(const SurfType& theSurface)
			: ImpSurf_defectWire<SurfType>(theSurface)
		{}

		ImpSurf_defWire_Intersect
		(
			const Handle(typename SurfType::geomType)& theGeom,
			const typename base::outer& theOuter,
			const typename base::inner& theInner
		)
			: ImpSurf_defectWire<SurfType>(theGeom, theOuter, theInner)
		{}

		const word& TypeName() const override
		{
			return typeName;
		}

		//- Static functions and operators

		static Standard_Boolean 
			Check
		(
			const SurfType& theSurface,
			const Standard_Real theTol
		);
	};
}

#include <ImpSurf_defWire_IntersectI.hxx>

#endif // !_ImpSurf_defWire_Intersect_Header

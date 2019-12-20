#pragma once
#ifndef _SingSurf_Common_Header
#define _SingSurf_Common_Header

#include <ImpSurf_singular.hxx>

#include "Mesh2d_gSurfPlane.hxx"

namespace AutLib
{

	// Forward Declarations
	class Geo_ColoringSurfMetric;

	template<class SurfPln>
	class SingSurf_Common
		: public ImpSurf_singular<SurfPln>
	{

		typedef typename SurfPln::surfType surfType;
		typedef typename SurfPln::plnCurve plnCurve;

		/*Private Data*/


		//- Static functions and operators

		static std::shared_ptr<typename SurfPln::plnWire> 
			GetOuterWire
			(
				const typename surfType::wireType& theWire,
				const Geo_ColoringSurfMetric& theColors
			);

		static std::shared_ptr<typename SurfPln::plnWire>
			GetInnerWire
			(
				const typename surfType::wireType& theWire,
				const Geo_ColoringSurfMetric& theColors
			);

	public:

		typedef ImpSurf_singular<SurfPln> base;

		SingSurf_Common
		(
			const typename SurfPln::surfType& theSurface,
			std::shared_ptr<Singularity_TypeDetection<SurfPln>>& theType
		)
			: ImpSurf_singular<SurfPln>(theSurface, theType)
		{}

		SingSurf_Common
		(
			const Handle(typename SurfPln::surfType::geomType)& theGeom,
			const typename base::outer& theOuter,
			const typename base::inner& theInner,
			const std::shared_ptr<Singularity_TypeDetection<SurfPln>>& theType
		)
			: ImpSurf_singular<SurfPln>(theGeom, theOuter, theInner, theType)
		{}


		std::shared_ptr<SurfPln> GetPlane() const override;


		//- Static functions and operators

		static std::shared_ptr<SurfPln> 
			ModifyPlane
			(
				const std::shared_ptr<SingSurf_Common>& theSurface
			);
	};
}

#include <SingSurf_CommonI.hxx>

#endif // !_SingSurf_Common_Header

#pragma once
#ifndef _ImpSurf_singular_Header
#define _ImpSurf_singular_Header

#include <Mesh_ImpSurface.hxx>
#include <word.hxx>

namespace AutLib
{

	// Forward Declarations
	template<class SurfPln>
	class Singularity_TypeDetection;

	template<class SurfPln>
	class ImpSurf_singular
		: public Mesh_ImpSurface<typename SurfPln::surfType>
	{

		/*Private Data*/

		std::shared_ptr<Singularity_TypeDetection<SurfPln>> theType_;

	protected:

		typedef Mesh_ImpSurface<typename SurfPln::surfType> base;

		ImpSurf_singular
		(
			const typename SurfPln::surfType& theSurface,
			const std::shared_ptr<Singularity_TypeDetection<SurfPln>>& theType
		)
			: Mesh_ImpSurface<typename SurfPln::surfType>(theSurface)
			, theType_(theType)
		{}

		ImpSurf_singular
		(
			const Handle(typename SurfPln::surfType::geomType)& theGeom,
			const typename base::outer& theOuter,
			const typename base::inner& theInner,
			const std::shared_ptr<Singularity_TypeDetection<SurfPln>>& theType
		)
			: Mesh_ImpSurface<typename SurfPln::surfType>(theGeom, theOuter, theInner)
			, theType_(theType)
		{}

	public:

		//virtual const word& TypeName() const = 0;

		const std::shared_ptr<Singularity_TypeDetection<SurfPln>>& 
			Type() const
		{
			return theType_;
		}

	};
}

#endif // !_ImpSurf_singular_Header

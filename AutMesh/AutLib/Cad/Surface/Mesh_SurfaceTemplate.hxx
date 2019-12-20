#pragma once
#ifndef _Mesh_SurfaceTemplate_Header
#define _Mesh_SurfaceTemplate_Header

#include <Standard_Handle.hxx>

#include <memory>
#include <vector>

class Geom_Surface;

#include "GModel_Surface.hxx"
#include "Mesh_SurfPlane.hxx"

namespace AutLib
{

	// Forward Declarations
	class Numeric_AdaptIntegrationInfo;

	template<class SurfType>
	class Mesh_SurfPlane;

	template<class SurfType>
	class Mesh_SurfaceTemplate
		: public SurfType
	{

		typedef typename SurfType::wireType wireType;
		typedef std::vector<std::shared_ptr<wireType>> wireList;

		typedef Numeric_AdaptIntegrationInfo intgInfo;

		/*Private Data*/

	public:

		typedef std::shared_ptr<wireList> inner;
		typedef std::shared_ptr<wireType> outer;

		Mesh_SurfaceTemplate(const SurfType& theSurface)
			: SurfType(theSurface)
		{}

		Mesh_SurfaceTemplate
		(
			const Handle(typename SurfType::geomType)& theGeom, 
			const outer& theOuter,
			const inner& theInner
		)
			: SurfType(theGeom, theOuter, theInner)
		{}


		virtual std::shared_ptr<Mesh_SurfPlane<SurfType>>
			GetPlane() const;

		//- Static functions and operators

		static std::shared_ptr<SurfType> 
			ReParameterization
			(
				const SurfType& theSurface,
				const Standard_Real thsScale
			);

		static std::shared_ptr<SurfType> 
			ReParameterization
			(
				const SurfType& theSurface,
				intgInfo& theInfo
			);
	};
}

#include <Mesh_SurfaceTemplateI.hxx>

#endif // !_Mesh_SurfaceTemplate_Header

#pragma once
#ifndef _Mesh_CadTools_Header
#define _Mesh_CadTools_Header

#include <Standard_Handle.hxx>
#include <Standard_TypeDef.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Mesh2d_SizeMapAnIsoFwd.hxx>
#include <Mesh2d_SizeMapSurfaceFwd.hxx>
#include <Pnt2d.hxx>

#include <memory>

class Geom_Surface;
class Geom2d_Curve;

namespace AutLib
{

	// Forward Declarations
	class Numeric_AdaptIntegrationInfo;

	class Mesh_CadTools
	{

	public:

		typedef Numeric_AdaptIntegrationInfo intgInfo;

		static Standard_Real 
			CalcLength
		(
			const Pnt2d& theP0, 
			const Pnt2d& theP1,
			const Entity2d_Box& theBoundingBox,
			const Handle(Geom_Surface)& theSurface,
			intgInfo& theInfo
		);

		static Standard_Real 
			CalcLength
		(
			const Geom2d_Curve& theCurve, 
			const Standard_Real theFirst,
			const Standard_Real theLast,
			const Mesh2d_SizeMapAnIso& theSizeMap
		);

		static Standard_Real
			CalcLength
			(
				const Geom2d_Curve& theCurve,
				const Standard_Real theFirst,
				const Standard_Real theLast,
				const Mesh2d_SizeMapSurface& theSizeMap
			);

		static Standard_Real 
			CalcLengthOnSurface
		(
			const Geom2d_Curve& theCurve,
			const Standard_Real theFirst,
			const Standard_Real theLast,
			const Entity2d_Box & theBoundingBox,
			const Handle(Geom_Surface)& theSurface
		);

		static Handle(Geom_Surface) 
			GeomReParameterization
		(
			const Handle(Geom_Surface)& theSurface, 
			const gp_Trsf2d& theParamTransf
		);

		static Handle(Geom_Surface) 
			GeomReParameterization_uExpand
		(
			const Handle(Geom_Surface)& theSurface, 
			const Standard_Real multiply
		);

		static Handle(Geom_Surface) 
			GeomReParameterization_vExpand
		(
			const Handle(Geom_Surface)& theSurface, 
			const Standard_Real multiply
		);

		static Handle(Geom_Surface) 
			ConvertToBSpline
		(
			const Handle(Geom_Surface)& theSurface,
			const Entity2d_Box& theTrimmed
		);

		template<class SurfType>
		static Standard_Real uCharLength(const SurfType& theSurface, const Standard_Real u, intgInfo& theInfo);

		template<class SurfType>
		static Standard_Real vCharLength(const SurfType& theSurface, const Standard_Real v, intgInfo& theInfo);

		template<class SurfType>
		static std::shared_ptr<SurfType> ConvertToBSpline(const SurfType& theSurface);

		template<class SurfType>
		static std::shared_ptr<SurfType> ReParameterization(const SurfType& theSurface, const Standard_Real thsScale);

		template<class SurfType>
		static std::shared_ptr<SurfType> ReParameterization_uExpand(const SurfType& theSurface, const Standard_Real theMult);

		template<class SurfType>
		static std::shared_ptr<SurfType> ReParameterization_vExpand(const SurfType& theSurface, const Standard_Real theMult);

		template<class SurfType>
		static std::shared_ptr<SurfType> ReParameterization(const SurfType& theSurface, intgInfo& theInfo);
	};


}

#include <Mesh_CadToolsI.hxx>

#endif // !_Mesh_CadTools_Header

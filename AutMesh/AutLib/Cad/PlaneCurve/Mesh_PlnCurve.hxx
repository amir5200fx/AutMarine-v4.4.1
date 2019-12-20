#pragma once
#ifndef _Mesh_CadPlnCurve_Header
#define _Mesh_CadPlnCurve_Header

#include <Standard_Handle.hxx>
#include <Standard_TypeDef.hxx>
#include <Entity2d_Chain.hxx>
#include <Mesh2d_SizeMapAnIso.hxx>
#include <Mesh2d_SizeMap.hxx>
#include <Mesh2d_SizeMapSurface.hxx>

#include <memory>

class Geom2d_Curve;

namespace AutLib
{

	// Forward Declarations
	class Geo_ApprxCurveInfo;
	class Mesh_CurveInfo;

	class Mesh_CadPlnCurveBase
	{

	protected:

		static std::shared_ptr<Entity2d_Chain> Mesh
		(
			const Standard_Real theFirst,
			const Standard_Real theLast,
			const Handle(Geom2d_Curve)& theCurve,
			const std::shared_ptr<Mesh2d_SizeMapSurface>& theSizeMap,
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		);

		static std::shared_ptr<Entity2d_Chain> Mesh
		(
			const Standard_Real theFirst,
			const Standard_Real theLast,
			const Handle(Geom2d_Curve)& theCurve, 
			const std::shared_ptr<Mesh2d_SizeMapAnIso>& theSizeMap,
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		);

		static std::shared_ptr<Entity2d_Chain> Mesh
		(
			const Standard_Real theFirst,
			const Standard_Real theLast,
			const Handle(Geom2d_Curve)& theCurve,
			const std::shared_ptr<Mesh2d_SizeMap>& theSizeMap,
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		);

		static std::shared_ptr<Entity2d_Chain> Discrete
		(
			const Standard_Real theFirst,
			const Standard_Real theLast,
			const Handle(Geom2d_Curve)& theCurve, 
			const std::shared_ptr<Geo_ApprxCurveInfo>& theInfo
		);

	};

	template<class CrvEntity>
	class Mesh_PlnCurve
		: public CrvEntity
		, public Mesh_CadPlnCurveBase
	{

		/*Private Data*/
		
	public:

		typedef typename CrvEntity::geomType curveType;
		typedef typename CrvEntity::infoType info;
		typedef info infoType;

		typedef Mesh_CadPlnCurveBase base;
		typedef CrvEntity entity;

		Mesh_PlnCurve(const CrvEntity& theCurve)
			: CrvEntity(theCurve)
		{}

		Mesh_PlnCurve
		(
			const Standard_Real theFirst, 
			const Standard_Real theLast,
			const Handle(curveType)& theCurve,
			const std::shared_ptr<info>& theInfo
		)
			: CrvEntity(theFirst, theLast, theCurve, theInfo)
		{}

		std::shared_ptr<Entity2d_Chain> Discrete
		(
			const std::shared_ptr<Geo_ApprxCurveInfo>& theInfo
		) const;

		virtual std::shared_ptr<Entity2d_Chain> Mesh
		(
			const std::shared_ptr<Mesh2d_SizeMapSurface>& theSizeMap,
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		) const;

		virtual std::shared_ptr<Entity2d_Chain> Mesh
		(
			const std::shared_ptr<Mesh2d_SizeMapAnIso>& theSizeMap, 
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		) const;

		virtual std::shared_ptr<Entity2d_Chain> Mesh
		(
			const std::shared_ptr<Mesh2d_SizeMap>& theSizeMap,
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		) const;

		/*virtual std::vector<std::shared_ptr<Aft2d_Edge>>
			TopoMesh
			(
				const std::shared_ptr<Mesh2d_SizeMap>& theSizeMap,
				const std::shared_ptr<Mesh_CurveInfo>& theInfo
			) const;

		virtual std::vector<std::shared_ptr<Aft2d_EdgeAnIso>>
			TopoMesh
			(
				const std::shared_ptr<Mesh2d_SizeMapAnIso>& theSizeMap,
				const std::shared_ptr<Mesh_CurveInfo>& theInfo
			) const;*/

		template<class SizeMap>
		std::shared_ptr<Entity2d_Chain> MeshTemp
		(
			const std::shared_ptr<SizeMap>& theSizeMap, 
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		) const;


		//- Static functions and operators

		template<class SizeMap, class EdgeType>
		static std::vector<std::shared_ptr<EdgeType>> TopoMesh
		(
			const std::shared_ptr<Mesh_PlnCurve>& theCurve,
			const std::shared_ptr<SizeMap>& theSizeMap,
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		);
	};
}

#include <Mesh_PlnCurveI.hxx>

#endif // !_Mesh_CadPlnCurve_Header

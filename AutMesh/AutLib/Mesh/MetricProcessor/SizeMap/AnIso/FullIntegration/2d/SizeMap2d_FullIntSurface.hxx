#pragma once
#ifndef _SizeMap2d_FullIntSurface_Header
#define _SizeMap2d_FullIntSurface_Header

#include <Global_InitRunTime.hxx>
#include <SizeMap2d_Surface.hxx>
#include <MetricMap2d_Surface.hxx>

#include <memory>

namespace AutLib
{

	struct SizeMap2d_FullIntSurfaceCache
	{
		mutable Entity2d_Metric1 CurrentMetric;
	};

	// Forward Declarations
	template<class SizeMap>
	class Mesh_LineIntegrand;

	template<class SizeMap, bool UnitLength>
	class Mesh_LineIntegrand_Function;

	template<class Function, bool RefInfo>
	class Numeric_AdaptIntegration;

	class SizeMap2d_FullIntSurface;
	class Numeric_AdaptIntegrationInfo;
	class Entity2d_Eigen;
	class SizeMap2d_FullIntSurfaceInfo;

	typedef Mesh_LineIntegrand<SizeMap2d_FullIntSurface> Mesh_LineIntegrand_FullIntSurface;
	typedef Mesh_LineIntegrand_Function<SizeMap2d_FullIntSurface, false>
		Mesh_LineIntegrand_Function_FullIntSurface;

	typedef Mesh_LineIntegrand_Function<SizeMap2d_FullIntSurface, true>
		Mesh_LineIntegrand_UnitLengthFunction_FullIntSurface;

	typedef Numeric_AdaptIntegration<Mesh_LineIntegrand_Function_FullIntSurface, true>
		Numeric_AdaptIntegration_FullIntSurface;

	typedef Numeric_AdaptIntegration<Mesh_LineIntegrand_UnitLengthFunction_FullIntSurface, true>
		Numeric_AdaptIntegration_UnitLengthFullIntSurface;

	class SizeMap2d_FullIntSurface
		: public Mesh2d_SizeMapSurface
		, public Global_InitRunTime
		, public SizeMap2d_FullIntSurfaceCache
	{

		typedef SizeMap2d_FullIntSurfaceInfo info;

		/*Private Data*/

		std::shared_ptr<SizeMap2d_Surface> theSizeMap_;
		std::shared_ptr<MetricMap2d_Surface> theMetricMap_;

		std::shared_ptr<info> theInfo_;

		Entity2d_Box theBoundingBox_;


		Pnt2d CorrEffRegion
		(
			const Pnt2d& theCentre,
			const Pnt2d& theP,
			const Standard_Real theRadius
		) const;

	protected:

		Entity2d_Box& Change_BoundingBox()
		{
			return theBoundingBox_;
		}

	public:

		typedef Aft2d_EdgeSurface front;

		SizeMap2d_FullIntSurface
		(
			const std::shared_ptr<info>& theInfo
		)
			: theInfo_(theInfo)
		{}


		const Entity2d_Box& BoundingBox() const override
		{
			return theBoundingBox_;
		}

		//- exclusive functions and operators

		const std::shared_ptr<SizeMap2d_Surface>& SurfaceSizeMap() const
		{
			return theSizeMap_;
		}

		const std::shared_ptr<MetricMap2d_Surface>& MetricMap() const
		{
			return theMetricMap_;
		}

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		Standard_Boolean IsLoaded() const
		{
			if (NOT theSizeMap_) return Standard_False;
			if (NOT theMetricMap_) return Standard_False;
			return Standard_True;
		}

		void LoadSizeMap
		(
			const std::shared_ptr<SizeMap2d_Surface>& theMap
		)
		{
			theSizeMap_ = theMap;
		}

		void LoadMetricMap
		(
			const std::shared_ptr<MetricMap2d_Surface>& theMap
		)
		{
			theMetricMap_ = theMap;
		}


		//- override virtual functions

		Standard_Real DimSize() const override;

		Standard_Real BaseElementSize() const override;

		Standard_Real CalcElementSize
		(
			const Pnt2d&
		) const override;

		Standard_Real CalcElementSize
		(
			const front&
		) const override;

		Standard_Real Oriented
		(
			const Pnt2d&,
			const front&
		) const override;

		Standard_Real CalcDistance
		(
			const Pnt2d&,
			const Pnt2d&
		) const override;

		Standard_Real CalcSquareDistance
		(
			const Pnt2d&,
			const Pnt2d&
		) const override;

		Standard_Real CalcDistance
		(
			const Pnt2d&,
			const front&
		) const override;

		Standard_Real CalcSquareDistance
		(
			const Pnt2d&,
			const front&
		) const override;

		Standard_Real CalcUnitDistance
		(
			const Pnt2d&,
			const Pnt2d&
		) const override;

		Pnt2d CalcOptimumCoord
		(
			const Standard_Real theSize,
			const front&
		) const override;

		Pnt2d CalcCentreOf
		(
			const Pnt2d&,
			const Pnt2d&
		) const override;

		Pnt2d CalcCentreOf
		(
			const frontType&
		) const;

		box CalcSearchRegion
		(
			const Standard_Real theRadius,
			const metric& theMetric,
			const Pnt2d& theCentre
		) const override;

		box CalcSearchRegion
		(
			const Standard_Real theRadius,
			const Pnt2d& theCentre,
			const front&
		) const override;

		box CalcSearchRegion
		(
			const Standard_Real theRadius,
			const front&
		) const override;

		box CalcEffectiveRegion
		(
			const Standard_Real theRadius,
			const Point& theCentre,
			const frontType&
		) const override;

		metric CalcEffectiveMetric
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1
		) const override;

		Pnt3d CalcCoord3D
		(
			const Pnt2d& theCoord
		) const override;

		Standard_Real CalcLength3D
		(
			const frontType& theEdge
		) const override;

		Standard_Real CalcLength3D
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1
		) const override;

		Standard_Real CalcLength3D
		(
			const Pnt3d& theP0,
			const Pnt3d& theP1
		) const override;

		Standard_Real Integrand
		(
			const Pnt2d& thePoint,
			const Pnt2d& theVector
		) const override;

		Standard_Real Integrand
		(
			const Pnt2d& thePoint,
			const gp_Vec2d& theVector
		) const override;

		Standard_Real IntegrandPerSize
		(
			const Pnt2d& thePoint,
			const Pnt2d& theVector
		) const override;

		Standard_Real IntegrandPerSize
		(
			const Pnt2d& thePoint,
			const gp_Vec2d& theVector
		) const override;

		void Make() override;
	};

	extern std::shared_ptr<Entity2d_Eigen>
		size_map2d_full_surface_adapt_eigen;
}

#include <SizeMap2d_FullIntSurfaceI.hxx>

#endif // !_SizeMap2d_FullIntSurface_Header

#pragma once
#ifndef _Mesh_SurfaceSizeMap_Header
#define _Mesh_SurfaceSizeMap_Header

#include <Mesh2d_SizeMapSurface.hxx>
#include <Entity2d_Box.hxx>
#include <Geom_Surface.hxx>

namespace AutLib
{

	template<class SizeMap3D>
	class Mesh_SurfaceSizeMap
		: public Mesh2d_SizeMapSurface
	{

		/*Private Data*/

		const SizeMap3D& theSizeMap_;

		const Geom_Surface& theSurface_;

		static Entity2d_Box theBoundingBox_;

	public:

		typedef Entity2d_Box box;
		typedef Entity2d_Metric1 metric;
		typedef Aft2d_EdgeSurface front;

		Mesh_SurfaceSizeMap
		(
			const SizeMap3D& theSizeMap,
			const Geom_Surface& theSurface
		)
			: theSizeMap_(theSizeMap)
			, theSurface_(theSurface)
		{}

		const box& BoundingBox() const override;

		const SizeMap3D& SizeMap3d() const
		{
			return theSizeMap_;
		}

		const Geom_Surface& Surface() const
		{
			return theSurface_;
		}

		Standard_Real DimSize() const override;

		Standard_Real BaseElementSize() const override
		{
			return theSizeMap_.BaseElementSize();
		}

		Standard_Real CalcElementSize
		(
			const Pnt2d& theP
		) const override
		{
			return theSizeMap_.CalcElementSize(theSurface_.Value(theP.X(), theP.Y()));
		}

		Standard_Real CalcElementSize
		(
			const front& theEdge
		) const override
		{
			return CalcElementSize(theEdge.Centre());
		}

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
			const front&
		) const override;

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
			const Pnt2d& P0,
			const Pnt2d& P1
		) const override;

		Standard_Real CalcLength3D
		(
			const Pnt3d& P0,
			const Pnt3d& P1
		) const override;

		Standard_Real CalcLength3D
		(
			const frontType& theEdge
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

		void Make() override
		{
			Change_IsDone() = Standard_True;
		}
	};
}

#include <Mesh_SurfaceSizeMapI.hxx>

#endif // !_Mesh_SurfaceSizeMap_Header

#pragma once
#ifndef _Geo_ApprxSurfMetric_Header
#define _Geo_ApprxSurfMetric_Header

#include <Global_Done.hxx>
#include <Standard_Handle.hxx>
#include <Entity2d_Box.hxx>
#include <GeoMesh2d_MetricBackgroundFwd.hxx>
#include <Mesh_SurfaceSizeMap.hxx>
#include <Mesh3d_SizeMap.hxx>
#include <Geo_ApprxSurfMetricInfo.hxx>

class Geom_Surface;

#include <memory>

namespace AutLib
{

	// Forward Declarations
	

	class Geo_ApprxSurfMetric
		: public Global_Done
	{

		typedef Geo_ApprxSurfMetricInfo info;
		typedef Mesh_SurfaceSizeMap<Mesh3d_SizeMap> sizeMap;
		typedef GeoMesh2d_MetricBackground backMetric;

		/*Private Data*/

		Handle(Geom_Surface) theSurface_;

		Entity2d_Box theBoundingBox_;

		std::shared_ptr<backMetric> theApprox_;
		std::shared_ptr<sizeMap> theSizeMap_;

		Standard_Boolean TrackMaxDet_;

		std::shared_ptr<info> theInfo_;

	public:

		Geo_ApprxSurfMetric
		(
			const std::shared_ptr<info>& theInfo
		)
			: theInfo_(theInfo)
		{}

		Geo_ApprxSurfMetric
		(
			const Handle(Geom_Surface)& theSurface,
			const Entity2d_Box& theBoundingBox,
			const std::shared_ptr<info>& theInfo
		)
			: theSurface_(theSurface)
			, theBoundingBox_(theBoundingBox)
			, theInfo_(theInfo)
		{}

		const Handle(Geom_Surface)& Surface() const
		{
			return theSurface_;
		}

		const Entity2d_Box& BoundingBox() const
		{
			return theBoundingBox_;
		}

		const std::shared_ptr<backMetric>& Approx() const
		{
			return theApprox_;
		}

		const std::shared_ptr<sizeMap>& SizeMap() const
		{
			return theSizeMap_;
		}

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		Standard_Boolean TrackMaxDeterminant() const
		{
			return TrackMaxDet_;
		}

		void Perform();

		void LoadSurface
		(
			const Handle(Geom_Surface)& theSurface,
			const Entity2d_Box& theBoundingBox
		)
		{
			if (IsDone()) Change_IsDone() = Standard_False;
			theSurface_ = theSurface;
			theBoundingBox_ = theBoundingBox;
		}

		void LoadSizeMap(const std::shared_ptr<sizeMap>& theSizeMap)
		{
			theSizeMap_ = theSizeMap;
		}

		void Reset()
		{
			theSurface_.Nullify();
			if (theApprox_) theApprox_.reset();
			if (theSizeMap_) theSizeMap_.reset();
		}

		void SetTrackMaxDeterminant(const Standard_Boolean track)
		{
			TrackMaxDet_ = track;
		}

	};

	extern std::shared_ptr<Geo_ApprxSurfMetricInfo> surface_metric_approximator_info;
}

#endif // !_Geo_ApprxSurfMetric_Header

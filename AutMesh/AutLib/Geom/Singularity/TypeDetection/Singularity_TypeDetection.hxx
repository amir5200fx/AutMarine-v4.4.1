#pragma once
#ifndef _Singularity_TypeDetection_Header
#define _Singularity_TypeDetection_Header

#include <Global_Done.hxx>
#include <Global_Verbose.hxx>
#include <Singularity_TypeDetectionInfo.hxx>
#include <Mesh3d_SizeMap.hxx>

#include <memory>
#include <vector>
#include <iostream>

//#include "Mesh2d_gSurfPlane.hxx"

namespace AutLib
{

	// Forward Declarations
	class Geo_ColoringSurfMetric;
	class Singularity_Horizon;

	template<class SurfPln>
	class Mesh_SingularityZone;

	template<class SurfPln>
	class Singularity_TypeDetection
		: public Global_Done
		, public Global_Verbose
	{

		typedef Singularity_TypeDetectionInfo info;
		typedef typename SurfPln::plnCurve plnCurve;

		/*Private Data*/

		std::shared_ptr<Singularity_Horizon> theHorizons_;
		std::shared_ptr<Geo_ColoringSurfMetric> theColors_;

		std::shared_ptr<Mesh3d_SizeMap> theSizeMap_;

		std::vector<std::shared_ptr<Mesh_SingularityZone<SurfPln>>> theZones_;

		std::shared_ptr<info> theInfo_;

	public:

		Singularity_TypeDetection()
		{}

		Singularity_TypeDetection
		(
			const std::shared_ptr<Singularity_Horizon>& theHorizons, 
			const std::shared_ptr<Geo_ColoringSurfMetric>& theColors, 
			const std::shared_ptr<Mesh3d_SizeMap>& theSizeMap,
			const std::shared_ptr<info>& theInfo
		)
			: theHorizons_(theHorizons)
			, theColors_(theColors)
			, theSizeMap_(theSizeMap)
			, theInfo_(theInfo)
		{}

		Standard_Integer NbZones() const
		{
			return (Standard_Integer)theZones_.size();
		}

		const std::vector<std::shared_ptr<Mesh_SingularityZone<SurfPln>>>& 
			Zones() const 
		{
			return theZones_;
		}

		const std::shared_ptr<Mesh3d_SizeMap>& SizeMap() const
		{
			return theSizeMap_;
		}

		const std::shared_ptr<Mesh_SingularityZone<SurfPln>>& 
			Zone
			(
				const Standard_Integer theIndex
			) const
		{
			return theZones_[theIndex];
		}

		const std::shared_ptr<Singularity_Horizon>& Horizons() const
		{
			return theHorizons_;
		}

		const std::shared_ptr<Geo_ColoringSurfMetric>& Colors() const
		{
			return theColors_;
		}

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		void LoadHorizons(const std::shared_ptr<Singularity_Horizon>& theHorizons)
		{
			theHorizons_ = theHorizons;
		}

		void LoadColors(const std::shared_ptr<Geo_ColoringSurfMetric>& theColors)
		{
			theColors_ = theColors;
		}

		void LoadSizeMap(const std::shared_ptr<Mesh3d_SizeMap>& theSizeMap)
		{
			theSizeMap_ = theSizeMap;
		}

		void LoadInfo(const std::shared_ptr<info>& theInfo)
		{
			theInfo_ = theInfo;
		}

		void Perform(std::ostream& os = std::cout);

		void ExportToPlt(OFstream& File) const;
	};


	extern std::shared_ptr<Singularity_TypeDetectionInfo> singularity_type_detection_info;
}

#include <Singularity_TypeDetectionI.hxx>

#endif // !_Singularity_TypeDetection_Header

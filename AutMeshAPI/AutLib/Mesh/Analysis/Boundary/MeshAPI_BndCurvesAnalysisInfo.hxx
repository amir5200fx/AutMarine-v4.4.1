#pragma once
#ifndef _MeshAPI_BndCurvesAnalysisInfo_Header
#define _MeshAPI_BndCurvesAnalysisInfo_Header

#include <Standard_TypeDef.hxx>

#include <memory>
#include <map>

namespace AutLib
{

	// Forward Declarations
	class TopoMesh_PlaneBoundariesInfo;
	class SizeMap2d_FullIntSurfaceInfo;
	class MetricMap2d_ExactSurfaceLowerBoundedInfo;

	class MeshAPI_BndCurvesAnalysisInfo
	{

		/*Private Data*/

		std::shared_ptr<TopoMesh_PlaneBoundariesInfo> theGlobalPlnBndInfo_;
		std::shared_ptr<SizeMap2d_FullIntSurfaceInfo> theGlobalSizeMapInfo_;
		std::shared_ptr<MetricMap2d_ExactSurfaceLowerBoundedInfo> theGlobalMetricMapInfo_;

		std::map<Standard_Integer, std::shared_ptr<TopoMesh_PlaneBoundariesInfo>> thePlnBndInfo_;
		std::map<Standard_Integer, std::shared_ptr<SizeMap2d_FullIntSurfaceInfo>> theSizeMapInfo_;
		std::map<Standard_Integer, std::shared_ptr<MetricMap2d_ExactSurfaceLowerBoundedInfo>> theMetricMapInfo_;

		Standard_Boolean OverridePlnBnd_;
		Standard_Boolean OverrideSizeMap_;
		Standard_Boolean OverrideMetricMap_;

	public:

		MeshAPI_BndCurvesAnalysisInfo();

		Standard_Boolean OverridePlnBnd() const
		{
			return OverridePlnBnd_;
		}

		Standard_Boolean OverrideSizeMap() const
		{
			return OverrideSizeMap_;
		}

		Standard_Boolean OverrideMetricMap() const
		{
			return OverrideMetricMap_;
		}

		const std::shared_ptr<TopoMesh_PlaneBoundariesInfo>& GlobalPlnBndInfo() const
		{
			return theGlobalPlnBndInfo_;
		}

		const std::shared_ptr<SizeMap2d_FullIntSurfaceInfo>& GlobalSizeMapInfo() const
		{
			return theGlobalSizeMapInfo_;
		}

		const std::shared_ptr<MetricMap2d_ExactSurfaceLowerBoundedInfo>& GlobalMetricMapInfo() const
		{
			return theGlobalMetricMapInfo_;
		}

		const std::map<Standard_Integer, std::shared_ptr<TopoMesh_PlaneBoundariesInfo>>&
			PlnBndInfo() const
		{
			return thePlnBndInfo_;
		}

		const std::map<Standard_Integer, std::shared_ptr<SizeMap2d_FullIntSurfaceInfo>>&
			SizeMapInfo() const
		{
			return theSizeMapInfo_;
		}

		const std::map<Standard_Integer, std::shared_ptr<MetricMap2d_ExactSurfaceLowerBoundedInfo>>&
			MetricMapInfo() const
		{
			return theMetricMapInfo_;
		}

		void OverrideGlobalPlnBndInfo
		(
			const std::shared_ptr<TopoMesh_PlaneBoundariesInfo>& theInfo
		)
		{
			theGlobalPlnBndInfo_ = theInfo;
		}

		void OverrideGlobalSizeMapInfo
		(
			const std::shared_ptr<SizeMap2d_FullIntSurfaceInfo>& theInfo
		)
		{
			theGlobalSizeMapInfo_ = theInfo;
		}

		void OverrideGlobalMetricMapInfo
		(
			const std::shared_ptr<MetricMap2d_ExactSurfaceLowerBoundedInfo>& theInfo
		)
		{
			theGlobalMetricMapInfo_ = theInfo;
		}

		void OverridePlnBndInfo(const Standard_Integer, const std::shared_ptr<TopoMesh_PlaneBoundariesInfo>& theInfo);

		void OverrideSizeMapInfo(const Standard_Integer, const std::shared_ptr<SizeMap2d_FullIntSurfaceInfo>& theInfo);

		void OverrideMetricMapInfo(const Standard_Integer, const std::shared_ptr<MetricMap2d_ExactSurfaceLowerBoundedInfo>& theInfo);

		void SetToOverridePlnBnd
		(
			const Standard_Boolean theOverride
		)
		{
			OverridePlnBnd_ = theOverride;
		}

		void SetToOverrideSizeMap
		(
			const Standard_Boolean theOverride
		)
		{
			OverrideSizeMap_ = theOverride;
		}

		void SetToOverrideMetricMap
		(
			const Standard_Boolean theOverride
		)
		{
			OverrideMetricMap_ = theOverride;
		}
	};
}

#endif // !_MeshAPI_BndCurvesAnalysisInfo_Header

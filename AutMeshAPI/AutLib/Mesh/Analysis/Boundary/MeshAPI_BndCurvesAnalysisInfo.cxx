#include <MeshAPI_BndCurvesAnalysisInfo.hxx>

AutLib::MeshAPI_BndCurvesAnalysisInfo::MeshAPI_BndCurvesAnalysisInfo()
	: OverridePlnBnd_(Standard_False)
	, OverrideSizeMap_(Standard_False)
	, OverrideMetricMap_(Standard_False)
{}

void AutLib::MeshAPI_BndCurvesAnalysisInfo::OverridePlnBndInfo
(
	const Standard_Integer theIndex,
	const std::shared_ptr<TopoMesh_PlaneBoundariesInfo>& theInfo
)
{
	thePlnBndInfo_.insert(std::make_pair(theIndex, theInfo));
}

void AutLib::MeshAPI_BndCurvesAnalysisInfo::OverrideSizeMapInfo
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<SizeMap2d_FullIntSurfaceInfo>& theInfo
)
{
	theSizeMapInfo_.insert(std::make_pair(theIndex, theInfo));
}

void AutLib::MeshAPI_BndCurvesAnalysisInfo::OverrideMetricMapInfo
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<MetricMap2d_ExactSurfaceLowerBoundedInfo>& theInfo
)
{
	theMetricMapInfo_.insert(std::make_pair(theIndex, theInfo));
}
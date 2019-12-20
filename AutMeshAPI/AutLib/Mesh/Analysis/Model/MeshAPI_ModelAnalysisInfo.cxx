#include <MeshAPI_ModelAnalysisInfo.hxx>

#include <Mesh_Info.hxx>
#include <error.hxx>
#include <OSstream.hxx>

const Standard_Real AutLib::MeshAPI_ModelAnalysisInfo::DEFAULT_MIN_SIZE(0.01);

AutLib::MeshAPI_ModelAnalysisInfo::MeshAPI_ModelAnalysisInfo()
	: theMinSize_(DEFAULT_MIN_SIZE)
	, OverrideMetricApprox_(Standard_False)
	, OverrideSingDetect_(Standard_False)
{}

void AutLib::MeshAPI_ModelAnalysisInfo::SetToOverrideMetricApproxInfo()
{
	OverrideMetricApprox_ = Standard_True;
}

void AutLib::MeshAPI_ModelAnalysisInfo::SetToOverrideSingDetectInfo()
{
	OverrideSingDetect_ = Standard_True;
}

void AutLib::MeshAPI_ModelAnalysisInfo::OverrideMetricApproxInfo
(
	const Standard_Integer theIndex,
	const std::shared_ptr<metricApproxInfo>& theInfo
)
{
	theMetricApproxInfo_.insert(std::make_pair(theIndex, theInfo));
}

void AutLib::MeshAPI_ModelAnalysisInfo::OverrideSingDetectInfo
(
	const Standard_Integer theIndex,
	const std::shared_ptr<singlDetectInfo>& theInfo
)
{
	theSinglDetectInfo_.insert(std::make_pair(theIndex, theInfo));
}
#include <MeshAPI_Info_ModelAnalysis.hxx>

#include <Geo_ApprxSurfMetricInfo.hxx>
#include <Geo_PlaneEqualizer.hxx>
#include <Singularity_TypeDetectionInfo.hxx>
#include <MeshAPI_ModelAnalysisInfo.hxx>
#include <MeshAPI_Info_NormalizedMetric.hxx>
#include <MeshAPI_Info_EqualizerMetric.hxx>

std::shared_ptr<AutLib::Geo_ApprxSurfMetricInfo>
AutLib::ModelAnalLib::mesh_api_approx_surface_metric_info = std::make_shared<AutLib::Geo_ApprxSurfMetricInfo>();

std::shared_ptr<AutLib::Singularity_TypeDetectionInfo>
AutLib::ModelAnalLib::mesh_api_singularity_detec_info = std::make_shared<AutLib::Singularity_TypeDetectionInfo>();

std::shared_ptr<AutLib::MeshAPI_ModelAnalysisInfo>
AutLib::ModelAnalLib::mesh_api_model_analysis_info = std::make_shared<AutLib::MeshAPI_ModelAnalysisInfo>();

void AutLib::ModelAnalLib::meshApi_modelAnalysis_init_runTime()
{
	auto& approxInfo = *mesh_api_approx_surface_metric_info;
	approxInfo.SetDegeneracy(1.0E-6);
	approxInfo.SetMaxLevel(6);
	approxInfo.SetMinLevel(2);
	approxInfo.SetTolerance(0.2);

	auto& typeInfo = *mesh_api_singularity_detec_info;
	typeInfo.SetNbSmoothingIters(3);
	typeInfo.SetSmoothingFactor(0.25);

	auto& algInfo = *mesh_api_model_analysis_info;
	algInfo.SetMinSize(0.01);
	algInfo.OverrideGlobalMetricApproxInfo(mesh_api_approx_surface_metric_info);
	algInfo.OverrideGlobalSingDetectInfo(mesh_api_singularity_detec_info);
	algInfo.OverrideNormalizedMetricInfo(NormMetricLib::mesh_api_metric_normalization_info);
	algInfo.OverrideEqualizerMetricInfo(EqualMetricLib::mesh_api_equalizer_metric_info);
}
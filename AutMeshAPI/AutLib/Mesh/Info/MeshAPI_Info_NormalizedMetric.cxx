#include <MeshAPI_Info_NormalizedMetric.hxx>

#include <Geo_NormalizedMetricInfo.hxx>
#include <Numeric_AdaptIntegration.hxx>

std::shared_ptr<AutLib::Numeric_AdaptIntegrationInfo>
AutLib::NormMetricLib::mesh_api_normalized_metric_integration_info = std::make_shared<AutLib::Numeric_AdaptIntegrationInfo>();

std::shared_ptr<AutLib::Geo_NormalizedMetricInfo>
AutLib::NormMetricLib::mesh_api_metric_normalization_info = std::make_shared<AutLib::Geo_NormalizedMetricInfo>();

void AutLib::NormMetricLib::meshApi_normalizedMetric_init_runTime()
{
	auto& intgInfo = *mesh_api_normalized_metric_integration_info;
	intgInfo.SetMaxNbIterations(150);
	intgInfo.SetTolerance(1.0E-3);

	auto& algInfo = *mesh_api_metric_normalization_info;
	algInfo.SetNbSegmentsU(2);
	algInfo.SetNbSegmentsV(2);

	algInfo.OverrideIntgInfo(mesh_api_normalized_metric_integration_info);
}
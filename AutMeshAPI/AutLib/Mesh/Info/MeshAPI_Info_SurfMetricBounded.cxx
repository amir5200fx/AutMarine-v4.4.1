#include <MeshAPI_Info_SurfMetricBounded.hxx>

#include <MetricMap2d_ExactSurfaceLowerBoundedInfo.hxx>

std::shared_ptr<AutLib::MetricMap2d_ExactSurfaceLowerBoundedInfo>
AutLib::SurfMetricLib::mesh_api_exact_surface_metric_info = std::make_shared<AutLib::MetricMap2d_ExactSurfaceLowerBoundedInfo>();

void AutLib::SurfMetricLib::meshApi_exactSurfaceMetric_init_runTime()
{
	auto& algInfo = *mesh_api_exact_surface_metric_info;
	algInfo.SetEpsilon(1.0E-5);
}
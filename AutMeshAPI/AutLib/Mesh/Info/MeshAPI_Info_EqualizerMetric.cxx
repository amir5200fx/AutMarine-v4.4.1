#include <MeshAPI_Info_EqualizerMetric.hxx>

#include <Geo_PlaneEqualizerInfo.hxx>

std::shared_ptr<AutLib::Geo_PlaneEqualizerInfo>
AutLib::EqualMetricLib::mesh_api_equalizer_metric_info = std::make_shared<AutLib::Geo_PlaneEqualizerInfo>();

void AutLib::EqualMetricLib::meshApi_equalizerMetric_init_runTime()
{
	auto& info = *mesh_api_equalizer_metric_info;
	info.SetAR(5);
}
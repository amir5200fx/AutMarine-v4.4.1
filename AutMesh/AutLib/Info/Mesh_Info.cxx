#include <Mesh_Info.hxx>

#include <Numeric_AdaptIntegration.hxx>
#include <SizeMap2d_AnIso_OptmPoint_IterCorrectInfo.hxx>
#include <SizeMap2d_FullIntAnIsoInfo.hxx>
#include <SizeMap2d_FullIntSurfaceInfo.hxx>
#include <Geo_NormalizedMetricInfo.hxx>

std::shared_ptr<AutLib::Numeric_AdaptIntegrationInfo>
AutLib::mesh_size_map2d_full_aniso_adapt_integration_info = std::make_shared<AutLib::Numeric_AdaptIntegrationInfo>();

std::shared_ptr<AutLib::SizeMap2d_AnIso_OptmPoint_IterCorrectInfo>
AutLib::mesh_size_map2d_full_aniso_optm_point_iter_correct_info = std::make_shared<AutLib::SizeMap2d_AnIso_OptmPoint_IterCorrectInfo>();

std::shared_ptr<AutLib::SizeMap2d_FullIntAnIsoInfo>
AutLib::mesh_size_map2d_full_aniso_info = std::make_shared<AutLib::SizeMap2d_FullIntAnIsoInfo>();

std::shared_ptr<AutLib::SizeMap2d_FullIntSurfaceInfo>
AutLib::mesh_size_map2d_full_surface_info = std::make_shared<AutLib::SizeMap2d_FullIntSurfaceInfo>();

void AutLib::mesh_init_runTime()
{
	auto& anIsoIntg = *mesh_size_map2d_full_aniso_adapt_integration_info;
	anIsoIntg.SetMaxNbIterations(200);
	anIsoIntg.SetTolerance(0.005);

	auto& iterCorr = *mesh_size_map2d_full_aniso_optm_point_iter_correct_info;
	iterCorr.SetMaxNbIterations(50);
	iterCorr.SetTolerance(0.01);
	iterCorr.SetUnderRelaxation(0.9);

	auto& anIsoSizeMap = *mesh_size_map2d_full_aniso_info;
	anIsoSizeMap.SetNbSamples(3);

	auto& surfaceSizeMap = *mesh_size_map2d_full_surface_info;
	surfaceSizeMap.SetNbSamples(3);
}
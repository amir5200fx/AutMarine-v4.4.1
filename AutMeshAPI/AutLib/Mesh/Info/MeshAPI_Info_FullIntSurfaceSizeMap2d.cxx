#include <MeshAPI_Info_FullIntSurfaceSizeMap2d.hxx>

#include <SizeMap2d_Surface_OptmPoint_IterCorrectInfo.hxx>
#include <Numeric_AdaptIntegration.hxx>
#include <SizeMap2d_FullIntSurfaceInfo.hxx>

std::shared_ptr<AutLib::SizeMap2d_Surface_OptmPoint_IterCorrectInfo>
AutLib::FullIntSurfaceSizeMap2dLib::mesh_api_opt_point_iter_corr_info = std::make_shared<AutLib::SizeMap2d_Surface_OptmPoint_IterCorrectInfo>();

std::shared_ptr<AutLib::Numeric_AdaptIntegrationInfo>
AutLib::FullIntSurfaceSizeMap2dLib::mesh_api_full_intg_surface_size_map2d_integration_info = std::make_shared<AutLib::Numeric_AdaptIntegrationInfo>();

std::shared_ptr<AutLib::SizeMap2d_FullIntSurfaceInfo>
AutLib::FullIntSurfaceSizeMap2dLib::mesh_api_full_intg_surface_size_map2d_info = std::make_shared<AutLib::SizeMap2d_FullIntSurfaceInfo>();

void AutLib::FullIntSurfaceSizeMap2dLib::meshApi_fullIntSurfaceSizeMap2d_init_runTime()
{
	auto& corrInfo = *mesh_api_opt_point_iter_corr_info;
	corrInfo.SetMaxNbIterations(30);
	corrInfo.SetTolerance(1.0E-3);
	corrInfo.SetUnderRelaxation(0.85);

	auto& intgInfo = *mesh_api_full_intg_surface_size_map2d_integration_info;
	intgInfo.SetMaxNbIterations(200);
	intgInfo.SetNbInitIterations(2);
	intgInfo.SetTolerance(1.0E-4);
	
	auto& mapInfo = *mesh_api_full_intg_surface_size_map2d_info;
	mapInfo.SetNbSamples(3);

	mapInfo.OverrideAdaptIntgInfo(mesh_api_full_intg_surface_size_map2d_integration_info);
	mapInfo.OverrideIterCorrInfo(mesh_api_opt_point_iter_corr_info);
}

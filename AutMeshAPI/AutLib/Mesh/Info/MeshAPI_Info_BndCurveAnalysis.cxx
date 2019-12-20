#include <MeshAPI_Info_BndCurveAnalysis.hxx>

#include <MeshAPI_BndCurvesAnalysisInfo.hxx>
#include <MeshAPI_Info_FullIntSurfaceSizeMap2d.hxx>
#include <MeshAPI_Info_PlaneBoundary.hxx>
#include <MeshAPI_Info_SurfMetricBounded.hxx>

std::shared_ptr<AutLib::MeshAPI_BndCurvesAnalysisInfo>
AutLib::BndCrvAnalLib::mesh_api_boundary_curve_analysis_info = std::make_shared<AutLib::MeshAPI_BndCurvesAnalysisInfo>();

void AutLib::BndCrvAnalLib::meshApi_bndCurveAnalysis_init_runTime()
{
	auto& algInfo = *mesh_api_boundary_curve_analysis_info;
	algInfo.SetToOverrideSizeMap(Standard_False);
	algInfo.SetToOverridePlnBnd(Standard_False);
	algInfo.SetToOverrideMetricMap(Standard_False);

	algInfo.OverrideGlobalSizeMapInfo(FullIntSurfaceSizeMap2dLib::mesh_api_full_intg_surface_size_map2d_info);
	algInfo.OverrideGlobalPlnBndInfo(PlnBoundaryLib::mesh_api_plane_boundary_mesh_info);
	algInfo.OverrideGlobalMetricMapInfo(SurfMetricLib::mesh_api_exact_surface_metric_info);
}
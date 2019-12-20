#include <MeshAPI_Info.hxx>

#include <Numeric_AdaptIntegration.hxx>
#include <Geo_ApprxSurfMetricInfo.hxx>
#include <Geo_NormalizedMetricInfo.hxx>
#include <Singularity_TypeDetectionInfo.hxx>
#include <MeshAPI_ModelAnalysisInfo.hxx>
#include <TopoMesh_PlaneBoundariesInfo.hxx>

std::shared_ptr<AutLib::Geo_ApprxSurfMetricInfo>
AutLib::mesh_api_approx_surface_metric_info = std::make_shared<AutLib::Geo_ApprxSurfMetricInfo>();

std::shared_ptr<AutLib::Singularity_TypeDetectionInfo>
AutLib::mesh_api_singularity_detec_info = std::make_shared<AutLib::Singularity_TypeDetectionInfo>();

std::shared_ptr<AutLib::TopoMesh_PlaneBoundariesInfo>
AutLib::mesh_api_plane_boundary_info = std::make_shared<AutLib::TopoMesh_PlaneBoundariesInfo>();


void AutLib::meshApi_init_runTime()
{
	auto& metricInfo = *mesh_api_approx_surface_metric_info;
	metricInfo.SetMinLevel(2);
	metricInfo.SetMaxLevel(6);
	metricInfo.SetTolerance(0.3);
	metricInfo.SetDegeneracy(1.0E-6);
	
	auto& typeDetInfo = *mesh_api_singularity_detec_info;
	typeDetInfo.SetNbSmoothingIters(3);

	CurveMeshLib::meshApi_curveMesh_init_runTime();

	NormMetricLib::meshApi_normalizedMetric_init_runTime();

	EqualMetricLib::meshApi_equalizerMetric_init_runTime();

	ModelAnalLib::meshApi_modelAnalysis_init_runTime();

	FullIntSurfaceSizeMap2dLib::meshApi_fullIntSurfaceSizeMap2d_init_runTime();

	PlnBoundaryLib::meshApi_planeBoundaryMesh_init_runTime();

	BndCrvAnalLib::meshApi_bndCurveAnalysis_init_runTime();
	
}
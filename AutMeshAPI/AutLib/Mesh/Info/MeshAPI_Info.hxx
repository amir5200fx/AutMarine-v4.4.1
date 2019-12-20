#pragma once
#ifndef _MeshAPI_Info_Header
#define _MeshAPI_Info_Header

#include <MeshAPI_Info_CurveMesh.hxx>
#include <MeshAPI_Info_NormalizedMetric.hxx>
#include <MeshAPI_Info_ModelAnalysis.hxx>
#include <MeshAPI_Info_PlaneBoundary.hxx>
#include <MeshAPI_Info_FullIntSurfaceSizeMap2d.hxx>
#include <MeshAPI_Info_BndCurveAnalysis.hxx>
#include <MeshAPI_Info_EqualizerMetric.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class Geo_ApprxSurfMetricInfo;
	class Singularity_TypeDetectionInfo;
	class TopoMesh_PlaneBoundariesInfo;
	class Geo_NormalizedMetricInfo;
	class Numeric_AdaptIntegrationInfo;

	extern std::shared_ptr<Geo_ApprxSurfMetricInfo>
		mesh_api_approx_surface_metric_info;
	extern std::shared_ptr<Singularity_TypeDetectionInfo>
		mesh_api_singularity_detec_info;

	extern std::shared_ptr<TopoMesh_PlaneBoundariesInfo>
		mesh_api_plane_boundary_info;

	void meshApi_init_runTime();
}

#endif // !_MeshAPI_Info_Header

#pragma once
#ifndef _MeshAPI_Info_SurfMetricBounded_Header
#define _MeshAPI_Info_SurfMetricBounded_Header

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class MetricMap2d_ExactSurfaceLowerBoundedInfo;

	namespace SurfMetricLib
	{

		extern std::shared_ptr<MetricMap2d_ExactSurfaceLowerBoundedInfo> mesh_api_exact_surface_metric_info;

		void meshApi_exactSurfaceMetric_init_runTime();
	}
}

#endif // !_MeshAPI_Info_SurfMetricBounded_Header

#pragma once
#ifndef _MeshAPI_Info_ModelAnalysis_Header
#define _MeshAPI_Info_ModelAnalysis_Header

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class MeshAPI_ModelAnalysisInfo;
	class Geo_ApprxSurfMetricInfo;
	class Singularity_TypeDetectionInfo;
	class Geo_NormalizedMetricInfo;
	class Geo_PlaneEqualizerInfo;

	namespace ModelAnalLib
	{

		extern std::shared_ptr<Geo_ApprxSurfMetricInfo>
			mesh_api_approx_surface_metric_info;

		extern std::shared_ptr<Singularity_TypeDetectionInfo>
			mesh_api_singularity_detec_info;

		extern std::shared_ptr<MeshAPI_ModelAnalysisInfo>
			mesh_api_model_analysis_info;

		void meshApi_modelAnalysis_init_runTime();
	}
}

#endif // !_MeshAPI_Info_ModelAnalysis_Header

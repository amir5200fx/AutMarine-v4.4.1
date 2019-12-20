#pragma once
#ifndef _MeshAPI_Info_NormalizedMetric_Header
#define _MeshAPI_Info_NormalizedMetric_Header

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class Geo_NormalizedMetricInfo;
	class Numeric_AdaptIntegrationInfo;

	namespace NormMetricLib
	{

		extern std::shared_ptr<Numeric_AdaptIntegrationInfo>
			mesh_api_normalized_metric_integration_info;

		extern std::shared_ptr<Geo_NormalizedMetricInfo> 
			mesh_api_metric_normalization_info;

		void meshApi_normalizedMetric_init_runTime();
	}
}

#endif // !_MeshAPI_Info_NormalizedMetric_Header

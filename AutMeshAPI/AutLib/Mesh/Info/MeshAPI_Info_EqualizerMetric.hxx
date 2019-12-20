#pragma once
#ifndef _MeshAPI_Info_EqualizerMetric_Header
#define _MeshAPI_Info_EqualizerMetric_Header

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class Geo_PlaneEqualizerInfo;

	namespace EqualMetricLib
	{

		extern std::shared_ptr<Geo_PlaneEqualizerInfo>
			mesh_api_equalizer_metric_info;

		void meshApi_equalizerMetric_init_runTime();
	}
}

#endif // !_MeshAPI_Info_EqualizerMetric_Header

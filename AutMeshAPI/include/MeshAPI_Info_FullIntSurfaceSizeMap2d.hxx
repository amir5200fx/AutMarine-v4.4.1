#pragma once
#ifndef _MeshAPI_Info_FullIntSurfaceSizeMap2d_Header
#define _MeshAPI_Info_FullIntSurfaceSizeMap2d_Header

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class SizeMap2d_FullIntSurfaceInfo;
	class SizeMap2d_Surface_OptmPoint_IterCorrectInfo;
	class Numeric_AdaptIntegrationInfo;

	namespace FullIntSurfaceSizeMap2dLib
	{

		extern std::shared_ptr<SizeMap2d_Surface_OptmPoint_IterCorrectInfo> mesh_api_opt_point_iter_corr_info;
		extern std::shared_ptr<Numeric_AdaptIntegrationInfo> mesh_api_full_intg_surface_size_map2d_integration_info;

		extern std::shared_ptr<SizeMap2d_FullIntSurfaceInfo> mesh_api_full_intg_surface_size_map2d_info;

		void meshApi_fullIntSurfaceSizeMap2d_init_runTime();
	}
}

#endif // !_MeshAPI_Info_FullIntSurfaceSizeMap2d_Header


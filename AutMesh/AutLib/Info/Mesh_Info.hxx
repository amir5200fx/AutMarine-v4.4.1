#pragma once
#ifndef _Mesh_Info_Header
#define _Mesh_Info_Header

#include <memory>

namespace AutLib
{
	// Forward Declarations
	class Numeric_AdaptIntegrationInfo;
	class SizeMap2d_AnIso_OptmPoint_IterCorrectInfo;
	class SizeMap2d_FullIntAnIsoInfo;
	class SizeMap2d_FullIntSurfaceInfo;

	extern std::shared_ptr<Numeric_AdaptIntegrationInfo>
		mesh_size_map2d_full_aniso_adapt_integration_info;

	extern std::shared_ptr<SizeMap2d_AnIso_OptmPoint_IterCorrectInfo>
		mesh_size_map2d_full_aniso_optm_point_iter_correct_info;

	extern std::shared_ptr<SizeMap2d_FullIntAnIsoInfo>
		mesh_size_map2d_full_aniso_info;

	extern std::shared_ptr<SizeMap2d_FullIntSurfaceInfo>
		mesh_size_map2d_full_surface_info;

	void mesh_init_runTime();
}

#endif // !_Mesh_Info_Header

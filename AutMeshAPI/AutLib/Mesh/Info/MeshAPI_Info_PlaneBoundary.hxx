#pragma once
#ifndef _MeshAPI_Info_PlaneBoundary_Header
#define _MeshAPI_Info_PlaneBoundary_Header

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class TopoMesh_PlaneBoundariesInfo;

	namespace PlnBoundaryLib
	{

		extern std::shared_ptr<TopoMesh_PlaneBoundariesInfo>
			mesh_api_plane_boundary_mesh_info;

		void meshApi_planeBoundaryMesh_init_runTime();
	}
}

#endif // !_MeshAPI_Info_PlaneBoundary_Header

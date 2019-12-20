#pragma once
#ifndef _MeshAPI_Info_CurveMesh_Header
#define _MeshAPI_Info_CurveMesh_Header

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class Mesh_CurveInfo;
	class Numeric_AdaptIntegrationInfo;
	class Numeric_NewtonSolverInfo;
	class Mesh_CurveOptmPoint_CorrectionInfo;

	namespace CurveMeshLib
	{
		extern std::shared_ptr<Numeric_AdaptIntegrationInfo> mesh_api_curve_overall_length_integration_info;
		extern std::shared_ptr<Numeric_AdaptIntegrationInfo> mesh_api_curve_newton_integration_info;

		extern std::shared_ptr<Numeric_NewtonSolverInfo> mesh_api_curve_newton_iter_info;

		extern std::shared_ptr<Mesh_CurveOptmPoint_CorrectionInfo>
			mesh_api_curve_point_corr_info;

		extern std::shared_ptr<Mesh_CurveInfo> mesh_api_curve_mesh_info;

		void meshApi_curveMesh_init_runTime();
	}
}

#endif // !_MeshAPI_Info_CurveMesh_Header

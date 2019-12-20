#pragma once
#ifndef _MeshAPI_Info_BndCurveAnalysis_Header
#define _MeshAPI_Info_BndCurveAnalysis_Header

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class MeshAPI_BndCurvesAnalysisInfo;

	namespace BndCrvAnalLib
	{

		extern std::shared_ptr<MeshAPI_BndCurvesAnalysisInfo> mesh_api_boundary_curve_analysis_info;

		void meshApi_bndCurveAnalysis_init_runTime();
	}
}

#endif // !_MeshAPI_Info_BndCurveAnalysis_Header

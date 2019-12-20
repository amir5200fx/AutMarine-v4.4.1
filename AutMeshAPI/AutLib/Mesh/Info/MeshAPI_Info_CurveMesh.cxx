#include <MeshAPI_Info_CurveMesh.hxx>

#include <Numeric_AdaptIntegration.hxx>
#include <Numeric_NewtonSolver.hxx>
#include <Mesh_CurveOptmPoint_CorrectionInfo.hxx>
#include <Mesh_CurveInfo.hxx>

std::shared_ptr<AutLib::Numeric_AdaptIntegrationInfo>
AutLib::CurveMeshLib::mesh_api_curve_overall_length_integration_info = std::make_shared<AutLib::Numeric_AdaptIntegrationInfo>();

std::shared_ptr<AutLib::Numeric_AdaptIntegrationInfo>
AutLib::CurveMeshLib::mesh_api_curve_newton_integration_info = std::make_shared<AutLib::Numeric_AdaptIntegrationInfo>();

std::shared_ptr<AutLib::Numeric_NewtonSolverInfo>
AutLib::CurveMeshLib::mesh_api_curve_newton_iter_info = std::make_shared<AutLib::Numeric_NewtonSolverInfo>();

std::shared_ptr<AutLib::Mesh_CurveOptmPoint_CorrectionInfo>
AutLib::CurveMeshLib::mesh_api_curve_point_corr_info = std::make_shared<AutLib::Mesh_CurveOptmPoint_CorrectionInfo>();

std::shared_ptr<AutLib::Mesh_CurveInfo>
AutLib::CurveMeshLib::mesh_api_curve_mesh_info = std::make_shared<AutLib::Mesh_CurveInfo>();

void AutLib::CurveMeshLib::meshApi_curveMesh_init_runTime()
{
	auto& overallLength = *mesh_api_curve_overall_length_integration_info;
	overallLength.SetMaxNbIterations(500);
	overallLength.SetNbInitIterations(4);
	overallLength.SetTolerance(1.0E-9);

	auto& newtonIntgInfo = *mesh_api_curve_newton_integration_info;
	newtonIntgInfo.SetMaxNbIterations(100);
	newtonIntgInfo.SetNbInitIterations(2);
	newtonIntgInfo.SetTolerance(1.0E-4);

	auto& newtonInfo = *mesh_api_curve_newton_iter_info;
	newtonInfo.SetUnderRelaxation(0.85);
	newtonInfo.SetTolerance(1.0E-6);
	newtonInfo.MaxNbIterations() = 100;

	auto& corrInfo = *mesh_api_curve_point_corr_info;
	corrInfo.SetMaxLevel(10);
	corrInfo.SetTolerance(5.0E-3);
	corrInfo.SetUnderRelaxation(0.9);

	auto& algInfo = *mesh_api_curve_mesh_info;
	algInfo.SetIgnoreNonConvergency(Standard_False);
	algInfo.SetMaxLevel_LengthCalc(10);
	algInfo.SetUnderRelaxation(0.85);

	algInfo.OverrideOverallLengthIntgInfo(mesh_api_curve_overall_length_integration_info);
	algInfo.OverrideNewtonIntgInfo(mesh_api_curve_newton_integration_info);
	algInfo.OverrideNewtonIterInfo(mesh_api_curve_newton_iter_info);
	algInfo.OverrideCorrAlgInfo(mesh_api_curve_point_corr_info);
}
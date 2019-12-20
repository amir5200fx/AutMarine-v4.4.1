#include <Mesh_Curve.hxx>

#include <Mesh_CurveOptmPoint_CorrectionInfo.hxx>
#include <Numeric_AdaptIntegration.hxx>

void AutLib::Mesh_CurveBase::InitRunTime()
{
	Debug_Null_Pointer(mesh_curve_info);
	auto& info = *mesh_curve_info;

	info.SetMaxLevel_LengthCalc(10);
	info.SetIgnoreNonConvergency(Standard_False);

	auto& intgInfo = info.NewtonIntgInfo();
	intgInfo->SetTolerance(1.0E-4);
	intgInfo->SetMaxNbIterations(500);
	
	auto& iterInfo = info.NewtonIterInfo();
	iterInfo->SetUnderRelaxation(0.85);
	iterInfo->SetTolerance(1.0E-8);

	auto& corrAlg = info.CorrAlgInfo();
	corrAlg->SetUnderRelaxation(0.85);
	corrAlg->SetMaxLevel(5);
	corrAlg->SetTolerance(1.0E-3);
}
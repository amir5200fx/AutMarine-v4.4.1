#include <Examples_Mesh.hxx>

#include <Cad3d_GModel.hxx>
#include <IO_IGES.hxx>
#include <MeshAPI_gModelAnalysis.hxx>
#include <MeshAPI_Info.hxx>
#include <MeshAPI_ModelAnalysisInfo.hxx>
#include <Geo_NormalizedMetricInfo.hxx>
#include <SizeMap3d_Uniform.hxx>
#include <Mesh_Info.hxx>
#include <error.hxx>
#include <OSstream.hxx>

void AutLib::Examples_Mesh::GModel_Analysis_Case1()
{
	IO_IGES reader;
	reader.SetVerbose(1);
	reader.Parameters().Deflection = 0.1;
	reader.Parameters().Angle = 5;
	//reader.SetToDiscrete();
	reader.ReadFile("A-10 NAW.IGS");

	fileName myFileName("Example_GModel_Analysis_Case1.plt");
	OFstream myFile(myFileName);

	auto shape = reader.Shape();

	auto model = Cad3d_GModel::GModel(shape);

	auto sizeMap = std::make_shared<SizeMap3d_Uniform>(8.0);
	sizeMap->Make();

	AutLib::meshApi_init_runTime();

	auto analysis = std::make_shared<MeshAPI_gModelAnalysis>(ModelAnalLib::mesh_api_model_analysis_info);
	analysis->LoadModel(model);
	analysis->LoadSizeMap(sizeMap);

	analysis->SetVerbisity(1);
	analysis->Perform(cout);

	analysis->Report(cout);

}
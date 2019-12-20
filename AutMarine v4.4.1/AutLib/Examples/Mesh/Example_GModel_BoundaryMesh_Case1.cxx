#include <Examples_Mesh.hxx>

#include <Cad3d_GModel.hxx>
#include <IO_IGES.hxx>
#include <MeshAPI_gModelAnalysis.hxx>
#include <MeshAPI_Info.hxx>
#include <Geo_NormalizedMetricInfo.hxx>
#include <MeshAPI_gCurveMesh.hxx>
#include <MeshAPI_gBndCurvesAnalysis.hxx>
#include <SizeMap3d_Uniform.hxx>
#include <Mesh_Info.hxx>
#include <error.hxx>
#include <OSstream.hxx>
#include <Aft2d_CoreAnIso.hxx>
#include <memory>

namespace AutLib
{
	
}

void AutLib::Examples_Mesh::GModel_BoundaryMesh_Case1()
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

	//auto surface = model->Surfaces()[13];
	auto surface = model->Surfaces()[0];
	std::vector<std::shared_ptr<GModel_Surface>> surfaces(1);
	surfaces[0] = surface;

	auto model0 = std::make_shared<Cad3d_GModel>(surfaces);

	auto sizeMap = std::make_shared<SizeMap3d_Uniform>(16.0);
	sizeMap->Make();

	AutLib::meshApi_init_runTime();

	
	auto analysis = std::make_shared<MeshAPI_gModelAnalysis>(ModelAnalLib::mesh_api_model_analysis_info);
	Debug_Null_Pointer(analysis);

	analysis->LoadModel(model);
	analysis->LoadSizeMap(sizeMap);

	analysis->SetVerbisity(1);
	analysis->Perform(cout);

	analysis->Report(cout);
	
	auto bndMesh = 
		std::make_shared<MeshAPI_gCurveMesh>(BndCrvAnalLib::mesh_api_boundary_curve_analysis_info);
	Debug_Null_Pointer(bndMesh);

	bndMesh->SetVerbisity(1);
	bndMesh->LoadAnalysis(analysis);
	bndMesh->Perform(cout);

	const auto& mesh = bndMesh->Mesh();

	for (const auto& x : mesh)
	{
		const auto& m = x.second;
		m->Mesh()->StaticData()->ExportToPlt(myFile);
	}
}
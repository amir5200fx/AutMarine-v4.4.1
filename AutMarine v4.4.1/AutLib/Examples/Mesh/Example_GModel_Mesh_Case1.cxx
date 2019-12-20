#include <Examples_Mesh.hxx>

#include <Cad3d_GModel.hxx>
#include <Mesh_CadTools.hxx>
#include <IO_IGES.hxx>
#include <IO_STEP.hxx>
#include <MeshAPI_gModelAnalysis.hxx>
#include <MeshAPI_Info.hxx>
#include <Geo_NormalizedMetricInfo.hxx>
#include <ImpSurf_defect.hxx>
#include <Mesh_CurveInfo.hxx>
#include <Mesh_CurveOptmPoint_CorrectionInfo.hxx>
#include <MeshAPI_gCurveMesh.hxx>
#include <MeshAPI_gBndCurvesAnalysis.hxx>
#include <MeshAPI_gModel.hxx>
#include <MeshAPI_Info_Model.hxx>
#include <Numeric_NewtonSolver.hxx>
#include <SizeMap3d_Uniform.hxx>
#include <Mesh_Info.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <memory>
#include <chrono>

void AutLib::Examples_Mesh::GModel_Mesh_Case1()
{
	IO_IGES reader;
	reader.SetVerbose(1);
	reader.Parameters().Deflection = 0.1;
	reader.Parameters().Angle = 5;
	//reader.SetToDiscrete();
	//reader.ReadFile("SailBoat.IGS");
	//reader.ReadFile("Engine Issue 1-0 STEP AP214.STEP");
	reader.ReadFile("SailBoat.IGS");

	fileName myFileName("Example_GModel_Mesh_Case1.plt");
	OFstream myFile(myFileName);

	fileName myFileNameb("Example_GModel_Mesh_Case1b.plt");
	OFstream myFileb(myFileNameb);

	auto shape = reader.Shape();

	auto model = Cad3d_GModel::GModel(shape);

	//auto surface = model->Surfaces()[247];
	//auto surface = model->Surfaces()[12331];
	//auto surface = model->Surfaces()[6297];
	//auto surface = model->Surfaces()[64];
	//auto surface = model->Surfaces()[825];
	auto surface = model->Surfaces()[48];
	std::vector<std::shared_ptr<GModel_Surface>> surfaces(1);
	surfaces[0] = surface;


	//surface->ExportCurvesFromPlaneToPlt(myFileb);
	//Mesh_CadTools::ConvertToBSpline(*surface)->ExportCurvesFromPlaneToPlt(myFileb);

	auto model0 = std::make_shared<Cad3d_GModel>(surfaces);

	//auto sizeMap = std::make_shared<SizeMap3d_Uniform>(90.0);
	auto sizeMap = std::make_shared<SizeMap3d_Uniform>(200);
	sizeMap->Make();

	AutLib::meshApi_init_runTime();

	auto analysis = std::make_shared<MeshAPI_gModelAnalysis>(ModelAnalLib::mesh_api_model_analysis_info);
	Debug_Null_Pointer(analysis);


	analysis->LoadModel(model);
	analysis->LoadSizeMap(sizeMap);

	//analysis->SetVerbisity(2);
	analysis->Perform(cout);

	analysis->Report(cout);
	//return;
	const auto& defects = analysis->Defects();
	for (const auto& x : defects)
	{
		auto def = std::dynamic_pointer_cast<ImpSurf_defect<GModel_Surface>>(x.second);
		Debug_Null_Pointer(def);

		cout << "surface nb. " << x.first << ", deficiency type: " << def->TypeName() << std::endl;
	}
	PAUSE;

	auto bndMesh =
		std::make_shared<MeshAPI_gCurveMesh>(BndCrvAnalLib::mesh_api_boundary_curve_analysis_info);
	Debug_Null_Pointer(bndMesh);

	bndMesh->SetVerbisity(1);
	bndMesh->LoadAnalysis(analysis);
	bndMesh->Perform(cout);

	const auto& bmesh = bndMesh->Mesh();

	for (const auto& x : bmesh)
	{
		const auto& m = x.second;
		m->Mesh()->StaticData()->ExportToPlt(myFileb);
		//m->Mesh3D()->ExportToPlt(myFile);
	}
	//return;
	ModelLib::mesh_api_model_info->SetVerbisity(1);

	

	auto mesher = std::make_shared<MeshAPI_gModel>(ModelLib::mesh_api_model_info);
	Debug_Null_Pointer(mesher);

	mesher->LoadCurveMesh(bndMesh);

	auto sTime = std::chrono::high_resolution_clock::now();

	mesher->Perform();

	auto eTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = eTime - sTime;
	cout << "Time = " << duration.count() << std::endl;
	
	mesher->CreateMesh3D();

	const auto& mesh = mesher->Mesh3D();
	for (const auto& x : mesh)
	{
		const auto& m = x.second;
		m->ExportToPlt(myFile);
	}
	
	const auto& pmesh = mesher->Mesh();
	Standard_Integer nbElements = 0;
	for (const auto& x : pmesh)
	{
		const auto& m = x.second;
		auto sMesh = m->StaticMesh();
		sMesh->ExportToPlt(myFileb);
		nbElements += sMesh->NbConnectivity();
	}

	cout << "nb elements = " << nbElements << std::endl;
	PAUSE;
}
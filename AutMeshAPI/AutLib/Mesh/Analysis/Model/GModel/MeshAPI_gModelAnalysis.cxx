#include <MeshAPI_gModelAnalysis.hxx>

#include <Singularity_TypeDetection.hxx>
#include <Cad3d_GModel.hxx>
#include <GModel_Wire.hxx>
#include <GModel_Surface.hxx>
#include <ImpSurf_defWire_Order.hxx>
#include <ImpSurf_defWire_Open.hxx>
#include <ImpSurf_defWire_Intersect.hxx>
#include <SingSurf_Common.hxx>
#include <SingSurf_General.hxx>
#include <Geo_ApprxSurfMetric.hxx>
#include <Geo_ColoringSurfMetric.hxx>
#include <Geo_NormalizedMetric.hxx>
#include <Geo_PlaneEqualizer.hxx>
#include <Geo_PlaneNurbs.hxx>
#include <GeoMesh2d_MetricBackground.hxx>
#include <Singularity_Horizon.hxx>
#include <Singularity_TypeDetection.hxx>
#include <Singularity_TypeDetectionInfo.hxx>
#include <SingularityZone_Pole_WholeSide.hxx>
#include <SingSurf_Common.hxx>
#include <SingSurf_General.hxx>
#include <Mesh2d_gSurfPlane.hxx>
#include <Mesh2d_gPlnCurve.hxx>
#include <MeshAPI_ModelAnalysisInfo.hxx>

#include <Geom_Surface.hxx>

namespace AutLib
{
	static Standard_Boolean 
		CheckRegulars
		(
			const Singularity_TypeDetection<Mesh2d_gSurfPlane>& detection
		)
	{
		if (NOT detection.NbZones())
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "the singular surface has no singularity zone!" << endl
				<< abort(FatalError);
		}

		const auto& zones = detection.Zones();
		for (const auto& x : zones)
		{
			Debug_Null_Pointer(x);
			if (NOT std::dynamic_pointer_cast<SingularityZone_Pole_WholeSide<Mesh2d_gSurfPlane>>(x))
			{
				return Standard_True;
			}
		}
		return Standard_False;
	}
}

template<>
void AutLib::MeshAPI_ModelAnalysis
<
	AutLib::MeshAPI_gBndCurvesAnalysis
>::Perform
(
	std::ostream& os
)
{
	if (NOT Model())
	{
		FatalErrorIn("void MeshAPI_ModelAnalysis::Perform()") << endl
			<< "Found no model" << endl
			<< abort(FatalError);
	}

	if (Verbose())
	{
		os << " @ void MeshAPI_ModelAnalysis: " << std::endl;
		os << " @ void MeshAPI_ModelAnalysis::Perform(std::ostream& os = std::cout):" << std::endl;
		os << " - VERBOSITY LEVEL = " << Verbose() << std::endl;
	}

	const auto& sizeMap = SizeMap();
	const auto& model = *Model();

	const auto& surfaces = model.Surfaces();

	auto normSurfMetric = 
		std::make_shared<Geo_NormalizedMetric<GModel_Surface>>(Info()->NormalizedMetricInfo());

	for (const auto& isurface : surfaces)
	{
		auto x = isurface;
		Debug_Null_Pointer(x);

		Debug_Null_Pointer(Info());

		/*auto convertor = std::make_shared<Geo_PlaneNurbs<GModel_Surface>>();
		Debug_Null_Pointer(convertor);

		convertor->LoadSurface(x);
		convertor->Perform();

		x = convertor->Modified();

		Debug_Null_Pointer(Info()->EqualizerMetricInfo());

		auto equalMetric = std::make_shared<Geo_PlaneEqualizer<GModel_Surface>>(Info()->EqualizerMetricInfo());
		Debug_Null_Pointer(equalMetric);

		equalMetric->LoadSurface(x);
		equalMetric->Perform(os);
		Debug_If_Condition_Message(NOT equalMetric->IsDone(), " the metric equalizer has not been performed!");

		if (equalMetric->IsApplied())
		{
			x = equalMetric->Modified();
		}*/

		/*fileName myFileName1("test1.plt");
		OFstream myFile1(myFileName1);
		x->ExportCurvesFromPlaneToPlt(myFile1);*/
		//cout << "surface nb. " << x->Index() << std::endl;
		if (Verbose())
		{
			os << " Checking surface nb. " << x->Index() << ";" << std::endl;
			os << "   - surface's Name: " << x->Name() << std::endl;
			os << std::endl;
		}

		if (Verbose())
		{
			os << "  Checking for wire order..." << std::endl;
			os << std::endl;
		}

		std::vector<std::shared_ptr<GModel_Wire>> wires;
		if (ImpSurf_defWire_Order<GModel_Surface>::Check(*x, wires))
		{

			if (Verbose())
			{
				os << "  defect wire has been detected: WIRE ORDER" << std::endl;
				os << "  ****the surface is registered as DEFECTED!****" << std::endl;
				os << "  continue..." << std::endl;
				os << std::endl;
			}

			theDefects_.insert
			(
				std::make_pair
				(
					x->Index(),
					std::make_shared<ImpSurf_defWire_Order<GModel_Surface>>
					(
						x->Geometry(),
						x->OuterWire(),
						x->InnerWires(), wires)));

			continue;
		}

		if (Verbose())
		{
			os << "  Checking for wire opening..." << std::endl;
			os << std::endl;
		}

		if (ImpSurf_defWire_Open<GModel_Surface>::Check(*x, wires, 1.0E-4))
		{

			if (Verbose())
			{
				os << "  defect wire has been detected: WIRE OPEN" << std::endl;
				os << "  ****the surface is registered as DEFECTED!****" << std::endl;
				os << "  continue..." << std::endl;
				os << std::endl;
			}

			theDefects_.insert
			(
				std::make_pair
				(
					x->Index(),
					std::make_shared<ImpSurf_defWire_Open<GModel_Surface>>
					(
						x->Geometry(),
						x->OuterWire(),
						x->InnerWires(), wires)));

			continue;
		}

		if (Verbose())
		{
			os << "  Checking for wire intersecting..." << std::endl;
			os << std::endl;
		}

		if (ImpSurf_defWire_Intersect<GModel_Surface>::Check(*x, 1.0E-4))
		{
			if (Verbose())
			{
				os << "  defect wire has been detected: WIRE INTERSECT" << std::endl;
				os << "  ****the surface is registered as DEFECTED****" << std::endl;
				os << "  continue..." << std::endl;
				os << std::endl;
			}

			theDefects_.insert
			(
				std::make_pair
				(
					x->Index(),
					std::make_shared<ImpSurf_defWire_Intersect<GModel_Surface>>
					(
						x->Geometry(),
						x->OuterWire(), x->InnerWires())));

			continue;
		}

		if (Verbose())
		{
			os << "  the surface has not any kind of deficiency!" << std::endl;
			os << "  continue to detect any kind of singularity..." << std::endl;
			os << std::endl;
		}

		auto approxInfo = Info()->GlobalMetricApproxInfo();
		Debug_Null_Pointer(approxInfo);

		if (Info()->OverrideMetricApproxInfo())
		{
			const auto& appMap = Info()->MetricApproxInfo();
			auto iter = appMap.find(x->Index());

			if (iter NOT_EQUAL appMap.end())
			{
				approxInfo = iter->second;
			}
		}

		if (Verbose())
		{
			os << "  - Overriding metric approximation settings? " << (Info()->OverrideMetricApproxInfo() ? "YES" : "NO") << std::endl;
			os << "  - Min Level: " << approxInfo->MinLevel() << std::endl;
			os << "  - Max Level: " << approxInfo->MaxLevel() << std::endl;
			os << "  - Tolerance: " << approxInfo->Tolerance() << std::endl;
			os << "  - Degeneracy: " << approxInfo->Degeneracy() << std::endl;
		}

		auto approx = 
			std::make_shared<Geo_ApprxSurfMetric>(x->Geometry(), x->BoundingBox(), approxInfo);
		Debug_Null_Pointer(approx);

		approx->SetTrackMaxDeterminant(Standard_True);

		if (Verbose())
		{
			os << "  Processing to make an approximation of the surface metric..." << std::endl;
		}

		approx->Perform();
		Debug_If_Condition_Message
		(
			NOT approx->IsDone(),
			"the Geo_ApprxSurfaceMetric has not been performed!");
		/*cout << "max = " << approx->Info()->MaxDeterminant() << std::endl;
		PAUSE;
		fileName myFileName1("test1.plt");
		OFstream myFile1(myFileName1);
		approx->Approx()->ExportToPlt(myFile1);*/
		if (Verbose())
		{
			os << "  making an approximation of the surface metric is done!" << std::endl;
			os << "  checking for normalizing the metric..." << std::endl;
			//os << "  Proceeding to detect the horizons of singularities..." << std::endl;
		}

		

		Debug_Null_Pointer(Info()->NormalizedMetricInfo());

		//auto normalizedMetric = 
		//	std::make_shared<Geo_NormalizedMetric<GModel_Surface>>
		//	(
		//		Info()->NormalizedMetricInfo()
		//		);
		//Debug_Null_Pointer(normalizedMetric);

		//normalizedMetric->LoadApprox(approx);
		//normalizedMetric->LoadSurface(x);

		//normalizedMetric->SetVerbisity(MAX(0, Verbose() - 1));
		//normalizedMetric->Perform(os);
		//Debug_If_Condition_Message
		//(
		//	NOT normalizedMetric->IsDone(),
		//	"the normalizing metric surface has not been performed!");

		//if (normalizedMetric->Applied())
		//{
		//	x = normalizedMetric->Normalized();

		//	if (Verbose())
		//	{
		//		os << "  remaking an approximation of the surface metric!" << std::endl;
		//	}

		//	approx =
		//		std::make_shared<Geo_ApprxSurfMetric>(x->Geometry(), x->BoundingBox(), approxInfo);
		//	Debug_Null_Pointer(approx);

		//	approx->SetTrackMaxDeterminant(Standard_True);

		//	approx->Perform();
		//	Debug_If_Condition_Message
		//	(
		//		NOT approx->IsDone(),
		//		"the Geo_ApprxSurfaceMetric has not been performed!");

		//	if (Verbose())
		//	{
		//		os << "  remaking an approximation of the surface metric is done!" << std::endl;
		//		os << "  maximum metric determinant of the surface: "<< approx->Info()->MaxDeterminant() << std::endl;
		//		//os << "  Proceeding to detect the horizons of singularities..." << std::endl;
		//	}
		//}

		if (Verbose())
		{
			os << "  Proceeding to detect the horizons of singularities..." << std::endl;
		}

		auto horizons =
			std::make_shared<Singularity_Horizon>(approx);

		horizons->Perform();
		Debug_If_Condition_Message
		(
			NOT horizons->IsDone(),
			"the SurfMetric_SingularityHorizon has not been performed!");

		if (Verbose())
		{
			os << "  detecting of horizons has been completed!" << std::endl;
			os << "  - Has been any horizons detected? " << (horizons->HasHorizon() ? "YES" : "NO") << std::endl;
			if (horizons->HasHorizon())
			{
				os << "  - Nb. of horizons: " << horizons->NbHorizons() << std::endl;
			}
		}

		if (NOT horizons->HasHorizon())
		{

			if (Verbose())
			{
				os << "  ****registering the surface as a perfection one!****" << std::endl;
				os << "  continue..." << std::endl;
			}

			theRegulars_.insert
			(
				std::make_pair
				(
					x->Index(), 
					std::make_shared<Mesh_SurfaceTemplate<GModel_Surface>>
					(
						x->Geometry(),
						x->OuterWire(), x->InnerWires())));

			continue;
		}
		else if (horizons->HasHorizon())
		{
			if (Verbose())
			{
				os << "  Coloring algorithm has been called!" << std::endl;
			}

			auto colors = 
				std::make_shared<Geo_ColoringSurfMetric>(approx);

			colors->Perform();
			Debug_If_Condition_Message(NOT colors->IsDone(), "the color algorithm has not been performed");

			const auto& edges = *x->OuterWire()->Edges();

			/*fileName myFileName("test.plt");
			OFstream myFile(myFileName);
			colors->ExportColorsToPlt(myFile);*/
			if (Verbose())
			{
				os << "  Coloring the regions has been finished" << std::endl;
				os << "  Proceeding to detect the type of singularities..." << std::endl;
			}

			Debug_Null_Pointer(Info());
			Debug_Null_Pointer(Info()->GlobalSinglDetectInfo());

			auto typeDetecInfo = Info()->GlobalSinglDetectInfo();
			if (Info()->OverrideSingDetectInfo())
			{
				const auto& typeMap = Info()->SinglDetectInfo();
				auto iter = typeMap.find(x->Index());

				if (iter IS_EQUAL typeMap.end())
				{
					typeDetecInfo = iter->second;
				}
			}

			if (Verbose())
			{
				os << "  - Overriding settings? " << (Info()->OverrideSingDetectInfo() ? "YES" : "NO") << std::endl;
				os << "  - Nb. of iterations: " << typeDetecInfo->NbIters() << std::endl;
				os << "  - Omega: " << typeDetecInfo->Omega() << std::endl;
			}

			auto detection = 
				std::make_shared<Singularity_TypeDetection<Mesh2d_gSurfPlane>>
				(
					horizons, colors, 
					sizeMap, typeDetecInfo);

			if (Verbose())
			{
				detection->SetVerbisity(MAX(0, Verbose() - 1));
			}
			
			detection->Perform(os);
			Debug_If_Condition_Message(NOT detection->IsDone(), "the type detection algorithm has not been performed");

			if (Verbose())
			{
				os << "  type detection has been performed successfully! " << std::endl;
			}

			if (CheckRegulars(*detection))
			{
				theCommonSingularities_.insert
				(
					std::make_pair(x->Index(), 
						std::make_shared<SingSurf_General<Mesh2d_gSurfPlane>>
						(
							x->Geometry(), 
							x->OuterWire(),
							x->InnerWires(), detection))
				);
			}
			else
			{
				theCommonSingularities_.insert
				(
					std::make_pair(x->Index(),
						std::make_shared<SingSurf_Common<Mesh2d_gSurfPlane>>
						(
							x->Geometry(),
							x->OuterWire(),
							x->InnerWires(), detection))
				);
			}
		}
	}

	if (Verbose())
	{
		Report(os);
	}

	Change_IsDone() = Standard_True;
}
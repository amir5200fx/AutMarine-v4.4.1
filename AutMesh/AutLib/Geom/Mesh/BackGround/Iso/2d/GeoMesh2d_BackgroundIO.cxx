#include <GeoMesh2d_Background.hxx>

#include <Entity2d_Triangulation.hxx>
#include <TecPlot.hxx>

namespace AutLib
{

	template<>
	void GeoMesh2d_Background::ExportToPlt(OFstream & File) const
	{
		if (NOT theSources_)
		{
			FatalErrorIn("void GeoMesh2d_MetricBackground::ExportMetricDeterminantToPlt()")
				<< "Found no metric sources" << endl
				<< abort(FatalError);
		}
		const auto& sources = *theSources_;
		std::vector<multiValued::real_1> var;
		var.reserve(sources.size());

		for (auto x : sources)
		{
			multiValued::real_1 v;
			v.Value(0) = x;
			var.push_back(std::move(v));
		}

		const auto& staticData = this->Mesh();
		const auto triangulation = staticData->StaticData();

		Io::ExportField
		(
			"Source",
			var,
			triangulation->Points(),
			triangulation->Connectivity(),
			File
		);
	}
}
#include <Geo_ColoringSurfMetric.hxx>

#include <Entity2d_Triangulation.hxx>
#include <Geo_ApprxSurfMetric.hxx>
#include <GeoMesh2d_MetricBackground.hxx>
#include <OFstream.hxx>
#include <TecPlot.hxx>

void AutLib::Geo_ColoringSurfMetric::ExportColorsToPlt
(
	OFstream & File
) const
{
	if (NOT IsDone())
		return;

	std::vector<multiValued::real_1> var;
	var.reserve(theElements_.size());

	for (const auto& x : theElements_)
	{
		multiValued::real_1 v;
		v.Value(0) = (Standard_Real)x.second;
		var.push_back(std::move(v));
	}

	const auto& staticData = theApprox_->Approx()->Mesh();
	const auto& triangulation = staticData->StaticData();

	//staticData->Triangulation()->ExportToPlt(File);

	Io::ExportCellCenteredField
	(
		"Color",
		var,
		triangulation->Points(),
		triangulation->Connectivity(),
		File
	);
}
#include <GModel_Wire.hxx>

#include <GModel_Edge.hxx>
#include <GModel_parCurve.hxx>
#include <TecPlot.hxx>

void AutLib::GModel_Wire::ExportPlaneCurvesToPlt(OFstream & File) const
{
	Debug_Null_Pointer(Edges());
	const auto& edges = *Edges();

	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);

		const auto& pcurve = x->Par();
		Debug_Null_Pointer(pcurve);

		pcurve->ExportToPlt(File);
	}
}
#include <GModel_parCurve.hxx>

#include <Cad_CurveInfo.hxx>
#include <TecPlot_Opencascade.hxx>

#include <Geom2d_Curve.hxx>

void AutLib::GModel_parCurve::ExportToPlt(OFstream & File) const
{
	if (Curve().IsNull())
	{
		FatalErrorIn("void AutLib::Pln_Curve::ExportToPlt(OFstream & File) const")
			<< "Null curve encountered!"
			<< abort(FatalError);
	}

	Io::ExportCurve
	(
		*Curve(), FirstParam(),
		LastParam(), theInfo_->NbDivisions(), File);
}
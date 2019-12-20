#include <GModel_Surface.hxx>

#include <Pnt3d.hxx>
#include <GModel_Wire.hxx>
#include <GModel_Edge.hxx>
#include <GModel_parCurve.hxx>
#include <Cad_CurveInfo.hxx>
#include <TecPlot.hxx>

void AutLib::GModel_Surface::ExportPlaneCurvesToPlt(OFstream & File) const
{
	Debug_Null_Pointer(OuterWire());
	const auto& outerWie = *OuterWire();

	outerWie.ExportPlaneCurvesToPlt(File);

	if (HasHole())
	{
		for (const auto& x : *InnerWires())
		{
			Debug_Null_Pointer(x);
			x->ExportPlaneCurvesToPlt(File);
		}
	}
}

namespace AutLib
{

	std::vector<Pnt3d> Discretize(const GModel_parCurve& theCurve, const GModel_Surface& theSurface, const Standard_Integer n)
	{
		const auto du = (theCurve.LastParam() - theCurve.FirstParam()) / ((Standard_Real)n);

		std::vector<Pnt3d> pts;
		pts.reserve(n + 1);
		forThose(Index, 0, n)
		{
			auto u = theCurve.FirstParam() + Index * du;
			pts.push_back(theSurface.Value(theCurve.Value(u)));
		}
		return std::move(pts);
	}


}

void AutLib::GModel_Surface::ExportCurvesFromPlaneToPlt(OFstream & File) const
{
	Debug_Null_Pointer(OuterWire());
	const auto& outerWie = *OuterWire();

	for (const auto& x : *outerWie.Edges())
	{
		Debug_Null_Pointer(x);
		auto pts = Discretize(*x->Par(), *this, x->Par()->Info()->NbDivisions());

		Io::ExportCurve(pts, File);
	}

	if (HasHole())
	{
		for (const auto& wire : *InnerWires())
		{
			Debug_Null_Pointer(wire);

			for (const auto& x : *wire->Edges())
			{
				Debug_Null_Pointer(x);
				auto pts = Discretize(*x->Par(), *this, x->Par()->Info()->NbDivisions());

				Io::ExportCurve(pts, File);
			}
		}
	}
}
#include <GModel_parWire.hxx>

#include <Entity2d_Box.hxx>
#include <GModel_parCurve.hxx>

AutLib::Entity2d_Box
AutLib::GModel_parWire::CalcParametricBoundingBox() const
{
	const auto& curves = Curves();

	auto box = curves[0]->BoundingBox();
	forThose(Index, 1, curves.size() - 1)
	{
		box = Entity2d_Box::Union(box, curves[Index]->BoundingBox());
	}
	return std::move(box);
}

std::vector<std::shared_ptr<AutLib::GModel_parCurve>>
AutLib::GModel_parWire::RetrieveCurvesFrom
(
	const std::vector<std::shared_ptr<GModel_parWire>>& theWires
)
{
	std::vector<std::shared_ptr<AutLib::GModel_parCurve>> merged;
	Standard_Integer nbcurves = 0;
	for (const auto& x : theWires)
	{
		Debug_Null_Pointer(x);
		nbcurves += x->NbCurves();
	}

	for (const auto& x : theWires)
	{
		Debug_Null_Pointer(x);

		const auto curves = x->Curves();

		for (const auto& icurve : curves)
		{
			Debug_Null_Pointer(icurve);
			merged.push_back(icurve);
		}
	}
	return std::move(merged);
}
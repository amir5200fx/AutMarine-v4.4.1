#include <GModel_Edge.hxx>

#include <GModel_parCurve.hxx>

#include <gp_Trsf2d.hxx>

std::shared_ptr<AutLib::GModel_Edge> 
AutLib::GModel_Edge::ReParameterization
(
	const GModel_Edge & theEdge, 
	const gp_Trsf2d & trans
)
{
	auto edge = std::make_shared<GModel_Edge>
		(
			theEdge.Index(),
			GModel_parCurve::Copy(*theEdge.Par(), trans),
			theEdge.Curve());
	return std::move(edge);
}

std::shared_ptr<AutLib::GModel_Edge>
AutLib::GModel_Edge::BSplinePlaneEdge
(
	const std::shared_ptr<GModel_Edge>& theEdge
)
{
	auto par = GModel_parCurve::ToBSpline(theEdge->Par());
	if (par IS_EQUAL theEdge->Par())
	{
		return theEdge;
	}

	auto edge = std::make_shared<GModel_Edge>
		(
			theEdge->Index(),
			par,
			theEdge->Curve());
	return std::move(edge);
}

std::shared_ptr<AutLib::GModel_Edge> 
AutLib::GModel_Edge::uPlaneExpand
(
	const GModel_Edge & theEdge,
	const Standard_Real multiply
)
{
	auto par = GModel_parCurve::uExpand(*theEdge.Par(), multiply);
	auto edge = std::make_shared<GModel_Edge>
		(
			theEdge.Index(),
			par,
			theEdge.Curve());
	return std::move(edge);
}

std::shared_ptr<AutLib::GModel_Edge>
AutLib::GModel_Edge::vPlaneExpand
(
	const GModel_Edge & theEdge,
	const Standard_Real multiply
)
{
	auto par = GModel_parCurve::vExpand(*theEdge.Par(), multiply);
	auto edge = std::make_shared<GModel_Edge>
		(
			theEdge.Index(),
			par,
			theEdge.Curve());
	return std::move(edge);
}
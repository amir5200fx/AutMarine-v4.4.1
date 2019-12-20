#include <Model_PlnSegment.hxx>

#include <Entity2d_Chain.hxx>
#include <Pln_Curve.hxx>

#include <Geom2dAPI_ProjectPointOnCurve.hxx>
#include <Geom2d_Line.hxx>

void AutLib::Model_PlnSegment::SetSystem
(
	const gp_Ax22d & theSystem
)
{
	ChangeSystem() = theSystem;

	Make();
}

AutLib::Model_PlnSegment::Model_PlnSegment
(
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	auto length = Distance(theP0, theP1);

	if (length < gp::Resolution())
	{
		FatalErrorIn("Model_PlnSegment(const Pnt2d& theP0, const Pnt2d& theP1)")
			<< "Null segment" << endl
			<< abort(FatalError);
	}

	gp_Vec2d vt(theP0, theP1);
	gp_Ax22d sys(theP0, vt);

	ChangeSystem() = sys;
	SetLength(length);
}

std::shared_ptr<AutLib::Pln_Curve>
AutLib::Model_PlnSegment::operator()
(
	const Pnt2d & theP0,
	const Pnt2d & theP1
	)
{
	Model_PlnSegment l(theP0, theP1);
	return l.Curve();
}

std::shared_ptr<AutLib::Pln_Curve> 
AutLib::Model_PlnSegment::operator()
(
	const Standard_Real theLength
	)
{
	Model_PlnSegment l(theLength);
	return l.Curve();
}

gp_Pnt2d 
AutLib::Model_PlnSegment::CalcP1() const
{
	const auto& pt = P0();
	const auto& dir = Axis().Direction();
	return gp_Pnt2d(pt.X() + dir.X()*Length(), pt.Y() + dir.Y()*Length());
}

void AutLib::Model_PlnSegment::Make()
{
	const auto& P0 = System().Location();
	const auto vec = Length()*System().XDirection();
	auto P1 = gp_Pnt2d(P0.X() + vec.X(), P0.Y() + vec.Y());

	Handle(Geom2d_Line) geom = new Geom2d_Line(System().XAxis());

	Geom2dAPI_ProjectPointOnCurve Projection;

	Projection.Init(P0, geom);
	auto first = Projection.LowerDistanceParameter();

	Projection.Init(P1, geom);
	auto last = Projection.LowerDistanceParameter();

	ChangeCurve() = std::make_shared<Pln_Curve>(first, last, geom);
}

void AutLib::Model_PlnSegment::Discrete()
{
	auto chain = std::make_shared<Entity2d_Chain>();

	auto& Pts = chain->Points();
	auto& Indices = chain->Connectivity();

	Pts.resize(2);
	Indices.resize(1);

	Pts[0] = P0();
	Pts[1] = CalcP1();

	Indices[0].Value(0) = 1;
	Indices[0].Value(1) = 2;

	SetMesh(chain);
}
#include <Singularity_TypeDetection.hxx>

std::vector<std::shared_ptr<AutLib::Pln_Curve>> 
AutLib::SingularityTools::RetrieveSides
(
	const Entity2d_Box & theBox
)
{
	Model_PlnSegment LineSegMaker;

	std::vector<std::shared_ptr<Pln_Curve>> curves(4);
	curves[0] = LineSegMaker(theBox.P0(), theBox.Corner(Box2d_PickAlgorithm_SE));
	curves[1] = LineSegMaker(theBox.Corner(Box2d_PickAlgorithm_SE), theBox.P1());
	curves[2] = LineSegMaker(theBox.P1(), theBox.Corner(Box2d_PickAlgorithm_NW));
	curves[3] = LineSegMaker(theBox.Corner(Box2d_PickAlgorithm_NW), theBox.P0());

	return std::move(curves);
}

std::shared_ptr<AutLib::Entity2d_Triangulation> 
AutLib::SingularityTools::GetTriangulation(const Entity2d_Box & theBox)
{
	auto P0 = theBox.P0();
	auto P1 = theBox.Corner(Box2d_PickAlgorithm_SE);
	auto P2 = theBox.P1();
	auto P3 = theBox.Corner(Box2d_PickAlgorithm_NW);

	auto Pm = theBox.CalcCentre();

	auto triangulation = std::make_shared<Entity2d_Triangulation>();
	auto& pts = triangulation->Points();

	pts.reserve(5);
	pts.push_back(std::move(P0));
	pts.push_back(std::move(P1));
	pts.push_back(std::move(P2));
	pts.push_back(std::move(P3));
	pts.push_back(std::move(Pm));

	auto& triangles = triangulation->Connectivity();
	triangles.reserve(4);

	connectivity::triple t0;
	t0.Value(0) = 1;
	t0.Value(1) = 2;
	t0.Value(2) = 5;

	connectivity::triple t1;
	t1.Value(0) = 2;
	t1.Value(1) = 3;
	t1.Value(2) = 5;

	connectivity::triple t2;
	t2.Value(0) = 3;
	t2.Value(1) = 4;
	t2.Value(2) = 5;

	connectivity::triple t3;
	t3.Value(0) = 4;
	t3.Value(1) = 1;
	t3.Value(2) = 5;

	triangles.push_back(std::move(t0));
	triangles.push_back(std::move(t1));
	triangles.push_back(std::move(t2));
	triangles.push_back(std::move(t3));

	return std::move(triangulation);
}

Standard_Real 
AutLib::SingularityTools::CalcPolyLength
(
	const Entity2d_Polygon & thePoly,
	const Geom_Surface & theSurface
)
{
	std::vector<Pnt3d> Q;
	Q.reserve(thePoly.NbPoints());

	for (const auto& x : thePoly.Points())
	{
		auto p = theSurface.Value(x.X(), x.Y());
		Q.push_back(p);
	}

	auto d = (Standard_Real)0;
	forThose(Index, 1, Q.size() - 1)
	{
		const auto& P0 = Q[Index - 1];
		const auto& P1 = Q[Index];

		d += P0.Distance(P1);
	}
	return d;
}

Standard_Real 
AutLib::SingularityTools::CalcLineSegmentLength
(
	const Pnt2d & theP0,
	const Pnt2d & theP1,
	const Geom_Surface & theSurface
)
{
	const auto P0 = theSurface.Value(theP0.X(), theP0.Y());
	const auto P1 = theSurface.Value(theP1.X(), theP1.Y());

	return P0.Distance(P1);
}

AutLib::Pnt2d 
AutLib::SingularityTools::FindParametricCoord
(
	const Entity2d_Polygon & thePoly, 
	const Geom_Surface & theSurface,
	const Standard_Real theLength
)
{
	const auto& pts = thePoly.Points();

	Standard_Real d = 0;
	Pnt3d P0 = theSurface.Value(pts[0].X(), pts[0].Y());

	forThose(Index, 1, pts.size() - 1)
	{
		Pnt3d P1 = theSurface.Value(pts[Index].X(), pts[Index].Y());

		d += Distance(P0, P1);

		if (d >= theLength)
		{
			return MEAN(pts[Index - 1], pts[Index]);
		}

		P0 = std::move(P1);
	}

	FatalErrorIn("Pnt2d FindParametricCoord()")
		<< "Found no coord" << endl
		<< abort(FatalError);
	return pts[0];
}
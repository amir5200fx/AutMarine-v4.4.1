#include <Cad_Tools.hxx>

#include <Global_Macros.hxx>
#include <Entity2d_Box.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Cad_FastDiscret_Parameters.hxx>

#include <TopoDS_Face.hxx>
#include <TopoDS.hxx>
#include <TopExp_Explorer.hxx>
#include <BRep_Tool.hxx>
#include <BRepBndLib.hxx>
#include <BndLib_AddSurface.hxx>
#include <BRepMesh_FastDiscret.hxx>
#include <Bnd_Box.hxx>
#include <Poly_Triangulation.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <GeomConvert.hxx>
#include <GeomAdaptor_Surface.hxx>
#include <Geom2dConvert.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>

AutLib::Entity2d_Box
AutLib::Cad_Tools::BoundingBox(const Bnd_Box2d & theBox)
{
	Standard_Real Xmin, Xmax;
	Standard_Real Ymin, Ymax;

	theBox.Get(Xmin, Ymin, Xmax, Ymax);

	Entity2d_Box box(Pnt2d(Xmin, Ymin), Pnt2d(Xmax, Ymax));
	return std::move(box);
}

AutLib::Entity3d_Box 
AutLib::Cad_Tools::BoundingBox
(
	const Bnd_Box & theBox
)
{
	Standard_Real Xmin, Xmax;
	Standard_Real Ymin, Ymax;
	Standard_Real Zmin, Zmax;

	theBox.Get(Xmin, Ymin, Zmin, Xmax, Ymax, Zmax);

	Entity3d_Box box(Pnt3d(Xmin, Ymin, Zmin), Pnt3d(Xmax, Ymax, Zmin));
	return std::move(box);
}

std::shared_ptr<AutLib::Entity3d_Triangulation> 
AutLib::Cad_Tools::GetTriangulation
(
	const TopoDS_Face & theFace
)
{
	TopLoc_Location Loc;
	auto Triangulation = BRep_Tool::Triangulation(theFace, Loc);

	if (Triangulation.IsNull()) return nullptr;

	auto myTriangulation = ConvertTriangulation(*Triangulation);
	return std::move(myTriangulation);
}

std::vector<std::shared_ptr<AutLib::Entity3d_Triangulation>> 
AutLib::Cad_Tools::GetTriangulationList
(
	const TopoDS_Shape & theShape
)
{
	std::vector<std::shared_ptr<AutLib::Entity3d_Triangulation>> triList;
	for
		(
			TopExp_Explorer Explorer(theShape, TopAbs_FACE);
			Explorer.More();
			Explorer.Next()
			)
	{
		triList.push_back(GetTriangulation(TopoDS::Face(Explorer.Current())));
	}

	return std::move(triList);
}

std::shared_ptr<AutLib::Entity3d_Triangulation> 
AutLib::Cad_Tools::ConvertTriangulation
(
	const Poly_Triangulation & thePoly
)
{
	auto myTriangulation = std::make_shared<Entity3d_Triangulation>();

	const auto& triangles = thePoly.Triangles();
	const auto& nodes = thePoly.Nodes();

	auto& myTriangles = myTriangulation->Connectivity();
	auto& myPts = myTriangulation->Points();

	myTriangles.resize(triangles.Size());
	myPts.resize(nodes.Size());

	Standard_Integer K = 0;
	for (auto& x : myTriangles)
	{
		const auto& TriangleIndex = triangles.Value(K + triangles.Lower());

		Standard_Integer I1, I2, I3;
		TriangleIndex.Get(I1, I2, I3);

		x.Value(0) = I1;
		x.Value(1) = I2;
		x.Value(2) = I3;

		++K;
	}

	K = 0;
	for (auto& x : myPts)
	{
		x = Pnt3d(nodes.Value(K + nodes.Lower()));
		++K;
	}
	return std::move(myTriangulation);
}

Bnd_Box
AutLib::Cad_Tools::BoundingBox
(
	const Handle(Geom_Surface)& theSurface,
	const Entity2d_Box& theParams
)
{
	const auto& P0 = theParams.P0();
	const auto& P1 = theParams.P1();

	GeomAdaptor_Surface adaptor(theSurface, P0.X(), P1.X(), P0.Y(), P1.Y());

	Bnd_Box b;
	BndLib_AddSurface::Add(adaptor, 0, b);

	return std::move(b);
}

Handle(Geom2d_BSplineCurve)
AutLib::Cad_Tools::ConvertToBSpline
(
	const Handle(Geom2d_Curve)& theCurve, 
	const Standard_Real theFirst, 
	const Standard_Real theLast
)
{
	Handle(Geom2d_TrimmedCurve) trimmedCurve =
		new Geom2d_TrimmedCurve
		(
			theCurve,
			theFirst,
			theLast
		);

	auto curve = Geom2dConvert::CurveToBSplineCurve(trimmedCurve);
	return std::move(curve);
}

Handle(Geom_BSplineSurface)
AutLib::Cad_Tools::ConvertToBSpline
(
	const Handle(Geom_Surface)& theSurface,
	const Entity2d_Box & theTrimmed
)
{
	if (Handle(Geom_BSplineSurface)::DownCast(theSurface))
	{
		auto surface = Handle(Geom_BSplineSurface)::DownCast(theSurface);
		return std::move(surface);
	}

	const auto& P0 = theTrimmed.P0();
	const auto& P1 = theTrimmed.P1();

	const auto U0 = P0.X();
	const auto U1 = P1.X();
	const auto V0 = P0.Y();
	const auto V1 = P1.Y();

	Handle(Geom_RectangularTrimmedSurface) trimmedSurface = 
		new Geom_RectangularTrimmedSurface(theSurface, U0, U1, V0, V1);

	auto surface = GeomConvert::SurfaceToBSplineSurface(trimmedSurface);
	return std::move(surface);
}

void AutLib::Cad_Tools::Triangulation
(
	const TopoDS_Face & theFace,
	const Cad_FastDiscret_Parameters & theParams
)
{
	TopoDS_Shape shape = theFace;
	Triangulation(shape, theParams);
}

void AutLib::Cad_Tools::Triangulation
(
	const TopoDS_Shape & theShape,
	const Cad_FastDiscret_Parameters & Parameters
)
{
	BRepMesh_FastDiscret::Parameters Params;
	Params.AdaptiveMin = Parameters.AdaptiveMin;
	Params.Angle = Parameters.Angle;
	Params.ControlSurfaceDeflection = Parameters.ControlSurfaceDeflection;
	Params.Deflection = Parameters.Deflection;
	Params.InParallel = Parameters.InParallel;
	Params.InternalVerticesMode = Parameters.InternalVerticesMode;
	Params.MinSize = Parameters.MinSize;
	Params.Relative = Parameters.Relative;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(theShape, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(theShape);
}

void AutLib::Cad_Tools::Split
(
	const Standard_Real x,
	const Handle(Geom2d_BSplineCurve)& theCurve,
	Handle(Geom2d_BSplineCurve)& theleft, 
	Handle(Geom2d_BSplineCurve)& theRight
)
{
	if (NOT INSIDE(x, theCurve->FirstParameter(), theCurve->LastParameter()))
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "Invalid parameter" << endl
			<< " - x: " << x << endl
			<< " - first parameter: " << theCurve->FirstParameter() << endl
			<< " - last parameter: " << theCurve->LastParameter() << endl;
	}

	Handle(Geom2d_TrimmedCurve) trimmed0 =
		new Geom2d_TrimmedCurve(theCurve, theCurve->FirstParameter(), x);
	Handle(Geom2d_TrimmedCurve) trimmed1 =
		new Geom2d_TrimmedCurve(theCurve, x, theCurve->LastParameter());

	theleft = Geom2dConvert::CurveToBSplineCurve(trimmed0);
	theRight = Geom2dConvert::CurveToBSplineCurve(trimmed1);
}
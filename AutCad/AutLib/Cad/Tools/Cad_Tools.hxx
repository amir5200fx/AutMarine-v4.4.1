#pragma once
#ifndef _Cad_Tools_Header
#define _Cad_Tools_Header

#include <Standard_Handle.hxx>
#include <Standard_TypeDef.hxx>
#include <Entity3d_TriangulationFwd.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity3d_BoxFwd.hxx>

class TopoDS_Shape;
class TopoDS_Vertex;
class TopoDS_Edge;
class TopoDS_Face;
class TopoDS_Solid;
class Poly_Triangulation;
class Geom2d_BSplineCurve;
class Geom2d_Curve;
class Geom_Surface;
class Geom_BSplineSurface;

class Bnd_Box2d;
class Bnd_Box;

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	struct Cad_FastDiscret_Parameters;

	class Cad_Tools
	{

	public:

		static Standard_Integer NbSurfaces(const TopoDS_Shape& theShape);

		static Entity2d_Box BoundingBox(const Bnd_Box2d& theBox);

		static Entity3d_Box BoundingBox(const Bnd_Box& theBox);

		static std::shared_ptr<Entity3d_Triangulation> GetTriangulation(const TopoDS_Face& theFace);

		static std::shared_ptr<Entity3d_Triangulation> GetTriangulation(const TopoDS_Shape& theShape);

		static std::vector<std::shared_ptr<Entity3d_Triangulation>> GetTriangulationList(const TopoDS_Shape& theShape);

		static std::shared_ptr<Entity3d_Triangulation> ConvertTriangulation(const Poly_Triangulation& thePoly);

		static Bnd_Box BoundingBox(const Handle(Geom_Surface)& theSurface, const Entity2d_Box& theParams);

		static Handle(Geom2d_BSplineCurve) 
			ConvertToBSpline
			(
				const Handle(Geom2d_Curve)& theCurve, 
				const Standard_Real theFirst,
				const Standard_Real theLast
			);

		static Handle(Geom_BSplineSurface)
			ConvertToBSpline
			(
				const Handle(Geom_Surface)& theSurface, 
				const Entity2d_Box& theTrimmed
			);

		static void Triangulation(const TopoDS_Face& theFace, const Cad_FastDiscret_Parameters& theParams);

		static void Triangulation(const TopoDS_Shape& theShape, const Cad_FastDiscret_Parameters& theParams);

		static void 
			Split
			(
				const Standard_Real x, 
				const Handle(Geom2d_BSplineCurve)& theCurve, 
				Handle(Geom2d_BSplineCurve)& theleft, Handle(Geom2d_BSplineCurve)& theRight);


	};
}

#endif // !_Cad_Tools_Header

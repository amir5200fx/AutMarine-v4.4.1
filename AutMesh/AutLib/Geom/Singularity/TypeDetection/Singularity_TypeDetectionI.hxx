#pragma once
#include <Pln_Curve.hxx>
#include <Model_PlnSegment.hxx>
#include <Cad_Tools.hxx>
#include <GeoMesh2d_Data.hxx>
#include <Geo_ApprxSurfMetric.hxx>
#include <Geo_ColoringSurfMetric.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Polygon.hxx>
#include <SingularityZone_Pole_Corner.hxx>
#include <SingularityZone_Pole_WholeSide.hxx>
#include <SingularityZone_Pole_PartialSide.hxx>
#include <SingularityZone_Pole_Loop.hxx>
#include <SingularityZone_Line_Corner.hxx>
#include <SingularityZone_Line_Dangle.hxx>
#include <SingularityZone_Line_Loop.hxx>
#include <SingularityZone_Line_TwoSided.hxx>
#include <SingularityZone_Line_WholeSide.hxx>
#include <Singularity_LineCurve.hxx>
#include <Singularity_PoleCurve.hxx>
#include <Singularity_Horizon.hxx>
#include <Mesh_SingularityZone.hxx>
#include <Mesh3d_SizeMap.hxx>

#include <Standard_Handle.hxx>
#include <Geom_Surface.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>

namespace AutLib
{

	

	namespace SingularityTools
	{

		std::vector<std::shared_ptr<Pln_Curve>> RetrieveSides(const Entity2d_Box& theBox);

		std::shared_ptr<Entity2d_Triangulation> GetTriangulation(const Entity2d_Box& theBox);

		Standard_Real CalcPolyLength
		(
			const Entity2d_Polygon& thePoly,
			const Geom_Surface& theSurface
		);

		Standard_Real CalcLineSegmentLength
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1,
			const Geom_Surface& theSurface
		);

		Pnt2d FindParametricCoord
		(
			const Entity2d_Polygon& thePoly,
			const Geom_Surface& theSurface,
			const Standard_Real theLength
		);

		template<class CurveType>
		std::shared_ptr<Singularity_PoleCurve<CurveType>> GetParametricCurve
		(
			const Entity2d_Polygon& thePoly
		)
		{
			if (thePoly.NbPoints() < 2)
			{
				FatalErrorIn("static pCurve_ptr GetParametricCurve(const Entity2d_Polygon& thePoly)")
					<< "Invalid polygon" << endl
					<< abort(FatalError);
			}

			Model_PlnSegment LineSegMaker;

			if (thePoly.NbPoints() == 2)
			{
				const auto& pts = thePoly.Points();
				auto pcurve = LineSegMaker(pts[0], pts[1]);
				auto curve = std::make_shared<Singularity_PoleCurve<CurveType>>
					(
						pcurve->FirstParam(),
						pcurve->LastParam(),
						Cad_Tools::ConvertToBSpline
						(
							pcurve->Curve(),
							pcurve->FirstParam(),
							pcurve->LastParam()
						), pln_curve_info
						);
				return std::move(curve);
			}

			auto pcurve = std::make_shared<Pln_Curve>();

			if (pcurve->Interpolation(thePoly.Points()))
			{
				FatalErrorIn("static pCurve_ptr GetParametricCurve(const Entity2d_Polygon& thePoly)")
					<< "Failed to interpolate" << endl
					<< abort(FatalError);
			}
			auto curve = std::make_shared<Singularity_PoleCurve<CurveType>>
				(
					pcurve->FirstParam(),
					pcurve->LastParam(),
					Cad_Tools::ConvertToBSpline
					(
						pcurve->Curve(),
						pcurve->FirstParam(),
						pcurve->LastParam()
					), pln_curve_info
					);
			return std::move(curve);
		}

		template<class CurveType>
		std::shared_ptr<CurveType> GetParametricCurve_Line
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1
		)
		{
			Model_PlnSegment LineSegMaker;
			auto pcurve = LineSegMaker(theP0, theP1);
			auto curve = std::make_shared<Singularity_LineCurve<CurveType>>
				(
					pcurve->FirstParam(),
					pcurve->LastParam(),
					Cad_Tools::ConvertToBSpline
					(
						pcurve->Curve(),
						pcurve->FirstParam(),
						pcurve->LastParam()
					), pln_curve_info
					);
			return std::move(curve);
		}

		template<class CurveType>
		std::shared_ptr<CurveType> GetParametricCurve_Pole
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1
		)
		{
			Model_PlnSegment LineSegMaker;

			auto pcurve = LineSegMaker(theP0, theP1);
			auto curve = std::make_shared<Singularity_PoleCurve<CurveType>>
				(
					pcurve->FirstParam(),
					pcurve->LastParam(),
					Cad_Tools::ConvertToBSpline
					(
						pcurve->Curve(),
						pcurve->FirstParam(),
						pcurve->LastParam()
					), pln_curve_info
					);

			curve->SetMid(MEAN(curve->Start(), curve->Last()));
			return std::move(curve);
		}

		template<class CurveType>
		std::vector<std::shared_ptr<CurveType>> GetLineHorizonCurves_Dangle
		(
			const Entity2d_Box& theBox,
			const Standard_Integer s0
		)
		{
			const auto& p0 = theBox.P0();
			const auto p1 = theBox.Corner(Box2d_PickAlgorithm_SE);
			const auto& p2 = theBox.P1();
			const auto p3 = theBox.Corner(Box2d_PickAlgorithm_NW);

			std::vector<std::shared_ptr<CurveType>> curves;
			curves.reserve(3);

			if (s0 IS_EQUAL 1)
			{
				curves.push_back(GetParametricCurve_Line<CurveType>(p0, p3));
				curves.push_back(GetParametricCurve_Pole<CurveType>(p3, p2));
				curves.push_back(GetParametricCurve_Line<CurveType>(p2, p1));

				return std::move(curves);
			}
			else if (s0 IS_EQUAL 2)
			{
				curves.push_back(GetParametricCurve_Line<CurveType>(p1, p0));
				curves.push_back(GetParametricCurve_Pole<CurveType>(p0, p3));
				curves.push_back(GetParametricCurve_Line<CurveType>(p3, p2));

				return std::move(curves);
			}
			else if (s0 IS_EQUAL 3)
			{
				curves.push_back(GetParametricCurve_Line<CurveType>(p2, p1));
				curves.push_back(GetParametricCurve_Pole<CurveType>(p1, p0));
				curves.push_back(GetParametricCurve_Line<CurveType>(p0, p3));

				return std::move(curves);
			}
			else if (s0 IS_EQUAL 4)
			{
				curves.push_back(GetParametricCurve_Line<CurveType>(p3, p2));
				curves.push_back(GetParametricCurve_Pole<CurveType>(p2, p1));
				curves.push_back(GetParametricCurve_Line<CurveType>(p1, p0));

				return std::move(curves);
			}

			FatalErrorIn(FunctionSIG)
				<< abort(FatalError);
			return std::move(curves);
		}

		template<class CurveType>
		std::vector<std::shared_ptr<CurveType>> GetLineHorizonCurves_Corner
		(
			const Entity2d_Box& theBox,
			const Standard_Integer s0,
			const Geom_Surface& theSurface,
			const Standard_Real tol
		)
		{
			const auto& p0 = theBox.P0();
			const auto p1 = theBox.Corner(Box2d_PickAlgorithm_SE);
			const auto& p2 = theBox.P1();
			const auto p3 = theBox.Corner(Box2d_PickAlgorithm_NW);

			std::vector<std::shared_ptr<CurveType>> curves;
			curves.reserve(2);

			if (s0 IS_EQUAL 1)
			{
				const auto d0 = CalcLineSegmentLength(p3, p2, theSurface);
				const auto d1 = CalcLineSegmentLength(p0, p3, theSurface);

				if (d0 <= tol AND d1 <= tol)
				{
					FatalErrorIn(FunctionSIG)
						<< abort(FatalError);
				}

				if (d0 <= tol)
				{
					curves.push_back(GetParametricCurve_Pole<CurveType>(p3, p2));
					curves.push_back(GetParametricCurve_Line<CurveType>(p0, p3));
				}
				else
				{
					curves.push_back(GetParametricCurve_Line<CurveType>(p3, p2));
					curves.push_back(GetParametricCurve_Pole<CurveType>(p0, p3));
				}

				return std::move(curves);
			}
			else if (s0 IS_EQUAL 2)
			{
				const auto d0 = CalcLineSegmentLength(p1, p0, theSurface);
				const auto d1 = CalcLineSegmentLength(p0, p3, theSurface);

				if (d0 <= tol AND d1 <= tol)
				{
					FatalErrorIn(FunctionSIG)
						<< abort(FatalError);
				}

				if (d0 <= tol)
				{
					curves.push_back(GetParametricCurve_Pole<CurveType>(p1, p0));
					curves.push_back(GetParametricCurve_Line<CurveType>(p0, p3));
				}
				else
				{
					curves.push_back(GetParametricCurve_Line<CurveType>(p1, p0));
					curves.push_back(GetParametricCurve_Pole<CurveType>(p0, p3));
				}

				return std::move(curves);
			}
			else if (s0 IS_EQUAL 3)
			{
				const auto d0 = CalcLineSegmentLength(p2, p1, theSurface);
				const auto d1 = CalcLineSegmentLength(p1, p0, theSurface);

				if (d0 <= tol AND d1 <= tol)
				{
					FatalErrorIn(FunctionSIG)
						<< abort(FatalError);
				}

				if (d0 <= tol)
				{
					curves.push_back(GetParametricCurve_Pole<CurveType>(p2, p1));
					curves.push_back(GetParametricCurve_Line<CurveType>(p1, p0));
				}
				else
				{
					curves.push_back(GetParametricCurve_Line<CurveType>(p2, p1));
					curves.push_back(GetParametricCurve_Pole<CurveType>(p1, p0));
				}

				return std::move(curves);
			}
			else if (s0 IS_EQUAL 4)
			{
				const auto d0 = CalcLineSegmentLength(p3, p2, theSurface);
				const auto d1 = CalcLineSegmentLength(p2, p1, theSurface);

				if (d0 <= tol AND d1 <= tol)
				{
					FatalErrorIn(FunctionSIG)
						<< abort(FatalError);
				}

				if (d0 <= tol)
				{
					curves.push_back(GetParametricCurve_Pole<CurveType>(p3, p2));
					curves.push_back(GetParametricCurve_Line<CurveType>(p2, p1));
				}
				else
				{
					curves.push_back(GetParametricCurve_Line<CurveType>(p3, p2));
					curves.push_back(GetParametricCurve_Pole<CurveType>(p2, p1));
				}

				return std::move(curves);
			}

			FatalErrorIn(FunctionSIG)
				<< abort(FatalError);
			return std::move(curves);
		}

		template<class CurveType>
		std::vector<std::shared_ptr<CurveType>> GetLineHorizonCurves_WholeSide
		(
			const Entity2d_Box& theBox,
			const Standard_Integer s0
		)
		{
			const auto& p0 = theBox.P0();
			const auto p1 = theBox.Corner(Box2d_PickAlgorithm_SE);
			const auto& p2 = theBox.P1();
			const auto p3 = theBox.Corner(Box2d_PickAlgorithm_NW);

			std::vector<std::shared_ptr<CurveType>> curves;
			curves.reserve(1);

			if (s0 IS_EQUAL 1)
			{
				curves.push_back(GetParametricCurve_Line<CurveType>(p0, p3));

				return std::move(curves);
			}
			else if (s0 IS_EQUAL 2)
			{
				curves.push_back(GetParametricCurve_Line<CurveType>(p1, p0));

				return std::move(curves);
			}
			else if (s0 IS_EQUAL 3)
			{
				curves.push_back(GetParametricCurve_Line<CurveType>(p2, p1));

				return std::move(curves);
			}
			else if (s0 IS_EQUAL 4)
			{
				curves.push_back(GetParametricCurve_Line<CurveType>(p3, p2));

				return std::move(curves);
			}

			FatalErrorIn(FunctionSIG)
				<< abort(FatalError);
			return std::move(curves);
		}

		template<class CurveType>
		std::vector<std::shared_ptr<CurveType>> GetLineHorizonCurves_Loop
		(
			const Entity2d_Box& theBox
		)
		{
			const auto& p0 = theBox.P0();
			const auto p1 = theBox.Corner(Box2d_PickAlgorithm_SE);
			const auto& p2 = theBox.P1();
			const auto p3 = theBox.Corner(Box2d_PickAlgorithm_NW);

			std::vector<std::shared_ptr<CurveType>> curves;
			curves.reserve(4);

			curves.push_back(GetParametricCurve_Line<CurveType>(p0, p3));
			curves.push_back(GetParametricCurve_Line<CurveType>(p3, p2));
			curves.push_back(GetParametricCurve_Line<CurveType>(p2, p1));
			curves.push_back(GetParametricCurve_Line<CurveType>(p1, p0));

			return std::move(curves);
		}

		template<class CurveType>
		std::vector<std::shared_ptr<CurveType>> GetLineHorizonCurves_TwoSided
		(
			const Entity2d_Box& theBox,
			const Standard_Integer s0
		)
		{
			const auto& p0 = theBox.P0();
			const auto p1 = theBox.Corner(Box2d_PickAlgorithm_SE);
			const auto& p2 = theBox.P1();
			const auto p3 = theBox.Corner(Box2d_PickAlgorithm_NW);

			std::vector<std::shared_ptr<CurveType>> curves;
			curves.reserve(2);

			if (s0 IS_EQUAL 1 OR s0 IS_EQUAL 3)
			{
				curves.push_back(GetParametricCurve_Line<CurveType>(p0, p3));
				curves.push_back(GetParametricCurve_Line<CurveType>(p2, p1));

				return std::move(curves);
			}
			else if (s0 IS_EQUAL 2 OR s0 IS_EQUAL 4)
			{
				curves.push_back(GetParametricCurve_Line<CurveType>(p3, p2));
				curves.push_back(GetParametricCurve_Line<CurveType>(p1, p0));

				return std::move(curves);
			}

			FatalErrorIn(FunctionSIG)
				<< abort(FatalError);
			return std::move(curves);
		}

		template<class SurfPln>
		std::shared_ptr<Mesh_SingularityZone<SurfPln>> TypeDetection
		(
			const Entity2d_Polygon& thePolygon0,
			const Entity2d_Polygon& thePolygon1,
			const GeoMesh2d_Data& bMesh,
			const std::vector<std::shared_ptr<Pln_Curve>>& Sides,
			const Geom_Surface& theSurface,
			const Mesh3d_SizeMap& theSizeMap,
			const Standard_Integer theVerbose,
			std::ostream& os
		)
		{
			const auto& pts0 = thePolygon0.Points();
			const auto& pts1 = thePolygon1.Points();

			if (pts0.size() < 2)
			{
				FatalErrorIn("std::shared_ptr<SurfMetric_SingularityHorizon> TypeDetection()")
					<< "Invalid polygon: must be at least two points in the polygon" << endl
					<< abort(FatalError);
			}

			if (pts1.size() < 2)
			{
				FatalErrorIn("std::shared_ptr<SurfMetric_SingularityHorizon> TypeDetection()")
					<< "Invalid polygon: must be at least two points in the polygon" << endl
					<< abort(FatalError);
			}

			const auto& P00 = pts0[0];
			const auto& P01 = pts0[pts0.size() - 1];

			const auto& P10 = pts1[0];
			const auto& P11 = pts1[pts1.size() - 1];

			const auto& e00 = bMesh.TriangleLocation(bMesh.FirstElement(), P00);
			const auto& e01 = bMesh.TriangleLocation(bMesh.FirstElement(), P01);

			const auto s00 = e00->Index();
			const auto s01 = e01->Index();

			const auto& c00 = *Sides[Index_Of(s00)];
			const auto& c01 = *Sides[Index_Of(s01)];

			Geom2dAPI_ProjectPointOnCurve Projector;

			Projector.Init(P00, c00.Curve(), c00.FirstParam(), c00.LastParam());
			const auto d00 = Projector.LowerDistance();

			Projector.Init(P01, c01.Curve(), c01.FirstParam(), c01.LastParam());
			const auto d01 = Projector.LowerDistance();

			if (d00 > EPS12)
			{
				FatalErrorIn("std::shared_ptr<SurfMetric_SingularityHorizon> TypeDetection()")
					<< "Invalid Data" << endl
					<< abort(FatalError);
			}

			if (d01 > EPS12)
			{
				FatalErrorIn("std::shared_ptr<SurfMetric_SingularityHorizon> TypeDetection()")
					<< "Invalid Data" << endl
					<< abort(FatalError);
			}

			const auto& e10 = bMesh.TriangleLocation(bMesh.FirstElement(), P10);
			const auto& e11 = bMesh.TriangleLocation(bMesh.FirstElement(), P11);

			const auto s10 = e10->Index();
			const auto s11 = e11->Index();

			const auto& c10 = *Sides[Index_Of(s10)];
			const auto& c11 = *Sides[Index_Of(s11)];

			Projector.Init(P10, c10.Curve(), c10.FirstParam(), c10.LastParam());
			const auto d10 = Projector.LowerDistance();

			Projector.Init(P11, c11.Curve(), c11.FirstParam(), c11.LastParam());
			const auto d11 = Projector.LowerDistance();

			if (d10 > EPS12)
			{
				FatalErrorIn("std::shared_ptr<SurfMetric_SingularityHorizon> TypeDetection()")
					<< "Invalid Data" << endl
					<< abort(FatalError);
			}

			if (d11 > EPS12)
			{
				FatalErrorIn("std::shared_ptr<SurfMetric_SingularityHorizon> TypeDetection()")
					<< "Invalid Data" << endl
					<< abort(FatalError);
			}

			const auto size00 = theSizeMap.CalcElementSize(theSurface.Value(P00.X(), P00.Y()));
			const auto size01 = theSizeMap.CalcElementSize(theSurface.Value(P01.X(), P01.Y()));
			const auto size0 = MEAN(size00, size01);

			const auto size10 = theSizeMap.CalcElementSize(theSurface.Value(P10.X(), P10.Y()));
			const auto size11 = theSizeMap.CalcElementSize(theSurface.Value(P11.X(), P11.Y()));
			const auto size1 = MEAN(size10, size11);

			const auto box0 = Entity2d_Box::BoundingBoxOf(pts0);
			const auto box1 = Entity2d_Box::BoundingBoxOf(pts1);

			const auto box = Entity2d_Box::Union(box0, box1);

			const auto curves = GetLineHorizonCurves_TwoSided<typename SurfPln::plnCurve>(box, s00);

			auto singularity =
				std::make_shared<SingularityZone_Line_TwoSided<SurfPln>>
				(
					curves[0],
					curves[1]
					);

			return std::move(singularity);
		}

		template<class SurfPln>
		std::shared_ptr<Mesh_SingularityZone<SurfPln>> TypeDetection
		(
			const Entity2d_Polygon& thePolygon,
			const GeoMesh2d_Data& bMesh,
			const std::vector<std::shared_ptr<Pln_Curve>>& Sides,
			const Geom_Surface& theSurface,
			const Mesh3d_SizeMap& theSizeMap,
			const Standard_Integer theVerbose,
			std::ostream& os
		)
		{
			if (theVerbose)
			{
				os << " @ TypeDetection: " << std::endl;
			}

			const auto& pts = thePolygon.Points();
			if (pts.size() < 2)
			{
				FatalErrorIn("std::shared_ptr<SurfMetric_SingularityHorizon> TypeDetection()")
					<< "Invalid polygon: must be at least two points in the polygon" << endl
					<< abort(FatalError);
			}

			const auto& P0 = pts[0];
			const auto& P1 = pts[pts.size() - 1];

			if (theVerbose)
			{
				os << "  - Is the polygon closed? " << (thePolygon.IsClosed() ? "YES" : "NO") << std::endl;
			}

			if (thePolygon.IsClosed())
			{
				const auto length =
					CalcPolyLength(thePolygon, theSurface);

				const auto size =
					theSizeMap.CalcElementSize(theSurface.Value(P0.X(), P0.Y()));

				if (theVerbose)
				{
					os << "  - Length of the polygon: " << length << std::endl;
					os << "  - Length < 1.25*Element Size? " << ((length < 1.25*size) ? "YES" : "NO") << std::endl;
					os << "     Element Size = " << size << std::endl;
					os << std::endl;
					os << "     if the criterion is met then a singularity must be a pole loop" << std::endl;
					os << "     otherwise the singularity is a line loop" << std::endl;
				}

				const auto box = Entity2d_Box::BoundingBoxOf(pts);

				auto curves = GetLineHorizonCurves_Loop<typename SurfPln::plnCurve>(box);

				if (length < 1.25*size)
				{
					
					if (theVerbose)
					{
						os << "  - Creating a POLE LOOP singularity..." << std::endl;
					}

					auto singularity =
						std::make_shared<SingularityZone_Pole_Loop<SurfPln>>
						(
							curves[0],
							curves[1],
							curves[2],
							curves[3]
							);

					return std::move(singularity);
				}
				else
				{
					
					if (theVerbose)
					{
						os << "  - Creating a LINE LOOP singularity..." << std::endl;
					}

					auto singularity =
						std::make_shared<SingularityZone_Line_Loop<SurfPln>>
						(
							curves[0],
							curves[1],
							curves[2],
							curves[3]
							);

					return std::move(singularity);
				}
			}
			else
			{

				const auto& e0 = bMesh.TriangleLocation(bMesh.FirstElement(), P0);
				const auto& e1 = bMesh.TriangleLocation(bMesh.FirstElement(), P1);

				const auto s0 = e0->Index();
				const auto s1 = e1->Index();

				const auto& c0 = *Sides[Index_Of(s0)];
				const auto& c1 = *Sides[Index_Of(s1)];

				Geom2dAPI_ProjectPointOnCurve Projector;
				Projector.Init(P0, c0.Curve(), c0.FirstParam(), c0.LastParam());
				const auto d0 = Projector.LowerDistance();

				Projector.Init(P1, c1.Curve(), c1.FirstParam(), c1.LastParam());
				const auto d1 = Projector.LowerDistance();

				if (d0 > EPS6)
				{
					FatalErrorIn("std::shared_ptr<SurfMetric_SingularityHorizon> TypeDetection()")
						<< "Invalid Data" << endl
						<< abort(FatalError);
				}

				if (d1 > EPS6)
				{
					FatalErrorIn("std::shared_ptr<SurfMetric_SingularityHorizon> TypeDetection()")
						<< "Invalid Data" << endl
						<< abort(FatalError);
				}

				const auto size0 = theSizeMap.CalcElementSize(theSurface.Value(P0.X(), P0.Y()));
				const auto size1 = theSizeMap.CalcElementSize(theSurface.Value(P1.X(), P1.Y()));
				const auto size = MEAN(size0, size1);

				const auto length = CalcPolyLength(thePolygon, theSurface);

				if (theVerbose)
				{
					os << "  - Length of the polygon: " << length << std::endl;
					os << "  - Length < 1.25*Element Size? " << ((length < 1.25*size) ? "YES" : "NO") << std::endl;
					os << "     Element Size = " << size << std::endl;
					os << std::endl;
					os << "     if the criterion is met then a singularity must be a POLE type" << std::endl;
					os << "     otherwise the singularity is a LINE type" << std::endl;
				}

				if (length < 1.25*size)
				{
					if (s0 IS_EQUAL s1)
					{
						const auto curve = GetParametricCurve<typename SurfPln::plnCurve>(thePolygon);

						const auto Pm = FindParametricCoord(thePolygon, theSurface, 0.5*length);
						curve->SetMid(Pm);

						if (theVerbose)
						{
							os << "  - Creating a PARTIALSIDE POLE singularity..." << std::endl;
						}

						auto singularity = std::make_shared<SingularityZone_Pole_PartialSide<SurfPln>>(curve);
						singularity->SetPole(Pm);

						return std::move(singularity);
					}
					else if (ABS(s0 - s1) IS_EQUAL 1)
					{
						const auto curve = GetParametricCurve<typename SurfPln::plnCurve>(thePolygon);

						const auto Pm = FindParametricCoord(thePolygon, theSurface, 0.5*length);
						curve->SetMid(Pm);

						if (theVerbose)
						{
							os << "  - Creating a CORNER POLE singularity..." << std::endl;
						}

						auto singularity = std::make_shared<SingularityZone_Pole_Corner<SurfPln>>(curve);
						singularity->SetPole(Pm);

						return std::move(singularity);
					}
					else if (ABS(s0 - s1) IS_EQUAL 2)
					{
						Model_PlnSegment LinSegMaker;
						const auto pcurve = LinSegMaker(P0, P1);
						auto curve = std::make_shared<Singularity_PoleCurve<typename SurfPln::plnCurve>>
							(
								pcurve->FirstParam(), pcurve->LastParam(),
								Cad_Tools::ConvertToBSpline(pcurve->Curve(), pcurve->FirstParam(), pcurve->LastParam()), pln_curve_info
								);

						const auto Pm = MEAN(P0, P1);
						curve->SetMid(Pm);

						if (theVerbose)
						{
							os << "  - Creating a WHOLESIDE POLE singularity..." << std::endl;
						}

						auto singularity = std::make_shared<SingularityZone_Pole_WholeSide<SurfPln>>(curve);
						singularity->SetPole(Pm);

						return std::move(singularity);
					}
					else
					{
						FatalErrorIn("std::shared_ptr<SurfMetric_SingularityHorizon> TypeDetection()")
							<< "Invalid data!" << endl
							<< abort(FatalError);
					}
				}
				else
				{
					const auto box = Entity2d_Box::BoundingBoxOf(pts);

					if (s0 IS_EQUAL s1)
					{
						auto curves = GetLineHorizonCurves_Dangle<typename SurfPln::plnCurve>(box, s0);

						if (theVerbose)
						{
							os << "  - Creating a DANGLE LINE singularity..." << std::endl;
						}

						auto singularity =
							std::make_shared<SingularityZone_Line_Dangle<SurfPln>>
							(
								curves[0],
								curves[1], curves[2]);

						return std::move(singularity);
					}
					else if (ABS(s0 - s1) IS_EQUAL 1)
					{
						auto curves =
							GetLineHorizonCurves_Corner<typename SurfPln::plnCurve>
							(
								box,
								s0, theSurface, 1.25*size);

						if (theVerbose)
						{
							os << "  - Creating a CORNER LINE singularity..." << std::endl;
						}

						auto singularity =
							std::make_shared<SingularityZone_Line_Corner<SurfPln>>(curves[0], curves[1]);

						return std::move(singularity);
					}
					else if (ABS(s0 - s1) IS_EQUAL 2)
					{
						auto curves = GetLineHorizonCurves_WholeSide<typename SurfPln::plnCurve>(box, s0);

						if (theVerbose)
						{
							os << "  - Creating a WHOLESIDE LINE singularity..." << std::endl;
						}

						auto singularity =
							std::make_shared<SingularityZone_Line_WholeSide<SurfPln>>(curves[0]);

						return std::move(singularity);
					}

					FatalErrorIn("std::shared_ptr<SurfMetric_SingularityHorizon> TypeDetection()")
						<< "Invalid data!" << endl
						<< abort(FatalError);
				}
			}

			FatalErrorIn("std::shared_ptr<SurfMetric_SingularityHorizon> TypeDetection()")
				<< "Invalid data!" << endl
				<< abort(FatalError);

			return nullptr;
		}
	}

	template<class SurfPln>
	void Singularity_TypeDetection<SurfPln>::Perform(std::ostream& os)
	{
		if (Verbose())
		{
			os << " @ void Singularity_TypeDetection<SurfPln>::Perform(std::ostream& os)" << std::endl;
			os << " - VERBOSITY LEVEL = " << Verbose() << std::endl;
		}

		if (NOT theHorizons_)
		{
			FatalErrorIn("void AutLib::SingularityZone_TypeDetection::Perform()")
				<< "Found no metric approximation" << endl
				<< abort(FatalError);
		}

		if (NOT theHorizons_->Approx())
		{
			FatalErrorIn("void AutLib::SingularityZone_TypeDetection::Perform()")
				<< "Found no metric approximation" << endl
				<< abort(FatalError);
		}

		if (NOT Colors())
		{
			FatalErrorIn("void AutLib::SingularityZone_TypeDetection::Perform()")
				<< "No coloring has not been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT theHorizons_->HasHorizon())
		{
			Change_IsDone() = Standard_True;
			return;
		}

		const auto& approx = *theHorizons_->Approx();
		const auto& surface = *approx.Surface();
		const auto& box = approx.BoundingBox();

		const auto& color = *Colors();

		std::map
			<
			Standard_Integer,
			std::shared_ptr<std::list<std::shared_ptr<Entity2d_Polygon>>>
			>
			IndexToHorizon;

		if (Verbose())
		{
			os << "  Nb. of Horizons: " << theHorizons_->NbHorizons() << std::endl;
		}

		forThose
		(
			Index,
			0,
			theHorizons_->NbHorizons() - 1
		)
		{
			if (Verbose())
			{
				os << "  horizon no. " << Index << std::endl;
			}

			const auto& horizon = *theHorizons_->Horizon(Index);

			const auto i = color.Value(horizon.GetPoint(horizon.NbPoints() / 2));

			if (Verbose())
			{
				os << "  color no. " << i << std::endl;
			}

			auto iter = IndexToHorizon.find(i);

			if (iter IS_EQUAL IndexToHorizon.end())
			{
				IndexToHorizon.insert
				(
					std::make_pair
					(
						i,
						std::make_shared<std::list<std::shared_ptr<Entity2d_Polygon>>>()
					)
				);
			}

			IndexToHorizon[i]->push_back(theHorizons_->Horizon(Index));
		}

		const auto triangulation = SingularityTools::GetTriangulation(box);
		const auto sides = SingularityTools::RetrieveSides(box);

		if (Verbose())
		{
			os << "  constructing topological background mesh... " << std::endl;
		}

		GeoMesh2d_Data bmesh;
		bmesh.Construct(*triangulation);

		if (Verbose())
		{
			os << "  topological background mesh has been constructed! " << std::endl;
		}

		theZones_.reserve(IndexToHorizon.size());

		auto iter = IndexToHorizon.begin();
		while (iter NOT_EQUAL IndexToHorizon.end())
		{
			Debug_Null_Pointer(iter->second);
			const auto& l = *iter->second;

			if (l.empty())
			{
				FatalErrorIn("void AutLib::SingularityZone_TypeDetection::Perform()")
					<< "empty list" << endl
					<< abort(FatalError);
			}

			if (l.size() IS_EQUAL 1)
			{
				auto type = 
					SingularityTools::TypeDetection<SurfPln>
					(
						*l.front(), bmesh, sides,
						surface, *theSizeMap_, Verbose(), os);
				type->SetIndex(iter->first);

				theZones_.push_back(type);
			}

			if (l.size() IS_EQUAL 2)
			{
				std::shared_ptr<Entity2d_Polygon> v[2];
				Standard_Integer K = 0;
				for (const auto& x : l)
				{
					v[K++] = x;
				}

				auto type = 
					SingularityTools::TypeDetection<SurfPln>
					(
						*v[0], *v[1], bmesh,
						sides, surface, *theSizeMap_, Verbose(), os);
				type->SetIndex(iter->first);

				theZones_.push_back(type);
			}

			if (l.size() > 2)
			{
				FatalErrorIn("void AutLib::SingularityZone_TypeDetection::Perform()")
					<< "Invalid Data" << endl
					<< abort(FatalError);
			}
			iter++;
		}

		Change_IsDone() = Standard_True;
	}
}
#include <Singularity_Horizon.hxx>

#include <Entity_Segment.hxx>
#include <Entity_Triangle.hxx>
#include <Entity2d_Metric1.hxx>
#include <Entity2d_Chain.hxx>
#include <Merge_StaticData.hxx>
#include <Geo_ApprxSurfMetric.hxx>
#include <GeoMesh2d_MetricBackground.hxx>
#include <SizeMap2d_Surface.hxx>
#include <Knit_Chain.hxx>
#include <Knit2d_ChainNode.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <gp_Vec.hxx>
#include <gp_Pnt.hxx>
#include <Geom_Surface.hxx>

namespace AutLib
{

	typedef Entity2d_Metric1 metric;

	typedef Entity_Segment<const Pnt2d&> segmentRef;
	typedef Entity_Triangle<const Pnt2d&> triangle;
	typedef Entity_Segment<Pnt2d> segment;

	template<class SizeMap = void>
	struct MetricAt
	{
		static metric _
		(
			const Geom_Surface& theSurface,
			const SizeMap& theMap,
			const Pnt2d& theP
		)
		{
			auto u = theP.X();
			auto v = theP.Y();

			gp_Vec D1U, D1V;
			gp_Pnt P;
			theSurface.D1(u, v, P, D1U, D1V);

			auto A = D1U.Dot(D1U);
			auto B = D1U.Dot(D1V);
			auto C = D1V.Dot(D1V);

			const auto h = theMap.CalcElementSize(theP);
			Debug_If_Condition(h <= gp::Resolution());

			const auto invH = 1.0 / (h*h);

			metric M(invH*A, invH*B, invH*C);
			return std::move(M);
		}
	};

	template<>
	struct MetricAt<void>
	{
		static metric _
		(
			const Geom_Surface& theSurface,
			const Pnt2d& theP
		)
		{
			auto u = theP.X();
			auto v = theP.Y();

			gp_Vec D1U, D1V;
			gp_Pnt P;
			theSurface.D1(u, v, P, D1U, D1V);

			auto A = D1U.Dot(D1U);
			auto B = D1U.Dot(D1V);
			auto C = D1V.Dot(D1V);

			metric M(A, B, C);
			return std::move(M);
		}
	};

	template<class SizeMap = void>
	struct Interpolate
	{

		static Standard_Boolean _
		(
			const Geom_Surface& theSurface,
			const SizeMap& theMap,
			const segmentRef& s,
			const Standard_Real theDegeneracy,
			const Standard_Real theInvMaxDet,
			Pnt2d& theCoord
		)
		{
			const auto& P0 = s.P0();
			const auto& P1 = s.P1();

			auto m0 = MetricAt<SizeMap>::_(theSurface, theMap, P0);
			auto m1 = MetricAt<SizeMap>::_(theSurface, theMap, P1);

			auto det0 = m0.Determinant() * theInvMaxDet;
			auto det1 = m1.Determinant() * theInvMaxDet;

			if (det0 > theDegeneracy AND det1 > theDegeneracy)
				return Standard_False;

			if (det0 <= theDegeneracy AND det1 <= theDegeneracy)
				return Standard_False;

			auto t = (theDegeneracy - det0) / (det1 - det0);
			if (t < 0) return Standard_False;
			if (t > 1) return Standard_False;

			theCoord = P0 + t * (P1 - P0);
			return Standard_True;
		}
	};

	template<>
	struct Interpolate<void>
	{

		static Standard_Boolean _
		(
			const Geom_Surface& theSurface,
			const segmentRef& s,
			const Standard_Real theDegeneracy,
			const Standard_Real theInvMaxDet,
			Pnt2d& theCoord
		)
		{
			const auto& P0 = s.P0();
			const auto& P1 = s.P1();

			auto m0 = MetricAt<void>::_(theSurface, P0);
			auto m1 = MetricAt<void>::_(theSurface, P1);

			auto det0 = m0.Determinant() * theInvMaxDet;
			auto det1 = m1.Determinant() * theInvMaxDet;

			if (det0 > theDegeneracy AND det1 > theDegeneracy)
				return Standard_False;

			if (det0 <= theDegeneracy AND det1 <= theDegeneracy)
				return Standard_False;

			auto t = (theDegeneracy - det0) / (det1 - det0);
			if (t < 0) return Standard_False;
			if (t > 1) return Standard_False;

			theCoord = P0 + t * (P1 - P0);
			return Standard_True;
		}
	};

	static void MergingThreePoints
	(
		const Pnt2d& P0,
		const Pnt2d& P1,
		const Pnt2d& P2,
		const Standard_Real theTol,
		Pnt2d& Q0,
		Pnt2d& Q1
	)
	{
		auto tol2 = theTol * theTol;
		if (P0.SquareDistance(P1) > tol2)
		{
			Q0 = P0;
			Q1 = P1;
			return;
		}

		if (P0.SquareDistance(P2) > tol2)
		{
			Q0 = P0;
			Q1 = P2;
			return;
		}

		if (P1.SquareDistance(P2) > tol2)
		{
			Q0 = P1;
			Q1 = P2;
			return;
		}
	}

	static Standard_Integer StandPoint
	(
		const Standard_Real det0,
		const Standard_Real det1,
		const Standard_Real det2,
		const Standard_Real theDegeneracy
	)
	{
		if (det0 <= theDegeneracy AND det1 <= theDegeneracy AND det2 <= theDegeneracy)
		{
			FatalErrorIn("Pnt2d StandPoint(const triangle& theTriangle, const Standard_Real det0, const Standard_Real det1, const Standard_Real det2, const Standard_Real theDegeneracy)")
				<< "Invalid Data : " << endl
				<< " - All of the determinants of the triangle are less than the degeneracy criterion!" << endl
				<< " - d0 = " << det0 << ", d1 = " << det1 << ", d2 = " << det2 << endl
				<< " - Degeneracy criterion = " << theDegeneracy << endl
				<< abort(FatalError);
		}

		Standard_Integer gt_deg, st_deg;
		gt_deg = 0;
		st_deg = 0;
		det0 <= theDegeneracy ? st_deg++ : gt_deg++;
		det1 <= theDegeneracy ? st_deg++ : gt_deg++;
		det2 <= theDegeneracy ? st_deg++ : gt_deg++;

		if (st_deg IS_EQUAL 1)
		{
			if (det0 <= theDegeneracy) return 0;
			if (det1 <= theDegeneracy) return 1;
			if (det2 <= theDegeneracy) return 2;
		}

		if (gt_deg IS_EQUAL 1)
		{
			if (det0 > theDegeneracy) return 0;
			if (det1 > theDegeneracy) return 1;
			if (det2 > theDegeneracy) return 2;
		}

		FatalErrorIn("Pnt2d StandPoint(const triangle& theTriangle, const Standard_Real det0, const Standard_Real det1, const Standard_Real det2, const Standard_Real theDegeneracy)")
			<< "Invalid Data : " << endl
			<< " - something goes wrong!" << endl
			<< abort(FatalError);

		return 0;
	}

	template<class SizeMap = void>
	struct CheckOrientation
	{

		static void _
		(
			const Geom_Surface& theSurface,
			const SizeMap& theMap,
			const triangle& theTriangle,
			const Standard_Real theDegeneracy,
			const Standard_Real theInvMaxDet,
			Entity2d_Chain& theSeg
		)
		{
			const auto& P0 = theTriangle.P0();
			const auto& P1 = theTriangle.P1();
			const auto& P2 = theTriangle.P2();

			auto m0 = MetricAt<SizeMap>::_(theSurface, theMap, P0);
			auto m1 = MetricAt<SizeMap>::_(theSurface, theMap, P1);
			auto m2 = MetricAt<SizeMap>::_(theSurface, theMap, P2);

			auto det0 = m0.Determinant() * theInvMaxDet;
			auto det1 = m1.Determinant() * theInvMaxDet;
			auto det2 = m2.Determinant() * theInvMaxDet;

			const auto& P = theTriangle.Vertex(StandPoint(det0, det1, det2, theDegeneracy));

			auto& pts = theSeg.Points();
			const auto& V0 = pts[0];
			const auto& V1 = pts[1];

			if (CrossProduct(V0 - P, V1 - P) < 0)
			{
				std::reverse(pts.begin(), pts.end());
			}
		}
	};

	template<>
	struct CheckOrientation<void>
	{

		static void _
		(
			const Geom_Surface& theSurface,
			const triangle& theTriangle,
			const Standard_Real theDegeneracy,
			const Standard_Real theInvMaxDet,
			Entity2d_Chain& theSeg
		)
		{
			const auto& P0 = theTriangle.P0();
			const auto& P1 = theTriangle.P1();
			const auto& P2 = theTriangle.P2();

			auto m0 = MetricAt<void>::_(theSurface, P0);
			auto m1 = MetricAt<void>::_(theSurface, P1);
			auto m2 = MetricAt<void>::_(theSurface, P2);

			auto det0 = m0.Determinant() * theInvMaxDet;
			auto det1 = m1.Determinant() * theInvMaxDet;
			auto det2 = m2.Determinant() * theInvMaxDet;

			const auto& P = theTriangle.Vertex(StandPoint(det0, det1, det2, theDegeneracy));

			auto& pts = theSeg.Points();
			const auto& V0 = pts[0];
			const auto& V1 = pts[1];

			if (CrossProduct(V0 - P, V1 - P) < 0)
			{
				std::reverse(pts.begin(), pts.end());
			}
		}
	};

	template<class SizeMap = void>
	struct GetPathFromTriangle
	{

		static std::shared_ptr<Entity2d_Chain> _
		(
			const Geom_Surface& theSurface,
			const SizeMap& theMap,
			const triangle& theTriangle,
			const Standard_Real theDegeneracy,
			const Standard_Real theMergTol,
			const Standard_Real theInvMaxDet
		)
		{
			auto seg =
				std::make_shared<Entity2d_Chain>();

			std::vector<Pnt2d> Pts;
			Pts.reserve(3);

			Pnt2d Coord;
			if (Interpolate<SizeMap>::_(theSurface, theMap, theTriangle.Segment(0), theDegeneracy, theInvMaxDet, Coord))
			{
				Pts.push_back(Coord);
			}

			if (Interpolate<SizeMap>::_(theSurface, theMap, theTriangle.Segment(1), theDegeneracy, theInvMaxDet, Coord))
			{
				Pts.push_back(Coord);
			}

			if (Interpolate<SizeMap>::_(theSurface, theMap, theTriangle.Segment(2), theDegeneracy, theInvMaxDet, Coord))
			{
				Pts.push_back(Coord);
			}

			if (Pts.empty())
			{
				return nullptr;
			}

			Pnt2d Q0, Q1;
			if (Pts.size() > 2)
			{
				MergingThreePoints(Pts[0], Pts[1], Pts[2], theMergTol, Q0, Q1);
			}
			else
			{
				Q0 = Pts[0];
				Q1 = Pts[1];
			}

			auto& points = seg->Points();
			points.resize(2);

			points[0] = Q0;
			points[1] = Q1;

			auto& Indices = seg->Connectivity();
			Indices.resize(1);
			Indices[0].Value(0) = 1;
			Indices[0].Value(1) = 2;

			CheckOrientation<SizeMap>::_(theSurface, theMap, theTriangle, theDegeneracy, theInvMaxDet, *seg);

			return std::move(seg);
		}
	};

	template<>
	struct GetPathFromTriangle<void>
	{

		static std::shared_ptr<Entity2d_Chain> _
		(
			const Geom_Surface& theSurface,
			const triangle& theTriangle,
			const Standard_Real theDegeneracy,
			const Standard_Real theMergTol,
			const Standard_Real theInvMaxDet
		)
		{
			auto seg =
				std::make_shared<Entity2d_Chain>();

			std::vector<Pnt2d> Pts;
			Pts.reserve(3);

			Pnt2d Coord;
			if (Interpolate<void>::_(theSurface, theTriangle.Segment(0), theDegeneracy, theInvMaxDet, Coord))
			{
				Pts.push_back(Coord);
			}

			if (Interpolate<void>::_(theSurface, theTriangle.Segment(1), theDegeneracy, theInvMaxDet, Coord))
			{
				Pts.push_back(Coord);
			}

			if (Interpolate<void>::_(theSurface, theTriangle.Segment(2), theDegeneracy, theInvMaxDet, Coord))
			{
				Pts.push_back(Coord);
			}

			if (Pts.empty())
			{
				return nullptr;
			}

			Pnt2d Q0, Q1;
			if (Pts.size() > 2)
			{
				MergingThreePoints(Pts[0], Pts[1], Pts[2], theMergTol, Q0, Q1);
			}
			else
			{
				Q0 = Pts[0];
				Q1 = Pts[1];
			}

			auto& points = seg->Points();
			points.resize(2);

			points[0] = Q0;
			points[1] = Q1;

			auto& Indices = seg->Connectivity();
			Indices.resize(1);
			Indices[0].Value(0) = 1;
			Indices[0].Value(1) = 2;

			CheckOrientation<void>::_(theSurface, theTriangle, theDegeneracy, theInvMaxDet, *seg);

			return std::move(seg);
		}
	};
}

Standard_Integer AutLib::Singularity_Horizon::NbHorizons() const
{
	if (NOT theKnitAlg_)
	{
		FatalErrorIn("Standard_Integer AutLib::SurfMetric_SingularityHorizon::NbHorizons() const")
			<< "The algorithm has not been performed!" << endl
			<< abort(FatalError);
	}
	return theKnitAlg_->NbPolygons();
}

const std::shared_ptr<AutLib::Entity2d_Polygon>& 
AutLib::Singularity_Horizon::Horizon
(
	const Standard_Integer theIndex
) const
{
	if (NOT IsDone())
	{
		FatalErrorIn("const std::shared_ptr<Entity2d_Chain>& Horizon(const Standard_Integer theIndex) const")
			<< "The algorithm has not been performed!" << endl
			<< abort(FatalError);
	}
	if (NOT theKnitAlg_)
	{
		FatalErrorIn("const std::shared_ptr<Entity2d_Chain>& Horizon(const Standard_Integer theIndex) const")
			<< "The surface has no horizon!" << endl
			<< abort(FatalError);
	}
	return theKnitAlg_->Polygon(theIndex);
}

Standard_Boolean 
AutLib::Singularity_Horizon::HasHorizon() const
{
	if (NOT IsDone())
	{
		FatalErrorIn("Standard_Boolean HasHorizon() const")
			<< "The algorithm has not been performed!" << endl
			<< abort(FatalError);
	}
	if (NOT theKnitAlg_) return Standard_False;
	return (Standard_Boolean)theKnitAlg_->NbPolygons();
}

void AutLib::Singularity_Horizon::Perform()
{
	if (NOT theApprox_)
	{
		FatalErrorIn("void AutLib::SurfMetric_SingularityHorizon::Perform()") << endl
			<< "Found no approximation of the metric surface" << endl
			<< abort(FatalError);
	}

	if (NOT theApprox_->Approx())
	{
		FatalErrorIn("void AutLib::SurfMetric_SingularityHorizon::Perform()")
			<< "Found no surface metric approximation" << endl
			<< abort(FatalError);
	}

	const auto& apprx = *theApprox_->Approx();

	Debug_Null_Pointer(theApprox_->Surface());
	const auto& surface = *theApprox_->Surface();

	Debug_Null_Pointer(apprx.Mesh());
	const auto& mesh = *apprx.Mesh();
	const auto& sources = apprx.Sources();

	const auto& info = *theApprox_->Info();
	const auto invMaxDet = (Standard_Real)1.0 / info.MaxDeterminant();

	std::vector<std::shared_ptr<Entity2d_Chain>> list;

	const auto& elements = mesh.Elements();
	if (theApprox_->SizeMap())
	{
		for (const auto x : elements)
		{
			Debug_Null_Pointer(x);
			const auto& element = *x;

			const auto& p0 = element.Node0()->Coord();
			const auto& p1 = element.Node1()->Coord();
			const auto& p2 = element.Node2()->Coord();

			triangle t(p0, p1, p2);

			auto path =
				GetPathFromTriangle<SizeMap2d_Surface>::_
				(
					surface,
					*theApprox_->SizeMap(),
					t,
					info.Degeneracy(),
					info.Tolerance(), invMaxDet);

			if (path) list.push_back(path);
		}
	}
	else
	{
		for (const auto x : elements)
		{
			Debug_Null_Pointer(x);
			const auto& element = *x;

			const auto& p0 = element.Node0()->Coord();
			const auto& p1 = element.Node1()->Coord();
			const auto& p2 = element.Node2()->Coord();

			triangle t(p0, p1, p2);

			auto path =
				GetPathFromTriangle<>::_
				(
					surface,
					t,
					info.Degeneracy(),
					info.Tolerance(), invMaxDet);

			if (path) list.push_back(path);
		}
	}

	if (list.empty())
	{
		Change_IsDone() = Standard_True;
		return;
	}

	Merge_StaticData<Entity2d_Chain> merge;
	merge.Import(list);
	merge.SetRemoveDegeneracy();

	merge.Perform();

	const auto& merged = merge.Merged();

	auto knitChain = std::make_shared<Knit2d_Chain>();
	knitChain->SetComparableKnit_ChainNodesTo
	(
		&Knit2d_ChainNode::IsLess
	);

	knitChain->SetComparableKnit_ChainEdgesTo
	(
		&Knit_ChainEdge<Knit2d_ChainNode>::IsLess
	);

	knitChain->Import(*merged);

	knitChain->Perform();
	theKnitAlg_ = std::move(knitChain);

	Change_IsDone() = Standard_True;
}
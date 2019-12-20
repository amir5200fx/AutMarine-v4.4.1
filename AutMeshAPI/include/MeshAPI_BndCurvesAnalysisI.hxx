#pragma once
#include <MetricMap2d_ExactSurfaceLowerBounded.hxx>
#include <TopoMesh_PlaneBoundariesInfo.hxx>
#include <SizeMap2d_Surface.hxx>
#include <Mesh_SurfaceTemplate.hxx>
namespace AutLib
{

	template<class TopoBndMesh, class SizeMap3d>
	std::shared_ptr<SizeMap2d_FullIntSurface> 
		MeshAPI_BndCurvesAnalysis<TopoBndMesh, SizeMap3d>::GetPlaneSizeMap() const
	{
		const auto geometry = Surface()->Geometry();
		const auto& boundingBox = Surface()->BoundingBox();

		auto surfaceSize = std::make_shared<SizeMap2d_Surface>(*SizeMap(), *geometry);
		Debug_Null_Pointer(surfaceSize);

		Debug_Null_Pointer(Info());
		Debug_Null_Pointer(Info()->GlobalMetricMapInfo());
		auto currentMetricInfo = Info()->GlobalMetricMapInfo();
		if (Info()->OverrideMetricMap())
		{
			auto metricInfo = Info()->MetricMapInfo();
			auto iter = metricInfo.find(Surface()->Index());
			if (iter NOT_EQUAL metricInfo.end())
			{
				currentMetricInfo = iter->second;
			}
		}

		auto surfaceMetric = std::make_shared<MetricMap2d_ExactSurfaceLowerBounded>(geometry, boundingBox, currentMetricInfo);
		Debug_Null_Pointer(surfaceMetric);

		
		Debug_Null_Pointer(Info()->GlobalSizeMapInfo());

		auto currentInfo = Info()->GlobalSizeMapInfo();
		if (Info()->OverrideSizeMap())
		{
			auto sizeInfo = Info()->SizeMapInfo();
			auto iter = sizeInfo.find(Surface()->Index());
			if (iter NOT_EQUAL sizeInfo.end())
			{
				currentInfo = iter->second;
			}
		}

		auto anIsoMap = std::make_shared<SizeMap2d_FullIntSurface>(currentInfo);
		Debug_Null_Pointer(anIsoMap);

		anIsoMap->LoadMetricMap(surfaceMetric);
		anIsoMap->LoadSizeMap(surfaceSize);

		return std::move(anIsoMap);
	}

	template<class TopoBndMesh, class SizeMap3d>
	void MeshAPI_BndCurvesAnalysis<TopoBndMesh, SizeMap3d>::CreateMesh3D()
	{
		auto chain = std::make_shared<Entity3d_Chain>();
		Debug_Null_Pointer(chain);

		auto& pts = chain->Points();
		auto& indices = chain->Connectivity();

		auto edges = TopoBndMesh::bndType::UpCast(Mesh()->Boundaries());
		auto pp = TopoBndMesh::bndType::nodeType::RetrieveGeometry(TopoBndMesh::bndType::RetrieveNodes(edges));

		const auto& surface = *Surface();

		pts.reserve(pp.size());
		for (const auto& x : pp)
		{
			pts.push_back(surface.Value(x));
		}

		indices.reserve(edges.size());
		for (const auto& x : edges)
		{
			auto v0 = x->Node0()->Index();
			auto v1 = x->Node1()->Index();

			connectivity::dual id;
			id.Value(0) = v0;
			id.Value(1) = v1;

			indices.push_back(id);
		}

		ChangeMesh3D() = std::move(chain);
	}

	template<class TopoBndMesh, class SizeMap3d>
	std::shared_ptr<typename MeshAPI_BndCurvesAnalysis<TopoBndMesh, SizeMap3d>::plnType> 
		MeshAPI_BndCurvesAnalysis<TopoBndMesh, SizeMap3d>::MakePlane
		(
			const std::shared_ptr<surfType>& theSurface
		)
	{
		/*auto plane = plnType::MakePlane(theSurface);
		return std::move(plane);*/

		auto down = std::dynamic_pointer_cast<Mesh_SurfaceTemplate<surfType>>(theSurface);
		Debug_Null_Pointer(down);

		auto plane = down->GetPlane();
		return std::move(plane);
	}

	template<class TopoBndMesh, class SizeMap3d>
	Standard_Boolean MeshAPI_BndCurvesAnalysis<TopoBndMesh, SizeMap3d>::Check() const
	{
		if (NOT IsDone())
		{
			FatalErrorIn("Standard_Boolean Check() const")
				<< "the algorithm has not been performed" << endl
				<< abort(FatalError);
		}
		return Check_;
	}

	template<class TopoBndMesh, class SizeMap3d>
	void MeshAPI_BndCurvesAnalysis<TopoBndMesh, SizeMap3d>::Perform()
	{
		if (NOT Surface())
		{
			FatalErrorIn("void AMesh_BndCurvesAnalysis::Perform()")
				<< "no surface has been loaded" << endl
				<< abort(FatalError);
		}

		if (NOT SizeMap())
		{
			FatalErrorIn("void MeshAPI_BndCurvesAnalysis::Perform()")
				<< "no size map has been loaded" << endl
				<< abort(FatalError);
		}

		ChangePlane() = MakePlane(Surface());
		Debug_Null_Pointer(Plane());

		auto mesher = std::make_shared<TopoBndMesh>();
		Debug_Null_Pointer(mesher);

		ChangeMetricMap() = GetPlaneSizeMap();

		mesher->LoadPlane(Plane());
		mesher->LoadSizeMap(MetricMap());

		Debug_Null_Pointer(Info());
		Debug_Null_Pointer(Info()->GlobalPlnBndInfo());

		auto currentInfo = Info()->GlobalPlnBndInfo();
		if (Info()->OverridePlnBnd())
		{
			const auto& plnInfo = Info()->PlnBndInfo();
			auto iter = plnInfo.find(Surface()->Index());

			if (iter NOT_EQUAL plnInfo.end())
			{
				currentInfo = iter->second;
			}
		}

		mesher->Perform(currentInfo);

		Debug_If_Condition_Message(NOT mesher->IsDone(), " boundary mesh algorithm has not been performed!");

		if (mesher->SimpleCheck())
		{
			ChangeCheck() = mesher->SimpleCheck();
		}

		if (mesher->InnerCheck())
		{
			ChangeCheck() = mesher->InnerCheck();
		}

		if (mesher->OrientCheck())
		{
			ChangeCheck() = mesher->OrientCheck();
		}

		if (mesher->NbPtsCheck())
		{
			ChangeCheck() = mesher->NbPtsCheck();
		}

		ChangeMesh() = std::move(mesher);

		CreateMesh3D();

		Change_IsDone() = Standard_True;
	}
}


#include <Geom_AdTree.hxx>
#include <Adt_AvlTree.hxx>

namespace AutLib
{

	template<class BndEdgeType>
	static std::vector<std::shared_ptr<typename BndEdgeType::edgeType>>
		Compact
		(
			const std::vector<std::shared_ptr<typename BndEdgeType::edgeType::nodeType>>& Nodes
		)
	{
		Adt_AvlTree<std::shared_ptr<typename BndEdgeType::edgeType>> compact;
		compact.SetComparableFunction(&BndEdgeType::edgeType::IsLess);

		for (const auto& x : Nodes)
		{
			Debug_Null_Pointer(x);

			auto node = std::dynamic_pointer_cast<typename BndEdgeType::bndNodeType>(x);
			Debug_Null_Pointer(node);

			auto edges = node->RetrieveBoundaryEdges();
			for (const auto& item : edges)
			{
				compact.InsertIgnoreDup(item.second.lock());
			}
		}

		std::vector<std::shared_ptr<typename BndEdgeType::edgeType>> edges;
		compact.RetrieveTo(edges);
		return std::move(edges);
	}

	template<class BndEdgeType>
	static Standard_Boolean CheckEdgeIntersection
	(
		const BndEdgeType& theE0,
		const BndEdgeType& theE1
	)
	{
		const auto v0 = theE0.Node0()->Index();
		const auto v1 = theE0.Node1()->Index();

		const auto q0 = theE1.Node0()->Index();
		const auto q1 = theE1.Node1()->Index();

		if (Processor::IsOneCommonPointTwoSegments(v0, v1, q0, q1))
		{
			return Standard_False;
		}

		const auto& P0 = theE0.Node0()->Coord();
		const auto& P1 = theE0.Node1()->Coord();

		const auto& Q0 = theE1.Node0()->Coord();
		const auto& Q1 = theE1.Node1()->Coord();

		if (Processor::HasIntersection_cgal(Q0, Q1, P0, P1))
		{
			return Standard_True;
		}
		return Standard_False;
	}
}

template<class TopoBndMesh, class SizeMap3d>
Standard_Boolean AutLib::MeshAPI_BndCurvesAnalysis<TopoBndMesh, SizeMap3d>::CheckIntersection
(
	const std::vector<std::shared_ptr<typename TopoBndMesh::bndType>>& theEdges
)
{
	auto edges = TopoBndMesh::bndType::UpCast(theEdges);
	auto nodes = TopoBndMesh::bndType::RetrieveNodes(edges);
	auto pts = TopoBndMesh::bndType::nodeType::RetrieveGeometry(nodes);

	auto box = Entity2d_Box::BoundingBoxOf(pts);

	Geom_AdTree<std::shared_ptr<typename TopoBndMesh::bndType::nodeType>> engine;
	engine.SetGeometryRegion(box.OffSet(1.0E-6*box.Diameter()));
	engine.SetGeometryCoordFunc(&TopoBndMesh::bndType::nodeType::GetCoord);

	engine.InsertToGeometry(nodes);

	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		const auto& n0 = *x->Node0();
		const auto& n1 = *x->Node1();

		auto radius = 1.15*Distance(n0.Coord(), n1.Coord());

		auto P0 = x->Centre() - Pnt2d(radius, radius);
		auto P1 = x->Centre() + Pnt2d(radius, radius);

		Debug_If_Condition(radius <= 0);

		std::vector<std::shared_ptr<typename TopoBndMesh::bndType::nodeType>> bnodes;
		engine.GeometrySearch(Entity2d_Box(P0, P1), bnodes);

		auto bedges = Compact<typename TopoBndMesh::bndType>(bnodes);

		for (const auto& edge : bedges)
		{
			Debug_Null_Pointer(edge);

			if (x IS_EQUAL edge) continue;

			if (AutLib::CheckEdgeIntersection(*x, *edge))
			{
				return Standard_True;
			}
		}
	}
	return Standard_False;
}
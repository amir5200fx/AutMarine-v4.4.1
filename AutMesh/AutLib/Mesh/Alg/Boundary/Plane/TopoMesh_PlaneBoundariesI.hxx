#pragma once
#include <Adt_AvlTree.hxx>
#include <GeoProcessor.hxx>
#include <TopoMesh_PlaneBoundariesInfo.hxx>
#include <TopoMesh_PlaneBoundaryTraits.hxx>
#include <error.hxx>
#include <OSstream.hxx>
namespace AutLib
{

	template<class PlaneType, class SizeMap, class BndType>
	std::shared_ptr<Entity2d_Chain> 
		TopoMesh_PlaneBoundariesBase<PlaneType, SizeMap, BndType>::StaticData() const
	{
		auto chain = std::make_shared<Entity2d_Chain>();

		Adt_AvlTree<std::shared_ptr<typename BndType::nodeType>> nodesReg;
		nodesReg.SetComparableFunction(&BndType::nodeType::IsLess);

		for (const auto& x : theBoundaries_)
		{
			Debug_Null_Pointer(x);
			nodesReg.InsertIgnoreDup(x->Node0());
			nodesReg.InsertIgnoreDup(x->Node1());
		}

		std::vector<std::shared_ptr<typename BndType::nodeType>> nodes;
		nodesReg.RetrieveTo(nodes);

		auto& pts = chain->Points();
		pts.reserve(nodes.size());
		for (const auto& x : nodes)
		{
			Debug_Null_Pointer(x);
			pts.push_back(x->Coord());
		}

		auto& indices = chain->Connectivity();
		indices.reserve(theBoundaries_.size());
		for (const auto& x : theBoundaries_)
		{
			Debug_Null_Pointer(x);
			auto connect = connectivity::dual();
			connect.Value(0) = x->Node0()->Index();
			connect.Value(1) = x->Node1()->Index();

			indices.push_back(std::move(connect));
		}

		return std::move(chain);
	}


	template<class PlaneType, class SizeMap, class BndType, bool WireChar, bool CheckDegen>
	void TopoMesh_PlaneBoundaries<PlaneType, SizeMap, BndType, WireChar, CheckDegen>::UpdateFront()
	{
		Debug_Null_Pointer(base::Map());
		const auto& sizeMap = *base::Map();

		const auto& boundaries = base::ChangeBoundaries();
		for (const auto& x : boundaries)
		{
			Debug_Null_Pointer(x);
			const auto& n0 = x->Node0();
			const auto& n1 = x->Node1();

			x->SetEffectiveMetric(sizeMap.CalcEffectiveMetric(n0->Coord(), n1->Coord()));
			x->SetCentre(sizeMap.CalcCentreOf(n0->Coord(), n1->Coord()));
			x->SetCharLength(sizeMap.CalcDistance(n0->Coord(), n1->Coord()));
		}

		for (const auto& x : boundaries)
		{
			Debug_Null_Pointer(x);

			auto n0 = std::dynamic_pointer_cast<typename BndType::bndNodeType>(x->Node0());
			Debug_Null_Pointer(n0);

			const auto& edges = n0->RetrieveBoundaryEdges();
			auto Iter = edges.begin();
			auto M = Iter->second.lock()->EffectiveMetric();
			Iter++;

			while (Iter NOT_EQUAL edges.end())
			{
				const auto& Mi = Iter->second.lock()->EffectiveMetric();
				if (M.Determinant() < Mi.Determinant())
				{
					M = Entity2d_Metric1::UnionSR(M, Mi);
				}
				else
				{
					M = Entity2d_Metric1::UnionSR(Mi, M);
				}
				Iter++;
			}

			n0->SetMetric(M);
		}
	}

	template<class PlaneType, class SizeMap, class BndType, bool WireChar, bool CheckDegen>
	Standard_Boolean TopoMesh_PlaneBoundaries<PlaneType, SizeMap, BndType, WireChar, CheckDegen>::IsTopologyValid() const
	{
		if (NOT IsDone())
		{
			FatalErrorIn("Standard_Boolean IsValidTopology() const") << endl
				<< "the algorithm has not been performed!" << endl
				<< abort(FatalError);
		}

		const auto& boundaries = base::Boundaries();
		for (const auto& x : boundaries)
		{
			Debug_Null_Pointer(x);

			if (x->Node0()->NbFrontEdges() NOT_EQUAL 2) return Standard_False;
			if (x->Node1()->NbFrontEdges() NOT_EQUAL 2) return Standard_False;
		}
		return Standard_True;
	}

	template<class PlaneType, class SizeMap, class BndType, bool WireChar, bool CheckDegen>
	void TopoMesh_PlaneBoundaries<PlaneType, SizeMap, BndType, WireChar, CheckDegen>::Perform
	(
		const std::shared_ptr<TopoMesh_PlaneBoundariesInfo>& theInfo
	)
	{
		if (NOT base::Map())
		{
			FatalErrorIn("void TopoMesh_PlaneBoundaries<PlaneType, SizeMap, BndType, WireChar>::Peform()")
				<< "the size map has not been loaded"
				<< abort(FatalError);
		}

		if (NOT base::Plane())
		{
			FatalErrorIn("void TopoMesh_PlaneBoundaries<PlaneType, SizeMap, BndType, WireChar>::Peform()")
				<< "the plane has not been loaded"
				<< abort(FatalError);
		}

		std::vector<std::shared_ptr<typename PlaneType::plnWire>> wires;
		base::Plane()->RetrieveWiresTo(wires);

		if (wires.empty())
		{
			FatalErrorIn("void TopoMesh_PlaneBoundaries<PlaneType, SizeMap, WireChar>::Peform()")
				<< "Invalid Plane: has no wire"
				<< abort(FatalError);
		}

		Debug_Null_Pointer(theInfo);
		const auto& infoMap = theInfo->CurveInfo();

		auto& boundaries = base::ChangeBoundaries();
		Standard_Integer Ke = 0;
		Standard_Integer Kn = 0;

		Standard_Boolean Checked = Standard_False;

		std::vector<Entity2d_Box> boxes;
		boxes.reserve(wires.size());
		for (const auto& wire : wires)
		{
			Debug_Null_Pointer(wire);

			std::vector<std::shared_ptr<BndType>> Medges;

			std::vector<Entity2d_Box> wBoxes;
			const auto& curves = wire->Curves();
			wBoxes.reserve(curves.size());
			for (const auto& x : curves)
			{
				Debug_Null_Pointer(x);

				Debug_Null_Pointer(theInfo->GlobalCurveInfo());
				auto currentInfo = theInfo->GlobalCurveInfo();

				if (theInfo->OverrideInfo() AND infoMap.size())
				{				
					auto iter = infoMap.find(x->Index());

					if (iter NOT_EQUAL infoMap.end())
					{
						currentInfo = iter->second;
					}
				}

				auto mesh = curveType::template TopoMesh<SizeMap, BndType>(x, base::Map(), currentInfo);

				auto nodes = BndType::RetrieveNodes(BndType::UpCast(mesh));
				auto box = Entity2d_Box::BoundingBoxOf(BndType::nodeType::RetrieveGeometry(nodes));

				wBoxes.push_back(std::move(box));

				for (const auto& edge : mesh)
				{
					Debug_Null_Pointer(edge);
					Medges.push_back(edge);
				}
			}

			auto iter = wBoxes.begin();
			auto wBox = *iter;
			iter++;
			while (iter NOT_EQUAL wBoxes.end())
			{
				wBox = Entity2d_Box::Union(wBox, *iter);
				iter++;
			}

			boxes.push_back(wBox);

			for (auto& x : Medges)
			{
				Debug_Null_Pointer(x);
				x->SetIndex(++Ke);
			}

			BndType::MergeDangles(Medges, 3.0E-3);

			for (const auto& x : Medges)
			{
				Debug_Null_Pointer(x);
				boundaries.push_back(x);
			}

			for (auto& x : Medges)
			{
				Debug_Null_Pointer(x);
				auto& n0 = x->Node0();

				n0->SetIndex(++Kn);
			}

			if (CheckWireNbPts(Medges))
			{
				NbPtsCheck_ = Standard_True;
				Checked = Standard_True;
				continue;
			}

			if (CheckSimplicity(Medges))
			{
				SimpleCheck_ = Standard_True;
				Checked = Standard_True;
				continue;
			}

			if (wires[0] IS_EQUAL wire)
			{
				if (CheckWireOrientation(Medges, Standard_True))
				{
					OrientCheck_ = Standard_True;
					Checked = Standard_True;
				}
			}
			else
			{
				if (CheckWireOrientation(Medges, Standard_False))
				{
					OrientCheck_ = Standard_True;
					Checked = Standard_True;
				}
			}
		}

		auto iter = boxes.begin();
		auto box0 = *iter;
		iter++;

		while (iter NOT_EQUAL boxes.end())
		{
			if (NOT Entity2d_Box::IsInside(iter->OffSet(1.0E-6), box0))
			{
				InnerCheck_ = Standard_True;
				break;
			}
			iter++;
		}

		BndType::ActiveBoundaryEdges(BndType::UpCast(boundaries));

		if (NOT Checked)
		{
			RemoveDegeneracies();
		}

		UpdateFront();

		Change_IsDone() = Standard_True;
	}
}

template<class PlaneType, class SizeMap, class BndType, bool WireChar, bool CheckDegen>
Standard_Boolean AutLib::TopoMesh_PlaneBoundaries<PlaneType, SizeMap, BndType, WireChar, CheckDegen>::CheckWireOrientation
(
	const std::vector<std::shared_ptr<BndType>>& theEdges, 
	const Standard_Boolean ccw
)
{
	auto nodes = BndType::RetrieveNodes(BndType::UpCast(theEdges));
	if (nodes.size() < 3)
	{
		return Standard_False;
	}

	auto pts = BndType::bndNodeType::RetrieveGeometry(nodes);

	if (ccw)
	{
		return !Processor::IsCcwOrder_cgal(pts);
	}

	return Processor::IsCcwOrder_cgal(pts);
}

template<class PlaneType, class SizeMap, class BndType, bool WireChar, bool CheckDegen>
Standard_Boolean AutLib::TopoMesh_PlaneBoundaries<PlaneType, SizeMap, BndType, WireChar, CheckDegen>::CheckWireNbPts
(
	const std::vector<std::shared_ptr<BndType>>& theEdges
)
{
	return theEdges.size() < 3;
}

template<class PlaneType, class SizeMap, class BndType, bool WireChar, bool CheckDegen>
Standard_Boolean AutLib::TopoMesh_PlaneBoundaries<PlaneType, SizeMap, BndType, WireChar, CheckDegen>::CheckSimplicity
(
	const std::vector<std::shared_ptr<BndType>>& theEdges
)
{
	auto nodes = BndType::RetrieveNodes(BndType::UpCast(theEdges));
	if (nodes.size() < 3)
	{
		return Standard_False;
	}

	auto pts = BndType::bndNodeType::RetrieveGeometry(nodes);

	return !Processor::IsSimple_cgal(pts);
}
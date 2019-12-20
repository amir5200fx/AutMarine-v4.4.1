#include <TopoMesh2d_GModelBoundaries.hxx>

namespace AutLib
{

	template<>
	void TopoMesh2d_GModelBoundaries::UpdateFront()
	{
		Debug_Null_Pointer(base::Map());
		const auto& sizeMap = *base::Map();

		const auto& boundaries = base::ChangeBoundaries();
		auto nodes = Aft2d_gSegmentEdge::RetrieveNodes(Aft2d_gSegmentEdge::UpCast(boundaries));
		for (const auto& x : nodes)
		{
			Debug_Null_Pointer(x);
			x->SetCoord3D(sizeMap.CalcCoord3D(x->Coord()));
		}

		for (const auto& x : boundaries)
		{
			Debug_Null_Pointer(x);
			const auto& n0 = x->Node0();
			const auto& n1 = x->Node1();

			x->SetEffectiveMetric(sizeMap.CalcEffectiveMetric(n0->Coord(), n1->Coord()));
			x->SetCentre(sizeMap.CalcCentreOf(n0->Coord(), n1->Coord()));
			x->SetCharLength(sizeMap.CalcDistance(n0->Coord(), n1->Coord()));
			x->SetLength3D(sizeMap.CalcLength3D(*x));
		}

		for (const auto& x : boundaries)
		{
			Debug_Null_Pointer(x);

			auto n0 = std::dynamic_pointer_cast<typename Aft2d_gSegmentEdge::bndNodeType>(x->Node0());
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
}
#include <Aft2d_FrontSurfaceInfo.hxx>

namespace AutLib
{

	template<>
	template<>
	void Aft2d_FrontSurfaceInfo::UpdateEdges
		<void, Mesh2d_SizeMapSurface>
		(
			const Mesh2d_SizeMapSurface& theSizeMap
			)
	{
		Debug_Null_Pointer(frontInfo::CurrentFront());
		const auto& current = *frontInfo::CurrentFront();

		if (frontInfo::IsPairedEdge0())
		{
			frontInfo::SetCreatedEdge0(nullptr);

			// remove the old coincident face from the GF
			deAttachFromFront(frontInfo::PairedEdge0());

			// remove cavity face
			if (frontInfo::PairedEdge0()->IsOnCavity())
				frontInfo::PairedEdge0()->RemoveEntityAsCavity();
		}
		else
		{
			EdgeCounter()++;

			const auto& P1 = frontInfo::ValidNode()->Coord();
			const auto& P2 = current.Node1()->Coord();

			frontInfo::SetCreatedEdge0(std::make_shared<frontType>(EdgeCounter()));
			auto& edge = *frontInfo::CreatedEdge0();

			edge.SetLength3D(theSizeMap.CalcLength3D(current));
			edge.SetCharLength(theSizeMap.CalcDistance(P1, P2));
			edge.SetCentre(theSizeMap.CalcCentreOf(P1, P2));
			edge.SetNode0(frontInfo::ValidNode());
			edge.SetNode1(current.Node1());
			edge.SetEffectiveMetric(theSizeMap.CalcEffectiveMetric(P1, P2));

			Debug_If_Condition(frontInfo::ValidNode() == current.Node1());

			AttachToFrontNodes(frontInfo::CreatedEdge0());
			AttachToMeshNodes(frontInfo::CreatedEdge0());
		}

		if (frontInfo::IsPairedEdge1())
		{
			frontInfo::SetCreatedEdge1(nullptr);

			// remove the old coincident face from the GF
			deAttachFromFront(frontInfo::PairedEdge1());

			// remove cavity face
			if (frontInfo::PairedEdge1()->IsOnCavity())
				frontInfo::PairedEdge1()->RemoveEntityAsCavity();
		}
		else
		{
			EdgeCounter()++;

			const auto& P1 = current.Node0()->Coord();
			const auto& P2 = frontInfo::ValidNode()->Coord();

			frontInfo::SetCreatedEdge1(std::make_shared<frontType>(EdgeCounter()));
			auto& edge = *frontInfo::CreatedEdge1();

			edge.SetLength3D(theSizeMap.CalcLength3D(current));
			edge.SetCharLength(theSizeMap.CalcDistance(P1, P2));
			edge.SetCentre(theSizeMap.CalcCentreOf(P1, P2));
			edge.SetNode0(current.Node0());
			edge.SetNode1(frontInfo::ValidNode());
			edge.SetEffectiveMetric(theSizeMap.CalcEffectiveMetric(P1, P2));

			Debug_If_Condition(frontInfo::ValidNode() == current.Node0());

			AttachToFrontNodes(frontInfo::CreatedEdge1());
			AttachToMeshNodes(frontInfo::CreatedEdge1());
		}
	}
}
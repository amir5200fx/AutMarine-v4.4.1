#pragma once
#ifndef _TopoMesh2d_PlaneBoundaries_Header
#define _TopoMesh2d_PlaneBoundaries_Header

#include <TopoMesh_PlaneBoundaries.hxx>
#include <Mesh2d_SurfPlane.hxx>
#include <Mesh2d_SizeMap.hxx>
#include <Aft2d_SegmentEdge.hxx>

namespace AutLib
{

	template<>
	class TopoMesh_PlaneBoundaries
		<
		Mesh2d_SurfPlane, 
		Mesh2d_SizeMap, 
		Aft2d_SegmentEdge, true, false
		>
		: public TopoMesh_PlaneBoundariesBase
		<
		Mesh2d_SurfPlane,
		Mesh2d_SizeMap, Aft2d_SegmentEdge
		>
		, public Global_Done
	{

		/*Private Data*/

	public:

		typedef TopoMesh_PlaneBoundariesBase
			<
			Mesh2d_SurfPlane, 
			Mesh2d_SizeMap, Aft2d_SegmentEdge
			> base;

		TopoMesh_PlaneBoundaries()
		{}

		TopoMesh_PlaneBoundaries
		(
			const std::shared_ptr<Mesh2d_SizeMap>& theSizeMap,
			const std::shared_ptr<Mesh2d_SurfPlane>& thePlane
		)
			: base(theSizeMap, thePlane)
		{}

		Standard_Boolean IsTopologyValid() const;

		void Perform(const std::shared_ptr<Mesh_CurveInfo>& theInfo);


	};

	typedef TopoMesh_PlaneBoundaries
		<
		Mesh2d_SurfPlane,
		Mesh2d_SizeMap, 
		Aft2d_SegmentEdge
		>
		TopoMesh2d_PlaneBoundaries;

	std::vector<std::shared_ptr<Aft2d_Edge>>
		DownCastBoundaryEdges(const std::vector<std::shared_ptr<Aft2d_SegmentEdge>>& theEdges);
}

#endif // !_TopoMesh2d_PlaneBoundaries_Header

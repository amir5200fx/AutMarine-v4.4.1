#pragma once
#include <Mesh2d_Surface.hxx>
#include <Mesh_SurfPlane.hxx>
#include <Mesh_SurfaceSizeMap.hxx>
#include <MetricMap2d_ExactSurfaceLowerBounded.hxx>
#include <SizeMap2d_FullIntSurface.hxx>
#include <TopoMesh_PlaneBoundaries.hxx>
#include <MeshAPI_Traits.hxx>
#include <MeshAPI_SurfaceInfo.hxx>
namespace AutLib
{

	template<class SurfType, class SizeMap3D>
	void MeshAPI_Surface<SurfType, SizeMap3D>::ComputeSurfaceMesh()
	{
		Debug_Null_Pointer(ParaTriangulation());
		Debug_Null_Pointer(Surface());

		const auto& tri2d = *ParaTriangulation();
		const auto& surface = *Surface();

		auto tri3d = std::make_shared<Entity3d_Triangulation>();
		Debug_Null_Pointer(tri3d);

		auto& pts = tri3d->Points();
		for (const auto& x : tri2d.Points())
		{
			auto p = surface.Value(x);
			pts.push_back(std::move(p));
		}

		tri3d->Connectivity() = tri2d.Connectivity();
		theTriangulation_ = std::move(tri3d);
	}

	template<class SurfType, class SizeMap3D>
	void MeshAPI_Surface<SurfType, SizeMap3D>::Perform
	(
		std::ostream & os
	)
	{
		if (NOT SizeMap())
		{
			FatalErrorIn("void MeshAPI_Surface<MshSurf, SizeMap3D>::Perform()")
				<< "the SizeMap has not been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT Surface())
		{
			FatalErrorIn("void MeshAPI_Surface<MshSurf, SizeMap3D>::Perform()")
				<< "the surface has not been loaded!" << endl
				<< abort(FatalError);
		}

		auto mesher = std::make_shared<Mesh2d_Surface>();
		Debug_Null_Pointer(mesher);

		Debug_Null_Pointer(Surface()->Geometry());
		const auto geometry = Surface()->Geometry();
		const auto& boundingBox = Surface()->BoundingBox();

		auto plane = Mesh_SurfPlane<SurfType>::MakePlane(Surface());
		Debug_Null_Pointer(plane);

		auto surfSizeMap = std::make_shared<Mesh_SurfaceSizeMap<SizeMap3D>>(*SizeMap(), *geometry);
		Debug_Null_Pointer(surfSizeMap);

		auto surfaceMetric = std::make_shared<MetricMap2d_ExactSurfaceLowerBounded>(geometry, boundingBox);
		Debug_Null_Pointer(surfaceMetric);

		auto sizeMapInfo = Info()->GlobalAnIsoSizeMapInfo();
		if (Info()->OverrideSizeMap()) sizeMapInfo = Info()->AnIsoSizeMapInfo();

		auto anIsoMap = std::make_shared<SizeMap2d_FullIntSurface>(sizeMapInfo);	
		Debug_Null_Pointer(anIsoMap);

		anIsoMap->LoadSizeMap(surfSizeMap);
		anIsoMap->LoadMetricMap(surfaceMetric);

		anIsoMap->Make();
		Debug_If_Condition_Message(NOT anIsoMap->IsDone(), "the sizemap2d_fullintaniso has not been performed!");

		auto boundaryMesh = 
			std::make_shared
			<
			TopoMesh_PlaneBoundaries
			<
			Mesh_SurfPlane<SurfType>,
			SizeMap2d_FullIntSurface,
			typename boundary_element_type<SurfType>::type
			>>(anIsoMap, plane);
		Debug_Null_Pointer(boundaryMesh);

		auto bndMeshInfo = Info()->GlobalCurveMeshInfo();
		if (Info()->OverrideCurveMeah()) bndMeshInfo = Info()->CurveMeshInfo();

		boundaryMesh->Perform(bndMeshInfo);

		auto upCast = boundary_element_type<SurfType>::type::UpCast(boundaryMesh->Boundaries());

		//- load boundary mesh to the advancing-front algorithm
		mesher->LoadBoundaryEdges(upCast);

		//- loading boundary and domain size map
		mesher->LoadSizeMap(anIsoMap);
		mesher->LoadBoundarySizeMap(anIsoMap);

		Debug_If_Condition_Message(NOT mesher->IsLoaded(), "the advancing front algorithm has not been loaded!");

		mesher->Perform();
		Debug_If_Condition_Message(NOT mesher->IsDone(), "the advancing front algorithm has not been performed!");

		ChangeParaMesh() = mesher->StaticMesh();

		ComputeSurfaceMesh();

		Change_IsDone() = Standard_True;
	}
}
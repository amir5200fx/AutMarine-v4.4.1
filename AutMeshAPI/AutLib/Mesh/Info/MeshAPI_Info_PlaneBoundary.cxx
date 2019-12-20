#include <MeshAPI_Info_PlaneBoundary.hxx>

#include <TopoMesh_PlaneBoundariesInfo.hxx>
#include <MeshAPI_Info_CurveMesh.hxx>

std::shared_ptr<AutLib::TopoMesh_PlaneBoundariesInfo>
AutLib::PlnBoundaryLib::mesh_api_plane_boundary_mesh_info = std::make_shared<AutLib::TopoMesh_PlaneBoundariesInfo>();

void AutLib::PlnBoundaryLib::meshApi_planeBoundaryMesh_init_runTime()
{
	auto& plnInfo = *mesh_api_plane_boundary_mesh_info;
	plnInfo.OverrideGlobalCurveInfo(CurveMeshLib::mesh_api_curve_mesh_info);
}
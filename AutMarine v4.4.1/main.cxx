#include <Examples_Mesh.hxx>
#include <error.hxx>
#include <iostream>

#include <Mesh_Info.hxx>
#include <MeshAPI_Info.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Aft2d_gSegmentEdge.hxx>

using namespace AutLib;

int main()
{
	mesh_init_runTime();
	meshApi_init_runTime();

	//FatalError.throwExceptions();
	IterFail.throwExceptions();

	Examples_Mesh::GModel_Mesh_Case1();

	system("pause");
}
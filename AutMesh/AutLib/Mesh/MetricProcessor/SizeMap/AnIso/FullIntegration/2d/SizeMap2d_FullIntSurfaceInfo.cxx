#include <SizeMap2d_FullIntSurfaceInfo.hxx>

#include <Mesh_Info.hxx>

const Standard_Integer AutLib::SizeMap2d_FullIntSurfaceInfo::DEFAULT_NB_SAMPLES(3);

AutLib::SizeMap2d_FullIntSurfaceInfo::SizeMap2d_FullIntSurfaceInfo()
	: theNbSamples_(DEFAULT_NB_SAMPLES)
{}
#pragma once
#include <error.hxx>
#include <OSstream.hxx>
namespace AutLib
{

	template<class CurveType>
	void Mesh_BndEdgeGeomAdaptor
		<
		CurveType, void, 
		Mesh_BndEdge_Position_Segment
		>::SingularityContraction
		(
			const Mesh2d_SizeMapSurface &
		)
	{
		FatalErrorIn("void SingularityContraction(const SizeMap2dAnIso &)")
			<< "not supposed to be called!" << endl
			<< abort(FatalError);
	}
}
#pragma once
#ifndef _Knit_ChainEdgeAdaptor_Header
#define _Knit_ChainEdgeAdaptor_Header

//#include <Mesh_EntityAdaptorM.hxx>
#include <Mesh_EdgeAdaptor.hxx>

namespace AutLib
{

	//Mesh_EntityToEntityAdaptor(Knit_ChainEdge, Facet, FacetType);

	template<class FacetType>
	class Knit_ChainEdgeAdaptor
		: public Mesh_EdgeAdaptor<FacetType, void>
	{

		/*Private Data*/

	public:

		Knit_ChainEdgeAdaptor()
		{}
	};
}

#endif // !_Knit_ChainEdgeAdaptor_Header

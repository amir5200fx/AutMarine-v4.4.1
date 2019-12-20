#pragma once
#ifndef _Mesh3d_Facet_Header
#define _Mesh3d_Facet_Header

#include <Mesh_Facet.hxx>
#include <Mesh3d_FacetTraits.hxx>
#include <Mesh3d_FacetAdaptor.hxx>

namespace AutLib
{

	// Forward Declarations

	class Mesh3d_Facet
		: public Mesh_Facet<Mesh3d_FacetTraits, Mesh3d_FacetAdaptor>
	{

		/*Private Data*/

	public:

		Mesh3d_Facet()
		{}

		Mesh3d_Facet(const Standard_Integer theIndex)
			: Mesh_Facet<Mesh3d_FacetTraits, Mesh3d_FacetAdaptor>(theIndex)
		{}

		Mesh3d_Facet
		(
			const Standard_Integer theIndex,
			const nodePtr& theNode0,
			const nodePtr& theNode1,
			const nodePtr& theNode2
		)
			: Mesh_Facet<Mesh3d_FacetTraits, Mesh3d_FacetAdaptor>(theIndex, theNode0, theNode1, theNode2)
		{}
	};
	
}

#endif // !_Mesh3d_Facet_Header

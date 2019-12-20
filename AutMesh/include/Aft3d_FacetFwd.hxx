#pragma once
#ifndef _Aft3d_FacetFwd_Header
#define _Aft3d_FacetFwd_Header

namespace AutLib
{

	// Forward Declarations
	template
		<
		class FacetTraits,
		class FacetAdaptor
		>
		class Mesh_Facet;

	struct Aft3d_FacetTraits;
	class Aft3d_FacetAdaptor;

	typedef Mesh_Facet<Aft3d_FacetTraits, Aft3d_FacetAdaptor>
		Aft3d_Facet;
}

#endif // !_Aft3d_FacetFwd_Header

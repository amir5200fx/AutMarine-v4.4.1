#pragma once
#ifndef _Mesh2d_ElementFwd_Header
#define _Mesh2d_ElementFwd_Header

namespace AutLib
{

	// Forward Declarations
	struct Mesh2d_ElementTraits;
	class Mesh2d_ElementAdaptor;

	template
		<
		class FacetTraits,
		class FacetAdaptor
		>
		class Mesh_Facet;

	typedef Mesh_Facet<Mesh2d_ElementTraits, Mesh2d_ElementAdaptor>
		Mesh2d_Element;
}

#endif // !_Mesh2d_ElementFwd_Header

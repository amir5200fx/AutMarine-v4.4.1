#pragma once
#ifndef _Mesh2d_ElementAdaptor_Header
#define _Mesh2d_ElementAdaptor_Header

#include <Mesh2d_ElementAdaptorTemplate.hxx>

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

	class Mesh2d_ElementAdaptor
		: public Mesh2d_ElementAdaptorTemplate<Mesh2d_Element>
	{

		/*Private Data*/

	public:

		Mesh2d_ElementAdaptor()
		{}
	};
}

#endif // !_Mesh2d_ElementAdaptor_Header

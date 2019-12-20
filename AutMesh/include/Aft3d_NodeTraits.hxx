#pragma once
#ifndef _Aft3d_NodeTraits_Header
#define _Aft3d_NodeTraits_Header

#include <Pnt3d.hxx>
#include <Aft3d_EdgeFwd.hxx>
#include <Aft3d_FacetFwd.hxx>
#include <Aft3d_ElementFwd.hxx>

namespace AutLib
{

	// Forward Declarations

	struct Aft3d_NodeTraits
	{
		typedef Aft3d_Edge edgeType;
		typedef Aft3d_Facet facetType;
		typedef Aft3d_Element elementType;

		typedef Pnt3d ptType;
	};
}

#endif // !_Aft3d_NodeTraits_Header

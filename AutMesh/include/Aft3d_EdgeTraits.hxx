#pragma once
#ifndef _Aft3d_EdgeTraits_Header
#define _Aft3d_EdgeTraits_Header

#include <Pnt3d.hxx>
#include <Aft3d_NodeFwd.hxx>
#include <Aft3d_FacetFwd.hxx>
#include <Aft3d_ElementFwd.hxx>

namespace AutLib
{

	struct Aft3d_EdgeTraits
	{
		typedef Pnt3d ptType;
		typedef Aft3d_Node nodeType;
		typedef Aft3d_Facet facetType;
		typedef Aft3d_Element elementType;

		enum { geomInfo = 1 };
	};
}

#endif // !_Aft3d_EdgeTraits_Header

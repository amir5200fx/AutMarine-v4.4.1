#pragma once
#ifndef _Aft2d_NodeTraits_Header
#define _Aft2d_NodeTraits_Header

#include <Pnt2d.hxx>
#include <Aft2d_EdgeFwd.hxx>
#include <Aft2d_ElementFwd.hxx>

namespace AutLib
{

	// Forward Declarations
	struct Aft2d_EdgeTraits;

	struct Aft2d_NodeTraits
	{

		typedef Aft2d_Edge edgeType;
		typedef Aft2d_Element elementType;
		typedef void facetType;

		typedef Pnt2d ptType;
	};
}

#endif // !_Aft2d_NodeTraits_Header

#pragma once
#ifndef _Aft2d_NodeAnIsoTraits_Header
#define _Aft2d_NodeAnIsoTraits_Header

#include <Pnt2d.hxx>
#include <Aft2d_EdgeAnIsoFwd.hxx>
#include <Aft2d_ElementAnIsoFwd.hxx>

namespace AutLib
{

	// Forward Declarations

	struct Aft2d_NodeAnIsoTraits
	{

		typedef Aft2d_EdgeAnIso edgeType;
		typedef Aft2d_ElementAnIso elementType;
		typedef void facetType;

		typedef Pnt2d ptType;
	};
}

#endif // !_Aft2d_NodeAnIsoTraits_Header

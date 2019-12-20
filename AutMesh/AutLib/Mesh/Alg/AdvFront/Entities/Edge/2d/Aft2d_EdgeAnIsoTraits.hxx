#pragma once
#ifndef _Aft2d_EdgeAnIsoTraits_Header
#define _Aft2d_EdgeAnIsoTraits_Header

#include <Pnt2d.hxx>
#include <Aft2d_NodeAnIso.hxx>
#include <Aft2d_ElementAnIsoFwd.hxx>

namespace AutLib
{

	// Forward Declarations

	struct Aft2d_EdgeAnIsoTraits
	{

		typedef Pnt2d ptType;
		typedef Aft2d_NodeAnIso nodeType;
		typedef Aft2d_ElementAnIso elementType;

		enum { geomInfo = 1 };
	};

}

#endif // !_Aft2d_EdgeAnIsoTraits_Header

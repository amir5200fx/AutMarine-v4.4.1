#pragma once
#ifndef _Aft2d_ElementAnIsoTraits_Header
#define _Aft2d_ElementAnIsoTraits_Header

#include <Pnt2d.hxx>
#include <Aft2d_NodeAnIsoFwd.hxx>
#include <Aft2d_EdgeAnIsoFwd.hxx>
#include <Aft2d_ElementAnIsoAdaptor.hxx>

namespace AutLib
{

	struct Aft2d_ElementAnIsoTraits
	{

		typedef Aft2d_NodeAnIso nodeType;
		typedef Aft2d_EdgeAnIso edgeType;
		typedef Pnt2d ptType;

		typedef Aft2d_ElementAnIsoAdaptor adaptorType;

		enum
		{
			dim = 2
		};
	};
}

#endif // !_Aft2d_ElementAnIsoTraits_Header

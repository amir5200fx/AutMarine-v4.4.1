#pragma once
#ifndef _Aft2d_ElementTraits_Header
#define _Aft2d_ElementTraits_Header

#include <Pnt2d.hxx>
#include <Aft2d_NodeFwd.hxx>
#include <Aft2d_EdgeFwd.hxx>
#include <Aft2d_ElementAdaptor.hxx>

namespace AutLib
{

	struct Aft2d_ElementTraits
	{

		typedef Aft2d_Node nodeType;
		typedef Aft2d_Edge edgeType;

		typedef Pnt2d ptType;

		typedef Aft2d_ElementAdaptor adaptorType;

		enum
		{
			dim = 2
		};
	};
}

#endif // !_Aft2d_ElementTraits_Header

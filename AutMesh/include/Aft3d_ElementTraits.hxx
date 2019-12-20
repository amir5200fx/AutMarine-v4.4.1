#pragma once
#ifndef _Aft3d_ElementTraits_Header
#define _Aft3d_ElementTraits_Header

#include <Aft3d_NodeFwd.hxx>
#include <Aft3d_EdgeFwd.hxx>
#include <Aft3d_Facet.hxx>
#include <Aft3d_ElementAdaptor.hxx>

namespace AutLib
{

	struct Aft3d_ElementTraits
	{
		typedef Aft3d_Node nodeType;
		typedef Aft3d_Edge edgeType;
		typedef Aft3d_Facet facetType;

		typedef Aft3d_ElementAdaptor adaptorType;

		enum
		{
			dim = 3
		};
	};
}

#endif // !_Aft3d_ElementTraits_Header

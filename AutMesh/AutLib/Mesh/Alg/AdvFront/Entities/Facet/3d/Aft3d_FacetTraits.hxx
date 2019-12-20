#pragma once
#ifndef _Aft3d_FacetTraits_Header
#define _Aft3d_FacetTraits_Header

#include <Pnt3d.hxx>
#include <Aft3d_NodeFwd.hxx>
#include <Aft3d_EdgeFwd.hxx>

namespace AutLib
{

	struct Aft3d_FacetTraits
	{
		typedef Aft3d_Node nodeType;
		typedef Aft3d_Edge edgeType;

		typedef Pnt3d ptType;
	};
}

#endif // !_Aft3d_FacetTraits_Header

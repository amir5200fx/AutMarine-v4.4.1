#pragma once
#ifndef _Aft3d_Facet_Header
#define _Aft3d_Facet_Header

#include <Pnt3d.hxx>
#include <Mesh_Facet.hxx>
#include <Aft3d_FacetAdaptor.hxx>
#include <Aft3d_FacetTraits.hxx>
#include <Aft3d_Edge.hxx>
#include <Aft3d_Node.hxx>

namespace AutLib
{

	typedef Mesh_Facet<Aft3d_FacetTraits, Aft3d_FacetAdaptor>
		Aft3d_Facet;
}

#endif // !_Aft3d_Facet_Header

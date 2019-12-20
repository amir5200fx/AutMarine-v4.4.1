#pragma once
#ifndef _Mesh2d_Element_Header
#define _Mesh2d_Element_Header

#include <Mesh_Facet.hxx>
#include <Mesh2d_ElementAdaptor.hxx>
#include <Mesh2d_ElementTraits.hxx>

namespace AutLib
{

	// Forward Declarations
	
	typedef Mesh_Facet<Mesh2d_ElementTraits, Mesh2d_ElementAdaptor>
		Mesh2d_Element;

	template<>
	template<>
	Mesh2d_Element::array3 Mesh2d_Element::InterpWeights<Mesh2d_Element::array3>(const Pnt2d& theCoord) const;
}

#endif // !_Mesh2d_Element_Header
#pragma once
#ifndef _Aft2d_NodeSurface_Header
#define _Aft2d_NodeSurface_Header

#include <Aft_Node.hxx>
#include <Aft_NodeIdentifierSurface.hxx>
#include <Aft2d_NodeSurfaceTraits.hxx>

namespace AutLib
{

	typedef Aft_Node<Aft2d_NodeSurfaceTraits, Aft_NodeIdentifierSurface>
		Aft2d_NodeSurface;
}

#endif // !_Aft2d_NodeSurface_Header

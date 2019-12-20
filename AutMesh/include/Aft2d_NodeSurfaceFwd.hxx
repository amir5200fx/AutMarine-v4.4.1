#pragma once
#ifndef _Aft2d_NodeSurfaceFwd_Header
#define _Aft2d_NodeSurfaceFwd_Header

namespace AutLib
{

	// Forward Declarations
	template
		<
		class NodeTraits,
		class NodeIdentifier
		>
		class Aft_Node;

	struct Aft2d_NodeSurfaceTraits;
	class Aft_NodeIdentifierSurface;

	typedef Aft_Node<Aft2d_NodeSurfaceTraits, Aft_NodeIdentifierSurface>
		Aft2d_NodeSurface;
}

#endif // !_Aft2d_NodeSurfaceFwd_Header

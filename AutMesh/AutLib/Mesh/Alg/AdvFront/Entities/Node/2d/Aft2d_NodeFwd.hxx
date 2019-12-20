#pragma once
#ifndef _Aft2d_NodeFwd_Header
#define _Aft2d_NodeFwd_Header

namespace AutLib
{

	// Forward Declarations
	template
		<
		class NodeTraits,
		class NodeIdentifier
		>
		class Aft_Node;

	struct Aft2d_NodeTraits;
	class Aft_NodeIdentifier;

	typedef Aft_Node<Aft2d_NodeTraits, Aft_NodeIdentifier>
		Aft2d_Node;
}

#endif // !_Aft2d_NodeFwd_Header

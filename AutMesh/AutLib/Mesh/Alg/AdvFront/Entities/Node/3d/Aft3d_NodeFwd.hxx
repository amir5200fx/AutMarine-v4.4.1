#pragma once
#ifndef _Aft3d_NodeFwd_Header
#define _Aft3d_NodeFwd_Header

namespace AutLib
{

	// Forward Declarations
	template
		<
		class NodeTraits,
		class NodeIdentifier
		>
		class Aft_Node;

	struct Aft3d_NodeTraits;
	class Aft_NodeIdentifier;

	typedef Aft_Node<Aft3d_NodeTraits, Aft_NodeIdentifier>
		Aft3d_Node;
}

#endif // !_Aft3d_NodeFwd_Header

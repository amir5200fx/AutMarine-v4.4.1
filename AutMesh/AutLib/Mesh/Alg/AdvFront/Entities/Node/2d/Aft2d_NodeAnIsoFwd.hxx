#pragma once
#ifndef _Aft2d_NodeAnIsoFwd_Header
#define _Aft2d_NodeAnIsoFwd_Header

namespace AutLib
{

	// Forward Declarations
	template
		<
		class NodeTraits,
		class NodeIdentifier
		>
		class Aft_Node;

	struct Aft2d_NodeAnIsoTraits;
	class Aft_NodeIdentifierAnIso;

	typedef Aft_Node<Aft2d_NodeAnIsoTraits, Aft_NodeIdentifierAnIso>
		Aft2d_NodeAnIso;
}

#endif // !_Aft2d_NodeAnIsoFwd_Header

#pragma once
#ifndef _Aft3d_NodeAnIsoFwd_Header
#define _Aft3d_NodeAnIsoFwd_Header

namespace AutLib
{

	// Forward Declarations
	template
		<
		class NodeTraits,
		class NodeIdentifier
		>
		class Aft_Node;

	struct Aft3d_NodeAnIsoTraits;
	class Aft_NodeIdentifierAnIso;

	typedef Aft_Node<Aft3d_NodeAnIsoTraits, Aft_NodeIdentifierAnIso>
		Aft3d_NodeAnIso;
}

#endif // !_Aft3d_NodeAnIsoFwd_Header

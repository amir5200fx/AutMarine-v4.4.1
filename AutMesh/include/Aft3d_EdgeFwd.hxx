#pragma once
#ifndef _Aft3d_EdgeFwd_Header
#define _Aft3d_EdgeFwd_Header

namespace AutLib
{

	// Forward Declarations
	template<class EdgeTraits>
	class Aft_Edge;

	struct Aft3d_EdgeTraits;

	typedef Aft_Edge<Aft3d_EdgeTraits> Aft3d_Edge;
}

#endif // !_Aft3d_EdgeFwd_Header

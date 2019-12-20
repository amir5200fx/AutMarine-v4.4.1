#pragma once
#ifndef _Aft2d_EdgeAnIsoFwd_Header
#define _Aft2d_EdgeAnIsoFwd_Header

namespace AutLib
{

	// Forward Declarations
	template<class EdgeTraits>
	class Aft_Edge;

	struct Aft2d_EdgeAnIsoTraits;

	typedef Aft_Edge<Aft2d_EdgeAnIsoTraits> Aft2d_EdgeAnIso;
}

#endif // !_Aft2d_EdgeAnIsoFwd_Header

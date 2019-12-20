#pragma once
#ifndef _Aft2d_ElementAnIsoFwd_Header
#define _Aft2d_ElementAnIsoFwd_Header

namespace AutLib
{
	// Forward Declarations
	struct Aft2d_ElementAnIsoTraits;

	template<class ElementTraits>
	class Aft_Element;

	typedef Aft_Element<Aft2d_ElementAnIsoTraits>
		Aft2d_ElementAnIso;
}

#endif // !_Aft2d_ElementAnIsoFwd_Header

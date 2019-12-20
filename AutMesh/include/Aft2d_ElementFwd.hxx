#pragma once
#ifndef _Aft2d_ElementFwd_Header
#define _Aft2d_ElementFwd_Header

namespace AutLib
{
	// Forward Declarations
	struct Aft2d_ElementTraits;

	template<class ElementTraits>
	class Aft_Element;

	typedef Aft_Element<Aft2d_ElementTraits>
		Aft2d_Element;
}

#endif // !_Aft2d_ElementFwd_Header

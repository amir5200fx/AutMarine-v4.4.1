#pragma once
#ifndef _Aft3d_ElementFwd_Header
#define _Aft3d_ElementFwd_Header

namespace AutLib
{

	// Forward Declarations
	struct Aft3d_ElementTraits;

	template<class ElementTraits>
	class Aft_Element;

	typedef Aft_Element<Aft3d_ElementTraits>
		Aft3d_Element;
}

#endif // !_Aft3d_ElementFwd_Header

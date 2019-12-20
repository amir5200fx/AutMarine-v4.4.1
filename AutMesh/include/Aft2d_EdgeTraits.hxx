#pragma once
#ifndef _Aft2d_EdgeTraits_Header
#define _Aft2d_EdgeTraits_Header

#include <Pnt2d.hxx>
#include <Aft2d_Node.hxx>
#include <Aft2d_ElementFwd.hxx>

namespace AutLib
{

	// Forward Declarations
	
	struct Aft2d_EdgeTraits
	{

		typedef Pnt2d ptType;
		typedef Aft2d_Node nodeType;
		typedef Aft2d_Element elementType;
		
		enum {geomInfo = 1};
	};

}

#endif // !_Aft2d_EdgeTraits_Header

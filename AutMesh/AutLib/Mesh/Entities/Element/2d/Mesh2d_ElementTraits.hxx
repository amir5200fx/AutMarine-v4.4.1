#pragma once
#ifndef _Mesh2d_ElementTraits_Header
#define _Mesh2d_ElementTraits_Header

#include <Pnt2d.hxx>

namespace AutLib
{

	// Forward Declarations
	class Mesh2d_Node;
	class Mesh2d_Edge;
	
	struct Mesh2d_ElementTraits
	{

		typedef Mesh2d_Node nodeType;
		typedef Mesh2d_Edge edgeType;

		typedef Pnt2d ptType;
	};
}

#endif // !_Mesh2d_ElementTraits_Header

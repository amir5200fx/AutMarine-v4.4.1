#pragma once
#ifndef _Mesh3d_FacetTraits_Header
#define _Mesh3d_FacetTraits_Header

namespace AutLib
{

	// Forward Declarations
	class Mesh3d_Node;
	class Mesh3d_Edge;

	struct Mesh3d_FacetTraits
	{
		typedef Mesh3d_Node nodeType;
		typedef Mesh3d_Edge edgeType;
	};
}

#endif // !_Mesh3d_FacetTraits_Header

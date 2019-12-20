#pragma once
#ifndef _MeshAPI_Traits_Header
#define _MeshAPI_Traits_Header

#include <Aft2d_gSegmentEdgeFwd.hxx>

namespace AutLib
{

	// Forward Declarations
	class GModel_Surface;
	class Cad3d_GModel;

	template<class SurfType> struct boundary_element_type {};
	template<> struct boundary_element_type<GModel_Surface> { typedef Aft2d_gSegmentEdge type; };


	template<class SurfType> struct model_type {};
	template<> struct model_type<GModel_Surface> { typedef Cad3d_GModel type; };
}

#endif // !_MeshAPI_Traits_Header

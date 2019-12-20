#pragma once
#ifndef _Aft2d_ElementSurfaceAdaptor_Header
#define _Aft2d_ElementSurfaceAdaptor_Header

#include <Mesh2d_ElementAdaptorTemplate.hxx>
#include <Aft2d_ElementSurfaceFwd.hxx>

namespace AutLib
{

	class Aft2d_ElementSurfaceAdaptor
		: public Mesh2d_ElementAdaptorTemplate<Aft2d_ElementSurface>
	{

		/*Private Data*/

	public:

		Aft2d_ElementSurfaceAdaptor()
		{}
	};
}

#endif // !_Aft2d_ElementSurfaceAdaptor_Header

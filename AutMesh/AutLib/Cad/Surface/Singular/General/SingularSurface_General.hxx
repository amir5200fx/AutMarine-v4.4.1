#pragma once
#ifndef _SingularSurface_General_Header
#define _SingularSurface_General_Header

#include <Cad_SingularSurface.hxx>

namespace AutLib
{

	template<class SurfType>
	class SingularSurface_General
		: public Cad_SingularSurface<SurfType>
	{

		/*Private Data*/

	public:

		SingularSurface_General()
		{}
	};
}

#endif // !_SingularSurface_General_Header

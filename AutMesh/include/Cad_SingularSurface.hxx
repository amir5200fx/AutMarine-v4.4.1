#pragma once
#ifndef _Cad_SingularSurface_Header
#define _Cad_SingularSurface_Header

#include <Cad_IrregularSurface.hxx>

namespace AutLib
{

	template<class SurfType>
	class Cad_SingularSurface
		: public Cad_IrregularSurface<SurfType>
	{

		/*private Data*/

	protected:

		Cad_SingularSurface(const SurfType& theSurface)
			: Cad_IrregularSurface<SurfType>(theSurface)
		{}
	};
}

#endif // !_Cad_SingularSurface_Header

#pragma once
#ifndef _Cad_DefectSurface_Header
#define _Cad_DefectSurface_Header

#include <Cad_IrregularSurface.hxx>

namespace AutLib
{

	template<class SurfType>
	class Cad_DefectSurface
		: public Cad_IrregularSurface<SurfType>
	{

		/*Private Data*/

	protected:

		Cad_DefectSurface(const SurfType& theSurface)
			: Cad_IrregularSurface<SurfType>(theSurface)
		{}
	};
}

#endif // !_Cad_DefectSurface_Header

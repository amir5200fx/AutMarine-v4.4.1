#pragma once
#ifndef _DefectSurface_Wire_Header
#define _DefectSurface_Wire_Header

#include <Cad_DefectSurface.hxx>

namespace AutLib
{

	template<class SurfType>
	class DefectSurface_Wire
		: public Cad_DefectSurface<SurfType>
	{

		/*Private Data*/

	protected:

		DefectSurface_Wire(const SurfType& theSurface)
			: Cad_DefectSurface<SurfType>(theSurface)
		{}
	};
}

#endif // !_DefectSurface_Wire_Header

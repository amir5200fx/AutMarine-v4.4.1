#pragma once
#ifndef _Cad_IrregularSurface_Header
#define _Cad_IrregularSurface_Header

#include <word.hxx>

#include <memory>

namespace AutLib
{

	template<class SurfType>
	class Cad_IrregularSurface
		: public SurfType
	{

		/*Private Data*/

	protected:

		Cad_IrregularSurface(const SurfType& theSurface)
			: SurfType(theSurface)
		{}

	public:

		virtual const word& TypeName() const = 0;
	};
}

#endif // !_Cad_IrregularSurface_Header

#pragma once
#ifndef _DefectSurface_WireMissedOuter_Header
#define _DefectSurface_WireMissedOuter_Header

#include <Standard_TypeDef.hxx>
#include <DefectSurface_Wire.hxx>

#include <memory>

namespace AutLib
{

	struct DefectSurface_WireMissedOuterBase
	{
		static const word typeName;
	};

	template<class SurfType>
	class DefectSurface_WireMissedOuter
		: public DefectSurface_Wire<SurfType>
		, public DefectSurface_WireMissedOuterBase
	{

		typedef typename SurfType::wireType wireType;

		/*Private Data*/

	public:

		DefectSurface_WireMissedOuter(const SurfType& theSurface)
			: DefectSurface_Wire<SurfType>(theSurface)
		{}

		const word& TypeName() const override
		{
			return typeName;
		}
	};
}

#endif // !_DefectSurface_WireMissedOuter_Header

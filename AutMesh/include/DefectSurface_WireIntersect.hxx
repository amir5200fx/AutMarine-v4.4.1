#pragma once
#ifndef _DefectSurface_WireIntersect_Header
#define _DefectSurface_WireIntersect_Header

#include <Standard_TypeDef.hxx>
#include <DefectSurface_Wire.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	struct DefectSurface_WireIntersectBase
	{
		static const word typeName;
	};

	template<class SurfType>
	class DefectSurface_WireIntersect
		: public DefectSurface_Wire<SurfType>
		, public DefectSurface_WireIntersectBase
	{

		typedef typename SurfType::wireType wireType;

		/*Private Data*/

		std::vector<std::shared_ptr<wireType>> theWires_;

	public:

		DefectSurface_WireIntersect
		(
			const SurfType& theSurface,
			const std::vector<std::shared_ptr<wireType>>& theWires
		)
			: DefectSurface_Wire<SurfType>(theSurface)
			, theWires_(theWires)
		{}

		const word& TypeName() const override
		{
			return typeName;
		}


	};
}

#endif // !_DefectSurface_WireIntersect_Header

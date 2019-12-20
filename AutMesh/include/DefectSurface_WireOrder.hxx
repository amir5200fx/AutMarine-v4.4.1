#pragma once
#ifndef _DefectSurface_WireOrder_Header
#define _DefectSurface_WireOrder_Header

#include <Standard_TypeDef.hxx>
#include <DefectSurface_Wire.hxx>

#include <vector>

namespace AutLib
{

	struct DefectSurface_WireOrderBase
	{
		static const word typeName;
	};

	template<class SurfType>
	class DefectSurface_WireOrder
		: public DefectSurface_Wire<SurfType>
		, public DefectSurface_WireOrderBase
	{

		typedef typename SurfType::wireType wireType;

		/*Private Data*/

		std::vector<std::shared_ptr<wireType>> theWires_;

	public:

		

		DefectSurface_WireOrder
		(
			const SurfType& theSurface, 
			const std::vector<std::shared_ptr<wireType>>& theWires
		)
			: DefectSurface_Wire<SurfType>(theSurface)
			, theWires_(theWires)
		{}

		const std::vector<std::shared_ptr<wireType>>& defWires() const
		{
			return theWires_;
		}

		const word& TypeName() const override
		{
			return typeName;
		}

		static Standard_Boolean Check
		(
			const SurfType& theSurface, 
			std::vector<std::shared_ptr<wireType>>& theWires
		);

		static Standard_Boolean Check
		(
			const wireType& theWire
		);
	};
}

#include <DefectSurface_WireOrderI.hxx>

#endif // !_DefectSurface_WireOrder_Header

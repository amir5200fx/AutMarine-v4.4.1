#pragma once
#ifndef _DefectSurface_WireOpen_Header
#define _DefectSurface_WireOpen_Header

#include <Standard_TypeDef.hxx>
#include <DefectSurface_Wire.hxx>

#include <vector>
#include <memory>

namespace AutLib
{

	struct DefectSurface_WireOpenBase
	{
		static const word typeName;
	};

	template<class SurfType>
	class DefectSurface_WireOpen
		: public DefectSurface_Wire<SurfType>
		, public DefectSurface_WireOpenBase
	{

		typedef typename SurfType::wireType wireType;

		/*Private Data*/

		std::vector<std::shared_ptr<wireType>> theWires_;

	public:

		DefectSurface_WireOpen
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

		//- Static functions and operators

		static Standard_Boolean Check
		(
			const SurfType& theSurface,
			std::vector<std::shared_ptr<wireType>>& theWires,
			const Standard_Real theTol
		);

		static Standard_Boolean Check
		(
			const wireType& theWire, 
			const Standard_Real theTol
		);
	};
}

#include <DefectSurface_WireOpenI.hxx>

#endif // !_DefectSurface_WireOpen_Header

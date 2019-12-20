#pragma once
#ifndef _ImpSurf_defWire_Open_Header
#define _ImpSurf_defWire_Open_Header

#include <ImpSurf_defectWire.hxx>

namespace AutLib
{

	template<class SurfType>
	class ImpSurf_defWire_Open
		: public ImpSurf_defectWire<SurfType>
	{

		typedef typename SurfType::wireType wireType;

		/*Private Data*/

		std::vector<std::shared_ptr<wireType>> theWires_;

	public:

		static const word typeName;

		typedef ImpSurf_defectWire<SurfType> base;

		ImpSurf_defWire_Open(const SurfType& theSurface)
			: ImpSurf_defectWire<SurfType>(theSurface)
		{}

		ImpSurf_defWire_Open
		(
			const Handle(typename SurfType::geomType)& theGeom,
			const typename base::outer& theOuter,
			const typename base::inner& theInner,
			const std::vector<std::shared_ptr<wireType>>& theWires
		)
			: ImpSurf_defectWire<SurfType>(theGeom, theOuter, theInner)
			, theWires_(theWires)
		{}

		const std::vector<std::shared_ptr<wireType>>& Wires() const
		{
			return theWires_;
		}

		const word& TypeName() const override
		{
			return typeName;
		}

		//- Static functions and operators

		static Standard_Boolean
			Check
			(
				const SurfType& theSurface,
				std::vector<std::shared_ptr<wireType>>& theWires,
				const Standard_Real theTol
			);

		static Standard_Boolean 
			Check
		(
			const wireType& theWire,
			const Standard_Real theTol
		);
	};
}

#include <ImpSurf_defWire_OpenI.hxx>

#endif // !_ImpSurf_defWire_Open_Header

#pragma once
#ifndef _SingularityZone_Pole_Loop_Header
#define _SingularityZone_Pole_Loop_Header

#include <SingularityZone_Pole.hxx>

namespace AutLib
{

	template<class SurfPln>
	class SingularityZone_Pole_Loop
		: public SingularityZone_Pole<SurfPln>
	{

		typedef typename SurfPln::plnCurve plnCurve;

		/*Private Data*/

		std::shared_ptr<plnCurve> theHorizon0_;
		std::shared_ptr<plnCurve> theHorizon1_;
		std::shared_ptr<plnCurve> theHorizon2_;
		std::shared_ptr<plnCurve> theHorizon3_;

	public:

		static const word typeName;

		SingularityZone_Pole_Loop()
		{}

		SingularityZone_Pole_Loop
		(
			const std::shared_ptr<plnCurve>& theHorizon0,
			const std::shared_ptr<plnCurve>& theHorizon1,
			const std::shared_ptr<plnCurve>& theHorizon2,
			const std::shared_ptr<plnCurve>& theHorizon3
		)
			: theHorizon0_(theHorizon0)
			, theHorizon1_(theHorizon1)
			, theHorizon2_(theHorizon2)
			, theHorizon3_(theHorizon3)
		{}

		Standard_Boolean IsLoaded() const
		{
			if (!theHorizon0_) return Standard_False;
			if (!theHorizon1_) return Standard_False;
			if (!theHorizon2_) return Standard_False;
			if (!theHorizon3_) return Standard_False;
			return Standard_True;
		}

		const std::shared_ptr<plnCurve>& Horizon0() const
		{
			return theHorizon0_;
		}

		const std::shared_ptr<plnCurve>& Horizon1() const
		{
			return theHorizon1_;
		}

		const std::shared_ptr<plnCurve>& Horizon2() const
		{
			return theHorizon2_;
		}

		const std::shared_ptr<plnCurve>& Horizon3() const
		{
			return theHorizon3_;
		}

		Standard_Integer NbHorizons() const override
		{
			return 4;
		}

		const std::shared_ptr<plnCurve>& 
			Horizon
			(
				const Standard_Integer theIndex
			) const override
		{
			return (&theHorizon0_)[theIndex];
		}

		Mesh_SingularityType Type() const override
		{
			return SingularityType_Pole_Loop;
		}

		const word& TypeName() const
		{
			return typeName;
		}

		void LoadHorizons
		(
			const std::shared_ptr<plnCurve>& theHorizon0,
			const std::shared_ptr<plnCurve>& theHorizon1,
			const std::shared_ptr<plnCurve>& theHorizon2,
			const std::shared_ptr<plnCurve>& theHorizon3
		)
		{
			theHorizon0_ = theHorizon0;
			theHorizon1_ = theHorizon1;
			theHorizon2_ = theHorizon2;
			theHorizon3_ = theHorizon3;
		}
	};
}

#endif // !_SingularityZone_Pole_Loop_Header

#pragma once
#ifndef _SingularityZone_Line_TwoSided_Header
#define _SingularityZone_Line_TwoSided_Header

#include <SingularityZone_Line.hxx>

namespace AutLib
{

	template<class SurfPln>
	class SingularityZone_Line_TwoSided
		: public SingularityZone_Line<SurfPln>
	{

		typedef typename SurfPln::plnCurve plnCurve;

		/*Private Data*/

		std::shared_ptr<plnCurve> theHorizon0_;
		std::shared_ptr<plnCurve> theHorizon1_;

	public:

		static const word typeName;

		SingularityZone_Line_TwoSided()
		{}

		SingularityZone_Line_TwoSided
		(
			const std::shared_ptr<plnCurve>& theHorizon0,
			const std::shared_ptr<plnCurve>& theHorizon1
		)
			: theHorizon0_(theHorizon0)
			, theHorizon1_(theHorizon1)
		{}

		Standard_Boolean IsLoaded() const
		{
			if (!theHorizon0_) return Standard_False;
			if (!theHorizon1_) return Standard_False;
			return Standard_True;
		}

		Standard_Integer NbHorizons() const override
		{
			return 2;
		}

		const std::shared_ptr<plnCurve>&
			Horizon
			(
				const Standard_Integer theIndex
			) const override
		{
			return (&theHorizon0_)[theIndex];
		}

		const std::shared_ptr<plnCurve>& Horizon0() const
		{
			return theHorizon0_;
		}

		const std::shared_ptr<plnCurve>& Horizon1() const
		{
			return theHorizon1_;
		}

		Mesh_SingularityType Type() const override
		{
			return SingularityType_Line_TwoSided;
		}

		const word& TypeName() const override
		{
			return typeName;
		}

		void LoadHorizons
		(
			const std::shared_ptr<plnCurve>& theHorizon0,
			const std::shared_ptr<plnCurve>& theHorizon1
		)
		{
			theHorizon0_ = theHorizon0;
			theHorizon1_ = theHorizon1;
		}
	};
}

#endif // !_SingularityZone_Line_TwoSided_Header

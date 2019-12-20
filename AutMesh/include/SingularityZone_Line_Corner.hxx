#pragma once
#ifndef _SingularityZone_Line_Corner_Header
#define _SingularityZone_Line_Corner_Header

#include <SingularityZone_Line.hxx>

namespace AutLib
{

	template<class SurfPln>
	class SingularityZone_Line_Corner
		: public SingularityZone_Line<SurfPln>
	{

		typedef typename SurfPln::plnCurve plnCurve;

		/*private Data*/

		std::shared_ptr<plnCurve> theHorizon0_;
		std::shared_ptr<plnCurve> theHorizon1_;

	public:

		static const word typeName;

		SingularityZone_Line_Corner()
		{}

		SingularityZone_Line_Corner
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

		const std::shared_ptr<plnCurve>& Horizon0() const
		{
			return theHorizon0_;
		}

		const std::shared_ptr<plnCurve>& Horizon1() const
		{
			return theHorizon1_;
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

		Mesh_SingularityType Type() const override
		{
			return SingularityType_Line_Corner;
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

#endif // !_SingularityZone_Line_Corner_Header

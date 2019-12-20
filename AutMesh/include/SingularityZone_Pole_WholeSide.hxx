#pragma once
#ifndef _SingularityZone_Pole_WholeSide_Header
#define _SingularityZone_Pole_WholeSide_Header

#include <SingularityZone_Pole.hxx>

namespace AutLib
{

	template<class SurfPln>
	class SingularityZone_Pole_WholeSide
		: public SingularityZone_Pole<SurfPln>
	{

		typedef typename SurfPln::plnCurve plnCurve;

		/*Private Data*/

		std::shared_ptr<plnCurve> theHorizon_;

	public:

		static const word typeName;

		SingularityZone_Pole_WholeSide()
		{}

		SingularityZone_Pole_WholeSide
		(
			const std::shared_ptr<plnCurve>& theHorizon
		)
			: theHorizon_(theHorizon)
		{}

		Standard_Boolean IsLoaded() const
		{
			if (!theHorizon_) return Standard_False;
			return Standard_True;
		}

		Standard_Integer NbHorizons() const override
		{
			return 1;
		}

		const std::shared_ptr<plnCurve>&
			Horizon
			(
				const Standard_Integer theIndex
			) const override
		{
			return theHorizon_;
		}

		const std::shared_ptr<plnCurve>& Horizon() const
		{
			return theHorizon_;
		}

		Mesh_SingularityType Type() const override
		{
			return SingularityType_Pole_WholeSide;
		}

		const word& TypeName() const
		{
			return typeName;
		}

		void LoadHorizon(const std::shared_ptr<plnCurve>& theHorizon)
		{
			theHorizon_ = theHorizon;
		}
	};
}

#endif // !_SingularityZone_Pole_WholeSide_Header

#pragma once
#ifndef _SingularityZone_Pole_Corner_Header
#define _SingularityZone_Pole_Corner_Header

#include <SingularityZone_Pole.hxx>

namespace AutLib
{

	template<class SurfPln>
	class SingularityZone_Pole_Corner
		: public SingularityZone_Pole<SurfPln>
	{

		typedef typename SurfPln::plnCurve plnCurve;

		/*Private Data*/

		std::shared_ptr<plnCurve> theHorizon_;

	public:

		static const word typeName;

		SingularityZone_Pole_Corner()
		{}

		SingularityZone_Pole_Corner
		(
			const std::shared_ptr<plnCurve>& theHorizon
		)
			: theHorizon_(theHorizon)
		{}

		Mesh_SingularityType Type() const override
		{
			return SingularityType_Pole_Corner;
		}

		const word& TypeName() const override
		{
			return typeName;
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

		void LoadHorizon(const std::shared_ptr<plnCurve>& theHorizon)
		{
			theHorizon_ = theHorizon;
		}
	};
}

#endif // !_SingularityZone_Pole_Corner_Header

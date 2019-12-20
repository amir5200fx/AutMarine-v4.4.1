#pragma once
#ifndef _SingularityZone_Line_WholeSide_Header
#define _SingularityZone_Line_WholeSide_Header

#include <SingularityZone_Line.hxx>

namespace AutLib
{

	template<class SurfPln>
	class SingularityZone_Line_WholeSide
		: public SingularityZone_Line<SurfPln>
	{

		typedef typename SurfPln::plnCurve plnCurve;

		/*Private Data*/

		std::shared_ptr<plnCurve> theHorizon_;

	public:

		static const word typeName;

		SingularityZone_Line_WholeSide()
		{}

		SingularityZone_Line_WholeSide
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
			return SingularityType_Line_WholeSide;
		}

		const word& TypeName() const override
		{
			return typeName;
		}

		void LoadHorizon(const std::shared_ptr<plnCurve>& theHorizon)
		{
			theHorizon_ = theHorizon;
		}
	};
}

#endif // !_SingularityZone_Line_WholeSide_Header

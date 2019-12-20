#pragma once
#ifndef _Singularity_Horizon_Header
#define _Singularity_Horizon_Header

#include <Global_Done.hxx>
#include <Entity2d_PolygonFwd.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class Geo_ApprxSurfMetric;
	class Knit2d_ChainNode;

	template<class NodeType>
	class Knit_Chain;

	typedef Knit_Chain<Knit2d_ChainNode> Knit2d_Chain;

	class Singularity_Horizon
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Geo_ApprxSurfMetric> theApprox_;
		std::shared_ptr<Knit2d_Chain> theKnitAlg_;

	public:

		Singularity_Horizon()
		{}

		Singularity_Horizon
		(
			const std::shared_ptr<Geo_ApprxSurfMetric>& theApprox
		)
			: theApprox_(theApprox)
		{}

		const std::shared_ptr<Knit2d_Chain>& KnitAlg() const
		{
			return theKnitAlg_;
		}

		const std::shared_ptr<Geo_ApprxSurfMetric>& Approx() const
		{
			return theApprox_;
		}

		Standard_Integer NbHorizons() const;

		const std::shared_ptr<Entity2d_Polygon>& Horizon
		(
			const Standard_Integer theIndex
		) const;

		Standard_Boolean HasHorizon() const;

		Standard_Boolean IsLoaded() const
		{
			return (Standard_Boolean)theApprox_;
		}

		void LoadApprox
		(
			const std::shared_ptr<Geo_ApprxSurfMetric>& theApprox
		)
		{
			theApprox_ = theApprox;
		}

		void Perform();
	};
}

#endif // !_Singularity_Horizon_Header

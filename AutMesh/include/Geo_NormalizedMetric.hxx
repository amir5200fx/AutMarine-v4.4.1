#pragma once
#ifndef _Geo_NormalizedMetric_Header
#define _Geo_NormalizedMetric_Header

#include <Global_Done.hxx>
#include <Global_Verbose.hxx>

#include <memory>
#include <iostream>

//#include "GModel_Surface.hxx"

namespace AutLib
{

	// Forward Declarations
	class Geo_NormalizedMetricInfo;
	class Numeric_AdaptIntegrationInfo;
	class Geo_ApprxSurfMetric;

	template<class SurfType>
	class Geo_NormalizedMetric
		: public Global_Done
		, public Global_Verbose
	{

		typedef Geo_NormalizedMetricInfo info;
		typedef Numeric_AdaptIntegrationInfo intgInfo;

		/*Private Data*/

		std::shared_ptr<SurfType> theSurface_;
		std::shared_ptr<Geo_ApprxSurfMetric> theApprox_;
		std::shared_ptr<info> theInfo_;

		std::shared_ptr<SurfType> theNormalized_;

		Standard_Boolean Applied_;

		Standard_Real 
			CalcMaxCharLengthU
			(
				intgInfo& theInfo
			) const;

		Standard_Real 
			CalcMaxCharLengthV
			(
				intgInfo& theInfo
			) const;

	public:

		Geo_NormalizedMetric
		(
			const std::shared_ptr<info>& theInfo
		)
			: theInfo_(theInfo)
			, Applied_(Standard_False)
		{}

		Geo_NormalizedMetric
		(
			const std::shared_ptr<SurfType>& theSurface,
			const std::shared_ptr<Geo_ApprxSurfMetric>& theApprox,
			const std::shared_ptr<info>& theInfo
		)
			: theInfo_(theInfo)
			, theSurface_(theSurface)
			, theApprox_(theApprox)
			, Applied_(Standard_False)
		{}

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		const std::shared_ptr<SurfType>& Surface() const
		{
			return theSurface_;
		}

		const std::shared_ptr<Geo_ApprxSurfMetric>& Approx() const
		{
			return theApprox_;
		}

		const std::shared_ptr<SurfType>& Normalized() const
		{
			return theNormalized_;
		}

		Standard_Boolean Applied() const
		{
			return Applied_;
		}

		void Perform(std::ostream& os);

		void LoadSurface
		(
			const std::shared_ptr<SurfType>& theSurface
		)
		{
			theSurface_ = theSurface;
		}

		void LoadApprox
		(
			const std::shared_ptr<Geo_ApprxSurfMetric>& theApprox
		)
		{
			theApprox_ = theApprox;
		}
	};
}

#include <Geo_NormalizedMetricI.hxx>

#endif // !_Geo_NormalizedMetric_Header

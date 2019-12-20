#pragma once
#ifndef _MeshAPI_ModelAnalysisInfo_Header
#define _MeshAPI_ModelAnalysisInfo_Header

#include <Standard_TypeDef.hxx>
#include <MeshAPI_Info.hxx>

#include <memory>
#include <map>

namespace AutLib
{

	class MeshAPI_ModelAnalysisInfo
	{

		typedef Geo_ApprxSurfMetricInfo metricApproxInfo;
		typedef Singularity_TypeDetectionInfo singlDetectInfo;
		typedef Geo_NormalizedMetricInfo normInfo;
		typedef Geo_PlaneEqualizerInfo equalizerInfo;

		/*Private Data*/

		Standard_Real theMinSize_;

		std::shared_ptr<metricApproxInfo> theGlobalMetricApproxInfo_;
		std::shared_ptr<singlDetectInfo> theGlobalSinglDetectInfo_;
		std::shared_ptr<normInfo> theNormInfo_;
		std::shared_ptr<equalizerInfo> theEqualInfo_;

		std::map<Standard_Integer, std::shared_ptr<metricApproxInfo>>
			theMetricApproxInfo_;

		std::map<Standard_Integer, std::shared_ptr<singlDetectInfo>>
			theSinglDetectInfo_;

		Standard_Boolean OverrideMetricApprox_;
		Standard_Boolean OverrideSingDetect_;

	public:

		MeshAPI_ModelAnalysisInfo();

		static const Standard_Real DEFAULT_MIN_SIZE;

		Standard_Real MinSize() const
		{
			return theMinSize_;
		}

		Standard_Boolean OverrideMetricApproxInfo() const
		{
			return OverrideMetricApprox_;
		}

		Standard_Boolean OverrideSingDetectInfo() const
		{
			return OverrideSingDetect_;
		}

		const std::shared_ptr<metricApproxInfo>&
			GlobalMetricApproxInfo() const
		{
			return theGlobalMetricApproxInfo_;
		}

		const std::shared_ptr<singlDetectInfo>&
			GlobalSinglDetectInfo() const
		{
			return theGlobalSinglDetectInfo_;
		}

		const std::shared_ptr<normInfo>& NormalizedMetricInfo() const
		{
			return theNormInfo_;
		}

		const std::shared_ptr<equalizerInfo>& EqualizerMetricInfo() const
		{
			return theEqualInfo_;
		}

		const std::map<Standard_Integer, std::shared_ptr<metricApproxInfo>>&
			MetricApproxInfo() const
		{
			return theMetricApproxInfo_;
		}

		const std::map<Standard_Integer, std::shared_ptr<singlDetectInfo>>&
			SinglDetectInfo() const
		{
			return theSinglDetectInfo_;
		}

		void SetMinSize(const Standard_Real theSize)
		{
			theMinSize_ = theSize;
		}

		void SetToOverrideMetricApproxInfo();

		void SetToOverrideSingDetectInfo();

		void OverrideGlobalMetricApproxInfo
		(
			const std::shared_ptr<metricApproxInfo>& theInfo
		)
		{
			theGlobalMetricApproxInfo_ = theInfo;
		}

		void OverrideGlobalSingDetectInfo
		(
			const std::shared_ptr<singlDetectInfo>& theInfo
		)
		{
			theGlobalSinglDetectInfo_ = theInfo;
		}

		void OverrideNormalizedMetricInfo
		(
			const std::shared_ptr<normInfo>& theInfo
		)
		{
			theNormInfo_ = theInfo;
		}

		void OverrideEqualizerMetricInfo
		(
			const std::shared_ptr<equalizerInfo>& theInfo
		)
		{
			theEqualInfo_ = theInfo;
		}

		void OverrideMetricApproxInfo
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<metricApproxInfo>& theInfo
		);

		void OverrideSingDetectInfo
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<singlDetectInfo>& theInfo
		);


		//- Static functions and operators
	};
}

#endif // !_MeshAPI_ModelAnalysisInfo_Header

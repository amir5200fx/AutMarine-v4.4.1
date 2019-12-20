#pragma once
#ifndef _Geo_NormalizedMetricInfo_Header
#define _Geo_NormalizedMetricInfo_Header

#include <Standard_TypeDef.hxx>
#include <Mesh_Info.hxx>

#include <memory>

namespace AutLib
{

	class Geo_NormalizedMetricInfo
	{

		typedef Numeric_AdaptIntegrationInfo intgInfo;

		/*Private Data*/

		Standard_Real theMaxDet_;

		Standard_Integer theNbSegmentsU_;
		Standard_Integer theNbSegmentsV_;

		std::shared_ptr<intgInfo> theIntgInfo_;

	public:

		static const Standard_Real DEFAULT_MAX_DETERMINANT;

		static const Standard_Integer DEFAULT_NB_SEGMENTS_U;
		static const Standard_Integer DEFAULT_NB_SEGMENTS_V;

		Geo_NormalizedMetricInfo();

		Standard_Real MaxDeterminant() const
		{
			return theMaxDet_;
		}

		Standard_Integer NbSegmentsU() const
		{
			return theNbSegmentsU_;
		}

		Standard_Integer NbSegmentsV() const
		{
			return theNbSegmentsV_;
		}

		const std::shared_ptr<intgInfo>& IntegrationInfo() const
		{
			return theIntgInfo_;
		}

		void SetMaxDeterminant
		(
			const Standard_Real theMax
		)
		{
			theMaxDet_ = theMax;
		}

		void SetNbSegmentsU
		(
			const Standard_Integer theSegments
		)
		{
			theNbSegmentsU_ = theSegments;
		}

		void SetNbSegmentsV
		(
			const Standard_Integer theSegments
		)
		{
			theNbSegmentsV_ = theSegments;
		}

		void OverrideIntgInfo(const std::shared_ptr<intgInfo>& theInfo)
		{
			theIntgInfo_ = theInfo;
		}
	};
}

#endif // !_Geo_NormalizedMetricInfo_Header

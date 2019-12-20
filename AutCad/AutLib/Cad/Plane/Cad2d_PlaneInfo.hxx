#pragma once
#ifndef _Cad2d_PlaneInfo_Header
#define _Cad2d_PlaneInfo_Header

#include <Geo_ApprxCurveInfo.hxx>

#include <memory>

namespace AutLib
{

	extern std::shared_ptr<Geo_ApprxCurveInfo> cad2d_plane_approximate_info;

	class Cad2d_PlaneInfo
	{

		/*Private Data*/

		Standard_Real theTolerance_;

		std::shared_ptr<Geo_ApprxCurveInfo> theApprxInfo_;

	public:

		static const Standard_Real DEFAULT_TOLERANCE;

		Cad2d_PlaneInfo()
			: theTolerance_(DEFAULT_TOLERANCE)
		{
			theApprxInfo_ = cad2d_plane_approximate_info;
		}

		Standard_Real Tolerance() const
		{
			return theTolerance_;
		}

		const std::shared_ptr<Geo_ApprxCurveInfo>& ApproxInfo() const
		{
			return theApprxInfo_;
		}

		void OverrideApproxInfo(const std::shared_ptr<Geo_ApprxCurveInfo>& theInfo)
		{
			theApprxInfo_ = theInfo;
		}
	};
}

#endif // !_Cad2d_PlaneInfo_Header

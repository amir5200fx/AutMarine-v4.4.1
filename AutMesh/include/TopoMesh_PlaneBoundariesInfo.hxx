#pragma once
#ifndef _TopoMesh_PlaneBoundariesInfo_Header
#define _TopoMesh_PlaneBoundariesInfo_Header

#include <Standard_TypeDef.hxx>

#include <memory>
#include <map>

namespace AutLib
{

	// Forward Declarations
	class Mesh_CurveInfo;
	class SizeMap2d_FullIntAnIsoInfo;

	class TopoMesh_PlaneBoundariesInfo
	{

		/*Private Data*/

		std::shared_ptr<Mesh_CurveInfo> theGlobalCurveInfo_;
		std::shared_ptr<SizeMap2d_FullIntAnIsoInfo> theMetricInfo_;

		std::map<Standard_Integer, std::shared_ptr<Mesh_CurveInfo>> theCurveInfo_;

		Standard_Boolean OverrideInfo_;

	public:

		TopoMesh_PlaneBoundariesInfo();

		const std::shared_ptr<Mesh_CurveInfo>& GlobalCurveInfo() const
		{
			return theGlobalCurveInfo_;
		}

		const std::shared_ptr<SizeMap2d_FullIntAnIsoInfo>& MetricInfo() const
		{
			return theMetricInfo_;
		}

		const std::map<Standard_Integer, std::shared_ptr<Mesh_CurveInfo>>& CurveInfo() const
		{
			return theCurveInfo_;
		}

		Standard_Boolean OverrideInfo() const
		{
			return OverrideInfo_;
		}

		void CreateCurveInfo
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		)
		{
			theCurveInfo_.insert(std::make_pair(theIndex, theInfo));
		}

		void OverrideGlobalCurveInfo
		(
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		)
		{
			theGlobalCurveInfo_ = theInfo;
		}

		void OverrideMetricInfo
		(
			const std::shared_ptr<SizeMap2d_FullIntAnIsoInfo>& theInfo
		)
		{
			theMetricInfo_ = theInfo;
		}

		void SetOverrideInfo
		(
			const Standard_Boolean Override
		)
		{
			OverrideInfo_ = Override;
		}
	};
}

#endif // !_TopoMesh_PlaneBoundariesInfo_Header

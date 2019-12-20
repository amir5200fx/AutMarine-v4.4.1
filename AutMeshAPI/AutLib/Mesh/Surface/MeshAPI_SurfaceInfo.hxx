#pragma once
#ifndef _MeshAPI_SurfaceInfo_Header
#define _MeshAPI_SurfaceInfo_Header

#include <Global_Macros.hxx>
#include <Global_InitRunTime.hxx>
#include <MeshAPI_Info.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class SizeMap2d_FullIntAnIsoInfo;
	class Mesh_CurveInfo;

	class MeshAPI_SurfaceInfo
	{

		/*private Data*/

		std::shared_ptr<SizeMap2d_FullIntAnIsoInfo> theAnIsoSizeMapInfo_;
		std::shared_ptr<SizeMap2d_FullIntAnIsoInfo> theGlobalAnIsoSizeMapInfo_;
		std::shared_ptr<Mesh_CurveInfo> theCurveMeshInfo_;
		std::shared_ptr<Mesh_CurveInfo> theGlobalCurveMeshInfo_;

		Standard_Boolean OverrideSizeMap_;
		Standard_Boolean OverrideCurveMeah_;

	public:

		MeshAPI_SurfaceInfo()
			: OverrideCurveMeah_(Standard_False)
			, OverrideSizeMap_(Standard_False)
		{}

		Standard_Boolean OverrideSizeMap() const
		{
			return OverrideSizeMap_;
		}

		Standard_Boolean OverrideCurveMeah() const
		{
			return OverrideCurveMeah_;
		}

		const std::shared_ptr<SizeMap2d_FullIntAnIsoInfo>& AnIsoSizeMapInfo() const
		{
			return theAnIsoSizeMapInfo_;
		}

		const std::shared_ptr<SizeMap2d_FullIntAnIsoInfo>& GlobalAnIsoSizeMapInfo() const
		{
			return theGlobalAnIsoSizeMapInfo_;
		}

		const std::shared_ptr<Mesh_CurveInfo>& CurveMeshInfo() const
		{
			return theCurveMeshInfo_;
		}

		const std::shared_ptr<Mesh_CurveInfo>& GlobalCurveMeshInfo() const
		{
			return theGlobalCurveMeshInfo_;
		}

		void OverrideAnIsoSizeMapInfo
		(
			const std::shared_ptr<SizeMap2d_FullIntAnIsoInfo>& theInfo
		)
		{
			theAnIsoSizeMapInfo_ = theInfo;
		}

		void OverrideCurveMeshInfo
		(
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		)
		{
			theCurveMeshInfo_ = theInfo;
		}

		void OverrideSizeMap(const Standard_Boolean theOverride)
		{
			OverrideSizeMap_ = theOverride;
		}

		void OverrideCurveMeah(const Standard_Boolean theOverride)
		{
			OverrideCurveMeah_ = theOverride;
		}
	};
}

#endif // !_MeshAPI_SurfaceInfo_Header

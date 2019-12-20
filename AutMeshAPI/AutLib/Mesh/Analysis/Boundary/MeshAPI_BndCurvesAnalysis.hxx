#pragma once
#ifndef _Mesh_BndCurvesAnalysis_Header
#define _Mesh_BndCurvesAnalysis_Header

#include <Global_Done.hxx>
#include <Entity3d_Chain.hxx>
#include <SizeMap2d_FullIntSurface.hxx>
#include <MeshAPI_BndCurvesAnalysisInfo.hxx>

#include <memory>

#include "TopoMesh2d_GModelBoundaries.hxx"
#include "Mesh3d_SizeMap.hxx"
#include "GModel_Surface.hxx"
#include "Aft2d_gSegmentEdge.hxx"
#include "Aft2d_BndEdgeAnIso.hxx"
#include "Aft2d_BndNodeAnIso.hxx"

namespace AutLib
{

	// Forward Declarations
	class Mesh_CurveInfo;
	class TopoMesh_PlaneBoundariesInfo;

	template<class TopoBndMesh, class SizeMap3d>
	class MeshAPI_BndCurvesAnalysis
		: public Global_Done
	{

	public:

		typedef typename TopoBndMesh::plnType plnType;
		typedef typename TopoBndMesh::surfType surfType;
		typedef TopoBndMesh topoMesh;

		typedef SizeMap3d sizeMap3d;
		typedef SizeMap2d_FullIntSurface sizeMap2d;

		typedef MeshAPI_BndCurvesAnalysisInfo info;

		/*Private Data*/

	private:

		std::shared_ptr<SizeMap3d> theSizeMap_;
		std::shared_ptr<surfType> theSurface_;

		std::shared_ptr<plnType> thePlane_;
		std::shared_ptr<TopoBndMesh> theMesh_;
		std::shared_ptr<Entity3d_Chain> theMesh3d_;

		std::shared_ptr<SizeMap2d_FullIntSurface> theMetricMap_;

		std::shared_ptr<info> theInfo_;

		Standard_Boolean Check_;


		Standard_Boolean& ChangeCheck()
		{
			return Check_;
		}

		std::shared_ptr<plnType>& ChangePlane()
		{
			return thePlane_;
		}

		std::shared_ptr<TopoBndMesh>& ChangeMesh()
		{
			return theMesh_;
		}

		std::shared_ptr<Entity3d_Chain>& ChangeMesh3D()
		{
			return theMesh3d_;
		}

		std::shared_ptr<SizeMap2d_FullIntSurface>& ChangeMetricMap()
		{
			return theMetricMap_;
		}

		std::shared_ptr<SizeMap2d_FullIntSurface> GetPlaneSizeMap() const;

		void CreateMesh3D();

		static std::shared_ptr<plnType> 
			MakePlane
			(
				const std::shared_ptr<surfType>& theSurface
			);

	public:

		MeshAPI_BndCurvesAnalysis(const std::shared_ptr<info>& theInfo)
			: theInfo_(theInfo)
			, Check_(Standard_False)
		{}

		MeshAPI_BndCurvesAnalysis
		(
			const std::shared_ptr<SizeMap3d>& theSizeMap,
			const std::shared_ptr<surfType>& theSurface,
			const std::shared_ptr<info>& theInfo
		)
			: theSizeMap_(theSizeMap)
			, theSurface_(theSurface)
			, theInfo_(theInfo)
			, Check_(Standard_False)
		{}

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		const std::shared_ptr<SizeMap3d>& SizeMap() const
		{
			return theSizeMap_;
		}

		const std::shared_ptr<surfType>& Surface() const
		{
			return theSurface_;
		}

		Standard_Boolean Check() const;

		const std::shared_ptr<plnType>& Plane() const
		{
			return thePlane_;
		}

		const std::shared_ptr<TopoBndMesh>& Mesh() const
		{
			return theMesh_;
		}

		const std::shared_ptr<Entity3d_Chain>& Mesh3D() const
		{
			return theMesh3d_;
		}

		const std::shared_ptr<SizeMap2d_FullIntSurface>& MetricMap() const
		{
			return theMetricMap_;
		}

		void Perform();

		void LoadSizeMap(const std::shared_ptr<SizeMap3d>& theSizeMap)
		{
			theSizeMap_ = theSizeMap;
		}

		void LoadSurface(const std::shared_ptr<surfType>& theSurface)
		{
			theSurface_ = theSurface;
		}


		//- Static functions and operators

		static Standard_Boolean
			CheckIntersection
			(
				const std::vector<std::shared_ptr<typename TopoBndMesh::bndType>>& theEdges
			);
	};
}

#include <MeshAPI_BndCurvesAnalysisI.hxx>

#endif // !_Mesh_BndCurvesAnalysis_Header

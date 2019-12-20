#pragma once
#ifndef _MeshAPI_Surface_Header
#define _MeshAPI_Surface_Header

#include <Global_Done.hxx>
#include <Global_Verbose.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity3d_Triangulation.hxx>

#include <memory>
#include <iostream>

//#include "GModel_Surface.hxx"
//#include "Mesh3d_SizeMap.hxx"
//#include "Aft2d_gSegmentEdge.hxx"

namespace AutLib
{

	// Forward Declarations
	class MeshAPI_SurfaceInfo;

	extern std::shared_ptr<MeshAPI_SurfaceInfo> mesh_api_surface_info;

	template<class SurfType, class SizeMap3D>
	class MeshAPI_Surface
		: public Global_Done
		, public Global_Verbose
	{

		typedef MeshAPI_SurfaceInfo info;

		/*Private Data*/

		std::shared_ptr<SurfType> theSurface_;
		std::shared_ptr<SizeMap3D> theSizeMap_;

		std::shared_ptr<Entity2d_Triangulation> theParaTriangulation_;
		std::shared_ptr<Entity3d_Triangulation> theTriangulation_;

		std::shared_ptr<info> theInfo_;


		std::shared_ptr<Entity2d_Triangulation>& ChangeParaMesh()
		{
			return theParaTriangulation_;
		}

		void ComputeSurfaceMesh();

	public:

		MeshAPI_Surface()
		{
			theInfo_ = mesh_api_surface_info;
		}

		MeshAPI_Surface
		(
			const std::shared_ptr<SurfType>& theSurface, 
			const std::shared_ptr<SizeMap3D>& theSizeMap
		)
			: theSurface_(theSurface)
			, theSizeMap_(theSizeMap)
		{
			theInfo_ = mesh_api_surface_info;
		}

		const std::shared_ptr<SurfType>& Surface() const
		{
			return theSurface_;
		}

		const std::shared_ptr<SizeMap3D>& SizeMap() const
		{
			return theSizeMap_;
		}

		const std::shared_ptr<Entity2d_Triangulation>& ParaTriangulation() const
		{
			return theParaTriangulation_;
		}

		const std::shared_ptr<Entity3d_Triangulation>& Triangulation() const
		{
			return theTriangulation_;
		}

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		void Perform(std::ostream& os = std::cout);

		void LoadSurface
		(
			const std::shared_ptr<SurfType>& theSurface
		)
		{
			theSurface_ = theSurface;
		}

		void LoadSizeMap
		(
			const std::shared_ptr<SizeMap3D>& theSizeMap
		)
		{
			theSizeMap_ = theSizeMap;
		}

		void OverrideInfo(const std::shared_ptr<info>& theInfo)
		{
			theInfo_ = theInfo;
		}
	};

	
}

#include <MeshAPI_SurfaceI.hxx>

#endif // !_MeshAPI_Surface_Header

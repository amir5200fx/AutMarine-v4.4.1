#pragma once
#ifndef _MeshAPI_Model_Header
#define _MeshAPI_Model_Header

#include <Global_Done.hxx>
#include <Global_Verbose.hxx>
#include <Mesh2d_Surface.hxx>
#include <Aft2d_ElementAnIso.hxx>
#include <Entity3d_Triangulation.hxx>

#include <memory>
#include <map>
#include <iostream>

#include "MeshAPI_gCurveMesh.hxx"

namespace AutLib
{

	// Forward Declarations
	class MeshAPI_ModelInfo;

	template<class CrvMesh>
	class MeshAPI_Model
		: public Global_Done
	{

		typedef typename CrvMesh::modelAnal::curveAnal::topoMesh::bndType bndType;
		typedef typename CrvMesh::modelAnal::curveAnal::sizeMap2d sizeMap2d;
		typedef Mesh2d_Surface planeMesh;

		typedef std::map<Standard_Integer, std::shared_ptr<Entity3d_Triangulation>>
			indexedSurfaceMesh3D;

		typedef std::map<Standard_Integer, std::shared_ptr<planeMesh>>
			indexedSurfaceMesh;


		/*Private Data*/

		std::shared_ptr<CrvMesh> theCurveMesh_;
		std::shared_ptr<MeshAPI_ModelInfo> theInfo_;

		indexedSurfaceMesh theMesh_;
		indexedSurfaceMesh3D theMesh3d_;


		indexedSurfaceMesh& ChangeMesh()
		{
			return theMesh_;
		}

	public:
	

		MeshAPI_Model
		(
			const std::shared_ptr<MeshAPI_ModelInfo>& theInfo
		)
			: theInfo_(theInfo)
		{}

		MeshAPI_Model
		(
			const std::shared_ptr<CrvMesh>& theMesh,
			const std::shared_ptr<MeshAPI_ModelInfo>& theInfo
		)
			: theCurveMesh_(theMesh)
			, theInfo_(theInfo)
		{}

		const std::shared_ptr<CrvMesh>& CurveMesh() const
		{
			return theCurveMesh_;
		}

		const indexedSurfaceMesh& Mesh() const
		{
			return theMesh_;
		}

		const indexedSurfaceMesh3D& Mesh3D() const
		{
			return theMesh3d_;
		}

		const std::shared_ptr<MeshAPI_ModelInfo>& Info() const
		{
			return theInfo_;
		}

		void Perform(std::ostream& out = std::cout);

		void LoadCurveMesh(const std::shared_ptr<CrvMesh>& theMesh)
		{
			theCurveMesh_ = theMesh;
		}

		void CreateMesh3D();

		void ExportToPlt(OFstream& File) const;

		void ExportSurfaceMeshToPlt(OFstream& File) const;
	};
}

#include <MeshAPI_ModelI.hxx>

#endif // !_MeshAPI_Model_Header

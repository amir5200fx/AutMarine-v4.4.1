#pragma once
#ifndef _MeshAPI_CurveMesh_Header
#define _MeshAPI_CurveMesh_Header

#include <Global_Done.hxx>
#include <Global_Verbose.hxx>
#include <MeshAPI_Info.hxx>
#include <OFstream.hxx>

#include <memory>
#include <map>
#include <iostream>

#include "MeshAPI_gModelAnalysis.hxx"

namespace AutLib
{

	// Forward Declarations
	class MeshAPI_BndCurvesAnalysisInfo;

	template<class ModelAnal>
	class MeshAPI_CurveMesh
		: public Global_Done
		, public Global_Verbose
	{

		typedef std::map<Standard_Integer, std::shared_ptr<typename ModelAnal::curveAnal>>
			indexedBoundaryMesh;

		typedef MeshAPI_BndCurvesAnalysisInfo info;

		/*Private Data*/

		std::shared_ptr<ModelAnal> theAnalysis_;

		indexedBoundaryMesh theMesh_;
		indexedBoundaryMesh theInvalids_;


		const std::shared_ptr<info>& theInfo_;


		indexedBoundaryMesh& ChangeInvalids()
		{
			return theInvalids_;
		}

		indexedBoundaryMesh& ChangeMesh()
		{
			return theMesh_;
		}

	public:

		typedef ModelAnal modelAnal;

		MeshAPI_CurveMesh
		(
			const std::shared_ptr<info>& theInfo
		)
			: theInfo_(theInfo)
		{}

		MeshAPI_CurveMesh
		(
			const std::shared_ptr<ModelAnal>& theAnalysis,
			const std::shared_ptr<info>& theInfo
		)
			: theAnalysis_(theAnalysis)
			, theInfo_(theInfo)
		{}

		const std::shared_ptr<ModelAnal>& Analysis() const
		{
			return theAnalysis_;
		}

		const indexedBoundaryMesh& Mesh() const
		{
			return theMesh_;
		}

		const indexedBoundaryMesh& InvalidMesh() const
		{
			return theInvalids_;
		}

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		void Perform(std::ostream& out = std::cout);

		void LoadAnalysis
		(
			const std::shared_ptr<ModelAnal>& theAnalysis
		)
		{
			theAnalysis_ = theAnalysis;
		}

		void ExportToPlt(OFstream& File) const;
	};
}

#include <MeshAPI_CurveMeshI.hxx>

#endif // !_MeshAPI_CurveMesh_Header

#pragma once
#ifndef _MeshAPI_ModelAnalysis_Header
#define _MeshAPI_ModelAnalysis_Header

#include <Global_Done.hxx>
#include <Global_Verbose.hxx>
#include <MeshAPI_Traits.hxx>
#include <MeshAPI_Info.hxx>

#include <map>
#include <memory>
#include <iostream>

//#include "MeshAPI_gBndCurvesAnalysis.hxx"
//#include "Cad3d_GModel.hxx"

namespace AutLib
{

	template<class BndCrvAnal>
	class MeshAPI_ModelAnalysis
		: public Global_Done
		, public Global_Verbose
	{

	public:

		typedef std::map<Standard_Integer, std::shared_ptr<typename BndCrvAnal::surfType>>
			indexedSurfaceMap;
		typedef typename model_type<typename BndCrvAnal::surfType>::type 
			modelType;

		typedef std::map<Standard_Integer, std::shared_ptr<BndCrvAnal>>
			indexedBoundaryMesh;

		typedef MeshAPI_ModelAnalysisInfo info;
		typedef BndCrvAnal curveAnal;

	private:

		/*Private Data*/

		std::shared_ptr<modelType> theModel_;
		std::shared_ptr<typename BndCrvAnal::sizeMap3d> theSizeMap_;

		indexedSurfaceMap theRegulars_;
		indexedSurfaceMap theDefects_;

		indexedSurfaceMap theSingularities_;

		//- surfaces that have one or more curve with length of zero
		indexedSurfaceMap theCommonSingularities_;

		indexedBoundaryMesh theBndMesh_;

		std::shared_ptr<info> theInfo_;


		//- Static functions and operators


	public:

		MeshAPI_ModelAnalysis
		(
			const std::shared_ptr<info>& theInfo
		)
			: theInfo_(theInfo)
		{}

		MeshAPI_ModelAnalysis
		(
			const std::shared_ptr<modelType>& theModel,
			const std::shared_ptr<info>& theInfo
		)
			: theInfo_(theInfo)
			, theModel_(theModel)
		{}

		const std::shared_ptr<modelType>& Model() const
		{
			return theModel_;
		}

		const std::shared_ptr<typename BndCrvAnal::sizeMap3d>& SizeMap() const
		{
			return theSizeMap_;
		}

		Standard_Integer NbRegulars() const
		{
			return (Standard_Integer)theRegulars_.size();
		}

		Standard_Integer NbDefects() const
		{
			return (Standard_Integer)theDefects_.size();
		}

		Standard_Integer NbSingularities() const
		{
			return (Standard_Integer)theSingularities_.size();
		}

		Standard_Integer NbCommonSingularities() const
		{
			return (Standard_Integer)theCommonSingularities_.size();
		}

		const indexedSurfaceMap& Regulars() const
		{
			return theRegulars_;
		}

		indexedSurfaceMap& Regulars()
		{
			return theRegulars_;
		}

		const indexedSurfaceMap& Defects() const
		{
			return theDefects_;
		}

		indexedSurfaceMap& Defects()
		{
			return theDefects_;
		}

		const indexedSurfaceMap& Singularities() const
		{
			return theSingularities_;
		}

		indexedSurfaceMap& Singularities()
		{
			return theSingularities_;
		}

		const indexedSurfaceMap& CommonSingularities() const
		{
			return theCommonSingularities_;
		}

		indexedSurfaceMap& CommonSingularities()
		{
			return theCommonSingularities_;
		}

		const indexedBoundaryMesh& BoundaryMesh() const
		{
			return theBndMesh_;
		}

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		void LoadModel(const std::shared_ptr<modelType>& theModel)
		{
			theModel_ = theModel;
		}

		void LoadSizeMap(const std::shared_ptr<typename BndCrvAnal::sizeMap3d>& theSizeMap)
		{
			theSizeMap_ = theSizeMap;
		}

		void Perform(std::ostream& os = std::cout);

		void Report(std::ostream& os) const;
	};
}

#include <MeshAPI_ModelAnalysisI.hxx>

#endif // !_MeshAPI_ModelAnalysis_Header

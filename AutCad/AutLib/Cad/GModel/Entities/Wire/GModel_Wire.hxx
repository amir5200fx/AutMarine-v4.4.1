#pragma once
#ifndef _GModel_Wire_Header
#define _GModel_Wire_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Entity2d_Box.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class GModel_Edge;

	class GModel_Wire
		: public Global_Indexed
		, public Global_Named
	{

		typedef std::shared_ptr<GModel_Edge> edge_ptr;
		typedef std::vector<edge_ptr> edgeList;
		typedef std::shared_ptr<edgeList> edgeList_ptr;

		/*Private Data*/

		edgeList_ptr theEdges_;

	public:

		GModel_Wire
		(
			const Standard_Integer theIndex,
			const edgeList_ptr& theEdges
		)
			: theEdges_(theEdges)
			, Global_Indexed(theIndex)
		{}

		GModel_Wire
		(
			const Standard_Integer theIndex,
			const word& theName,
			const edgeList_ptr& theEdges
		)
			: theEdges_(theEdges)
			, Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

		GModel_Wire(const edgeList_ptr& theEdges)
			: theEdges_(theEdges)
		{}

		const edgeList_ptr& Edges() const
		{
			return theEdges_;
		}

		Standard_Integer NbEdges() const
		{
			Debug_Null_Pointer(theEdges_);
			return (Standard_Integer)theEdges_->size();
		}

		Entity2d_Box CalcParametricBoundingBox() const;

		void ExportPlaneCurvesToPlt(OFstream& File) const;

		//- Static functions and operators

		static std::shared_ptr<GModel_Wire> 
			ReParameterization
			(
				const GModel_Wire& theWire, 
				const gp_Trsf2d& trans
			);

		static std::shared_ptr<GModel_Wire> 
			BSplinePlaneEdges
			(
				const GModel_Wire& theWire
			);

		static std::shared_ptr<GModel_Wire>
			uPlaneExpand
			(
				const GModel_Wire& theWire,
				const Standard_Real multiply
			);

		static std::shared_ptr<GModel_Wire>
			vPlaneExpand
			(
				const GModel_Wire& theWire,
				const Standard_Real multiply
			);
	};
}

#endif // !_GModel_Wire_Header

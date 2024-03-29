#pragma once
#ifndef _Aft_TBndEdge_Header
#define _Aft_TBndEdge_Header

#include <Aft_BndEdge.hxx>
#include <Mesh_BndEdgeGeomAdaptor.hxx>
#include <Entity2d_ChainFwd.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	template<class TBndEdgeTraits, Mesh_BndEdge_Position POS = Mesh_BndEdge_Position_Segment>
	class Aft_TBndEdge
		: public Mesh_BndEdgeGeomAdaptor
		<
		typename TBndEdgeTraits::curveType, 
		typename TBndEdgeTraits::surfType, POS
		>
		, public Aft_BndEdge<typename TBndEdgeTraits::bndEdgeTraits>
	{

		/*Private Data*/

	public:

		typedef Aft_BndEdge<typename TBndEdgeTraits::bndEdgeTraits> bndEdgeType;
		typedef TBndEdgeTraits traitsType;

		Aft_TBndEdge()
		{}

		Aft_TBndEdge
		(
			const Standard_Integer theIndex
		)
			: Aft_BndEdge<typename TBndEdgeTraits::bndEdgeTraits>(theIndex)
		{}

		Aft_TBndEdge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<typename Aft_BndEdge<typename TBndEdgeTraits::bndEdgeTraits>::nodeType>& theNode0,
			const std::shared_ptr<typename Aft_BndEdge<typename TBndEdgeTraits::bndEdgeTraits>::nodeType>& theNode1
		)
			: Aft_BndEdge<typename TBndEdgeTraits::bndEdgeTraits>(theIndex, theNode0, theNode1)
		{}

		//- Static functions and operators

		static std::vector<std::shared_ptr<Aft_TBndEdge>>
			GetTopology
			(
				const Entity2d_Chain& theChain,
				const std::shared_ptr<typename TBndEdgeTraits::curveType>& theCurve
			);

		static void MergeDangles
		(
			const std::vector<std::shared_ptr<Aft_TBndEdge>>& theWire,
			const Standard_Real theTol
		);

		static std::vector<std::shared_ptr<typename TBndEdgeTraits::bndEdgeTraits::edgeType>>
			UpCast
			(
				const std::vector<std::shared_ptr<Aft_TBndEdge>>& theEdges
			);
	};
}

#include <Aft_TBndEdgeI.hxx>

#endif // !_Aft_TBndEdge_Header

#pragma once
#ifndef _Knit_Chain_Header
#define _Knit_Chain_Header

#include <Entity_Polygon.hxx>
#include <Entity_StaticData.hxx>
#include <Mesh_RegisterEntityM.hxx>
#include <Knit_ChainRegister.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	template<class NodeType, class FacetType>
	class Knit_ChainBase
		: public Mesh_RegisterKnit_ChainNode<NodeType>
		, public Mesh_RegisterKnit_ChainEdge<Knit_ChainEdge<NodeType, FacetType>>
	{

		/*Private Data*/

		Standard_Boolean IsDone_;

	protected:

		Knit_ChainBase()
			: IsDone_(Standard_False)
		{}

		Standard_Boolean& Change_IsDone()
		{
			return IsDone_;
		}

	public:

		Standard_Boolean IsDone() const
		{
			return IsDone_;
		}

	};

	template<class NodeType>
	class Knit_Chain
		: public Knit_ChainBase<NodeType, typename NodeType::facetInfo>
	{

		typedef typename NodeType::ptType Point;
		typedef std::shared_ptr<NodeType> node_ptr;

		typedef Knit_ChainEdge<NodeType, typename NodeType::facetInfo> edge;
		typedef std::shared_ptr<edge> edge_ptr;

		typedef Entity_Polygon<Point> polygon;
		typedef std::vector<std::shared_ptr<polygon>> polyList;

		typedef Knit_ChainBase<NodeType, typename NodeType::facetInfo> base;

		/*Private Data*/

		polyList thePolygons_;


		node_ptr Next(const node_ptr& theNode);

		node_ptr FindStart(const Knit_ChainNodeType type) const;

		std::shared_ptr<polygon> GetPolygon(const node_ptr& theStart);

		void SetTypes();

	public:

		Knit_Chain()
		{}

		Standard_Integer NbPolygons() const
		{
			return (Standard_Integer)thePolygons_.size();
		}

		const std::shared_ptr<polygon>& Polygon(const Standard_Integer theIndex) const
		{
			return thePolygons_[theIndex];
		}

		void Perform();

		void Import(const Entity_StaticData<Point, connectivity::dual>& theChain);
	};
}

#include <Knit_ChainI.hxx>

#endif // !_Knit_Chain_Header

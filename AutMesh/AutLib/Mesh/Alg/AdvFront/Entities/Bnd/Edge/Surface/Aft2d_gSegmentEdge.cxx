#include <Aft2d_gSegmentEdge.hxx>

#include <Mesh_PlnCurve.hxx>
#include <Singularity_PoleCurve.hxx>
#include <Singularity_LineCurve.hxx>
#include <Mesh2d_PoleEdgeTemplate.hxx>
#include <Mesh2d_LineEdgeTemplate.hxx>
#include <Mesh2d_PoleNodeTemplate.hxx>
#include <Mesh2d_LineNodeTemplate.hxx>
#include <Mesh2d_gPlnCurve.hxx>
#include <GModel_parCurve.hxx>
#include <Entity2d_Chain.hxx>
#include <Aft2d_gSegmentNode.hxx>
#include <Aft2d_gCornerNode.hxx>
#include <Aft2d_NodeSurface.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

namespace AutLib
{

	namespace gSegment
	{

		static std::vector<std::shared_ptr<AutLib::Aft2d_gSegmentEdge>>
			GetTopology
			(
				const Entity2d_Chain& theChain,
				const std::shared_ptr<Mesh_PlnCurve<GModel_parCurve>>& theCurve
			)
		{
			const auto& pts = theChain.Points();

			if (pts.size() < 2)
			{
				FatalErrorIn(FunctionSIG) << endl
					<< "Invalid Chain" << endl
					<< abort(FatalError);
			}

			std::vector<std::shared_ptr<Aft2d_NodeSurface>> nodes;
			nodes.reserve(pts.size());

			Standard_Integer K = 0;
			auto n0 = std::make_shared<Aft2d_gCornerNode>(++K, pts[K - 1]);
			nodes.push_back(n0);
			n0->InsertToCurves(theCurve->Index(), theCurve);

			forThose(Index, 1, pts.size() - 2)
			{
				auto n = std::make_shared<Aft2d_gSegmentNode>(++K, pts[K - 1]);
				nodes.push_back(n);

				n->SetCurve(theCurve);
			}

			auto n1 = std::make_shared<Aft2d_gCornerNode>(++K, pts[K - 1]);
			nodes.push_back(n1);
			n1->InsertToCurves(theCurve->Index(), theCurve);

			const auto& connect = theChain.Connectivity();

			std::vector<std::shared_ptr<Aft2d_gSegmentEdge>> edges;
			edges.reserve(connect.size());

			K = 0;
			for (const auto& x : connect)
			{
				const auto& n0 = nodes[Index_Of(x.Value(0))];
				const auto& n1 = nodes[Index_Of(x.Value(1))];

				Debug_Null_Pointer(n0);
				Debug_Null_Pointer(n1);

				auto edge = std::make_shared<Aft2d_gSegmentEdge>(++K, n0, n1);
				Debug_Null_Pointer(edge);

				edges.push_back(edge);

				edge->SetCurve(theCurve);
			}
			return std::move(edges);
		}


		static std::vector<std::shared_ptr<AutLib::Aft2d_gSegmentEdge>>
			GetTopology
			(
				const Entity2d_Chain& theChain,
				const std::shared_ptr<Singularity_PoleCurve<Mesh2d_gPlnCurve>>& theCurve
			)
		{
			const auto& pts = theChain.Points();

			if (pts.size() NOT_EQUAL 3)
			{
				FatalErrorIn(FunctionSIG) << endl
					<< "Invalid Chain" << endl
					<< abort(FatalError);
			}

			std::vector<std::shared_ptr<Aft2d_NodeSurface>> nodes;
			nodes.reserve(pts.size());

			Standard_Integer K = 0;
			auto n0 = std::make_shared<Mesh2d_PoleNodeTemplate<Aft2d_gCornerNode>>(++K, pts[K - 1]);
			nodes.push_back(n0);
			n0->InsertToCurves(theCurve->Index(), theCurve);
			n0->SetFixed(Standard_False);

			/*auto n1 = std::make_shared<Mesh2d_PoleNodeTemplate<Aft2d_gSegmentNode>>(++K, pts[K - 1]);
			nodes.push_back(n1);
			n1->SetCurve(theCurve);
			n1->SetFixed(Standard_True);*/
			auto n1 = std::make_shared<Mesh2d_PoleNodeTemplate<Aft2d_gCornerNode>>(++K, pts[K - 1]);
			nodes.push_back(n1);
			n1->InsertToCurves(theCurve->Index(), theCurve);
			n1->SetFixed(Standard_True);

			auto n2 = std::make_shared<Mesh2d_PoleNodeTemplate<Aft2d_gCornerNode>>(++K, pts[K - 1]);
			nodes.push_back(n2);
			n2->InsertToCurves(theCurve->Index(), theCurve);
			n2->SetFixed(Standard_False);

			const auto& connect = theChain.Connectivity();

			std::vector<std::shared_ptr<Aft2d_gSegmentEdge>> edges;
			edges.reserve(connect.size());
			
			K = 0;
			for (const auto& x : connect)
			{
				const auto& n0 = nodes[Index_Of(x.Value(0))];
				const auto& n1 = nodes[Index_Of(x.Value(1))];

				Debug_Null_Pointer(n0);
				Debug_Null_Pointer(n1);

				auto edge = std::make_shared<Mesh2d_PoleEdgeTemplate<Aft2d_gSegmentEdge>>(++K, n0, n1);
				Debug_Null_Pointer(edge);

				edges.push_back(edge);

				edge->SetCurve(theCurve);
			}
			return std::move(edges);
		}

		static std::vector<std::shared_ptr<AutLib::Aft2d_gSegmentEdge>>
			GetTopology
			(
				const Entity2d_Chain& theChain,
				const std::shared_ptr<Singularity_LineCurve<Mesh2d_gPlnCurve>>& theCurve
			)
		{
			const auto& pts = theChain.Points();

			if (pts.size() < 2)
			{
				FatalErrorIn(FunctionSIG) << endl
					<< "Invalid Chain" << endl
					<< abort(FatalError);
			}

			std::vector<std::shared_ptr<Aft2d_NodeSurface>> nodes;
			nodes.reserve(pts.size());

			Standard_Integer K = 0;
			auto n0 = std::make_shared<Mesh2d_LineNodeTemplate<Aft2d_gCornerNode>>(++K, pts[K - 1]);
			nodes.push_back(n0);
			n0->InsertToCurves(theCurve->Index(), theCurve);

			forThose(Index, 1, pts.size() - 2)
			{
				auto n = std::make_shared<Mesh2d_LineNodeTemplate<Aft2d_gSegmentNode>>(++K, pts[K - 1]);
				nodes.push_back(n);

				n->SetCurve(theCurve);
			}

			auto n1 = std::make_shared<Mesh2d_LineNodeTemplate<Aft2d_gCornerNode>>(++K, pts[K - 1]);
			nodes.push_back(n1);
			n1->InsertToCurves(theCurve->Index(), theCurve);

			const auto& connect = theChain.Connectivity();

			std::vector<std::shared_ptr<Aft2d_gSegmentEdge>> edges;
			edges.reserve(connect.size());

			K = 0;
			for (const auto& x : connect)
			{
				const auto& n0 = nodes[Index_Of(x.Value(0))];
				const auto& n1 = nodes[Index_Of(x.Value(1))];

				Debug_Null_Pointer(n0);
				Debug_Null_Pointer(n1);

				auto edge = std::make_shared<Mesh2d_LineEdgeTemplate<Aft2d_gSegmentEdge>>(++K, n0, n1);
				Debug_Null_Pointer(edge);

				edges.push_back(edge);

				edge->SetCurve(theCurve);
			}
			return std::move(edges);
		}
	}
}

template<>
std::vector<std::shared_ptr<AutLib::Aft2d_gSegmentEdge>>
AutLib::Aft2d_gSegmentEdge::GetTopology
(
	const Entity2d_Chain& theChain,
	const std::shared_ptr<Mesh_PlnCurve<GModel_parCurve>>& theCurve
)
{
	if (std::dynamic_pointer_cast<Mesh_SingularityCurve<Mesh2d_gPlnCurve>>(theCurve))
	{
		auto poleCast = std::dynamic_pointer_cast<Singularity_PoleCurve<Mesh2d_gPlnCurve>>(theCurve);
		if (poleCast)
		{
			auto edges = gSegment::GetTopology(theChain, poleCast);
			return std::move(edges);
		}

		auto lineCast = std::dynamic_pointer_cast<Singularity_LineCurve<Mesh2d_gPlnCurve>>(theCurve);
		if (lineCast)
		{
			auto edges = gSegment::GetTopology(theChain, lineCast);
			return std::move(edges);
		}

		FatalErrorIn(FunctionSIG)
			<< "Invalid Data" << endl
			<< abort(FatalError);

		return std::vector<std::shared_ptr<AutLib::Aft2d_gSegmentEdge>>();
	}
	else
	{
		auto edges = gSegment::GetTopology(theChain, theCurve);
		return std::move(edges);
	}
}

template<>
void AutLib::Aft2d_gSegmentEdge::MergeDangles
(
	const std::vector<std::shared_ptr<AutLib::Aft2d_gSegmentEdge>>& theWire,
	const Standard_Real theTol
)
{
	forThose(Index, 1, theWire.size() - 1)
	{
		Debug_Null_Pointer(theWire[Index - 1]);
		Debug_Null_Pointer(theWire[Index]);

		auto& e0 = *theWire[Index - 1];
		auto& e1 = *theWire[Index];
		
		if (e0.Node1() IS_EQUAL e1.Node0())
			continue;

		if (Distance(e0.Node1()->Coord(), e1.Node0()->Coord()) > theTol)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "Invalid Wire" << endl
				<< abort(FatalError);
		}

		const auto pn0 = std::dynamic_pointer_cast<Mesh2d_PoleNodeTemplate<Aft2d_gCornerNode>>(e0.Node1());
		const auto pn1 = std::dynamic_pointer_cast<Mesh2d_PoleNodeTemplate<Aft2d_gCornerNode>>(e1.Node0());

		if (pn0 OR pn1)
		{
			const auto cn0 = std::dynamic_pointer_cast<Aft2d_gCornerNode>(e0.Node1());
			const auto cn1 = std::dynamic_pointer_cast<Aft2d_gCornerNode>(e1.Node0());

			auto node = 
				Mesh2d_PoleNodeTemplate<Aft2d_gCornerNode>::MergeNodes
				(
					cn0, cn1,
					Aft2d_gSegmentNode::Merge_Alg_New);

			e0.SetNode1(node);
			e1.SetNode0(node);

			continue;
		}

		const auto ln0 = std::dynamic_pointer_cast<Mesh2d_LineNodeTemplate<Aft2d_gCornerNode>>(e0.Node1());
		const auto ln1 = std::dynamic_pointer_cast<Mesh2d_LineNodeTemplate<Aft2d_gCornerNode>>(e1.Node0());

		if (ln0 OR ln1)
		{
			auto node =
				Mesh2d_LineNodeTemplate<Aft2d_gCornerNode>::MergeNodes
				(
					ln0, ln1,
					Aft2d_gSegmentNode::Merge_Alg_New);

			e0.SetNode1(node);
			e1.SetNode0(node);

			continue;
		}

		/*const auto sn0 = std::dynamic_pointer_cast<Aft2d_gSegmentNode>(e0.Node1());
		const auto sn1 = std::dynamic_pointer_cast<Aft2d_gSegmentNode>(e1.Node0());

		if (sn0 AND sn1)
		{
			auto node =
				Aft2d_gSegmentNode::MergeNodes(sn0, sn1, Aft2d_gSegmentNode::Merge_Alg_New);

			e0.SetNode1(node);
			e1.SetNode0(node);

			continue;
		}*/

		const auto cn0 = std::dynamic_pointer_cast<Aft2d_gCornerNode>(e0.Node1());
		const auto cn1 = std::dynamic_pointer_cast<Aft2d_gCornerNode>(e1.Node0());

		if (cn0 AND cn1)
		{
			auto node =
				Aft2d_gCornerNode::MergeNodes(cn0, cn1, Aft2d_gCornerNode::Merge_Alg_New);

			e0.SetNode1(node);
			e1.SetNode0(node);

			continue;
		}

		FatalErrorIn(FunctionSIG) << endl
			<< "Invalid Wire" << endl
			<< abort(FatalError);
	}

	auto& e0 = *theWire[theWire.size() - 1];
	auto& e1 = *theWire[0];

	if (e0.Node1() IS_EQUAL e1.Node0())
		return;

	if (Distance(e0.Node1()->Coord(), e1.Node0()->Coord()) > theTol)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "Invalid Wire" << endl
			<< " dist: " << Distance(e0.Node1()->Coord(), e1.Node0()->Coord()) << ", Tol: " << theTol << endl
			<< abort(FatalError);
	}

	const auto pn0 = std::dynamic_pointer_cast<Mesh2d_PoleNodeTemplate<Aft2d_gCornerNode>>(e0.Node1());
	const auto pn1 = std::dynamic_pointer_cast<Mesh2d_PoleNodeTemplate<Aft2d_gCornerNode>>(e1.Node0());

	if (pn0 OR pn1)
	{
		const auto cn0 = std::dynamic_pointer_cast<Aft2d_gCornerNode>(e0.Node1());
		const auto cn1 = std::dynamic_pointer_cast<Aft2d_gCornerNode>(e1.Node0());

		auto node =
			Mesh2d_PoleNodeTemplate<Aft2d_gCornerNode>::MergeNodes
			(
				cn0, cn1,
				Aft2d_gSegmentNode::Merge_Alg_New);

		e0.SetNode1(node);
		e1.SetNode0(node);

		return;
	}

	const auto ln0 = std::dynamic_pointer_cast<Mesh2d_LineNodeTemplate<Aft2d_gCornerNode>>(e0.Node1());
	const auto ln1 = std::dynamic_pointer_cast<Mesh2d_LineNodeTemplate<Aft2d_gCornerNode>>(e1.Node0());

	if (ln0 OR ln1)
	{
		auto node =
			Mesh2d_LineNodeTemplate<Aft2d_gCornerNode>::MergeNodes
			(
				ln0, ln1,
				Aft2d_gSegmentNode::Merge_Alg_New);

		e0.SetNode1(node);
		e1.SetNode0(node);

		return;
	}

	/*const auto sn0 = std::dynamic_pointer_cast<Aft2d_gSegmentNode>(e0.Node1());
	const auto sn1 = std::dynamic_pointer_cast<Aft2d_gSegmentNode>(e1.Node0());

	if (sn0 AND sn1)
	{
		auto node =
			Aft2d_gSegmentNode::MergeNodes(sn0, sn1, Aft2d_gSegmentNode::Merge_Alg_New);

		e0.SetNode1(node);
		e1.SetNode0(node);

		return;
	}*/

	const auto cn0 = std::dynamic_pointer_cast<Aft2d_gCornerNode>(e0.Node1());
	const auto cn1 = std::dynamic_pointer_cast<Aft2d_gCornerNode>(e1.Node0());

	if (cn0 AND cn1)
	{
		auto node =
			Aft2d_gCornerNode::MergeNodes(cn0, cn1, Aft2d_gCornerNode::Merge_Alg_New);

		e0.SetNode1(node);
		e1.SetNode0(node);

		return;
	}

	FatalErrorIn(FunctionSIG) << endl
		<< "Invalid Wire" << endl
		<< abort(FatalError);
}
#include <Pln_Edge.hxx>

#include <Pln_Ring.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Vertex.hxx>
#include <Merge2d_Chain.hxx>
#include <Geo2d_ApprxCurve.hxx>

Standard_Boolean 
AutLib::Pln_Edge::IsRing() const
{
	return (Standard_Boolean)std::dynamic_pointer_cast<Pln_Ring>
		(
			std::const_pointer_cast<Pln_Entity>(shared_from_this())
			);
}

void AutLib::Pln_Edge::Transform
(
	const gp_Trsf2d & transform
)
{
	Debug_Null_Pointer(theCurve_);
	theCurve_->Transform(transform);

	if (Approx())
	{
		Approx()->Transform(transform);
	}
}

void AutLib::Pln_Edge::Reverse()
{
	Debug_Null_Pointer(theCurve_);

	theCurve_->Reverse();
	std::swap(theVtx0_, theVtx1_);
}

void AutLib::Pln_Edge::Approx
(
	const info & theInfo
)
{
	if (NOT Curve())
	{
		FatalErrorIn("void Approx(const info& theInfo)")
			<< "Null curve pointer" << endl
			<< abort(FatalError);
	}

	const auto& curve = *Curve();
	Geo2d_ApprxCurve app(curve.Curve(), curve.FirstParam(), curve.LastParam());
	
	app.Perform(theInfo);

	theChain_ = app.Chain();
}

//- Static functions and operators

std::vector<std::shared_ptr<AutLib::Pln_Edge>>
AutLib::Pln_Edge::MakeEdges
(
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
	const Standard_Real theTol
)
{
	if (theCurves.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "Empty curve list" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<Pln_Edge>> createdEdges;
	if (theCurves.size() IS_EQUAL 1)
	{
		Debug_Null_Pointer(theCurves[0]);

		const auto& curve = *theCurves[0];
		if (NOT curve.IsClosed(theTol))
		{
			FatalErrorIn("edgeList MakeEdges(const curveList& theCurves, const Standard_Real theTol)")
				<< "Invalid Edge: It's supposed to be a closed edge!" << endl
				<< abort(FatalError);
		}

		auto vtx = std::make_shared<Pln_Vertex>(1, curve.Value(curve.FirstParam()));
		auto edge = std::make_shared<Pln_Ring>(1, vtx, theCurves[0]);

		vtx->ImportToEdges(edge);

		createdEdges.push_back(edge);
		return std::move(createdEdges);
	}

	std::vector<Pnt2d> Coords;
	Coords.reserve(theCurves.size() * 2);
	for (const auto& x : theCurves)
	{
		Debug_Null_Pointer(x);

		Coords.push_back(x->FirstCoord());
		Coords.push_back(x->LastCoord());
	}

	Entity2d_Chain
		chain(Coords, AutLib::dualConnectivityList((Standard_Integer)theCurves.size()));

	Merge2d_Chain merge;
	merge.InfoAlg().SetRadius(theTol);

	merge.Import(chain);
	merge.Perform();

	const auto& merged = merge.Merged();
	const auto& mPts = merged->Points();
	const auto& mEdges = merged->Connectivity();

	std::vector<std::shared_ptr<Pln_Vertex>> Vertices;
	Vertices.reserve(mPts.size());
	Standard_Integer K = 0;
	for (const auto& x : mPts)
	{
		Vertices.push_back(std::make_shared<Pln_Vertex>(++K, x));
	}

	std::vector<std::shared_ptr<Pln_Edge>> Edges;
	Edges.reserve(mEdges.size());
	K = 0;
	for (const auto& x : mEdges)
	{
		if (x.IsDegenerated())
		{
			auto ring = std::make_shared<Pln_Ring>
				(
					K + 1,
					Vertices[Index_Of(x.Value(0))], theCurves[K]);
			Edges.push_back(ring);

			Vertices[Index_Of(x.Value(0))]->ImportToEdges(ring);
			++K;
		}
		else
		{
			auto edge = std::make_shared<Pln_Edge>
				(
					K + 1, 
					Vertices[Index_Of(x.Value(0))],
					Vertices[Index_Of(x.Value(1))], theCurves[K]);
			Edges.push_back(edge);

			Vertices[Index_Of(x.Value(0))]->ImportToEdges(edge);
			Vertices[Index_Of(x.Value(1))]->ImportToEdges(edge);
			++K;
		}
	}
	return std::move(Edges);
}

std::vector<std::shared_ptr<AutLib::Pln_Curve>> 
AutLib::Pln_Edge::RetrieveCurves
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
)
{
	std::vector<std::shared_ptr<Pln_Curve>> Curves;
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		Curves.push_back(x->Curve());
	}
	return std::move(Curves);
}

std::vector<std::shared_ptr<AutLib::Pln_Vertex>> 
AutLib::Pln_Edge::RetrieveVertices
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
)
{
	Adt_AvlTree<std::shared_ptr<Pln_Vertex>> compact;
	compact.SetComparableFunction(&Pln_Vertex::IsLess);

	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		compact.InsertIgnoreDup(x->Vtx0());
		compact.InsertIgnoreDup(x->Vtx1());
	}

	std::vector<std::shared_ptr<Pln_Vertex>> list;
	compact.RetrieveTo(list);

	return std::move(list);
}

std::shared_ptr<AutLib::Geo_ApprxCurveInfo> 
AutLib::pln_edge_discretizer_info = std::make_shared<AutLib::Geo_ApprxCurveInfo>();
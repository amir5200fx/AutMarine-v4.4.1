#pragma once
#ifndef _Pln_Edge_Header
#define _Pln_Edge_Header

#include <Pln_Entity.hxx>
#include <Entity2d_ChainFwd.hxx>
#include <Geo_ApprxCurveInfo.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <gp_Trsf2d.hxx>

namespace AutLib
{

	// Forward Declarations
	class Pln_Vertex;
	class Pln_Wire;
	class Pln_Curve;

	class Pln_Edge
		: public Pln_Entity
	{

		typedef Geo_ApprxCurveInfo info;

		/*Private Data*/

		std::shared_ptr<Pln_Vertex> theVtx0_;
		std::shared_ptr<Pln_Vertex> theVtx1_;

		std::shared_ptr<Pln_Curve> theCurve_;

		std::shared_ptr<Entity2d_Chain> theChain_;

		std::weak_ptr<Pln_Wire> theWire_;


	public:

		typedef Pln_Curve curveType;

		Pln_Edge()
		{}

		Pln_Edge(const Standard_Integer theIndex)
			: Pln_Entity(theIndex)
		{}

		Pln_Edge
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Pln_Entity(theIndex, theName)
		{}

		Pln_Edge
		(
			const std::shared_ptr<Pln_Vertex>& theV0,
			const std::shared_ptr<Pln_Vertex>& theV1,
			const std::shared_ptr<Pln_Curve>& theCurve
		)
			: theVtx0_(theV0)
			, theVtx1_(theV1)
			, theCurve_(theCurve)
		{}

		Pln_Edge
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<Pln_Vertex>& theV0, 
			const std::shared_ptr<Pln_Vertex>& theV1,
			const std::shared_ptr<Pln_Curve>& theCurve
		)
			: Pln_Entity(theIndex)
			, theVtx0_(theV0)
			, theVtx1_(theV1)
			, theCurve_(theCurve)
		{}

		Pln_Edge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Vertex>& theV0,
			const std::shared_ptr<Pln_Vertex>& theV1,
			const std::shared_ptr<Pln_Curve>& theCurve
		)
			: Pln_Entity(theIndex, theName)
			, theVtx0_(theV0)
			, theVtx1_(theV1)
			, theCurve_(theCurve)
		{}

		Standard_Boolean IsRing() const;

		const std::shared_ptr<Pln_Vertex>& Vtx0() const
		{
			return theVtx0_;
		}

		const std::shared_ptr<Pln_Vertex>& Vtx1() const
		{
			return theVtx1_;
		}

		const std::shared_ptr<Pln_Curve>& Curve() const
		{
			return theCurve_;
		}

		const std::shared_ptr<Entity2d_Chain>& Approx() const
		{
			return theChain_;
		}

		void Transform(const gp_Trsf2d& transform);

		void Reverse();

		void Approx(const info& theInfo);

		void Split
		(
			const Standard_Real x,
			std::shared_ptr<Pln_Vertex>& theVertex,
			std::shared_ptr<Pln_Edge>& theLeft,
			std::shared_ptr<Pln_Edge>& theRight
		) const;

		void Split
		(
			const std::vector<Standard_Real>& theParameters, 
			std::vector<std::shared_ptr<Pln_Vertex>>& theVertices, 
			std::vector<std::shared_ptr<Pln_Edge>>& theEdges
		) const;

		void SetVtx0(const std::shared_ptr<Pln_Vertex>& theVtx0)
		{
			theVtx0_ = theVtx0;
		}

		void SetVtx1(const std::shared_ptr<Pln_Vertex>& theVtx1)
		{
			theVtx1_ = theVtx1;
		}

		void SetCurve(const std::shared_ptr<Pln_Curve>& theCurve)
		{
			theCurve_ = theCurve;
		}


		//- Static functions and operators

		static std::vector<std::shared_ptr<Pln_Edge>> 
			MakeEdges
			(
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
				const Standard_Real theTol
			);

		static std::vector<std::shared_ptr<Pln_Curve>> 
			RetrieveCurves
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
			);

		static std::vector<std::shared_ptr<Pln_Vertex>> 
			RetrieveVertices
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
			);

		static Standard_Boolean IsLess
		(
			const std::shared_ptr<Pln_Edge>& theEdge0, 
			const std::shared_ptr<Pln_Edge>& theEdge1
		)
		{
			Debug_Null_Pointer(theEdge0);
			Debug_Null_Pointer(theEdge1);
			return theEdge0->Index() < theEdge1->Index();
		}

		static Standard_Boolean IsLess
		(
			const std::weak_ptr<Pln_Edge>& theEdge0,
			const std::weak_ptr<Pln_Edge>& theEdge1
		)
		{
			Debug_Null_Pointer(theEdge0.lock());
			Debug_Null_Pointer(theEdge1.lock());
			return theEdge0.lock()->Index() < theEdge1.lock()->Index();
		}
	};

	extern std::shared_ptr<Geo_ApprxCurveInfo> pln_edge_discretizer_info;
}

#endif // !_Pln_Edge_Header

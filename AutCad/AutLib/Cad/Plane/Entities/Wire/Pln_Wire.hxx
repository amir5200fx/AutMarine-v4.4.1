#pragma once
#ifndef _Pln_Wire_Header
#define _Pln_Wire_Header

#include <Pln_Entity.hxx>
#include <Pln_Orientation.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <vector>

namespace AutLib
{

	// Forward Declarations
	class Pln_Edge;
	class Pln_Vertex;

	class Pln_Wire
		: public Pln_Entity
	{

		typedef std::shared_ptr<Pln_Edge> edge_ptr;
		typedef std::vector<edge_ptr> edgeList;

		/*Private Data*/

		Pln_Orientation theOrientation_;

		std::shared_ptr<edgeList> theEdges_;

		std::shared_ptr<Entity2d_Box> theBoundingBox_;


		void CalcBoundingBox();

		void CheckWire(const edgeList& theEdges) const;

		void CreateWire(const std::shared_ptr<edgeList>& theEdges);

	public:

		Pln_Wire(const std::shared_ptr<edgeList>& theEdges)
			: theEdges_(theEdges)
		{}

		Pln_Wire
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<edgeList>& theEdges
		)
			: theEdges_(theEdges)
			, Pln_Entity(theIndex)
		{}

		Pln_Wire
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<edgeList>& theEdges
		)
			: theEdges_(theEdges)
			, Pln_Entity(theIndex, theName)
		{}

		Standard_Integer NbEdges() const
		{
			Debug_Null_Pointer(theEdges_);
			return (Standard_Integer)theEdges_->size();
		}

		const std::shared_ptr<edgeList>& Edges() const
		{
			return theEdges_;
		}

		const std::shared_ptr<Entity2d_Box>& BoundingBox() const
		{
			return theBoundingBox_;
		}

		Pln_Orientation Orientation() const
		{
			return theOrientation_;
		}

		void SetOrientation(const Pln_Orientation theOrient)
		{
			theOrientation_ = theOrient;
		}

		void Reverse();

		void RetrieveVerticesTo
		(
			std::vector<std::shared_ptr<Pln_Vertex>>& theVertices
		) const;


		//- Static functions and operators

		static std::vector<std::shared_ptr<Pln_Wire>> 
			RetrieveWires
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
			);

		static Pln_Orientation RetrieveOrientation(const Pln_Wire& theWire);
	};
}

#endif // !_Pln_Wire_Header

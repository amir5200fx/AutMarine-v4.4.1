#pragma once
#ifndef _Pln_Vertex_Header
#define _Pln_Vertex_Header

#include <Pnt2d.hxx>
#include <Adt_AvlTree.hxx>
#include <Pln_Entity.hxx>
#include <Cad_EntityPrecision.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class Pln_Edge;

	class Pln_Vertex
		: public Pln_Entity
		, public Cad_EntityPrecision
	{

		/*Private Data*/

		Pnt2d theCoord_;

		Adt_AvlTree<std::weak_ptr<Pln_Edge>> theEdges_;


		void SetComparableFunction();

	public:

		Pln_Vertex()
		{
			SetComparableFunction();
		}

		Pln_Vertex(const Standard_Integer theIndex)
			: Pln_Entity(theIndex)
		{
			SetComparableFunction();
		}

		Pln_Vertex
		(
			const Standard_Integer theIndex,
			const Pnt2d& theCoord
		)
			: Pln_Entity(theIndex)
			, theCoord_(theCoord)
		{
			SetComparableFunction();
		}

		Pln_Vertex
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Pnt2d& theCoord
		)
			: Pln_Entity(theIndex, theName)
			, theCoord_(theCoord)
		{
			SetComparableFunction();
		}

		const Pnt2d& Coord() const
		{
			return theCoord_;
		}

		Pnt2d& Coord()
		{
			return theCoord_;
		}

		Standard_Integer NbEdges() const
		{
			return theEdges_.Size();
		}

		Standard_Integer NbRings() const;

		Standard_Real SharpAngle() const;

		Standard_Boolean IsOrphan() const
		{
			return theEdges_.IsEmpty();
		}

		Standard_Boolean IsManifold() const;

		Standard_Boolean HasRing() const;

		void SetCoord(const Pnt2d& theCoord)
		{
			theCoord_ = theCoord;
		}

		void ImportToEdges(const std::weak_ptr<Pln_Edge>& theEdge)
		{
			theEdges_.Insert(theEdge);
		}

		void ImportToEdges_dup(const std::weak_ptr<Pln_Edge>& theEdge)
		{
			theEdges_.InsertIgnoreDup(theEdge);
		}

		void RemoveFromEdges(const std::weak_ptr<Pln_Edge>& theEdge)
		{
			theEdges_.Remove(theEdge);
		}

		void RetrieveEdgesTo(std::vector<std::weak_ptr<Pln_Edge>>& theEdges) const
		{
			theEdges_.RetrieveTo(theEdges);
		}

		static Standard_Boolean IsLess
		(
			const std::shared_ptr<Pln_Vertex>& theVtx0,
			const std::shared_ptr<Pln_Vertex>& theVtx1
		)
		{
			Debug_Null_Pointer(theVtx0);
			Debug_Null_Pointer(theVtx1);

			return theVtx0->Index() < theVtx1->Index();
		}
	};
}

#endif // !_Pln_Vertex_Header

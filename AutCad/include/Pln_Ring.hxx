#pragma once
#ifndef _Pln_Ring_Header
#define _Pln_Ring_Header

#include <Pln_Edge.hxx>

namespace AutLib
{

	class Pln_Ring
		: public Pln_Edge
	{

		/*Private Data*/

	public:

		Pln_Ring()
		{}

		Pln_Ring
		(
			const Standard_Integer theIndex
		)
			: Pln_Edge(theIndex)
		{}

		Pln_Ring
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Pln_Edge(theIndex, theName)
		{}

		Pln_Ring
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Vertex>& theVrtx,
			const std::shared_ptr<Pln_Curve>& theCurve
		)
			: Pln_Edge(theIndex, theName, theVrtx, theVrtx, theCurve)
		{}

		Pln_Ring
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Pln_Vertex>& theVrtx,
			const std::shared_ptr<Pln_Curve>& theCurve
		)
			: Pln_Edge(theIndex, theVrtx, theVrtx, theCurve)
		{}

		Pln_Ring
		(
			const std::shared_ptr<Pln_Vertex>& theVrtx,
			const std::shared_ptr<Pln_Curve>& theCurve
		)
			: Pln_Edge(theVrtx, theVrtx, theCurve)
		{}
	};
}

#endif // !_Pln_Ring_Header

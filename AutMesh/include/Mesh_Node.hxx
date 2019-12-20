#pragma once
#ifndef _Mesh_Node_Header
#define _Mesh_Node_Header

#include <Mesh_Entity.hxx>

#include <memory>

namespace AutLib
{

	template<class Point>
	class Mesh_Node
		: public Mesh_Entity
	{

		/*Private Data*/

		Point theCoord_;

	public:

		typedef Point ptType;

		enum
		{
			rank = 0,
			hierarchy = 0
		};

		Mesh_Node()
		{}

		Mesh_Node
		(
			const Standard_Integer theIndex
		)
			: Mesh_Entity(theIndex)
		{}

		Mesh_Node
		(
			const Standard_Integer theIndex,
			const Point& theCoord
		)
			: Mesh_Entity(theIndex)
			, theCoord_(theCoord)
		{}

		const Point& Coord() const
		{
			return theCoord_;
		}

		Point& Coord()
		{
			return theCoord_;
		}

		void SetCoord(const Point& theCoord)
		{
			theCoord_ = theCoord;
		}
	};
}

#endif // !_Mesh_Node_Header

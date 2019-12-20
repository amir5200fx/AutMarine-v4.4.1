#pragma once
#ifndef _Mesh_ElementAdaptor_Header
#define _Mesh_ElementAdaptor_Header

#include <Standard_TypeDef.hxx>

#include <memory>

namespace AutLib
{

	template<class ElementType, int nbEntities = 3>
	class Mesh_ElementAdaptor
	{

		/*Private Data*/

		std::weak_ptr<ElementType> theNeighbors_[nbEntities];

	public:

		Mesh_ElementAdaptor()
		{}

		const std::weak_ptr<ElementType>& Neighbor(const Standard_Integer theIndex) const
		{
			return theNeighbors_[theIndex];
		}

		std::weak_ptr<ElementType>& Neighbor(const Standard_Integer theIndex)
		{
			return theNeighbors_[theIndex];
		}

		void SetNeighbor(const Standard_Integer theIndex, const std::weak_ptr<ElementType>& theElement)
		{
			theNeighbors_[theIndex] = theElement;
		}
	};
}

#endif // !_Mesh_ElementAdaptor_Header

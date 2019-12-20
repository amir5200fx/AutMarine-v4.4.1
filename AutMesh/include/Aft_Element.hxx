#pragma once
#ifndef _Aft_Element_Header
#define _Aft_Element_Header

#include <Aft_ElementDim.hxx>

namespace AutLib
{

	template<class ElementTraits>
	class Aft_Element
		: public Aft_ElementDim<ElementTraits, (int)ElementTraits::dim>
	{

		/*Private Data*/

	public:

		typedef Aft_ElementDim<ElementTraits, ElementTraits::dim> base;

		typedef typename ElementTraits::nodeType nodeType;
		typedef typename ElementTraits::edgeType edgeType;

		typedef std::shared_ptr<nodeType> nodePtr;
		typedef std::shared_ptr<edgeType> edgePtr;

		Aft_Element()
		{}

		Aft_Element(const Standard_Integer theIndex)
			: Aft_ElementDim<ElementTraits, ElementTraits::dim>(theIndex)
		{}

		/*Aft_Element
		(
			const Standard_Integer theIndex,
			const nodePtr& theNode0,
			const nodePtr& theNode1, 
			const nodePtr& theNode2
		)
			: Aft_ElementDim<ElementTraits, ElementTraits::dim>
			(theIndex, theNode0, theNode1, theNode2)
		{}*/
	};
}

#endif // !_Aft_Element_Header

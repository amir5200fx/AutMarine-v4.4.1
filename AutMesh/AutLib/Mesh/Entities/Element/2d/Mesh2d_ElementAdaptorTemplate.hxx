#pragma once
#ifndef _Mesh2d_ElementAdaptorTemplate_Header
#define _Mesh2d_ElementAdaptorTemplate_Header

#include <Mesh_ElementAdaptor.hxx>

namespace AutLib
{

	template<class ElementType>
	class Mesh2d_ElementAdaptorTemplate
		: public Mesh_ElementAdaptor<ElementType>
	{

		/*Private Data*/

		typedef Mesh_ElementAdaptor<ElementType> base;

	public:

		Mesh2d_ElementAdaptorTemplate()
		{}

		const std::weak_ptr<ElementType>& Neighbor0() const
		{
			return base::Neighbor(0);
		}

		std::weak_ptr<ElementType>& Neighbor0()
		{
			return base::Neighbor(0);
		}

		const std::weak_ptr<ElementType>& Neighbor1() const
		{
			return base::Neighbor(1);
		}

		std::weak_ptr<ElementType>& Neighbor1()
		{
			return base::Neighbor(1);
		}

		const std::weak_ptr<ElementType>& Neighbor2() const
		{
			return base::Neighbor(2);
		}

		std::weak_ptr<ElementType>& Neighbor2()
		{
			return base::Neighbor(2);
		}

		void SetNeighbor0(const std::weak_ptr<ElementType>& theElement)
		{
			base::Neighbor(0) = theElement;
		}

		void SetNeighbor1(const std::weak_ptr<ElementType>& theElement)
		{
			base::Neighbor(1) = theElement;
		}

		void SetNeighbor2(const std::weak_ptr<ElementType>& theElement)
		{
			base::Neighbor(2) = theElement;
		}
	};
}

#endif // !_Mesh2d_ElementAdaptorTemplate_Header

#pragma once
#ifndef _Mesh3d_ElementAdaptorTemplate_Header
#define _Mesh3d_ElementAdaptorTemplate_Header

#include <Mesh2d_ElementAdaptorTemplate.hxx>

namespace AutLib
{

	template<class ElementType>
	class Mesh3d_ElementAdaptorTemplate
		: public Mesh2d_ElementAdaptorTemplate<ElementType>
	{

		/*Private Data*/

		typedef Mesh2d_ElementAdaptorTemplate<ElementType> base;

	public:

		Mesh3d_ElementAdaptorTemplate()
		{}

		const std::weak_ptr<ElementType>& Neighbor3() const
		{
			return base::Neighbor(3);
		}

		std::weak_ptr<ElementType>& Neighbor3()
		{
			return base::Neighbor(3);
		}

		void SetNeighbor3(const std::weak_ptr<ElementType>& theElement)
		{
			base::Neighbor(3) = theElement;
		}
	};
}

#endif // !_Mesh3d_ElementAdaptorTemplate_Header

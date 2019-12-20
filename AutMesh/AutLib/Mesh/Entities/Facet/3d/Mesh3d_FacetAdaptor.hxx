#pragma once
#ifndef _Mesh3d_FacetAdaptor_Header
#define _Mesh3d_FacetAdaptor_Header

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class Mesh3d_Element;

	class Mesh3d_FacetAdaptor
	{

		/*Private Data*/

		std::weak_ptr<Mesh3d_Element> theLeft_;
		std::weak_ptr<Mesh3d_Element> theRight_;

	public:

		Mesh3d_FacetAdaptor()
		{}

		const std::weak_ptr<Mesh3d_Element>& LeftElement() const
		{
			return theLeft_;
		}

		std::weak_ptr<Mesh3d_Element>& LeftElement()
		{
			return theLeft_;
		}

		const std::weak_ptr<Mesh3d_Element>& RightElement() const
		{
			return theRight_;
		}

		std::weak_ptr<Mesh3d_Element>& RightElement() 
		{
			return theRight_;
		}

		void SetLeftElement(const std::weak_ptr<Mesh3d_Element>& theElement)
		{
			theLeft_ = theElement;
		}

		void SetRightElement(const std::weak_ptr<Mesh3d_Element>& theElement)
		{
			theRight_ = theElement;
		}
	};
}

#endif // !_Mesh3d_FacetAdaptor_Header

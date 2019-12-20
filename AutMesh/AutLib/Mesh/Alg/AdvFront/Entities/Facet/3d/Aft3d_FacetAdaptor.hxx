#pragma once
#ifndef _Aft3d_FacetAdaptor_Header
#define _Aft3d_FacetAdaptor_Header

#include <memory>
#include <Aft3d_ElementFwd.hxx>


namespace AutLib
{

	// Forward Declarations

	class Aft3d_FacetAdaptor
	{

		typedef std::weak_ptr<Aft3d_Element> element_weak;

		/*Private Data*/

		element_weak theRight_;
		element_weak theLeft_;

	public:

		Aft3d_FacetAdaptor()
		{}

		const element_weak& RightElement() const
		{
			return theRight_;
		}

		element_weak& RightElement()
		{
			return theRight_;
		}

		const element_weak& LeftElement() const
		{
			return theLeft_;
		}

		element_weak& LeftElement()
		{
			return theLeft_;
		}

		void SetRightElement(const element_weak& theRight)
		{
			theRight_ = theRight;
		}

		void SetLeftElement(const element_weak& theLeft)
		{
			theLeft_ = theLeft;
		}
	};
}

#endif // !_Aft3d_FacetAdaptor_Header
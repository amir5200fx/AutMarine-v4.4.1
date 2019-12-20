#pragma once
#ifndef _Aft_BndFacet_Header
#define _Aft_BndFacet_Header

#include <memory>

namespace AutLib
{

	template<class BndFacetTraits>
	class Aft_BndFacet
		: public typename BndFacetTraits::facetType
	{

		/*Private Data*/

		std::shared_ptr<typename BndFacetTraits::surfType> theSurface_;

	public:

		typedef typename BndFacetTraits::surfType surfType;

		enum
		{
			hierarchy = 1
		};

		Aft_BndFacet()
		{}

		const std::shared_ptr<surfType>& Surface() const
		{
			return theSurface_;
		}

		void SetSurface(const std::shared_ptr<surfType>& theSurface)
		{
			theSurface_ = theSurface;
		}
	};
}

#endif // !_Aft_BndFacet_Header

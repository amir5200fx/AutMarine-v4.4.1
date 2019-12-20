#pragma once
#ifndef _Geo_PlaneEqualizer_Header
#define _Geo_PlaneEqualizer_Header

#include <Global_Done.hxx>
#include <Geo_PlaneEqualizerInfo.hxx>

#include <memory>
#include <iostream>

#include "GModel_Surface.hxx"

namespace AutLib
{

	template<class SurfType>
	class Geo_PlaneEqualizer
		: public Global_Done
	{

		typedef Geo_PlaneEqualizerInfo info;

		/*Private Data*/

		std::shared_ptr<SurfType> theSurface_;

		std::shared_ptr<SurfType> theModified_;
		std::shared_ptr<info> theInfo_;

		Standard_Boolean Applied_;


		std::shared_ptr<SurfType>& ChangeModified()
		{
			return theModified_;
		}

		static std::pair<Standard_Real, Standard_Integer> CalcMaxAR(const SurfType& theSurface);

	public:

		Geo_PlaneEqualizer
		(
			const std::shared_ptr<info>& theInfo
		)
			: theInfo_(theInfo)
			, Applied_(Standard_False)
		{}

		Geo_PlaneEqualizer
		(
			const std::shared_ptr<SurfType>& theSurface,
			const std::shared_ptr<info>& theInfo
		)
			: theSurface_(theSurface)
			, theInfo_(theInfo)
			, Applied_(Standard_False)
		{}

		Standard_Boolean IsApplied() const
		{
			return Applied_;
		}

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		const std::shared_ptr<SurfType>& Surface() const
		{
			return theSurface_;
		}

		const std::shared_ptr<SurfType>& Modified() const
		{
			return theModified_;
		}

		void Perform(std::ostream& os);

		void LoadSurface(const std::shared_ptr<SurfType>& theSurface)
		{
			theSurface_ = theSurface;
		}
	};
}

#include <Geo_PlaneEqualizerI.hxx>

#endif // !_Geo_PlaneEqualizer_Header

#pragma once
#ifndef _Geo_PlaneNurbs_Header
#define _Geo_PlaneNurbs_Header

#include <Standard_TypeDef.hxx>
#include <Global_Done.hxx>

#include <memory>

#include "GModel_Surface.hxx"
#include "GModel_Wire.hxx"

namespace AutLib
{

	template<class SurfType>
	class Geo_PlaneNurbs
		: public Global_Done
	{

		typedef typename SurfType::wireType wireType;
		/*Private Data*/

		std::shared_ptr<SurfType> theSurface_;

		std::shared_ptr<SurfType> theModified_;


		std::shared_ptr<SurfType>& ChangeModified()
		{
			return theModified_;
		}

	public:

		Geo_PlaneNurbs()
		{}

		Geo_PlaneNurbs
		(
			const std::shared_ptr<SurfType>& theSurface
		)
			: theSurface_(theSurface)
		{}

		const std::shared_ptr<SurfType>& Surface() const
		{
			return theSurface_;
		}

		const std::shared_ptr<SurfType>& Modified() const
		{
			return theModified_;
		}

		void Perform();

		void LoadSurface
		(
			const std::shared_ptr<SurfType>& theSurface
		)
		{
			theSurface_ = theSurface;
		}
	};
}

#include <Geo_PlaneNurbsI.hxx>

#endif // !_Geo_PlaneNurbs_Header

#pragma once
#ifndef _Geo_PlaneEqualizerInfo_Header
#define _Geo_PlaneEqualizerInfo_Header

#include <Standard_TypeDef.hxx>
#include <Global_Verbose.hxx>

namespace AutLib
{

	class Geo_PlaneEqualizerInfo
		: public Global_Verbose
	{

		/*private Data*/

		Standard_Real theAR_;

	public:

		static const Standard_Real DEFAULT_AR;

		Geo_PlaneEqualizerInfo()
		{}

		Standard_Real AR() const
		{
			return theAR_;
		}

		void SetAR(const Standard_Real theAR)
		{
			theAR_ = theAR;
		}
	};
}

#endif // !_Geo_PlaneEqualizerInfo_Header

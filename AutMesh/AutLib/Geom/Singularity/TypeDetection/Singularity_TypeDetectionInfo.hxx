#pragma once
#ifndef _Singularity_TypeDetectionInfo_Header
#define _Singularity_TypeDetectionInfo_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{

	class Singularity_TypeDetectionInfo
	{

		/*Private Data*/

		Standard_Integer theNbIters_;
		Standard_Real theOmega_;

	public:

		static const Standard_Integer DEFAULT_NB_ITERS;
		static const Standard_Real DEFAULT_OMEGA;

		Singularity_TypeDetectionInfo()
			: theOmega_(DEFAULT_OMEGA)
			, theNbIters_(DEFAULT_NB_ITERS)
		{}

		Standard_Integer NbIters() const
		{
			return theNbIters_;
		}

		Standard_Real Omega() const
		{
			return theOmega_;
		}

		void SetSmoothingFactor(const Standard_Real theOmega)
		{
			theOmega_ = theOmega;
		}

		void SetNbSmoothingIters(const Standard_Integer theNbIters)
		{
			theNbIters_ = theNbIters;
		}
	};
}

#endif // !_Singularity_TypeDetectionInfo_Header

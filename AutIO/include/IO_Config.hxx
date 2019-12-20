#pragma once
#ifndef _IO_Config_Header
#define _IO_Config_Header

#include <Standard_Handle.hxx>
#include <Standard_TypeDef.hxx>

class ShapeFix_Shape;

namespace AutLib
{

	class IO_Config
	{

		/*Private Data*/

		Standard_Boolean FixShape_;
		Standard_Boolean Discrete_;

		Standard_Integer theVerbose_;

		Standard_Real theMinTol_;
		Standard_Real theMaxTol_;
		Standard_Real thePrecision_;

	protected:

		Standard_Boolean FixShape() const
		{
			return FixShape_;
		}

		Standard_Boolean Discrete() const
		{
			return Discrete_;
		}

		Standard_Integer Verbosity() const
		{
			return theVerbose_;
		}

	public:

		IO_Config()
			: FixShape_(Standard_False)
			, Discrete_(Standard_False)
			, theVerbose_(0)
			, theMinTol_(1.0E-6)
			, theMaxTol_(1.0e-2)
			, thePrecision_(1.0e-4)
		{}

		Standard_Real MinTol() const
		{
			return theMinTol_;
		}

		Standard_Real MaxTol() const
		{
			return theMaxTol_;
		}

		Standard_Real Precision() const
		{
			return thePrecision_;
		}

		void SetToFixShape()
		{
			FixShape_ = Standard_True;
		}

		void SetToDiscrete()
		{
			Discrete_ = Standard_True;
		}

		void SetVerbose(const Standard_Integer theVerbose)
		{
			theVerbose_ = theVerbose;
		}

		void SetMinTol(const Standard_Real theMinTol)
		{
			theMinTol_ = theMinTol;
		}

		void SetMaxTol(const Standard_Real theMaxTol)
		{
			theMaxTol_ = theMaxTol;
		}

		void SetPrecision(const Standard_Real thePrec)
		{
			thePrecision_ = thePrec;
		}
	};
}

#endif // !_IO_Config_Header

#pragma once
#ifndef _Cad_Curve_Header
#define _Cad_Curve_Header

#include <Standard_Handle.hxx>
#include <Entity_Box.hxx>

namespace AutLib
{

	template<class CurveType>
	class Cad_Curve
	{

	public:

		typedef Handle(CurveType) curve_ptr;

	private:

		/*Private Data*/

		curve_ptr theCurve_;

		Standard_Real theFirst_;
		Standard_Real theLast_;

	public:

		Cad_Curve()
		{}

		Cad_Curve
		(
			const Standard_Real theFirst, 
			const Standard_Real theLast,
			const curve_ptr& theCurve
		)
			: theFirst_(theFirst)
			, theLast_(theLast)
			, theCurve_(theCurve)
		{}

		void Init
		(
			const Standard_Real theFirst, 
			const Standard_Real theLast, 
			const curve_ptr& theCurve
		)
		{
			theFirst_ = theFirst;
			theLast_ = theLast;
			theCurve_ = theCurve;
		}

		Standard_Real FirstParam() const
		{
			return theFirst_;
		}

		Standard_Real& FirstParam()
		{
			return theFirst_;
		}

		Standard_Real LastParam() const
		{
			return theLast_;
		}

		Standard_Real& LastParam()
		{
			return theLast_;
		}

		const curve_ptr& Curve() const
		{
			return theCurve_;
		}

		curve_ptr& Curve()
		{
			return theCurve_;
		}

		void SetFirstParam(const Standard_Real theFirst)
		{
			theFirst_ = theFirst;
		}

		void SetLastParam(const Standard_Real theLast)
		{
			theLast_ = theLast;
		}

		void SetCurve(const curve_ptr& theCurve)
		{
			theCurve_ = theCurve;
		}

	};
}

#endif // !_Cad_Curve_Header

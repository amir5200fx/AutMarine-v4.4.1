#pragma once
#ifndef _Geo_ApprxSurfMetricInfo_Header
#define _Geo_ApprxSurfMetricInfo_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{

	// Forward Declarations
	class Geo_ApprxSurfMetric;

	class Geo_ApprxSurfMetricInfo
	{

		friend class Geo_ApprxSurfMetric;

		/*Private Data*/

		Standard_Integer theMinLevel_;
		Standard_Integer theMaxLevel_;

		Standard_Real theTolerance_;
		Standard_Real theDegeneracy_;

		Standard_Real theMaxDet_;

		Standard_Boolean HasDegeneracy_;

	protected:

		Standard_Boolean& Change_HasDegeneracy()
		{
			return HasDegeneracy_;
		}

		Standard_Real& ChangeMaxDeterminant()
		{
			return theMaxDet_;
		}

	public:

		static const Standard_Integer MIN_LEVEL;
		static const Standard_Integer MAX_LEVEL;

		static const Standard_Real DEFAULT_TOLERANCE;
		static const Standard_Real DEFAULT_DEGENERACY;

		Geo_ApprxSurfMetricInfo()
			: theMinLevel_(MIN_LEVEL)
			, theMaxLevel_(MAX_LEVEL)
			, theTolerance_(DEFAULT_TOLERANCE)
			, theDegeneracy_(DEFAULT_DEGENERACY)
			, HasDegeneracy_(Standard_False)
			, theMaxDet_(0)
		{}

		Standard_Integer MinLevel() const
		{
			return theMinLevel_;
		}

		Standard_Integer& MinLevel()
		{
			return theMinLevel_;
		}

		Standard_Integer MaxLevel() const
		{
			return theMaxLevel_;
		}

		Standard_Integer& MaxLevel()
		{
			return theMaxLevel_;
		}

		Standard_Real Tolerance() const
		{
			return theTolerance_;
		}

		Standard_Real& Tolerance()
		{
			return theTolerance_;
		}

		Standard_Real Degeneracy() const
		{
			return theDegeneracy_;
		}

		Standard_Real& Degeneracy()
		{
			return theDegeneracy_;
		}

		Standard_Real MaxDeterminant() const
		{
			return theMaxDet_;
		}

		Standard_Boolean HasDegeneracy() const
		{
			return HasDegeneracy_;
		}

		void SetMinLevel(const Standard_Integer theMinLevel)
		{
			theMinLevel_ = theMinLevel;
		}

		void SetMaxLevel(const Standard_Integer theMaxLevel)
		{
			theMaxLevel_ = theMaxLevel;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}

		void SetDegeneracy(const Standard_Real theDeg)
		{
			theDegeneracy_ = theDeg;
		}

		void Reset()
		{
			HasDegeneracy_ = Standard_False;
			theMaxDet_ = 0;
		}

		void SetToDefault()
		{
			HasDegeneracy_ = Standard_False;
			theMaxDet_ = 0;

			theMinLevel_ = MIN_LEVEL;
			theMaxLevel_ = MAX_LEVEL;
			theTolerance_ = DEFAULT_TOLERANCE;
			theDegeneracy_ = DEFAULT_DEGENERACY;
		}
	};
}

#endif // !_Geo_ApprxSurfMetricInfo_Header

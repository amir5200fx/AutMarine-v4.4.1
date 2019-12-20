#pragma once
#ifndef _Model_PlnCurve_Header
#define _Model_PlnCurve_Header

#include <Model_PlnEntity.hxx>
#include <OFstream.hxx>

namespace AutLib
{

	// Forward Declarations
	class Pln_Curve;

	class Model_PlnCurve
		: public Model_PlnEntitySystem
		, public Model_PlnEntityID
		, public Model_PlnEntityDiscrete
	{

		/*Private Data*/

		std::shared_ptr<Pln_Curve> theCurve_;

	protected:

		Model_PlnCurve()
		{}

		std::shared_ptr<Pln_Curve>& ChangeCurve()
		{
			return theCurve_;
		}

	public:

		const std::shared_ptr<Pln_Curve>& Curve() const
		{
			return theCurve_;
		}

		virtual void Make() = 0;

		void Transform(const gp_Trsf2d& theTrans);

		void ExportToPlt(OFstream& File) const;
	};
}

#endif // !_Model_PlnCurve_Header

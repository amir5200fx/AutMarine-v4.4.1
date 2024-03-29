#pragma once
#ifndef _GModel_Curve_Header
#define _GModel_Curve_Header

#include <Cad_Curve.hxx>
#include <Entity3d_Box.hxx>
#include <OFstream.hxx>

#include <Precision.hxx>

class Geom_Curve;

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class Cad_CurveInfo;

	class GModel_Curve
		: public Cad_Curve<Geom_Curve>
	{

		/*Private Data*/

		std::shared_ptr<Cad_CurveInfo> theInfo_;

	public:

		GModel_Curve
		(
			const Standard_Real theFirst,
			const Standard_Real theLast, 
			const Handle(Geom_Curve)& theCurve, 
			const std::shared_ptr<Cad_CurveInfo>& theInfo
		)
			: Cad_Curve<Geom_Curve>(theFirst, theLast, theCurve)
			, theInfo_(theInfo)
		{}

		Standard_Boolean IsClosed
		(
			const Standard_Real theTol = Precision::Confusion()
		) const;

		Standard_Boolean IsDegenerated
		(
			const Standard_Real theTol = Precision::PConfusion()
		) const
		{
			return ABS(FirstParam() - LastParam()) <= theTol;
		}

		Standard_Real IsValid() const
		{
			return FirstParam() <= LastParam();
		}

		Pnt3d Start() const;

		Pnt3d Last() const;

		Pnt3d Value(const Standard_Real x) const;

		Pnt3d NormalizedParameterValue(const Standard_Real x) const;

		Entity3d_Box BoundingBox(const Standard_Real theTol = 0.0) const;

		void Split
		(
			const Standard_Real x,
			std::shared_ptr<GModel_Curve>& theC1,
			std::shared_ptr<GModel_Curve>& theC2
		) const;

		void OverrideInfo(const std::shared_ptr<Cad_CurveInfo>& theInfo)
		{
			theInfo_ = theInfo;
		}
	};

	extern std::shared_ptr<Cad_CurveInfo> gmodel_curve_info;
}

#endif // !_GModel_Curve_Header

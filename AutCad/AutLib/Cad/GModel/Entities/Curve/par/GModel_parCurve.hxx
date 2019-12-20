#pragma once
#ifndef _GModel_parCurve_Header
#define _GModel_parCurve_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Cad_Curve.hxx>
#include <Entity2d_Box.hxx>
#include <Entity2d_ChainFwd.hxx>

#include <Precision.hxx>

class Geom2d_Curve;

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class Cad_CurveInfo;

	class GModel_parCurve
		: public Cad_Curve<Geom2d_Curve>
		, public Global_Indexed
		, public Global_Named
	{

		typedef std::shared_ptr<GModel_parCurve> pCurve_ptr;
		typedef std::vector<pCurve_ptr> curveList;

		/*Private Data*/

		std::shared_ptr<Cad_CurveInfo> theInfo_;

	public:

		typedef Cad_Curve<Geom2d_Curve> curveType;
		typedef Geom2d_Curve geomType;
		typedef Cad_CurveInfo infoType;

		GModel_parCurve
		(
			const Standard_Real theFirst,
			const Standard_Real theLast,
			const Handle(Geom2d_Curve)& theCurve,
			const std::shared_ptr<Cad_CurveInfo>& theInfo
		)
			: Cad_Curve<Geom2d_Curve>(theFirst, theLast, theCurve)
			, theInfo_(theInfo)
		{}

		const std::shared_ptr<Cad_CurveInfo>& Info() const
		{
			return theInfo_;
		}

		Standard_Boolean IsClosed
		(
			const Standard_Real theTol = Precision::Confusion()
		) const;

		Pnt2d Start() const;

		Pnt2d Last() const;

		Pnt2d Value(const Standard_Real x) const;

		Pnt2d NormalizedParameterValue
		(
			const Standard_Real x
		) const;

		Entity2d_Box BoundingBox
		(
			const Standard_Real theTol = 0.0
		) const;

		void ReverseGeometry();

		virtual void Split
		(
			const Standard_Real x,
			std::shared_ptr<GModel_parCurve>& theC1,
			std::shared_ptr<GModel_parCurve>& theC2
		) const;

		virtual void BSplineSplit
		(
			const Standard_Real x,
			std::shared_ptr<GModel_parCurve>& theC1,
			std::shared_ptr<GModel_parCurve>& theC2
		) const;

		virtual curveList Split
		(
			const std::list<Standard_Real>& theParams,
			const Standard_Real theTol
		) const;

		virtual curveList BSplineSplit
		(
			const std::list<Standard_Real>& theParams,
			const Standard_Real theTol
		) const;

		void OverrideInfo(const std::shared_ptr<Cad_CurveInfo>& theInfo)
		{
			theInfo_ = theInfo;
		}

		void ExportToPlt(OFstream& File) const;

		//- Static functions and operators

		static std::shared_ptr<GModel_parCurve> Copy(const GModel_parCurve& theCurve, const gp_Trsf2d& theTrans);

		static std::shared_ptr<GModel_parCurve> 
			ToBSpline
			(
				const std::shared_ptr<GModel_parCurve>& theCurve
			);

		static std::shared_ptr<GModel_parCurve>
			uExpand
			(
				const GModel_parCurve& theCurve,
				const Standard_Real multiply
			);

		static std::shared_ptr<GModel_parCurve>
			vExpand
			(
				const GModel_parCurve& theCurve,
				const Standard_Real multiply
			);
	};

	extern std::shared_ptr<Cad_CurveInfo> gmodel_parcurve_info;
}

#endif // !_GModel_parCurve_Header

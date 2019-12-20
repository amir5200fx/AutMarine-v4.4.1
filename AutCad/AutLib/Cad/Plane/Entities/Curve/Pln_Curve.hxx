#pragma once
#ifndef _Pln_Curve_Header
#define _Pln_Curve_Header

#include <Pln_Entity.hxx>
#include <Entity2d_Box.hxx>
#include <Cad_Curve.hxx>

#include <Standard_Handle.hxx>
#include <Geom2d_Curve.hxx>

namespace AutLib
{

	// Forward Declarations
	class Cad_CurveInfo;

	extern std::shared_ptr<Cad_CurveInfo> pln_curve_info;

	class Pln_Curve
		: public Cad_Curve<Geom2d_Curve>
		, public Pln_Entity
	{

		typedef Cad_CurveInfo info;

		/*Private Data*/

		std::shared_ptr<info> theInfo_;

	public:

		typedef Geom2d_Curve geomType;
		typedef Cad_CurveInfo infoType;

		Pln_Curve()
		{
			theInfo_ = pln_curve_info;
		}

		Pln_Curve
		(
			const Standard_Real theFirst,
			const Standard_Real theLast,
			const Handle(Geom2d_Curve)& theCurve
		)
			: Cad_Curve<Geom2d_Curve>(theFirst, theLast, theCurve)
		{
			theInfo_ = pln_curve_info;
		}

		Pln_Curve
		(
			const Standard_Real theFirst, 
			const Standard_Real theLast, 
			const Handle(Geom2d_Curve)& theCurve,
			const std::shared_ptr<info>& theInfo
		)
			: Cad_Curve<Geom2d_Curve>(theFirst, theLast, theCurve)
			, theInfo_(theInfo)
		{}

		Pln_Curve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Standard_Real theFirst,
			const Standard_Real theLast,
			const Handle(Geom2d_Curve)& theCurve
		)
			: Cad_Curve<Geom2d_Curve>(theFirst, theLast, theCurve)
			, Pln_Entity(theIndex, theName)
		{
			theInfo_ = pln_curve_info;
		}

		Standard_Boolean IsClosed
		(
			const Standard_Real theTolerance
		) const
		{
			return Distance(FirstCoord(), LastCoord()) 
				<= theTolerance;
		}

		Pnt2d Value(const Standard_Real theParam) const;

		Pnt2d FirstCoord() const
		{
			return Value(FirstParam());
		}

		Pnt2d LastCoord() const
		{
			return Value(LastParam());
		}

		Pnt2d NormalizedParameterValue
		(
			const Standard_Real theParam
		) const;

		Entity2d_Box BoundingBox() const;

		Standard_Boolean Interpolation
		(
			const std::vector<Pnt2d>& theQ,
			const Standard_Integer theDeg = 2,
			const Standard_Real theTolerance = 1.0E-6
		);

		void Split
		(
			const Standard_Real x, 
			std::shared_ptr<Pln_Curve>& theLeft,
			std::shared_ptr<Pln_Curve>& theRight
		) const;

		void Split
		(
			const Standard_Real x,
			Pnt2d& theCoord,
			std::shared_ptr<Pln_Curve>& theLeft,
			std::shared_ptr<Pln_Curve>& theRight
		) const;

		template<bool Sorted = true>
		void Split
		(
			const std::vector<Standard_Real>& theParams,
			std::vector<Pnt2d>& theCoords,
			std::vector<std::shared_ptr<Pln_Curve>>& theCurves, 
			const Standard_Real theTol = 1.0E-7
		) const;

		template<>
		void Split<false>
			(
				const std::vector<Standard_Real>& theParams,
				std::vector<Pnt2d>& theCoords,
				std::vector<std::shared_ptr<Pln_Curve>>& theCurves, 
				const Standard_Real theTol
				) const;

		void Reverse();

		void Mirror(const gp_Pnt2d& P);

		void Mirror(const gp_Ax2d& A);

		void Rotate(const gp_Pnt2d& P, const Standard_Real Ang);

		void Scale(const gp_Pnt2d& P, const Standard_Real S);

		void Translate(const gp_Vec2d& V);

		void Translate(const gp_Pnt2d& P1, const gp_Pnt2d& P2);

		void Transform(const gp_Trsf2d& T);

		void OverrideInfo(const std::shared_ptr<Cad_CurveInfo>& theInfo)
		{
			theInfo_ = theInfo;
		}

		void ExportToPlt(OFstream& File) const;
	};

}

#endif // !_Pln_Curve_Header

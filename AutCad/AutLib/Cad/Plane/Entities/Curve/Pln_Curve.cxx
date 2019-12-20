#include <Pln_Curve.hxx>

#include <StdFail_NotDone.hxx>
#include <Bnd_Box2d.hxx>
#include <BndLib_Add2dCurve.hxx>
#include <Geom2dAPI_Interpolate.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>
#include <Cad_CurveInfo.hxx>

std::shared_ptr<AutLib::Cad_CurveInfo> 
AutLib::pln_curve_info = std::make_shared<AutLib::Cad_CurveInfo>();

AutLib::Pnt2d 
AutLib::Pln_Curve::Value
(
	const Standard_Real theParam
) const
{
	Debug_Null_Pointer(Curve());
#ifdef DEBUG
	if (!INSIDE(theParam, FirstParam(), LastParam()))
	{
		FatalErrorIn("Pnt2d AutLib::Plane_Curve::Value(const Standard_Real theParam) const")
			<< "Invalid Parameter: " << theParam << endl
			<< " - First Parameter: " << FirstParam() << endl
			<< " - Last Parameter: " << LastParam() << endl
			<< abort(FatalError);
	}
#endif // DEBUG

	return Curve()->Value(theParam);
}

AutLib::Pnt2d 
AutLib::Pln_Curve::NormalizedParameterValue
(
	const Standard_Real theParam
) const
{
	Debug_Null_Pointer(Curve());
#ifdef DEBUG
	if (!INSIDE(theParam, 0, 1))
	{
		FatalErrorIn("Pnt2d AutLib::Plane_Curve::NormalizedParameterValue(const Standard_Real theParam) const")
			<< "Invalid Parameter: " << theParam << endl
			<< " - First Parameter: " << 0 << endl
			<< " - Last Parameter: " << 1 << endl
			<< abort(FatalError);
	}
#endif // DEBUG
	return Curve()->Value(FirstParam() + theParam * (LastParam() - FirstParam()));
}

AutLib::Entity2d_Box 
AutLib::Pln_Curve::BoundingBox() const
{
	Debug_Null_Pointer(Curve());
	Bnd_Box2d BndBox;
	BndLib_Add2dCurve::Add(Curve(), FirstParam(), LastParam(), 0, BndBox);

	Standard_Real Xmin, Xmax, Ymin, Ymax;
	BndBox.Get(Xmin, Ymin, Xmax, Ymax);
	return Entity2d_Box(Pnt2d(Xmin, Ymin), Pnt2d(Xmax, Ymax));
}

Standard_Boolean 
AutLib::Pln_Curve::Interpolation
(
	const std::vector<Pnt2d>& theQ,
	const Standard_Integer theDeg,
	const Standard_Real theTolerance
)
{
	if (theQ.size() < 2)
	{
		FatalErrorIn("Standard_Boolean AutLib::Plane_Curve::Interpolation(const pointList & theQ, const Standard_Integer theDeg, const Standard_Real theTolerance)")
			<< "Not enough points"
			<< abort(FatalError);
	}

	Handle(TColgp_HArray1OfPnt2d) PtsPtr = new TColgp_HArray1OfPnt2d(1, (Standard_Integer)theQ.size());
	auto& Pts = *PtsPtr;
	forThose(Index, 0, theQ.size() - 1)
		Pts.SetValue(Index + 1, theQ[Index]);

	Geom2dAPI_Interpolate Interpolation(PtsPtr, Standard_False, theTolerance);
	Interpolation.Perform();

	if (!Interpolation.IsDone())
	{
		return Standard_True;
	}

	try
	{
		Init
		(
			Interpolation.Curve()->FirstParameter(),
			Interpolation.Curve()->LastParameter(),
			Interpolation.Curve()
		);
		return Standard_False;
	}
	catch (StdFail_NotDone&)
	{
		return Standard_True;
	}
}

void AutLib::Pln_Curve::Split
(
	const Standard_Real x,
	std::shared_ptr<Pln_Curve>& theLeft,
	std::shared_ptr<Pln_Curve>& theRight
) const
{
	if (NOT INSIDE(x, FirstParam(), LastParam()))
	{
		FatalErrorIn("Standard_Boolean AutLib::Plane_Curve::Split(const Standard_Real x, std::shared_ptr<planeCurve>& theLeft, std::shared_ptr<planeCurve>& theRight) const")
			<< "Invalid Parameter: " << x << endl
			<< " - First Parameter: " << FirstParam() << endl
			<< " - Last Parameter: " << LastParam() << endl
			<< abort(FatalError);
	}

	if (!theLeft)
	{
		theLeft = std::make_shared<Pln_Curve>();
	}

	if (!theRight)
	{
		theRight = std::make_shared<Pln_Curve>();
	}

	theLeft->Init(FirstParam(), x, Curve());
	theRight->Init(x, LastParam(), Curve());
}

void AutLib::Pln_Curve::Split
(
	const Standard_Real x,
	Pnt2d & theCoord,
	std::shared_ptr<Pln_Curve>& theLeft, 
	std::shared_ptr<Pln_Curve>& theRight
) const
{
	if (NOT INSIDE(x, FirstParam(), LastParam()))
	{
		FatalErrorIn("Standard_Boolean AutLib::Plane_Curve::Split(const Standard_Real x, std::shared_ptr<planeCurve>& theLeft, std::shared_ptr<planeCurve>& theRight) const")
			<< "Invalid Parameter: " << x << endl
			<< " - First Parameter: " << FirstParam() << endl
			<< " - Last Parameter: " << LastParam() << endl
			<< abort(FatalError);
	}

	if (!theLeft)
	{
		theLeft = std::make_shared<Pln_Curve>();
	}

	if (!theRight)
	{
		theRight = std::make_shared<Pln_Curve>();
	}

	theLeft->Init(FirstParam(), x, Curve());
	theRight->Init(x, LastParam(), Curve());

	theCoord = Curve()->Value(x);
}

namespace AutLib
{

	Standard_Boolean CheckParameters(const std::vector<Standard_Real>& params, const Standard_Real theTol)
	{
		auto x0 = RealFirst();
		for (const auto x : params)
		{
			if ((x - x0) <= theTol)
			{
				return Standard_True;
			}
		}
		return Standard_False;
	}
}

template<>
void AutLib::Pln_Curve::Split<true>
(
	const std::vector<Standard_Real>& theParams,
	std::vector<Pnt2d>& theCoords,
	std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
	const Standard_Real theTol
	) const
{
	if (CheckParameters(theParams, theTol))
	{
		FatalErrorIn("void AutLib::Plane_Curve::Split()")
			<< "The parameter list is not sorted"
			<< abort(FatalError);
	}

	Pnt2d Coord;
	auto curve = this;
	std::shared_ptr<Pln_Curve> rightCurve;

	for (auto x : theParams)
	{
		auto leftCurve = std::make_shared<Pln_Curve>();
		rightCurve = std::make_shared<Pln_Curve>();

		curve->Split(x, Coord, leftCurve, rightCurve);

		theCoords.push_back(Coord);
		theCurves.push_back(leftCurve);

		curve = rightCurve.get();
	}
	theCurves.push_back(rightCurve);
}

void AutLib::Pln_Curve::Reverse()
{
	Curve()->Reverse();
	auto temp = LastParam();
	SetLastParam(Curve()->ReversedParameter(FirstParam()));
	SetFirstParam(Curve()->ReversedParameter(temp));
}

void AutLib::Pln_Curve::Mirror(const gp_Pnt2d & P)
{
	Debug_Null_Pointer(Curve());
	Curve()->Mirror(P);
}

void AutLib::Pln_Curve::Mirror(const gp_Ax2d & A)
{
	Debug_Null_Pointer(Curve());
	Curve()->Mirror(A);
}

void AutLib::Pln_Curve::Rotate(const gp_Pnt2d & P, const Standard_Real Ang)
{
	Debug_Null_Pointer(Curve());
	Curve()->Rotate(P, Ang);
}

void AutLib::Pln_Curve::Scale(const gp_Pnt2d & P, const Standard_Real S)
{
	Debug_Null_Pointer(Curve());
	Curve()->Scale(P, S);
}

void AutLib::Pln_Curve::Translate(const gp_Vec2d & V)
{
	Debug_Null_Pointer(Curve());
	Curve()->Translate(V);
}

void AutLib::Pln_Curve::Translate(const gp_Pnt2d & P1, const gp_Pnt2d & P2)
{
	Debug_Null_Pointer(Curve());
	Curve()->Translate(P1, P2);
}

void AutLib::Pln_Curve::Transform(const gp_Trsf2d & T)
{
	Debug_Null_Pointer(Curve());
	Curve()->Transform(T);
}
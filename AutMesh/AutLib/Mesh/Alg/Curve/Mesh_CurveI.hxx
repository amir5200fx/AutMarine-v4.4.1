#pragma once
#include <GeoProcessor.hxx>
#include <Mesh_CurveEntity.hxx>
#include <Mesh_CurveOptmPoint_Correction.hxx>
#include <Mesh_CurveOptmPoint_Newton.hxx>
namespace AutLib
{

	template<class CurveType, class SizeMap>
	void Mesh_Curve<CurveType, SizeMap>::MakeChain(const std::vector<Standard_Real>& theParameters)
	{
		theChain_ = std::make_shared<chain>();

		auto& Points = theChain_->Points();
		Points.reserve(theParameters.size());

		const auto& curve = *theCurve_;

		for (const auto x : theParameters)
		{
			Points.push_back(curve.Value(x));
		}

		Standard_Integer K = 0;
		auto& Indices = theChain_->Connectivity();
		Indices.resize(theParameters.size() - 1);
		for (auto& x : Indices)
		{
			x.Value(0) = K + 1;
			x.Value(1) = K + 2;
			++K;
		}
	}

	template<class CurveType, class SizeMap>
	Standard_Real Mesh_Curve<CurveType, SizeMap>::CalcLength
	(
		const entity & theCurve, 
		const Standard_Integer theLevel, 
		const Standard_Integer theMaxLevel,
		intgInfo & theInfo
	)
	{
		try
		{
			return Mesh_CurveLength::Length(theCurve, theInfo);
		}
		catch (const NonConvergency_Iteration_Failure&)
		{
			if (theLevel > theMaxLevel)
			{
				FatalErrorIn(FunctionSIG)
					<< "Can not Calculate length of the curve" << endl
					<< abort(FatalError);
			}
			return 
				CalcLength
				(
					entity
					(
						theCurve.Curve(),
						theCurve.SizeMap(),
						theCurve.FirstParameter(),
						MEAN(theCurve.FirstParameter(), theCurve.LastParameter())),
					theLevel + 1, theMaxLevel, theInfo)
				+ CalcLength
				(
					entity
					(
						theCurve.Curve(),
						theCurve.SizeMap(),
						MEAN(theCurve.FirstParameter(), theCurve.LastParameter()),
						theCurve.LastParameter()),
					theLevel + 1, theMaxLevel, theInfo);
		}
	}

	template<class CurveType, class SizeMap>
	Standard_Real Mesh_Curve<CurveType, SizeMap>::CalcLength
	(
		const entity & theCurve,
		const Standard_Integer theMaxLevel,
		intgInfo & theInfo
	)
	{
		return CalcLength(theCurve, 0, theMaxLevel, theInfo);
	}

	template<class CurveType, class SizeMap>
	Standard_Real Mesh_Curve<CurveType, SizeMap>::CalcNextParameter
	(
		const Standard_Real theU0,
		const Standard_Real theGuess,
		const Standard_Real theStep,
		const Standard_Real theUmax, 
		const Standard_Integer theLevel,
		const Standard_Integer theMaxLevel,
		const entity & theCurve,
		const info & theInfo
	)
	{
		Mesh_CurveOptmPoint_Correction<CurveType, SizeMap>
			correction(theU0, theGuess, theCurve, *theInfo.CorrAlgInfo());
		correction.Perform();

		Debug_If_Condition_Message(NOT correction.IsDone(), "mesh_curveoptpoint_correction algorithm has not been performed!");
		auto corrected = correction.Corrected();

		Mesh_CurveOptmPoint_Newton<CurveType, SizeMap>
			Iteration(theU0, theStep, theCurve);

		try
		{
			Iteration.Perform(corrected, *theInfo.NewtonIterInfo(), *theInfo.NewtonIntgInfo());
			Debug_If_Condition_Message(NOT Iteration.IsDone(), "mesh_curveoptpoint_newton algorithm has not been performed!");

			return Iteration.Corrected();
		}
		catch (const NonConvergency_Iteration_Failure&)
		{
			if (theLevel > theMaxLevel)
			{
				if (theInfo.IgnoreNonConvergency())
				{
					return Iteration.Corrected();
				}

				FatalErrorIn(FunctionSIG)
					<< "Can not Calculate parameter of the curve" << endl
					<< abort(FatalError);
			}

			const auto ds2 = theStep / 2;
			const auto du = theU0 + (corrected - theU0) / 2;

			auto u0 = 
				CalcNextParameter
				(
					theU0,
					du, ds2, theUmax, 
					theLevel + 1, theMaxLevel,
					theCurve, theInfo);
			return 
				CalcNextParameter
				(
					u0, u0 + du, ds2,
					theUmax, theLevel + 1,
					theMaxLevel, theCurve, theInfo
				);
		}
	}

	template<class CurveType, class SizeMap>
	Standard_Real Mesh_Curve<CurveType, SizeMap>::CalcNextParameter
	(
		const Standard_Real theU0, 
		const Standard_Real theGuess,
		const Standard_Real theStep,
		const Standard_Real theUmax, 
		const entity & theCurve, 
		const info & theInfo
	)
	{
		return 
			CalcNextParameter
			(
				theU0, theGuess, theStep,
				theUmax, 0, theInfo.MaxLevel_LengthCalc(),
				theCurve, theInfo);
	}

	template<class CurveType, class SizeMap>
	void Mesh_Curve<CurveType, SizeMap>::Perform()
	{
		if (NOT Curve())
		{
			FatalErrorIn("void Mesh_Curve<CurveType, SizeMap>::Perform()")
				<< "No curve has been loaded to discretization" << endl
				<< abort(FatalError);
		}

		if (NOT Map())
		{
			FatalErrorIn("void Mesh_Curve<CurveType, SizeMap>::Perform()")
				<< "No sizeMap has been loaded to discretization" << endl
				<< abort(FatalError);
		}

		Mesh_CurveEntity<CurveType, SizeMap> 
			Integrand(*Curve(), *Map(), FirstParameter(), LastParameter());

		// Determine the Length of the curve under the current space function
		auto curveLength = 
			CalcLength
			(
				Integrand, Info()->MaxLevel_LengthCalc(),
				*Info()->OverallLengthIntgInfo());

		// uniform nb. of segment under the current space function
		auto NbSegments = 
			MAX
			(
				Processor::Round(curveLength*(1.0 + EPS6)),
				Processor::Round(curveLength*(1.0 - EPS6)));

		// There must be at least one segment
		if (NbSegments < 1) NbSegments = 1;
		Debug_If_Condition(NbSegments < 1);

		const auto Ds = curveLength / (Standard_Real)NbSegments;
		const auto dt = 1.0 / curveLength;
		Standard_Real U0, U1, Guess;

		std::vector<Standard_Real> Parameters(NbSegments + 1);

		Parameters[0] = theFirst_;
		Parameters[Parameters.size() - 1] = theLast_;

		U0 = Parameters[0];
		Guess = U0 + dt;  // Debug: 4/14/2018

		if (Guess < theFirst_) Guess = theFirst_;
		if (Guess > theLast_) Guess = theLast_;

		forThose(Index, 1, NbSegments - 1)
		{
			U1 = CalcNextParameter
			(
				U0, Guess, Ds, 
				theLast_, Integrand, *Info());

			if (NOT INSIDE(U1, U0, theLast_))
			{
				FatalErrorIn("void Mesh_Curve<CurveType, SizeMap>::Perform()")
					<< "Invalid Parameter: " << U1 << endl
					<< " - First parameter: " << theFirst_ << endl
					<< " - Last parameter: " << theLast_ << endl
					<< abort(FatalError);
			}

			Parameters[Index] = U1;

			Guess = U1 + MIN(dt, Info()->UnderRelaxation()*(Parameters[Index] - Parameters[Index - 1]));

			Debug_If_Condition(Guess <= U1);

			U0 = U1;
		}

		MakeChain(Parameters);

		Change_IsDone() = Standard_True;
	}
}
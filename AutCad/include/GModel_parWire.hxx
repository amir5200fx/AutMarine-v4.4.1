#pragma once
#ifndef _GModel_parWire_Header
#define _GModel_parWire_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <error.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class GModel_parCurve;

	class GModel_parWire
		: public Global_Indexed
		, public Global_Named
	{

		typedef std::shared_ptr<GModel_parCurve> curve_ptr;
		typedef std::vector<curve_ptr> curveList;

		/*Private Data*/

		std::shared_ptr<curveList> theCurves_;

	public:

		GModel_parWire
		(
			const std::shared_ptr<curveList>& theCurves
		)
			: theCurves_(theCurves)
		{}

		GModel_parWire
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<curveList>& theCurves
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, theCurves_(theCurves)
		{}

		GModel_parWire
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<curveList>& theCurves
		)
			: Global_Indexed(theIndex)
			, theCurves_(theCurves)
		{}

		Standard_Integer NbCurves() const
		{
			Debug_Null_Pointer(theCurves_);
			return (Standard_Integer)theCurves_->size();
		}

		Entity2d_Box CalcParametricBoundingBox() const;

		const curveList& Curves() const
		{
			Debug_Null_Pointer(theCurves_);
			return *theCurves_;
		}

		void ExportToPlt(OFstream& File) const;

		static std::vector<std::shared_ptr<GModel_parCurve>>
			RetrieveCurvesFrom
			(
				const std::vector<std::shared_ptr<GModel_parWire>>& theWires
			);
	};
}

#endif // !_GModel_parWire_Header

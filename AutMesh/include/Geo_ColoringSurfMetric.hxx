#pragma once
#ifndef _Geo_ColoringSurfMetric_Header
#define _Geo_ColoringSurfMetric_Header

#include <Global_Done.hxx>
#include <Mesh2d_ElementFwd.hxx>
#include <error.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class Geo_ApprxSurfMetric;
	class Pnt2d;

	class Geo_ColoringSurfMetric
		: public Global_Done
	{

	public:

		typedef std::pair<std::shared_ptr<Mesh2d_Element>, Standard_Integer> elementColor;

	private:

		/*Private Data*/

		std::vector<elementColor> theElements_;

		std::shared_ptr<Geo_ApprxSurfMetric> theApprox_;

	public:

		Geo_ColoringSurfMetric()
		{}

		Geo_ColoringSurfMetric
		(
			const std::shared_ptr<Geo_ApprxSurfMetric>& theApprox
		)
			: theApprox_(theApprox)
		{}

		Standard_Boolean IsLoaded() const
		{
			return (Standard_Boolean)theApprox_;
		}

		Standard_Integer Value(const Standard_Integer theIndex) const
		{
			Debug_If_Condition(NOT IsDone());
			return theElements_[theIndex].second;
		}

		Standard_Integer Value(const Pnt2d& theCoord) const;

		const std::shared_ptr<Mesh2d_Element>& Element
		(
			const Standard_Integer theIndex
		) const
		{
			Debug_If_Condition(NOT IsDone());
			return theElements_[theIndex].first;
		}

		const std::shared_ptr<Geo_ApprxSurfMetric>& Approx() const
		{
			return theApprox_;
		}

		void LoadMetricApproximation
		(
			const std::shared_ptr<Geo_ApprxSurfMetric>& theApprox
		)
		{
			theApprox_ = theApprox;
		}

		void Perform();

		void ExportColorsToPlt(OFstream& File) const;
	};
}

#endif // !_Geo_ColoringSurfMetric_Header

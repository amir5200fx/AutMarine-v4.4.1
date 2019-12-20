#pragma once
#ifndef _Aft_NodeIdentifierAnIso_Header
#define _Aft_NodeIdentifierAnIso_Header

#include <Aft_NodeIdentifier.hxx>
#include <Entity2d_Metric1.hxx>

namespace AutLib
{

	class Aft_NodeIdentifierAnIso
		: public Aft_NodeIdentifier
	{

		/*Private Data*/

		Entity2d_Metric1 theMetric_;

	public:

		typedef Entity2d_Metric1 metricType;

		Aft_NodeIdentifierAnIso()
		{}

		const Entity2d_Metric1& Metric() const
		{
			return theMetric_;
		}

		void SetMetric(const Entity2d_Metric1& theMetric)
		{
			theMetric_ = theMetric;
		}
	};
}

#endif // !_Aft_NodeIdentifierAnIso_Header

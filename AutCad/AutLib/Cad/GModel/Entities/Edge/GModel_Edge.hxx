#pragma once
#ifndef _GModel_Edge_Header
#define _GModel_Edge_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <memory>

class gp_Trsf2d;

namespace AutLib
{

	// Forward Declarations
	class GModel_parCurve;
	class GModel_Curve;

	class GModel_Edge
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

		std::shared_ptr<GModel_parCurve> thePar_;
		std::shared_ptr<GModel_Curve> theCurve_;

	public:

		GModel_Edge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<GModel_parCurve>& thePar,
			const std::shared_ptr<GModel_Curve>& theCurve
		)
			: Global_Indexed(theIndex)
			, thePar_(thePar)
			, theCurve_(theCurve)
		{}

		GModel_Edge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<GModel_parCurve>& thePar,
			const std::shared_ptr<GModel_Curve>& theCurve
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, thePar_(thePar)
			, theCurve_(theCurve)
		{}

		const std::shared_ptr<GModel_parCurve>& Par() const
		{
			return thePar_;
		}

		const std::shared_ptr<GModel_Curve>& Curve() const
		{
			return theCurve_;
		}

		//- Static functions and operators

		static std::shared_ptr<GModel_Edge> 
			ReParameterization
			(
				const GModel_Edge& theEdge, 
				const gp_Trsf2d& trans
			);

		static std::shared_ptr<GModel_Edge> 
			BSplinePlaneEdge
			(
				const std::shared_ptr<GModel_Edge>& theEdge
			);

		static std::shared_ptr<GModel_Edge>
			uPlaneExpand
			(
				const GModel_Edge& theEdge,
				const Standard_Real multiply
			);

		static std::shared_ptr<GModel_Edge>
			vPlaneExpand
			(
				const GModel_Edge& theEdge,
				const Standard_Real multiply
			);
	};
}

#endif // !_GModel_Edge_Header

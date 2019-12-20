#pragma once
#ifndef _Singularity_PoleCurve_Header
#define _Singularity_PoleCurve_Header

#include <Mesh_SingularityCurve.hxx>
#include <Entity2d_Chain.hxx>
#include <Mesh2d_SizeMapSurface.hxx>
#include <Mesh2d_SizeMapAnIso.hxx>
#include <Mesh2d_SizeMap.hxx>
#include <Mesh_CurveInfo.hxx>

namespace AutLib
{

	class Singularity_PoleCurveBase
	{

	public:


	};

	template<class PlnCurve>
	class Singularity_PoleCurve
		: public Mesh_SingularityCurve<PlnCurve>
	{

		/*Private Data*/

		Pnt2d theMid_;

	public:

		typedef typename Mesh_SingularityCurve<PlnCurve>::infoType info;
		typedef typename Mesh_SingularityCurve<PlnCurve>::curveType curveType;

		Singularity_PoleCurve
		(
			const Standard_Real theFirst,
			const Standard_Real theLast,
			const Handle(curveType)& theCurve,
			const std::shared_ptr<info>& theInfo
		)
			: Mesh_SingularityCurve<PlnCurve>(theFirst, theLast, theCurve, theInfo)
		{}

		const Pnt2d& Mid() const
		{
			return theMid_;
		}

		void SetMid(const Pnt2d& theP)
		{
			theMid_ = theP;
		}

		std::shared_ptr<Entity2d_Chain> Mesh
		(
			const std::shared_ptr<Mesh2d_SizeMapSurface>& theSizeMap,
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		) const override;

		std::shared_ptr<Entity2d_Chain> Mesh
		(
			const std::shared_ptr<Mesh2d_SizeMapAnIso>& theSizeMap,
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		) const override;

		std::shared_ptr<Entity2d_Chain> Mesh
		(
			const std::shared_ptr<Mesh2d_SizeMap>& theSizeMap,
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		) const override;
	};
}

#include <Singularity_PoleCurveI.hxx>

#endif // !_Singularity_PoleCurve_Header

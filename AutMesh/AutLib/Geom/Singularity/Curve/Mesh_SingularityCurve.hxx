#pragma once
#ifndef _Mesh_SingularityCurve_Header
#define _Mesh_SingularityCurve_Header

#include <Standard_Handle.hxx>
#include <Standard_TypeDef.hxx>

#include <memory>

class Geom2d_Curve;
class Geom_Curve;
class Geom_Surface;

namespace AutLib
{

	template<class PlnCurve>
	class Mesh_SingularityCurve
		: public PlnCurve
	{

		/*private Data*/

		Handle(Geom_Curve) thePaired3d_;

	protected:

		typedef typename PlnCurve::infoType info;
		typedef typename PlnCurve::geomType curveType;

		Mesh_SingularityCurve
		(
			const Standard_Real theFirst,
			const Standard_Real theLast,
			const Handle(curveType)& theCurve,
			const std::shared_ptr<info>& theInfo
		)
			: PlnCurve(theFirst, theLast, theCurve, theInfo)
		{}

	public:

		typedef info infoType;

		const Handle(Geom_Curve)& Paired3d() const
		{
			return thePaired3d_;
		}

		void CreatePaired3d(const Geom_Surface& theSurface);
	};
}

#endif // !_Mesh_SingularityCurve_Header

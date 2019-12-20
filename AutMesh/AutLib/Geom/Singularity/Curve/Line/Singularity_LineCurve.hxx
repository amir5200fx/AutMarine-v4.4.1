#pragma once
#ifndef _Singularity_LineCurve_Header
#define _Singularity_LineCurve_Header

#include <Mesh_SingularityCurve.hxx>

namespace AutLib
{

	template<class PlnCurve>
	class Singularity_LineCurve
		: public Mesh_SingularityCurve<PlnCurve>
	{

		/*Private Data*/

	public:

		typedef typename Mesh_SingularityCurve<PlnCurve>::infoType info;
		typedef typename Mesh_SingularityCurve<PlnCurve>::curveType curveType;

		Singularity_LineCurve
		(
			const Standard_Real theFirst,
			const Standard_Real theLast,
			const Handle(curveType)& theCurve,
			const std::shared_ptr<info>& theInfo
		)
			: Mesh_SingularityCurve<PlnCurve>(theFirst, theLast, theCurve, theInfo)
		{}
	};
}

#endif // !_Singularity_LineCurve_Header

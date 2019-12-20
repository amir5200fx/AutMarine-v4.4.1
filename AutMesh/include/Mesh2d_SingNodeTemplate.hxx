#pragma once
#ifndef _Mesh2d_SingNodeTemplate_Header
#define _Mesh2d_SingNodeTemplate_Header

#include <Pnt2d.hxx>

namespace AutLib
{

	template<class BndNodeType>
	class Mesh2d_SingNodeTemplate
		: public BndNodeType
	{

		/*Private Data*/

	protected:

		Mesh2d_SingNodeTemplate()
		{}

		Mesh2d_SingNodeTemplate
		(
			const Standard_Integer theIndex
		)
			: BndNodeType(theIndex)
		{}

		Mesh2d_SingNodeTemplate
		(
			const Standard_Integer theIndex, 
			const Pnt2d& theCoord
		)
			: BndNodeType(theIndex, theCoord)
		{}

	public:

		enum
		{
			hierarchy = 2
		};
	};
}

#endif // !_Mesh2d_SingNodeTemplate_Header

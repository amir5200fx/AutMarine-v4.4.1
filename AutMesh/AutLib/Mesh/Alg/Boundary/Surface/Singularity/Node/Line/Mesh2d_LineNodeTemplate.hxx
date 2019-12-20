#pragma once
#ifndef _Mesh2d_LineNodeTemplate_Header
#define _Mesh2d_LineNodeTemplate_Header

#include <Mesh2d_SingNodeTemplate.hxx>

namespace AutLib
{


	template<class BndNodeType>
	class Mesh2d_LineNodeTemplate
		: public Mesh2d_SingNodeTemplate<BndNodeType>
	{

		/*Private Data*/

	public:

		typedef Mesh2d_SingNodeTemplate<BndNodeType> base;

		Mesh2d_LineNodeTemplate()
		{}

		Mesh2d_LineNodeTemplate(const Standard_Integer theIndex)
			: Mesh2d_SingNodeTemplate<BndNodeType>(theIndex)
		{}

		Mesh2d_LineNodeTemplate
		(
			const Standard_Integer theIndex,
			const Pnt2d& theCoord
		)
			: Mesh2d_SingNodeTemplate<BndNodeType>(theIndex, theCoord)
		{}


		//- Static functions and operators

		static std::shared_ptr<BndNodeType> MergeNodes
		(
			const std::shared_ptr<BndNodeType>& theNode0,
			const std::shared_ptr<BndNodeType>& theNode1,
			const typename base::Merge_Alg Alg = base::Merge_Alg_New
		);
	};
}

#include <Mesh2d_LineNodeTemplateI.hxx>

#endif // !_Mesh2d_LineNodeTemplate_Header

#pragma once
#ifndef _Mesh2d_PoleNodeTemplate_Header
#define _Mesh2d_PoleNodeTemplate_Header

#include <Mesh2d_SingNodeTemplate.hxx>

namespace AutLib
{

	class Mesh2d_PoleNodeInfo
	{

		/*Private Data*/

		Standard_Boolean IsFixed_;

	public:

		Mesh2d_PoleNodeInfo()
			: IsFixed_(Standard_False)
		{}

		Standard_Boolean IsFixed() const
		{
			return IsFixed_;
		}

		void SetFixed(const Standard_Boolean IsFixed)
		{
			IsFixed_ = IsFixed;
		}
	};

	template<class BndNodeType>
	class Mesh2d_PoleNodeTemplate
		: public Mesh2d_PoleNodeInfo
		, public Mesh2d_SingNodeTemplate<BndNodeType>
	{

		/*Private Data*/

	public:

		typedef Mesh2d_SingNodeTemplate<BndNodeType> base;

		Mesh2d_PoleNodeTemplate()
		{}

		Mesh2d_PoleNodeTemplate
		(
			const Standard_Integer theIndex
		)
			: Mesh2d_SingNodeTemplate<BndNodeType>(theIndex)
		{}

		Mesh2d_PoleNodeTemplate
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

#include <Mesh2d_PoleNodeTemplateI.hxx>

#endif // !_Mesh2d_PoleNodeTemplate_Header

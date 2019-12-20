#pragma once
#include <Global_Macros.hxx>
template<class BndNodeType>
std::shared_ptr<BndNodeType>
AutLib::Mesh2d_PoleNodeTemplate<BndNodeType>::MergeNodes
(
	const std::shared_ptr<BndNodeType>& theNode0,
	const std::shared_ptr<BndNodeType>& theNode1, 
	const typename base::Merge_Alg Alg
)
{
	Debug_Null_Pointer(theNode0);
	Debug_Null_Pointer(theNode1);

	if (Alg IS_EQUAL base::Merge_Alg_FirstPreferred)
	{
		auto node = theNode0;
		return std::move(node);
	}
	else if (Alg IS_EQUAL base::Merge_Alg_SecondPreferred)
	{
		auto node = MergeNodes(theNode1, theNode0, base::Merge_Alg_FirstPreferred);
		return std::move(node);
	}
	else
	{
		auto node = 
			std::make_shared<Mesh2d_PoleNodeTemplate>(0, MEAN(theNode0->Coord(), theNode1->Coord()));
		node->SetFixed(Standard_False);
		return std::move(node);
	}
}
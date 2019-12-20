#pragma once
#include <Global_Macros.hxx>
namespace AutLib
{

	/*template<class BndNodeTraits, Mesh_BndNode_Position POS>
	std::shared_ptr<Aft_BndNode<BndNodeTraits, POS>> 
		Aft_BndNode<BndNodeTraits, POS>::MergeNodes
		(
			const std::shared_ptr<Aft_BndNode>& theNode0, 
			const std::shared_ptr<Aft_BndNode>& theNode1,
			const typename base::Merge_Alg theAlg
		)
	{
		if (theAlg IS_EQUAL base::Merge_Alg_FirstPreferred)
		{
			auto node = theNode0;
			return std::move(node);
		}
		else if (theAlg IS_EQUAL base::Merge_Alg_SecondPreferred)
		{
			auto node = MergeNodes(theNode1, theNode0, base::Merge_Alg_FirstPreferred);
			return std::move(node);
		}
		else
		{
			auto node =
				std::make_shared<Aft_BndNode>(0, MEAN(theNode0->Coord(), theNode1->Coord()));
			return std::move(node);
		}
	}*/
}
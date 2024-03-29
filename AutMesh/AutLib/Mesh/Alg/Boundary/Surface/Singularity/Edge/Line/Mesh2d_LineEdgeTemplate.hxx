#pragma once
#ifndef _Mesh2d_LineEdgeTemplate_Header
#define _Mesh2d_LineEdgeTemplate_Header

#include <Mesh2d_SingEdgeTemplate.hxx>
#include <Entity2d_Chain.hxx>

#include <vector>

namespace AutLib
{

	template<class BndEdgeType>
	class Mesh2d_LineEdgeTemplate
		: public Mesh2d_SingEdgeTemplate<BndEdgeType>
	{

		/*Private Data*/

	public:

		typedef Mesh2d_SingEdgeTemplate<BndEdgeType> base;
		typedef typename base::bndNodeType bndNodeType;
		typedef typename base::bndEdgeType bndEdgeType;

		typedef typename bndEdgeType::edgeType edgeType;
		typedef typename bndEdgeType::nodeType nodeType;

		Mesh2d_LineEdgeTemplate()
		{}

		Mesh2d_LineEdgeTemplate(const Standard_Integer theIndex)
			: Mesh2d_SingEdgeTemplate<BndEdgeType>(theIndex)
		{}

		Mesh2d_LineEdgeTemplate
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<typename BndEdgeType::nodeType>& theNode0,
			const std::shared_ptr<typename BndEdgeType::nodeType>& theNode1
		)
			: Mesh2d_SingEdgeTemplate<BndEdgeType>(theIndex, theNode0, theNode1)
		{}

		Standard_Boolean IsLineSingular() const override
		{
			return Standard_True;
		}

		Standard_Boolean IsSingular() const override
		{
			return Standard_True;
		}

		//- Static functions and operators

		static std::vector<std::shared_ptr<edgeType>> 
			GetTopology
			(
				const Entity2d_Chain& theChain
			);
	};
}

#include <Mesh2d_LineEdgeTemplateI.hxx>

#endif // !_Mesh2d_LineEdgeTemplate_Header

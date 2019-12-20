#pragma once
#ifndef _Mesh2d_PoleEdgeTemplate_Header
#define _Mesh2d_PoleEdgeTemplate_Header

#include <Mesh2d_SingEdgeTemplate.hxx>
#include <Mesh2d_SizeMapSurface.hxx>
#include <Entity2d_ChainFwd.hxx>

#include <vector>

#include "Mesh2d_PoleNodeTemplate.hxx"
#include "Aft2d_gCornerNode.hxx"

namespace AutLib
{

	template<class BndEdgeType>
	class Mesh2d_PoleEdgeTemplate
		: public Mesh2d_SingEdgeTemplate<BndEdgeType>
	{

		/*Private Data*/

	public:

		typedef Mesh2d_SingEdgeTemplate<BndEdgeType> base;
		typedef typename base::bndNodeType bndNodeType;
		typedef typename base::bndEdgeType bndEdgeType;

		typedef typename bndEdgeType::edgeType edgeType;
		typedef typename bndEdgeType::nodeType nodeType;

		Mesh2d_PoleEdgeTemplate()
		{}

		Mesh2d_PoleEdgeTemplate
		(
			const Standard_Integer theIndex
		)
			: Mesh2d_SingEdgeTemplate<BndEdgeType>(theIndex)
		{}

		Mesh2d_PoleEdgeTemplate
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<typename BndEdgeType::nodeType>& theNode0,
			const std::shared_ptr<typename BndEdgeType::nodeType>& theNode1
		)
			: Mesh2d_SingEdgeTemplate<BndEdgeType>(theIndex, theNode0, theNode1)
		{}

		void SingularityContraction(const Mesh2d_SizeMapSurface& theSizeMap) override;


		Standard_Boolean IsPoleSingular() const override
		{
			return Standard_True;
		}

		Standard_Boolean IsSingular() const override
		{
			return Standard_True;
		}

		//- Static functions and operators

		static std::vector<std::shared_ptr<edgeType>> GetTopology(const Entity2d_Chain& theChain);
	};
}

#include <Mesh2d_PoleEdgeTemplateI.hxx>

#endif // !_Mesh2d_PoleEdgeTemplate_Header

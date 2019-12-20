#pragma once
#ifndef _Mesh2d_SingEdgeTemplate_Header
#define _Mesh2d_SingEdgeTemplate_Header

#include <Standard_TypeDef.hxx>

#include <memory>

namespace AutLib
{

	template<class BndEdgeType>
	class Mesh2d_SingEdgeTemplate
		: public BndEdgeType
	{

		/*Private Data*/

	public:

		typedef typename BndEdgeType::bndNodeType bndNodeType;
		typedef typename BndEdgeType::bndEdgeType bndEdgeType;

		enum
		{
			hierarchy = 2
		};

		Mesh2d_SingEdgeTemplate()
		{}

		Mesh2d_SingEdgeTemplate(const Standard_Integer theIndex)
			: BndEdgeType(theIndex)
		{}

		Mesh2d_SingEdgeTemplate
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<typename BndEdgeType::nodeType>& theNode0,
			const std::shared_ptr<typename BndEdgeType::nodeType>& theNode1
		)
			: BndEdgeType(theIndex, theNode0, theNode1)
		{}

		//- Static functions and operators


	};
}

#endif // !_Mesh2d_SingEdgeTemplate_Header

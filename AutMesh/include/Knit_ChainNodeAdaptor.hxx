#pragma once
#ifndef _Knit_ChainNodeAdaptor_Header
#define _Knit_ChainNodeAdaptor_Header

#include <Standard_TypeDef.hxx>
#include <Adt_AvlTree.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <list>
#include <memory>

namespace AutLib
{

	template<class EdgeType>
	class Knit_ChainNodeAdaptor
	{

		/*Private Data*/

		Adt_AvlTree<std::weak_ptr<EdgeType>> theEdges_;

	public:

		Knit_ChainNodeAdaptor()
		{
			theEdges_.SetComparableFunction(&EdgeType::IsLess);
		}

		Standard_Integer NbEdges() const
		{
			return (Standard_Integer)theEdges_.Size();
		}

		Standard_Boolean IsEmpty() const
		{
			return !NbEdges();
		}

		/*const std::list<std::weak_ptr<EdgeType>>& Edges() const
		{
			return theEdges_;
		}*/

		void InsertToEdges(const std::weak_ptr<EdgeType>& theEdge)
		{
			Debug_Null_Pointer(theEdge.lock());
			theEdges_.Insert(theEdge);
		}

		void RemoveFromEdges(const std::weak_ptr<EdgeType>& theEdge)
		{
			Debug_Null_Pointer(theEdge.lock());
			theEdges_.Remove(theEdge);
		}

		void RetrieveEdgesTo(std::vector<std::weak_ptr<EdgeType>>& theEdges) const
		{
			theEdges_.RetrieveTo(theEdges);
		}
	};
}

#endif // !_Knit_ChainNodeAdaptor_Header

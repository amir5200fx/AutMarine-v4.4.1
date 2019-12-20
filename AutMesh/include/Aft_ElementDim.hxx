#pragma once
#ifndef _Aft_ElementDim_Header
#define _Aft_ElementDim_Header

#include <Mesh_Facet.hxx>
#include <Mesh_Element.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <memory>

namespace AutLib
{

	template<class ElementTraits, int Dim>
	class Aft_ElementDim
	{};

	template<class ElementTraits>
	class Aft_ElementDim<ElementTraits, 3>
		: public Mesh_Element
		<
		typename ElementTraits::nodeType,
		typename ElementTraits::edgeType,
		typename ElementTraits::adaptorType,
		typename ElementTraits::facetType
		>
	{

		/*Private Data*/
		
	public:

		enum
		{
			nbNodes = 4
		};

		static const std::shared_ptr<Aft_ElementDim> null_ptr;

		typedef typename ElementTraits::nodeType nodeType;
		typedef typename ElementTraits::edgeType edgeType;
		typedef typename ElementTraits::facetType facetType;

		typedef typename ElementTraits::adaptorType adaptorType;

		typedef Mesh_Element
			<
			typename ElementTraits::nodeType,
			typename ElementTraits::edgeType,
			typename ElementTraits::adaptorType,
			typename ElementTraits::facetType
			> base;

		Aft_ElementDim()
		{}

		Aft_ElementDim(const Standard_Integer theIndex)
			: base(theIndex)
		{}

		Aft_ElementDim
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<nodeType>& theNode0, 
			const std::shared_ptr<nodeType>& theNode1, 
			const std::shared_ptr<nodeType>& theNode2, 
			const std::shared_ptr<nodeType>& theNode3
		)
			: base(theIndex, theNode0, theNode1, theNode2, theNode3)
		{}

		Standard_Integer OppositeVertexIndex(const std::shared_ptr<facetType>& theFace) const
		{
			Debug_Null_Pointer(theFace);
			for (int i = 0; i < 4; i++)
			{
				if (base::Face(i) == theFace)
				{
					return i;
				}
			}

			FatalErrorIn("Standard_Integer OppositeVertexIndex(const std::shared_ptr<facetType>& theFace) const")
				<< "Found no opposite vertex"
				<< abort(FatalError);

			return 0;
		}

		Standard_Integer OppositeVertexIndex(const std::shared_ptr<Aft_ElementDim>& theElement) const
		{
			Debug_Null_Pointer(theElement);
			for (int i = 0; i < 4; i++)
			{
				if (base::Neighbor(i).lock() == theElement)
				{
					return i;
				}
			}

			FatalErrorIn("Standard_Integer OppositeVertexIndex(const std::shared_ptr<ElementTraitsType>& theElement) const")
				<< "Found no opposite vertex"
				<< abort(FatalError);

			return 0;
		}

		const std::shared_ptr<nodeType>& OppositeVertex(const std::shared_ptr<facetType>& theFace) const
		{
			Debug_Null_Pointer(theFace);
			for (int i = 0; i < 4; i++)
			{
				if (base::Face(i) == theFace)
				{
					return Node(i);
				}
			}
			return nodeType::null_ptr;
		}

		const std::shared_ptr<nodeType>& OppositeVertex(const std::shared_ptr<Aft_ElementDim>& theElement) const
		{
			Debug_Null_Pointer(theElement);
			for (int i = 0; i < 4; i++)
			{
				if (base::Neighbor(i).lock() == theElement)
				{
					return Node(i);
				}
			}
			return nodeType::null_ptr;
		}
	};

	template<class ElementTraits>
	class Aft_ElementDim<ElementTraits, 2>
		: public Mesh_Facet<ElementTraits, typename ElementTraits::adaptorType>
	{

		typedef Mesh_Facet<ElementTraits, typename ElementTraits::adaptorType> facet;

		typedef typename ElementTraits::nodeType nodeType;
		typedef typename ElementTraits::edgeType edgeType;
		
		typedef std::shared_ptr<nodeType> nodePtr;
		typedef std::shared_ptr<edgeType> edgePtr;
		typedef std::shared_ptr<Aft_ElementDim> elementPtr;

		/*private Data*/

	public:

		static const std::shared_ptr<Aft_ElementDim> null_ptr;

		enum
		{
			nbNodes = 3
		};

		Aft_ElementDim()
		{}

		Aft_ElementDim(const Standard_Integer theIndex)
			: Mesh_Facet<ElementTraits, typename ElementTraits::adaptorType>(theIndex)
		{}

		Aft_ElementDim
		(
			const Standard_Integer theIndex,
			const nodePtr& theNode0,
			const nodePtr& theNode1, 
			const nodePtr& theNode2
		)
			: Mesh_Facet
			<
			ElementTraits,
			typename ElementTraits::adaptorType
			>(theIndex, theNode0, theNode1, theNode2)
		{}

		Standard_Integer OppositeVertexIndex(const edgePtr& theEdge) const
		{
			Debug_Null_Pointer(theEdge);
			for (int i = 0; i < 3; i++)
			{
				if (facet::Edge(i) == theEdge)
				{
					return i;
				}
			}

			FatalErrorIn("Standard_Integer OppositeVertexIndex(const Aft2d_Edge& theEdge) const")
				<< "Found no opposite vertex"
				<< abort(FatalError);

			return 0;
		}

		Standard_Integer OppositeVertexIndex(const elementPtr& theElement) const
		{
			Debug_Null_Pointer(theElement);
			for (int i = 0; i < 3; i++)
			{
				if (facet::Neighbor(i).lock() == theElement)
				{
					return i;
				}
			}

			FatalErrorIn("Standard_Integer OppositeVertexIndex(const Aft2d_Element& theElement) const")
				<< "Found no opposite vertex"
				<< abort(FatalError);

			return 0;
		}

		const nodePtr& OppositeVertex(const edgePtr& theEdge) const
		{
			for (int i = 0; i < 3; i++)
			{
				if (facet::Edge(i) == theEdge)
				{
					return this->Node(i);
				}
			}
			return nodeType::null_ptr;
		}

		const nodePtr& OppositeVertex(const elementPtr& theElement) const
		{
			for (int i = 0; i < 3; i++)
			{
				if (facet::Neighbor(i).lock() == theElement)
				{
					return this->Node(i);
				}
			}
			return nodeType::null_ptr;
		}
	};
}

#endif // !_Aft_ElementDim_Header

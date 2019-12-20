#pragma once
#ifndef _Mesh_Element_Header
#define _Mesh_Element_Header

#include <Mesh_Entity.hxx>

#include <memory>

#define MESH_ELEMENT_ACCESSMETHOD(PARAM_TYPE, PARAM_NAME)																									\
  const std::shared_ptr<PARAM_TYPE>& PARAM_NAME##0() const {return the##PARAM_NAME##s_[0];}																	\
  const std::shared_ptr<PARAM_TYPE>& PARAM_NAME##1() const {return the##PARAM_NAME##s_[1];}																	\
  const std::shared_ptr<PARAM_TYPE>& PARAM_NAME##2() const {return the##PARAM_NAME##s_[2];}																	\
  const std::shared_ptr<PARAM_TYPE>& PARAM_NAME##3() const {return the##PARAM_NAME##s_[3];}																	\
  std::shared_ptr<PARAM_TYPE>& PARAM_NAME##0() {return the##PARAM_NAME##s_[0];}																				\
  std::shared_ptr<PARAM_TYPE>& PARAM_NAME##1() {return the##PARAM_NAME##s_[1];}																				\
  std::shared_ptr<PARAM_TYPE>& PARAM_NAME##2() {return the##PARAM_NAME##s_[2];}																				\
  std::shared_ptr<PARAM_TYPE>& PARAM_NAME##3() {return the##PARAM_NAME##s_[3];}																				\
  const std::shared_ptr<PARAM_TYPE>& PARAM_NAME(const Standard_Integer theIndex) const {return the##PARAM_NAME##s_[theIndex];}								\
  std::shared_ptr<PARAM_TYPE>& PARAM_NAME(const Standard_Integer theIndex) {return the##PARAM_NAME##s_[theIndex];}											\
  void Set##PARAM_NAME(const Standard_Integer theIndex, const std::shared_ptr<PARAM_TYPE>& the##PARAM_NAME) {the##PARAM_NAME##s_[theIndex]=the##PARAM_NAME;}

namespace AutLib
{

	template<class NodeType, class EdgeType, class ElementAdaptor, class FacetType = void>
	class Mesh_Element
		: public Mesh_Entity
		, public ElementAdaptor
	{

	public:

		typedef NodeType nodeType;
		typedef EdgeType edgeType;
		typedef FacetType facetType;

	private:

		/*Private Data*/

		std::shared_ptr<nodeType> theNodes_[4];
		
		std::shared_ptr<edgeType> theEdges_[6];
		std::shared_ptr<facetType> theFaces_[4];

	public:

		enum
		{
			hierarchy = 0
		};

		Mesh_Element()
		{}

		Mesh_Element(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
		{}

		Mesh_Element
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<nodeType>& theNode0,
			const std::shared_ptr<nodeType>& theNode1, 
			const std::shared_ptr<nodeType>& theNode2, 
			const std::shared_ptr<nodeType>& theNode3
		)
			: Global_Indexed(theIndex)
		{
			Node0() = theNode0;
			Node1() = theNode1;
			Node2() = theNode2;
			Node3() = theNode3;
		}

		const std::shared_ptr<edgeType>& Edge4() const
		{
			return theEdges_[4];
		}

		std::shared_ptr<edgeType>& Edge4()
		{
			return theEdges_[4];
		}

		const std::shared_ptr<edgeType>& Edge5() const
		{
			return theEdges_[5];
		}

		std::shared_ptr<edgeType>& Edge5()
		{
			return theEdges_[5];
		}

		MESH_ELEMENT_ACCESSMETHOD(nodeType, Node)
			MESH_ELEMENT_ACCESSMETHOD(edgeType, Edge)
			MESH_ELEMENT_ACCESSMETHOD(facetType, Face)

	};
}

#undef MESH_ELEMENT_ACCESSMETHOD

#endif // !_Mesh_Element_Header

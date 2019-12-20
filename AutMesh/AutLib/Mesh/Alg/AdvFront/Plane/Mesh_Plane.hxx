#pragma once
#ifndef _Mesh_Plane_Header
#define _Mesh_Plane_Header

#include <Geom_AdTree.hxx>
#include <Geom_PriorityList.hxx>
#include <Aft_Core.hxx>
#include <Global_Done.hxx>
#include <Entity2d_Chain.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Aft2d_FrontTraits.hxx>

#include <Aft_FrontInfo.hxx>
#include <Aft_FrontGlobalData.hxx>

#include <map>

#include "Mesh2d_SizeMapAnIso.hxx"

namespace AutLib
{

	// Forward Declarations
	template
		<
		class FrontEntity,
		template<class> class GeomSearch,
		template<class> class PriorityList
		>
		class Aft_FrontGlobalData;

	template<class FrontTraits, class FrontAdaptor>
	class Aft2d_FrontInfoTemplate;

	template<class FrontTraits>
	class Aft2d_FrontInfoAdaptorTemplate;

	template<class T>
	class Geom_AdTree;

	struct Mesh_PlaneInfo
	{
		static const Standard_Integer ALLOWED_MAX_LEVEL_GENERATION;

		static const Standard_Real DEFAULT_LOCALFRONT_FACTOR;
		static const Standard_Real DEFAULT_MIN_DISTANCE_FACTOR;
	};

	class Mesh_PlaneNumberingCache
	{

		typedef std::map<unsigned, unsigned> indexMap;

		/*Private Data*/

	protected:

		mutable unsigned nodeIndex;
		mutable unsigned edgeIndex;
		mutable unsigned elementIndex;

		mutable std::shared_ptr<indexMap> NodesIndices;
		mutable std::shared_ptr<indexMap> EdgesIndices;
		mutable std::shared_ptr<indexMap> ElementsIndices;

	protected:

		Mesh_PlaneNumberingCache()
		{}

	};

	template<class SizeMap, class BoundarySizeMap>
	class Mesh_Plane
		: public Aft_Core
		<
		SizeMap,
		Aft2d_FrontInfoTemplate
		<
		Aft2d_FrontTraits<typename SizeMap::frontType>,
		Aft2d_FrontInfoAdaptorTemplate<Aft2d_FrontTraits<typename SizeMap::frontType>>
		>,
		Aft_FrontGlobalData<typename SizeMap::frontType, Geom_AdTree, Geom_PriorityList>
		>
		, public Global_Done
		, public Mesh_PlaneInfo
		, public Mesh_PlaneNumberingCache
	{

		typedef Aft2d_FrontTraits<typename SizeMap::frontType> frontTraits;

		typedef typename frontTraits::elementType elementType;
		typedef typename frontTraits::edgeType frontType;
		typedef typename frontTraits::edgeType edgeType;
		typedef typename frontTraits::nodeType nodeType;

		typedef std::shared_ptr<frontType> front_ptr;
		typedef std::shared_ptr<elementType> element_ptr;
		typedef std::shared_ptr<nodeType> node_ptr;

		typedef std::map<unsigned, unsigned> indexMap;

		/*Private Data*/

		//- Boundary size map which may be different with the domain's size map
		std::shared_ptr<BoundarySizeMap> theBoundaryMap_;

		std::vector<front_ptr> theBoundaryEdges_;

		std::shared_ptr<Entity2d_Triangulation> theTriangulation_;


		//- functions and operators

		void Import(const std::vector<front_ptr>& theBoundary, const BoundarySizeMap& theBoundaryMap);

	protected:

		std::vector<front_ptr>& ChangeBoundaryEdges()
		{
			return theBoundaryEdges_;
		}

		Standard_Integer Meshing();

		Standard_Boolean CheckAngle
		(
			const frontType& theFront,
			const nodeType& theNode,
			const Standard_Real CosAngle
		) const;

		void MeshingOneLevel(/*OFstream& File*/);

		void FindValidNode
		(
			const Stl_Vector<node_ptr>& theCandidates,
			const Stl_Vector<front_ptr>& theEffectives
		);

		void Update();

		void InsertNewEdgesToLevels();

		void CompactNumbering_Nodes() const;

		void CompactNumbering_Edges() const;

		void CompactNumbering_Elements() const;

	public:

		typedef Aft_Core
			<
			SizeMap,
			Aft2d_FrontInfoTemplate
			<
			Aft2d_FrontTraits<typename SizeMap::frontType>,
			Aft2d_FrontInfoAdaptorTemplate<Aft2d_FrontTraits<typename SizeMap::frontType>>
			>,
			Aft_FrontGlobalData<typename SizeMap::frontType, Geom_AdTree, Geom_PriorityList>
			> base;

		/*typedef Aft2d_FrontInfoTemplate
			<
			Aft2d_FrontTraits<typename SizeMap::frontType>,
			Aft2d_FrontInfoAdaptorTemplate<Aft2d_FrontTraits<typename SizeMap::frontType>>
			> frontInfo;

		typedef Aft_FrontGlobalData
			<
			typename SizeMap::frontType,
			Geom_AdTree,
			Geom_PriorityList
			> frontData;*/

		typedef typename base::globalData globalData;
		typedef typename base::frontData frontData;

		Mesh_Plane()
		{}

		Standard_Boolean IsBoundaryLoaded() const
		{
			return (Standard_Boolean)theBoundaryEdges_.size();
		}

		Standard_Boolean IsBoundaryMapLoaded() const
		{
			return (Standard_Boolean)theBoundaryMap_;
		}

		Standard_Boolean IsLoaded() const
		{
			if (NOT base::IsSizeMapLoaded()) return Standard_False;
			if (NOT IsBoundaryLoaded()) return Standard_False;
			if (NOT IsBoundaryMapLoaded()) return Standard_False;
			return Standard_True;
		}

		const std::vector<front_ptr>& BoundaryEdges() const
		{
			return theBoundaryEdges_;
		}

		const std::shared_ptr<Entity2d_Triangulation>& StaticMesh() const
		{
			return theTriangulation_;
		}

		const std::shared_ptr<BoundarySizeMap>& BoundaryMap() const
		{
			return theBoundaryMap_;
		}

		void LoadBoundaryEdges(const std::vector<front_ptr>& theBoundaryEdges)
		{
			theBoundaryEdges_ = theBoundaryEdges;
		}

		void LoadBoundarySizeMap(const std::shared_ptr<BoundarySizeMap>& theSizeMap)
		{
			theBoundaryMap_ = theSizeMap;
		}

		void Perform();

		void CreateStaticMesh();

		void CompactNumbering() const;

		void CompactNumbering(const std::vector<element_ptr>& theElements) const;

		//- static functions and operators

		static void ActiveFront(const std::vector<front_ptr>& theEdges);

		static Stl_Vector<node_ptr> RetrieveNodesFrom
		(
			const Stl_Vector<front_ptr>& theEffectives
		);

		static Stl_Vector<node_ptr> RetrieveNodesFrom
		(
			const Stl_Vector<element_ptr>& theElements
		);

		static Stl_Vector<front_ptr> RetrieveEdgesFrom
		(
			const Stl_Vector<element_ptr>& theElements
		);

		template<class EntityType>
		static Standard_Integer FindMaxIndex
		(
			const std::vector<std::shared_ptr<EntityType>>& theEntities
		);

		static Stl_Vector<Pnt2d> RetrieveGeometryFrom
		(
			const Stl_Vector<node_ptr>& nodes
		);

		static Stl_Vector<connectivity::triple> RetrieveGeometryFrom
		(
			const Stl_Vector<element_ptr>& elements,
			std::map<unsigned, unsigned>& theNodesIndices
		);
	};
}

#include <Mesh_PlaneI.hxx>

#endif // !_Mesh_Plane_Header

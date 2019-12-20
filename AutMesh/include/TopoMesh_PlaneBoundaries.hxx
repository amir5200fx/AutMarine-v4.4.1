#pragma once
#ifndef _TopoMesh_PlaneBoundaries_Header
#define _TopoMesh_PlaneBoundaries_Header

#include <Mesh_TypeTraits.hxx>
#include <Global_Done.hxx>
#include <Entity2d_Chain.hxx>

#include <memory>


#include "Mesh2d_gSurfPlane.hxx"
#include "Mesh2d_SizeMapAnIso.hxx"
#include "Aft2d_gSegmentEdge.hxx"
#include "Mesh2d_gPlnWire.hxx"

namespace AutLib
{

	// Forward Declarations
	class Mesh_CurveInfo;
	class TopoMesh_PlaneBoundariesInfo;

	template<class PlaneType, class SizeMap, class BndType>
	class TopoMesh_PlaneBoundariesBase
	{

		/*Private Data*/

		std::shared_ptr<SizeMap> theMap_;
		std::shared_ptr<PlaneType> thePlane_;

		std::vector<std::shared_ptr<BndType>> theBoundaries_;

	protected:

		TopoMesh_PlaneBoundariesBase()
		{}

		TopoMesh_PlaneBoundariesBase
		(
			const std::shared_ptr<SizeMap>& theSizeMap, 
			const std::shared_ptr<PlaneType>& thePlane
		)
			: theMap_(theSizeMap)
			, thePlane_(thePlane)
		{}

		std::vector<std::shared_ptr<BndType>>& ChangeBoundaries()
		{
			return theBoundaries_;
		}

	public:

		typedef BndType bndType;
		typedef PlaneType plnType;		

		const std::shared_ptr<SizeMap>& Map() const
		{
			return theMap_;
		}

		const std::shared_ptr<PlaneType>& Plane() const
		{
			return thePlane_;
		}

		const std::vector<std::shared_ptr<BndType>>& Boundaries() const
		{
			return theBoundaries_;
		}

		std::shared_ptr<Entity2d_Chain> StaticData() const;

		void LoadSizeMap(const std::shared_ptr<SizeMap>& theMap)
		{
			theMap_ = theMap;
		}

		void LoadPlane(const std::shared_ptr<PlaneType>& thePlane)
		{
			thePlane_ = thePlane;
		}
	};

	template
		<
		class PlaneType,
		class SizeMap, 
		class BndType, 
		bool WireChar = true, bool CheckDegen = false>
	class TopoMesh_PlaneBoundaries
		: public TopoMesh_PlaneBoundariesBase<PlaneType, SizeMap, BndType>
		, public Global_Done
	{

		template< bool cond, typename U >
		using resolvedType = typename std::enable_if< cond, U >::type;

		/*Private Data*/

		Standard_Boolean SimpleCheck_;
		Standard_Boolean InnerCheck_;
		Standard_Boolean OrientCheck_;
		Standard_Boolean NbPtsCheck_;


		void UpdateFront();

	public:

		typedef typename PlaneType::surfType surfType;
		typedef typename PlaneType::plnCurve curveType;

		typedef BndType bndType;

		typedef TopoMesh_PlaneBoundariesBase<PlaneType, SizeMap, BndType> base;

		TopoMesh_PlaneBoundaries()
			: InnerCheck_(Standard_False)
			, OrientCheck_(Standard_False)
			, NbPtsCheck_(Standard_False)
			, SimpleCheck_(Standard_False)
		{}

		TopoMesh_PlaneBoundaries
		(
			const std::shared_ptr<SizeMap>& theSizeMap,
			const std::shared_ptr<PlaneType>& thePlane
		)
			: base(theSizeMap, thePlane)
			, InnerCheck_(Standard_False)
			, OrientCheck_(Standard_False)
			, NbPtsCheck_(Standard_False)
			, SimpleCheck_(Standard_False)
		{}

		Standard_Boolean IsTopologyValid() const;

		Standard_Boolean SimpleCheck() const
		{
			return SimpleCheck_;
		}

		Standard_Boolean InnerCheck() const
		{
			return InnerCheck_;
		}

		Standard_Boolean OrientCheck() const
		{
			return OrientCheck_;
		}

		Standard_Boolean NbPtsCheck() const
		{
			return NbPtsCheck_;
		}

		void Perform(const std::shared_ptr<TopoMesh_PlaneBoundariesInfo>& theInfo);

		template<class U = void>
		resolvedType<is_false<CheckDegen>::value, U> RemoveDegeneracies() {}

		template<class U = void>
		resolvedType<is_true<CheckDegen>::value, U> RemoveDegeneracies()
		{
			auto& boundaries = base::ChangeBoundaries();
			std::vector<std::shared_ptr<BndType>> modified;
			modified.reserve(boundaries.size());

			Standard_Boolean contracted = Standard_False;
			for (const auto& x : boundaries)
			{
				Debug_Null_Pointer(x);
				if (NOT x->IsPoleSingular())
				{
					modified.push_back(x);
				}
				else
				{
					x->SingularityContraction(*base::Map());

					if (NOT contracted) contracted = Standard_True;
				}
			}

			if (NOT contracted) return;

			modified.shrink_to_fit();
			boundaries = modified;

			Standard_Integer Ke = 0;
			Standard_Integer Kn = 0;
			for (const auto& x : boundaries)
			{
				Debug_Null_Pointer(x);
				x->SetIndex(++Ke);
				x->Node0()->SetIndex(++Kn);
			}
		}


		//- Static functions and operators

		static Standard_Boolean
			CheckWireOrientation
			(
				const std::vector<std::shared_ptr<BndType>>& theEdges,
				const Standard_Boolean ccw
			);

		static Standard_Boolean
			CheckWireNbPts
			(
				const std::vector<std::shared_ptr<BndType>>& theEdges
			);

		static Standard_Boolean CheckSimplicity
		(
			const std::vector<std::shared_ptr<BndType>>& theEdges
		);
	};
}

#include <TopoMesh_PlaneBoundariesI.hxx>

#endif // !_TopoMesh_PlaneBoundaries_Header

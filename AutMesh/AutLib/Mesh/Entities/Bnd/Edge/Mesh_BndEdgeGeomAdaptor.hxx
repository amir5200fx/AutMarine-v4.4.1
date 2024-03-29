#pragma once
#ifndef _Mesh_BndEdgeGeomAdaptor_Header
#define _Mesh_BndEdgeGeomAdaptor_Header

#include <Mesh_EntityAdaptorM.hxx>
#include <Mesh_BndEdge_Position.hxx>
#include <Aft2d_EdgeSurfaceFwd.hxx>

namespace AutLib
{

	// Forward Declarations
	template<class FrontType>
	class Mesh_SizeMap;

	typedef Mesh_SizeMap<Aft2d_EdgeSurface>
		Mesh2d_SizeMapSurface;

	Mesh_EntityToEntityAdaptor(BndEdge, Surface, SurfType);

	template<class CurveType>
	class Mesh_BndEdgeGeomAdaptorBase
	{

		/*Private Data*/

		std::weak_ptr<CurveType> theCurve_;

	public:

		Mesh_BndEdgeGeomAdaptorBase()
		{}

		const std::weak_ptr<CurveType>& Curve() const
		{
			return theCurve_;
		}

		void SetCurve(const std::weak_ptr<CurveType>& theCurve)
		{
			theCurve_ = theCurve;
		}
	};

	template<class CurveType, class SurfType, Mesh_BndEdge_Position POS = Mesh_BndEdge_Position_Segment>
	class Mesh_BndEdgeGeomAdaptor
		: public Mesh_BndEdgeToSurfaceAdaptor<SurfType>
		, public Mesh_BndEdgeGeomAdaptorBase<CurveType>
	{

		/*Private Data*/

	public:

		Mesh_BndEdgeGeomAdaptor()
		{}
	};

	template<class CurveType>
	class Mesh_BndEdgeGeomAdaptor<CurveType, void, Mesh_BndEdge_Position_Segment>
		: public Mesh_BndEdgeGeomAdaptorBase<CurveType>
	{

		/*Private Data*/

	public:

		Mesh_BndEdgeGeomAdaptor()
		{}

		virtual void SingularityContraction(const Mesh2d_SizeMapSurface&);
	};

	template<class SurfType>
	class Mesh_BndEdgeGeomAdaptor<void, SurfType, Mesh_BndEdge_Position_Facet>
	{

		/*Private Data*/

		std::weak_ptr<SurfType> theSurface_;

	public:

		Mesh_BndEdgeGeomAdaptor()
		{}

		const std::weak_ptr<SurfType>& Surface() const
		{
			return theSurface_;
		}

		void SetSurface(const std::weak_ptr<SurfType>& theSurface)
		{
			theSurface_ = theSurface;
		}
	};
}

#include <Mesh_BndEdgeGeomAdaptorI.hxx>

#endif // !_Mesh_BndEdgeGeomAdaptor_Header

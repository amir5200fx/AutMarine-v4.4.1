#pragma once
#ifndef _GModel_Surface_Header
#define _GModel_Surface_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Entity2d_Box.hxx>

#include <memory>
#include <vector>

#include <Standard_Handle.hxx>
#include <TopoDS_Face.hxx>

class Geom_Surface;
class Poly_Triangulation;

namespace AutLib
{

	// Forward Declarations
	class GModel_Wire;
	class GModel_parCurve;
	class Cad3d_GModel;
	class Numeric_AdaptIntegrationInfo;
	class Entity2d_Metric1;

	class GModel_SurfaceInfo
	{

		friend class Cad3d_GModel;

		/*Private Data*/

		Handle(Poly_Triangulation) theTriangulation_;

	protected:

		GModel_SurfaceInfo()
		{}

	public:

		void SetTriangulation(const Handle(Poly_Triangulation)& theTriangulation)
		{
			theTriangulation_ = theTriangulation;
		}

		const Handle(Poly_Triangulation)& Triangulation() const
		{
			return theTriangulation_;
		}
	};

	class GModel_Surface
		: public Global_Indexed
		, public Global_Named
		, public GModel_SurfaceInfo
		, public std::enable_shared_from_this<GModel_Surface>
	{

		typedef std::shared_ptr<GModel_Wire> wire_ptr;
		typedef wire_ptr outer;

		typedef std::shared_ptr<std::vector<wire_ptr>> inner;

		/*Private Data*/

		Handle(Geom_Surface) theGeom_;

		outer theOuter_;
		inner theInner_;

		Entity2d_Box theBoundingBox_;

		Entity2d_Box CalcParametricBoundingBox() const;

		TopoDS_Face theFace_;

	public:

		typedef GModel_parCurve pCurveType;
		typedef GModel_Wire wireType;
		typedef Geom_Surface geomType;

		GModel_Surface
		(
			const Handle(Geom_Surface)& theGeom,
			const outer& theOuter,
			const inner& theInner
		)
			: theGeom_(theGeom)
			, theOuter_(theOuter)
			, theInner_(theInner)
		{
			theBoundingBox_ = CalcParametricBoundingBox();
		}

		GModel_Surface
		(
			const Standard_Integer theIndex,
			const Handle(Geom_Surface)& theGeom,
			const outer& theOuter,
			const inner& theInner
		)
			: theGeom_(theGeom)
			, theOuter_(theOuter)
			, theInner_(theInner)
			, Global_Indexed(theIndex)
		{
			theBoundingBox_ = CalcParametricBoundingBox();
		}

		GModel_Surface
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom_Surface)& theGeom,
			const outer& theOuter,
			const inner& theInner
		)
			: theGeom_(theGeom)
			, theOuter_(theOuter)
			, theInner_(theInner)
			, Global_Indexed(theIndex)
			, Global_Named(theName)
		{
			theBoundingBox_ = CalcParametricBoundingBox();
		}

		virtual ~GModel_Surface()
		{}

		Standard_Integer NbHoles() const
		{
			if (NOT theInner_) return 0;
			return (Standard_Integer)theInner_->size();
		}

		Standard_Boolean HasHole() const
		{
			return NbHoles();
		}

		Standard_Boolean IsBSpline() const;

		const outer& OuterWire() const
		{
			return theOuter_;
		}

		const inner& InnerWires() const
		{
			return theInner_;
		}

		const Handle(Geom_Surface)& Geometry() const
		{
			return theGeom_;
		}

		const Entity2d_Box& BoundingBox() const
		{
			return theBoundingBox_;
		}

		const TopoDS_Face& Face() const
		{
			return theFace_;
		}

		Entity2d_Metric1 MetricAt(const Pnt2d& theCoord) const;

		Pnt3d Value(const Pnt2d& theCoord) const;

		void GetParametricBouns
		(
			Standard_Real& theXmin,
			Standard_Real& theXmax,
			Standard_Real& theYmin,
			Standard_Real& theYmax
		) const;

		void SetFace(const TopoDS_Face& theFace)
		{
			theFace_ = theFace;
		}

		void ExportPlaneCurvesToPlt(OFstream& File) const;

		void ExportCurvesFromPlaneToPlt(OFstream& File) const;

		void ExportToPlt(OFstream& File) const;

		void ExportMetricDetToPlt(OFstream& File) const;


		
	};

	extern std::shared_ptr<Numeric_AdaptIntegrationInfo>
		gmodel_surface_reparameterization_integration_info;
}

#endif // !_GModel_Surface_Header

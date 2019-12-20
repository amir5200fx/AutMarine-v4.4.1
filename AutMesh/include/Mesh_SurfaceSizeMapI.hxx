#pragma once
namespace AutLib
{

	template<class SizeMap3D>
	const typename Mesh_SurfaceSizeMap<SizeMap3D>::box & 
		Mesh_SurfaceSizeMap<SizeMap3D>::BoundingBox() const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return theBoundingBox_;
	}

	template<class SizeMap3D>
	Standard_Real Mesh_SurfaceSizeMap<SizeMap3D>::DimSize() const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return 0;
	}

	template<class SizeMap3D>
	Standard_Real Mesh_SurfaceSizeMap<SizeMap3D>::Oriented(const Pnt2d &, const front &) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return 0;
	}

	template<class SizeMap3D>
	Standard_Real Mesh_SurfaceSizeMap<SizeMap3D>::CalcDistance(const Pnt2d &, const Pnt2d &) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return 0;
	}

	template<class SizeMap3D>
	Standard_Real Mesh_SurfaceSizeMap<SizeMap3D>::CalcSquareDistance(const Pnt2d &, const Pnt2d &) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return 0;
	}

	template<class SizeMap3D>
	Standard_Real Mesh_SurfaceSizeMap<SizeMap3D>::CalcDistance(const Pnt2d &, const front &) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return 0;
	}

	template<class SizeMap3D>
	Standard_Real Mesh_SurfaceSizeMap<SizeMap3D>::CalcSquareDistance(const Pnt2d &, const front &) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return 0;
	}

	template<class SizeMap3D>
	Standard_Real Mesh_SurfaceSizeMap<SizeMap3D>::CalcUnitDistance(const Pnt2d &, const Pnt2d &) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return 0;
	}

	template<class SizeMap3D>
	Pnt2d Mesh_SurfaceSizeMap<SizeMap3D>::CalcOptimumCoord(const Standard_Real theSize, const front &) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return Pnt2d::null;
	}

	template<class SizeMap3D>
	Pnt2d Mesh_SurfaceSizeMap<SizeMap3D>::CalcCentreOf(const Pnt2d &, const Pnt2d &) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return Pnt2d::null;
	}

	template<class SizeMap3D>
	Pnt2d Mesh_SurfaceSizeMap<SizeMap3D>::CalcCentreOf(const front &) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return Pnt2d::null;
	}

	template<class SizeMap3D>
	typename Mesh_SurfaceSizeMap<SizeMap3D>::box 
		Mesh_SurfaceSizeMap<SizeMap3D>::CalcSearchRegion(const Standard_Real theRadius, const metric & theMetric, const Pnt2d & theCentre) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return box();
	}

	template<class SizeMap3D>
	typename Mesh_SurfaceSizeMap<SizeMap3D>::box
		Mesh_SurfaceSizeMap<SizeMap3D>::CalcSearchRegion(const Standard_Real theRadius, const Pnt2d & theCentre, const front &) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return box();
	}

	template<class SizeMap3D>
	typename Mesh_SurfaceSizeMap<SizeMap3D>::box
		AutLib::Mesh_SurfaceSizeMap<SizeMap3D>::CalcSearchRegion(const Standard_Real theRadius, const front &) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return box();
	}

	template<class SizeMap3D>
	typename Mesh_SurfaceSizeMap<SizeMap3D>::box 
		Mesh_SurfaceSizeMap<SizeMap3D>::CalcEffectiveRegion(const Standard_Real theRadius, const Point & theCentre, const frontType &) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return box();
	}

	template<class SizeMap3D>
	typename Mesh_SurfaceSizeMap<SizeMap3D>::metric
		Mesh_SurfaceSizeMap<SizeMap3D>::CalcEffectiveMetric(const Pnt2d & theP0, const Pnt2d & theP1) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return metric();
	}

	template<class SizeMap3D>
	Pnt3d Mesh_SurfaceSizeMap<SizeMap3D>::CalcCoord3D(const Pnt2d & theCoord) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return Pnt3d();
	}

	template<class SizeMap3D>
	Standard_Real Mesh_SurfaceSizeMap<SizeMap3D>::CalcLength3D
	(
		const Pnt2d & P0,
		const Pnt2d & P1
	) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return 0;
	}

	template<class SizeMap3D>
	Standard_Real Mesh_SurfaceSizeMap<SizeMap3D>::CalcLength3D
	(
		const Pnt3d & P0, 
		const Pnt3d & P1
	) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return 0;
	}

	template<class SizeMap3D>
	Standard_Real Mesh_SurfaceSizeMap<SizeMap3D>::CalcLength3D
	(
		const frontType & theEdge
	) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return 0;
	}

	template<class SizeMap3D>
	Standard_Real Mesh_SurfaceSizeMap<SizeMap3D>::Integrand(const Pnt2d & thePoint, const Pnt2d & theVector) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return 0;
	}

	template<class SizeMap3D>
	Standard_Real Mesh_SurfaceSizeMap<SizeMap3D>::Integrand(const Pnt2d & thePoint, const gp_Vec2d & theVector) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return 0;
	}

	template<class SizeMap3D>
	Standard_Real Mesh_SurfaceSizeMap<SizeMap3D>::IntegrandPerSize(const Pnt2d & thePoint, const Pnt2d & theVector) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return 0;
	}

	template<class SizeMap3D>
	Standard_Real Mesh_SurfaceSizeMap<SizeMap3D>::IntegrandPerSize(const Pnt2d & thePoint, const gp_Vec2d & theVector) const
	{
		FatalErrorIn(FunctionSIG)
			<< "This not supposed to be called" << endl
			<< abort(FatalError);
		return 0;
	}
}
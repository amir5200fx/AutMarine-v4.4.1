#pragma once
#include <Pnt2d.hxx>
#include <error.hxx>
#include <OSstream.hxx>
#include <vector>

namespace AutLib
{

	template<class SurfType>
	Standard_Real Mesh_CadTools::uCharLength
	(
		const SurfType & theSurface,
		const Standard_Real u,
		intgInfo& theInfo
	)
	{
		Standard_Real umin, umax, vmin, vmax;
		theSurface.GetParametricBouns(umin, umax, vmin, vmax);

		if (u < umin AND u > umax)
		{
			FatalErrorIn("Standard_Real uCharLength(const SurfType& theSurface, const Standard_Real u)")
				<< "Invalid u-parameter:" << endl
				<< " - v= " << u << endl
				<< " - umin= " << umin << ", umax= " << umax << endl
				<< abort(FatalError);
		}

		auto box = theSurface.BoundingBox();
		auto geom = theSurface.Geometry();

		auto P0 = Pnt2d(u, vmin);
		auto P1 = Pnt2d(u, vmax);

		return CalcLength(P0, P1, box, geom, theInfo);
	}

	template<class SurfType>
	Standard_Real Mesh_CadTools::vCharLength
	(
		const SurfType & theSurface,
		const Standard_Real v,
		intgInfo & theInfo
	)
	{
		Standard_Real umin, umax, vmin, vmax;
		theSurface.GetParametricBouns(umin, umax, vmin, vmax);

		if (v < vmin AND v > vmax)
		{
			FatalErrorIn("Standard_Real vCharLength(const SurfType& theSurface, const Standard_Real v, intgInfo& theInfo)")
				<< "Invalid v-parameter:" << endl
				<< " - v= " << v << endl
				<< " - vmin= " << vmin << ", vmax= " << vmax << endl
				<< abort(FatalError);
		}

		auto box = theSurface.BoundingBox();
		auto geom = theSurface.Geometry();

		auto P0 = Pnt2d(umin, v);
		auto P1 = Pnt2d(umax, v);

		return CalcLength(P0, P1, box, geom, theInfo);
	}

	template<class SurfType>
	std::shared_ptr<SurfType> Mesh_CadTools::ConvertToBSpline
	(
		const SurfType & theSurface
	)
	{
		auto oldGeom = theSurface.Geometry();
		auto geom = Mesh_CadTools::ConvertToBSpline(oldGeom, theSurface.BoundingBox());

		auto surf = std::make_shared<SurfType>(geom, theSurface.OuterWire(), theSurface.InnerWires());
		surf->SetIndex(theSurface.Index());
		surf->SetName(theSurface.Name());

		return std::move(surf);
	}

	template<class SurfType>
	std::shared_ptr<SurfType> Mesh_CadTools::ReParameterization
	(
		const SurfType & theSurface, 
		const Standard_Real theScale
	)
	{
		typedef typename SurfType::wireType wireType;

		Standard_Real umin, umax, vmin, vmax;
		theSurface.GetParametricBouns(umin, umax, vmin, vmax);

		auto P0 = Pnt2d(umin, vmin);

		gp_Trsf2d transf;
		transf.SetScale(P0, theScale);

		auto oldGeom = theSurface.Geometry();
		auto geom = Mesh_CadTools::GeomReParameterization(oldGeom, transf);

		const auto& oldOuter = theSurface.OuterWire();

		auto newOuter = wireType::ReParameterization(*oldOuter, transf);
		newOuter->SetIndex(oldOuter->Index());
		newOuter->SetName(oldOuter->Name());

		if (theSurface.HasHole())
		{
			const auto& oldInner = theSurface.InnerWires();
			auto newInners = std::make_shared<std::vector<std::shared_ptr<wireType>>>();
			newInners->reserve(oldInner->size());

			for (const auto& x : *oldInner)
			{
				Debug_Null_Pointer(x);
				auto c = wireType::ReParameterization(*x, transf);
				c->SetIndex(x->Index());
				c->SetName(x->Name());

				newInners->push_back(c);
			}

			auto surf = std::make_shared<SurfType>(geom, newOuter, newInners);
			surf->SetIndex(theSurface.Index());
			surf->SetName(theSurface.Name());

			if (theSurface.Triangulation()) surf->SetTriangulation(theSurface.Triangulation());

			return std::move(surf);
		}
		else
		{
			auto surf = std::make_shared<SurfType>(geom, newOuter, nullptr);
			surf->SetIndex(theSurface.Index());
			surf->SetName(theSurface.Name());

			if (theSurface.Triangulation()) surf->SetTriangulation(theSurface.Triangulation());

			return std::move(surf);
		}
	}

	template<class SurfType>
	std::shared_ptr<SurfType> Mesh_CadTools::ReParameterization_uExpand
	(
		const SurfType & theSurface, 
		const Standard_Real theMult
	)
	{
		typedef typename SurfType::wireType wireType;

		auto oldGeom = theSurface.Geometry();
		auto geom = Mesh_CadTools::GeomReParameterization_uExpand(oldGeom, theMult);

		const auto& oldOuter = theSurface.OuterWire();

		auto newOuter = wireType::uPlaneExpand(*oldOuter, theMult);
		newOuter->SetIndex(oldOuter->Index());
		newOuter->SetName(oldOuter->Name());

		if (theSurface.HasHole())
		{
			const auto& oldInner = theSurface.InnerWires();
			auto newInners = std::make_shared<std::vector<std::shared_ptr<wireType>>>();
			newInners->reserve(oldInner->size());

			for (const auto& x : *oldInner)
			{
				Debug_Null_Pointer(x);
				auto c = wireType::uPlaneExpand(*x, theMult);
				c->SetIndex(x->Index());
				c->SetName(x->Name());

				newInners->push_back(c);
			}

			auto surf = std::make_shared<SurfType>(geom, newOuter, newInners);
			surf->SetIndex(theSurface.Index());
			surf->SetName(theSurface.Name());

			if (theSurface.Triangulation()) surf->SetTriangulation(theSurface.Triangulation());

			return std::move(surf);
		}
		else
		{
			auto surf = std::make_shared<SurfType>(geom, newOuter, nullptr);
			surf->SetIndex(theSurface.Index());
			surf->SetName(theSurface.Name());

			if (theSurface.Triangulation()) surf->SetTriangulation(theSurface.Triangulation());

			return std::move(surf);
		}
	}

	template<class SurfType>
	std::shared_ptr<SurfType> Mesh_CadTools::ReParameterization_vExpand
	(
		const SurfType & theSurface,
		const Standard_Real theMult
	)
	{
		typedef typename SurfType::wireType wireType;

		auto oldGeom = theSurface.Geometry();
		auto geom = Mesh_CadTools::GeomReParameterization_vExpand(oldGeom, theMult);

		const auto& oldOuter = theSurface.OuterWire();

		auto newOuter = wireType::vPlaneExpand(*oldOuter, theMult);
		newOuter->SetIndex(oldOuter->Index());
		newOuter->SetName(oldOuter->Name());

		if (theSurface.HasHole())
		{
			const auto& oldInner = theSurface.InnerWires();
			auto newInners = std::make_shared<std::vector<std::shared_ptr<wireType>>>();
			newInners->reserve(oldInner->size());

			for (const auto& x : *oldInner)
			{
				Debug_Null_Pointer(x);
				auto c = wireType::vPlaneExpand(*x, theMult);
				c->SetIndex(x->Index());
				c->SetName(x->Name());

				newInners->push_back(c);
			}

			auto surf = std::make_shared<SurfType>(geom, newOuter, newInners);
			surf->SetIndex(theSurface.Index());
			surf->SetName(theSurface.Name());

			if (theSurface.Triangulation()) surf->SetTriangulation(theSurface.Triangulation());

			return std::move(surf);
		}
		else
		{
			auto surf = std::make_shared<SurfType>(geom, newOuter, nullptr);
			surf->SetIndex(theSurface.Index());
			surf->SetName(theSurface.Name());

			if (theSurface.Triangulation()) surf->SetTriangulation(theSurface.Triangulation());

			return std::move(surf);
		}
	}

	template<class SurfType>
	std::shared_ptr<SurfType> Mesh_CadTools::ReParameterization
	(
		const SurfType & theSurface,
		intgInfo & theInfo
	)
	{
		Standard_Real umin, umax, vmin, vmax;
		theSurface.GetParametricBouns(umin, umax, vmin, vmax);

		auto lu0 = uCharLength(theSurface, umin, theInfo);
		auto lu1 = uCharLength(theSurface, umax, theInfo);
		auto lu = MAX(lu0, lu1);

		auto lv0 = vCharLength(theSurface, vmin, theInfo);
		auto lv1 = vCharLength(theSurface, vmax, theInfo);
		auto lv = MAX(lv0, lv1);

		auto du = umax - umin;
		auto dv = vmax - vmin;

		auto scale = MAX(lu, lv) / MAX(du, dv);
		auto surface = ReParameterization(theSurface, scale);

		return std::move(surface);
	}
}
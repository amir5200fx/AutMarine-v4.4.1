#pragma once
#include <Cad_Tools.hxx>
#include <error.hxx>
#include <OSstream.hxx>
namespace AutLib
{

	template<class SurfType>
	void Geo_PlaneNurbs<SurfType>::Perform()
	{
		if (NOT Surface())
		{
			FatalErrorIn("void Perform()")
				<< "No surface has been loaded!" << endl
				<< abort(FatalError);
		}

		auto bspline = Surface();
		if (NOT bspline->IsBSpline())
		{
			bspline = Mesh_CadTools::ConvertToBSpline(*Surface());
		}

		const auto& surface = *bspline;

		const auto& oldOuter = surface.OuterWire();

		auto newOuter = wireType::BSplinePlaneEdges(*oldOuter);
		newOuter->SetIndex(oldOuter->Index());
		newOuter->SetName(oldOuter->Name());
		
		if (surface.HasHole())
		{
			const auto& oldInner = surface.InnerWires();
			auto newInners = std::make_shared<std::vector<std::shared_ptr<wireType>>>();
			newInners->reserve(oldInner->size());

			for (const auto& x : *oldInner)
			{
				Debug_Null_Pointer(x);
				auto c = wireType::BSplinePlaneEdges(*x);
				c->SetIndex(x->Index());
				c->SetName(x->Name());

				newInners->push_back(c);
			}

			auto surf = std::make_shared<SurfType>(surface.Geometry(), newOuter, newInners);
			surf->SetIndex(surface.Index());
			surf->SetName(surface.Name());

			if (surface.Triangulation()) surf->SetTriangulation(surface.Triangulation());

			ChangeModified() = std::move(surf);
		}
		else
		{
			auto surf = std::make_shared<SurfType>(surface.Geometry(), newOuter, nullptr);
			surf->SetIndex(surface.Index());
			surf->SetName(surface.Name());

			if (surface.Triangulation()) surf->SetTriangulation(surface.Triangulation());

			ChangeModified() = std::move(surf);
		}

		Change_IsDone() = Standard_True;
	}
}
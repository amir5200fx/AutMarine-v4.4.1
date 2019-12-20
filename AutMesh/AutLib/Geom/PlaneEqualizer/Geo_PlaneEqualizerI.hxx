#pragma once
#include <Mesh_CadTools.hxx>
#include <error.hxx>
#include <OSstream.hxx>
namespace AutLib
{

	template<class SurfType>
	std::pair<Standard_Real, Standard_Integer>
		Geo_PlaneEqualizer<SurfType>::CalcMaxAR
	(
		const SurfType & theSurface
	)
	{
		const auto& box = theSurface.BoundingBox();

		const auto& P0 = box.P0();
		const auto& P1 = box.P1();

		auto dx = P1.X() - P0.X();
		auto dy = P1.Y() - P0.Y();

		if (dy > dx)
		{
			auto p = std::make_pair(dy / dx, 0);
			return std::move(p);
		}
		else
		{
			auto p = std::make_pair(dx / dy, 1);
			return std::move(p);
		}
	}

	template<class SurfType>
	void Geo_PlaneEqualizer<SurfType>::Perform(std::ostream & os)
	{
		if (NOT Surface())
		{
			FatalErrorIn("void Perform(std::ostream& os)")
				<< "No surface has been loaded!" << endl
				<< abort(FatalError);
		}

		const auto ar = CalcMaxAR(*Surface());
		if (ar.first <= Info()->AR())
		{
			ChangeModified() = Surface();
			Change_IsDone() = Standard_True;

			return;
		}

		Applied_ = Standard_True;

		if (ar.second IS_EQUAL 0)
		{
			ChangeModified() = Mesh_CadTools::template ReParameterization_uExpand(*Surface(), ar.first / Info()->AR());
		}
		else
		{
			ChangeModified() = Mesh_CadTools::template ReParameterization_vExpand(*Surface(), ar.first / Info()->AR());
		}

		Change_IsDone() = Standard_True;
	}
}
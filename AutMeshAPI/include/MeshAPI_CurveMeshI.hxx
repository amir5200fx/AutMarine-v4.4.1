#pragma once
#include <error.hxx>
#include <OSstream.hxx>
namespace AutLib
{

	template<class ModelAnal>
	void MeshAPI_CurveMesh<ModelAnal>::Perform(std::ostream & out)
	{
		if (NOT Analysis())
		{
			FatalErrorIn("void AutLib::GModel_BoundaryMesh::Perform(std::ostream & out)")
				<< "no model analysis has been loaded" << endl
				<< abort(FatalError);
		}

		const auto& analysis = *Analysis();
		const auto& surfaces = analysis.Regulars();

		if (Verbose())
		{
			out << " @ MeshAPI_CurveMesh<ModelAnal>::Perform(std::ostream & out):" << std::endl;
			out << "    - going to meshing the curves of the surfaces." << std::endl;
		}

		Debug_Null_Pointer(Info());

		for (const auto& x : surfaces)
		{
			Debug_Null_Pointer(x.second);
			const auto& surface = *x.second;

			if (Verbose())
			{
				out << "   - surface nb. " << x.first << std::endl;
			}

			auto banalysis = std::make_shared<typename ModelAnal::curveAnal>(Info());
			Debug_Null_Pointer(banalysis);

			banalysis->LoadSurface(x.second);
			banalysis->LoadSizeMap(analysis.SizeMap());
			
			banalysis->Perform();
			Debug_If_Condition_Message(NOT banalysis->IsDone(), "the boundary mesh analysis has not been performed");

			//- check if there is any intersection between inners and outer wires
			if (banalysis->Check())
			{
				ChangeInvalids().insert(std::make_pair(x.first, banalysis));
				continue;
			}

			if (ModelAnal::curveAnal::CheckIntersection(banalysis->Mesh()->Boundaries()))
			{
				ChangeInvalids().insert(std::make_pair(x.first, banalysis));
				continue;
			}

			ChangeMesh().insert(std::make_pair(x.first, banalysis));
		}

		const auto& commons = analysis.CommonSingularities();
		for (const auto& x : commons)
		{
			Debug_Null_Pointer(x.second);
			const auto& surface = *x.second;

			if (Verbose())
			{
				out << "   - surface (common singular) nb. " << x.first << std::endl;
			}

			auto banalysis = std::make_shared<typename ModelAnal::curveAnal>(Info());
			Debug_Null_Pointer(banalysis);

			banalysis->LoadSurface(x.second);
			banalysis->LoadSizeMap(analysis.SizeMap());

			banalysis->Perform();
			Debug_If_Condition_Message(NOT banalysis->IsDone(), "the boundary mesh analysis has not been performed");

			//- check if there is any intersection between inners and outer wires
			if (banalysis->Check())
			{
				ChangeInvalids().insert(std::make_pair(x.first, banalysis));
				continue;
			}

			if (ModelAnal::curveAnal::CheckIntersection(banalysis->Mesh()->Boundaries()))
			{
				ChangeInvalids().insert(std::make_pair(x.first, banalysis));
				continue;
			}

			ChangeMesh().insert(std::make_pair(x.first, banalysis));
		}

		Change_IsDone() = Standard_True;
	}
}
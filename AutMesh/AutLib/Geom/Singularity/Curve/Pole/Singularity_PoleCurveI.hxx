#pragma once
namespace AutLib
{

	template<class PlnCurve>
	std::shared_ptr<Entity2d_Chain>
		Singularity_PoleCurve<PlnCurve>::Mesh
		(
			const std::shared_ptr<Mesh2d_SizeMapSurface>& theSizeMap,
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		) const
	{
		auto chain = std::make_shared<Entity2d_Chain>();
		Debug_Null_Pointer(chain);

		auto& pts = chain->Points();
		pts.reserve(3);

		pts.push_back(this->Value(this->FirstParam()));
		pts.push_back(this->NormalizedParameterValue(0.5));
		pts.push_back(this->Value(this->LastParam()));

		auto& indices = chain->Connectivity();
		indices.reserve(2);

		connectivity::dual I0;
		I0.Value(0) = 1;
		I0.Value(1) = 2;
		indices.push_back(I0);

		connectivity::dual I1;
		I1.Value(0) = 2;
		I1.Value(1) = 3;
		indices.push_back(I1);

		return std::move(chain);
	}

	template<class PlnCurve>
	std::shared_ptr<Entity2d_Chain> 
		Singularity_PoleCurve<PlnCurve>::Mesh
		(
			const std::shared_ptr<Mesh2d_SizeMapAnIso>& theSizeMap,
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		) const
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid operation: this function not supposed to be called!" << endl
			<< abort(FatalError);
		return nullptr;
	}

	template<class PlnCurve>
	std::shared_ptr<Entity2d_Chain> 
		Singularity_PoleCurve<PlnCurve>::Mesh
		(
			const std::shared_ptr<Mesh2d_SizeMap>& theSizeMap,
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
		) const
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid operation: this function not supposed to be called!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}
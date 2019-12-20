#pragma once
namespace AutLib
{

	inline Standard_Real 
		SizeMap2d_FullIntAnIso_NelderMeadObject::EstimateError
		(
			const Standard_Real d0,
			const Standard_Real d1
		)
	{
		auto e0 = ABS(1.0 - d0);
		auto e1 = ABS(1.0 - d1);

		return MEAN(e0, e1);
	}
}
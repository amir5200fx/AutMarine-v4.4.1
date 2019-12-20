#pragma once
namespace AutLib
{

	template<class SurfType>
	const word ImpSurf_defWire_Intersect<SurfType>::typeName("wire_intersect");

	template<class SurfType>
	Standard_Boolean ImpSurf_defWire_Intersect<SurfType>::Check
	(
		const SurfType & theSurface, 
		const Standard_Real theTol
	)
	{
		if (NOT theSurface.HasHole())
		{
			return Standard_False;
		}

		const auto& outer = theSurface.OuterWire();
		const auto& inners = *theSurface.InnerWires();

		auto oBox = outer->CalcParametricBoundingBox();

		auto iter = inners.begin();
		auto iBox = (*iter)->CalcParametricBoundingBox();

		iter++;

		while (iter NOT_EQUAL inners.end())
		{
			iBox = Entity2d_Box::Union(iBox, (*iter)->CalcParametricBoundingBox());
			iter++;
		}

		auto offset = iBox.OffSet(theTol);

		if (NOT Entity2d_Box::IsInside(offset, oBox))
		{
			return Standard_True;
		}
		return Standard_False;
	}
}
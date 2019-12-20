#include <SizeMap2d_FullIntAnIso_NelderMeadObject.hxx>

#include <SizeMap2d_FullIntAnIso.hxx>

#include <error.hxx>
#include <OSstream.hxx>

const Standard_Real AutLib::SizeMap2d_FullIntAnIso_NelderMeadObjectInfo::DEFAULT_TOLERANCE(1.0E-3);

Standard_Real 
AutLib::SizeMap2d_FullIntAnIso_NelderMeadObject::Value
(
	const Pnt2d & theCoord
) const
{
	Debug_Null_Pointer(SizeMap());
	const auto& map = *SizeMap();

	d0 = map.CalcDistance(theCoord, P0());
	d1 = map.CalcDistance(theCoord, P1());

	return EstimateError(d0, d1);
}
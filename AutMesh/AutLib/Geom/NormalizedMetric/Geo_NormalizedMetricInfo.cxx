#include <Geo_NormalizedMetricInfo.hxx>

const Standard_Real AutLib::Geo_NormalizedMetricInfo::DEFAULT_MAX_DETERMINANT(1000.0);

const Standard_Integer AutLib::Geo_NormalizedMetricInfo::DEFAULT_NB_SEGMENTS_U(2);
const Standard_Integer AutLib::Geo_NormalizedMetricInfo::DEFAULT_NB_SEGMENTS_V(2);

AutLib::Geo_NormalizedMetricInfo::Geo_NormalizedMetricInfo()
	: theMaxDet_(DEFAULT_MAX_DETERMINANT)
	, theNbSegmentsU_(DEFAULT_NB_SEGMENTS_U)
	, theNbSegmentsV_(DEFAULT_NB_SEGMENTS_V)
{}
#include <Mesh_CurveLength.hxx>

#include <Numeric_AdaptIntegration.hxx>

std::shared_ptr<AutLib::Numeric_AdaptIntegrationInfo> 
AutLib::mesh_curve_length_info = std::make_shared<AutLib::Numeric_AdaptIntegrationInfo>();
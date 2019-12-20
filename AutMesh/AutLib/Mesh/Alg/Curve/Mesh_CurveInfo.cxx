#include <Mesh_CurveInfo.hxx>

#include <Numeric_AdaptIntegration.hxx>
#include <Numeric_NewtonSolver.hxx>

const Standard_Integer AutLib::Mesh_CurveInfo::DEFAULT_MAX_LEVEL_LENGTH_CALC(10);
const Standard_Real AutLib::Mesh_CurveInfo::DEFAULT_UNDER_RELAXATION(0.9);

std::shared_ptr<AutLib::Numeric_AdaptIntegrationInfo> 
AutLib::mesh_curve_overall_length_integration_info = std::make_shared<AutLib::Numeric_AdaptIntegrationInfo>();

std::shared_ptr<AutLib::Numeric_AdaptIntegrationInfo>
AutLib::mesh_curve_newton_integration_info = std::make_shared<AutLib::Numeric_AdaptIntegrationInfo>();

std::shared_ptr<AutLib::Mesh_CurveInfo>
AutLib::mesh_curve_info = std::make_shared<AutLib::Mesh_CurveInfo>();
#include <Mesh_CurveOptmPoint_Newton.hxx>

#include <Mesh_CurveInfo.hxx>

std::shared_ptr<AutLib::Numeric_NewtonSolverInfo> 
AutLib::mesh_curve_newton_iter_info = std::make_shared<AutLib::Numeric_NewtonSolverInfo>();
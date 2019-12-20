#include <Mesh_CurveOptmPoint_CorrectionInfo.hxx>

const Standard_Real AutLib::Mesh_CurveOptmPoint_CorrectionInfo::DEFAULT_TOLERANCE(1.0E-3);
const Standard_Real AutLib::Mesh_CurveOptmPoint_CorrectionInfo::DEFAULT_UNDER_RELAXATION(0.9);

const Standard_Integer AutLib::Mesh_CurveOptmPoint_CorrectionInfo::DEFAULT_MAX_LEVEL(20);

#include <Mesh_CurveInfo.hxx>

std::shared_ptr<AutLib::Mesh_CurveOptmPoint_CorrectionInfo>
AutLib::mesh_curve_point_corr_info = std::make_shared<AutLib::Mesh_CurveOptmPoint_CorrectionInfo>();
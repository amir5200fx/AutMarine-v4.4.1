#pragma once
#ifndef _MeshAPI_gModelAnalysis_Header
#define _MeshAPI_gModelAnalysis_Header

#include <MeshAPI_ModelAnalysis.hxx>
#include <MeshAPI_gBndCurvesAnalysis.hxx>
#include <Cad3d_GModel.hxx>

namespace AutLib
{

	typedef MeshAPI_ModelAnalysis<MeshAPI_gBndCurvesAnalysis>
		MeshAPI_gModelAnalysis;

	template<>
	void MeshAPI_gModelAnalysis::Perform(std::ostream& os /* = std::cout */);
}

#endif // !_MeshAPI_gModelAnalysis_Header

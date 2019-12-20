#pragma once
namespace AutLib
{

	template<class BndCrvAnal>
	void MeshAPI_ModelAnalysis<BndCrvAnal>::Report(std::ostream & os) const
	{
		os << " total nb. of surfaces = " << Model()->NbSurfaces() << std::endl;
		os << std::endl;

		os << "  - nb. of regular surfaces = " << NbRegulars() << std::endl;
		os << "  - nb. of singularities = " << NbSingularities() << std::endl;
		os << "  - nb. of common singularities = " << NbCommonSingularities() << std::endl;
		os << "  - nb. of defect surfaces = " << NbDefects() << std::endl;
	}
}
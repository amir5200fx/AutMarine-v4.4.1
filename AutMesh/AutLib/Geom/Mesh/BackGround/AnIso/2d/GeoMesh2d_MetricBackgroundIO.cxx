#include <GeoMesh2d_MetricBackground.hxx>
#include <GeoMesh2d_Background.hxx>

namespace AutLib
{

	template<>
	void GeoMesh2d_MetricBackground::ExportToPlt
	(
		OFstream& File
	) const
	{
		if (NOT theSources_)
		{
			FatalErrorIn("void GeoMesh2d_MetricBackground::ExportMetricDeterminantToPlt()")
				<< "Found no metric sources" << endl
				<< abort(FatalError);
		}
		const auto& sources = *theSources_;

		auto Det_ptr = std::make_shared<std::vector<Standard_Real>>(sources.size());
		Debug_Null_Pointer(Det_ptr);

		auto& Det = *Det_ptr;
		auto maxDet = (Standard_Real)0;
		forThose(Index, 0, sources.size() - 1)
		{
			Det[Index] = sources[Index].Determinant();
			if (Det[Index] > maxDet) maxDet = Det[Index];
		}

		forThose(Index, 0, sources.size() - 1)
		{
			//Det[Index] /= maxDet;
		}

		auto bmesh = this->Mesh();
		GeoMesh2d_Background mesh(bmesh, Det_ptr);
		mesh.ExportToPlt(File);
	}
}
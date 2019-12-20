#pragma once
#include <Mesh_CadTools.hxx>
#include <Geo_NormalizedMetricInfo.hxx>
#include <Geo_ApprxSurfMetricInfo.hxx>
#include <Geo_ApprxSurfMetric.hxx>
#include <error.hxx>
#include <OSstream.hxx>
namespace AutLib
{

	template<class SurfType>
	Standard_Real Geo_NormalizedMetric<SurfType>::CalcMaxCharLengthU
	(
		intgInfo& theInfo
	) const
	{
		Debug_Null_Pointer(Surface());

		Standard_Real umin, umax, vmin, vmax;
		Surface()->GetParametricBouns(umin, umax, vmin, vmax);

		auto maxLen = (Standard_Real)0;
		auto du = (umax - umin) / (Standard_Real)Info()->NbSegmentsU();
		forThose(Index, 0, Info()->NbSegmentsU())
		{
			auto x = umin + Index * du;
			auto len = Mesh_CadTools::uCharLength(*Surface(), x, theInfo);

			if (len > maxLen) maxLen = len;
		}
		return maxLen;
	}

	template<class SurfType>
	Standard_Real Geo_NormalizedMetric<SurfType>::CalcMaxCharLengthV
	(
		intgInfo & theInfo
	) const
	{
		Debug_Null_Pointer(Surface());

		Standard_Real umin, umax, vmin, vmax;
		Surface()->GetParametricBouns(umin, umax, vmin, vmax);

		auto maxLen = (Standard_Real)0;
		auto dv = (vmax - vmin) / (Standard_Real)Info()->NbSegmentsV();
		forThose(Index, 0, Info()->NbSegmentsV())
		{
			auto x = vmin + Index * dv;
			auto len = Mesh_CadTools::vCharLength(*Surface(), x, theInfo);

			if (len > maxLen) maxLen = len;
		}
		return maxLen;
	}

	template<class SurfType>
	void Geo_NormalizedMetric<SurfType>::Perform(std::ostream & os)
	{
		if (Verbose())
		{
			os << " @ void Geo_NormalizedMetric<SurfType>::Perform(std::ostream & os)" << std::endl;
		}

		if (NOT Surface())
		{
			FatalErrorIn("void Geo_NormalizedMetric<SurfType>::Perform(std::ostream & os)") << endl
				<< "No surface has been loaded" << endl
				<< abort(FatalError);
		}

		if (NOT Approx())
		{
			FatalErrorIn("void Geo_NormalizedMetric<SurfType>::Perform(std::ostream & os)") << endl
				<< "No approximation of surface metric has been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT Approx()->TrackMaxDeterminant())
		{
			FatalErrorIn("void Geo_NormalizedMetric<SurfType>::Perform(std::ostream & os)") << endl
				<< "maximum determinant has not been tracked!" << endl
				<< abort(FatalError);
		}

		if (NOT Info())
		{
			FatalErrorIn("void Geo_NormalizedMetric<SurfType>::Perform(std::ostream & os)") << endl
				<< "Info has not been loaded!" << endl
				<< abort(FatalError);
		}

		if (Verbose())
		{
			os << "  - the normalizing metric algorithm is applied if the maximum determinant " << std::endl;
			os << "    of the metric surface be bigger than the criterion" << std::endl;
			os << "    criterion: " << Info()->MaxDeterminant() << std::endl;
			os << "    max. of the determinant: " << Approx()->Info()->MaxDeterminant() << std::endl;
		}

		if (Approx()->Info()->MaxDeterminant() <= Info()->MaxDeterminant())
		{

			if (Verbose())
			{
				os << "  *****the surface needs no metric normalization****" << std::endl;
				os << "  continue..." << std::endl;
			}
			theNormalized_ = theSurface_;
		}
		else
		{

			if (Verbose())
			{
				os << "  - going to normalize the surface metric..." << std::endl;
			}

			Debug_Null_Pointer(Info()->IntegrationInfo());
			auto maxLu = CalcMaxCharLengthU(*Info()->IntegrationInfo());
			auto maxLv = CalcMaxCharLengthV(*Info()->IntegrationInfo());

			Standard_Real umin, umax, vmin, vmax;
			Surface()->GetParametricBouns(umin, umax, vmin, vmax);

			auto du = umax - umin;
			auto dv = vmax - vmin;

			auto scale = MAX(maxLu, maxLv) / MAX(du, dv);

			if (Verbose())
			{
				os << "   scale: " << scale << std::endl;
			}

			theNormalized_ = Mesh_CadTools::template ReParameterization<SurfType>(*Surface(), scale);

			Applied_ = Standard_True;

			if (Verbose())
			{
				os << "  *****the normalization is done successfully!*****" << scale << std::endl;
				os << "  continue..." << std::endl;
			}
		}

		Change_IsDone() = Standard_True;
	}
}
#pragma once
#include <MeshAPI_ModelInfo.hxx>
#include <MetricMap2d_Surface.hxx>
namespace AutLib
{

	template<class CrvMesh>
	void MeshAPI_Model<CrvMesh>::Perform(std::ostream & out)
	{

		if (NOT CurveMesh())
		{
			FatalErrorIn("void Perform(std::ostream& out = std::cout)")
				<< "no curve mesh has been loaded!" << endl
				<< abort(FatalError);
		}

		const auto& boundaries = CurveMesh()->Mesh();
		if (boundaries.empty())
		{
			Change_IsDone() = Standard_True;
			return;
		}

		const auto verbose = Info()->Verbose();

		for (const auto& x : boundaries)
		{
			Debug_Null_Pointer(x.second);

			if (verbose)
			{
				out << " meshing surface nb. " << x.first << std::endl;
			}

			Debug_Null_Pointer(x.second->Surface());
			const auto& surface = x.second->Surface();

			Debug_Null_Pointer(x.second->MetricMap());
			const auto& metricMap = x.second->MetricMap();

			Debug_Null_Pointer(x.second->Mesh());
			const auto& boundaryMesh = x.second->Mesh();

			const auto& boundaryEdges = boundaryMesh->Boundaries();
			if (boundaryEdges.size() < 3)
			{
				if (verbose)
				{
					out << " - Invalid boundary mesh has been loaded!" << endl;
				}
				continue;
			}

			auto mesher = std::make_shared<Mesh2d_Surface>();
			mesher->LoadBoundaryEdges(bndType::UpCast(boundaryEdges));
			mesher->LoadBoundarySizeMap(metricMap);
			mesher->LoadSizeMap(metricMap);

			mesher->Perform();

			ChangeMesh().insert(std::make_pair(x.first, std::move(mesher)));
		}
		
		Change_IsDone() = Standard_True;
	}

	template<class CrvMesh>
	void MeshAPI_Model<CrvMesh>::CreateMesh3D()
	{
		if (NOT IsDone())
		{
			FatalErrorIn("void CreateMesh3D()")
				<< "the algorithm has not been performed!" << endl
				<< abort(FatalError);
		}

		const auto& paraMesh = Mesh();
		for (const auto& x : paraMesh)
		{
			Debug_Null_Pointer(x.second);

			const auto map = std::dynamic_pointer_cast<sizeMap2d>(x.second->Map());
			Debug_Null_Pointer(map);

			const auto surfaceMetric = std::dynamic_pointer_cast<MetricMap2d_Surface>(map->MetricMap());
			Debug_Null_Pointer(surfaceMetric);

			Debug_Null_Pointer(surfaceMetric->Patch());
			const auto& patch = *surfaceMetric->Patch();

			x.second->CreateStaticMesh();

			const auto& para = *x.second->StaticMesh();

			auto triangulation3d = std::make_shared<Entity3d_Triangulation>();
			Debug_Null_Pointer(triangulation3d);

			auto& Pts = triangulation3d->Points();
			Pts.reserve(para.NbPoints());
			for (const auto& p : para.Points())
			{
				Pts.push_back(patch.Value(p.X(), p.Y()));
			}

			auto& indices = triangulation3d->Connectivity();
			indices = para.Connectivity();

			theMesh3d_.insert(std::make_pair(x.first, std::move(triangulation3d)));
		}
	}
}
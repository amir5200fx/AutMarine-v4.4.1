#include <IO_Shape.hxx>

#include <error.hxx>
#include <OSstream.hxx>
//#include <Entity3d_Triangulation.hxx>
//#include <Cad3d_SolidTools.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopExp_Explorer.hxx>
//#include <TecPlot_Opencascade.hxx>

//void AutLib::IO_Shape::ExportToPlt
//(
//	OFstream & File
//) const
//{
//	for (
//		TopExp_Explorer aFaceExp(Shape().Oriented(TopAbs_FORWARD), TopAbs_FACE);
//		aFaceExp.More();
//		aFaceExp.Next()
//		)
//	{
//		auto face = TopoDS::Face(aFaceExp.Current());
//
//		if (face.IsNull())
//		{
//			continue;
//		}
//
//		auto triangulation = 
//			Cad3d_SolidTools::GetTriangulation(face);
//
//		triangulation->ExportToPlt(File);
//	}
//}
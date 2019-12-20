#pragma once
#ifndef _IO_IGES_Header
#define _IO_IGES_Header

#include <Global_Verbose.hxx>
#include <IO_Config.hxx>
#include <IO_Info.hxx>
#include <IO_Shape.hxx>
#include <word.hxx>
#include <OFstream.hxx>

#include <Bnd_Box.hxx>
#include <BRepMesh_FastDiscret.hxx>
#include <TopoDS_Shape.hxx>

#include <iostream>

class ShapeFix_Shape;

namespace AutLib
{

	class IO_IGES
		: public IO_Config
		, public IO_Info
		, public IO_Shape
	{

		typedef BRepMesh_FastDiscret::Parameters params;

		/*Private Data*/

		params theParameters_;

		void doFixShape();

	public:

		IO_IGES()
		{}

		params& Parameters()
		{
			return theParameters_;
		}

		void ReadFile(const word& theFileName, std::ostream& os = std::cout);

		void ExportToPlt(OFstream& File) const;
	};
}

#endif // !_IO_IGES_Header

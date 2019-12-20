#pragma once
#ifndef _IO_STEP_Header
#define _IO_STEP_Header

#include <IO_Config.hxx>
#include <IO_Info.hxx>
#include <IO_Shape.hxx>
#include <word.hxx>

#include <Bnd_Box.hxx>
#include <BRepMesh_FastDiscret.hxx>
#include <TopoDS_Shape.hxx>

class ShapeFix_Shape;

namespace AutLib
{

	class IO_STEP
		: public IO_Config
		, public IO_Info
		, public IO_Shape
	{

		typedef BRepMesh_FastDiscret::Parameters params;

		/*Private Data*/

		params theParameters_;

		void doFixShape();

	public:

		IO_STEP()
		{}

		params& Parameters()
		{
			return theParameters_;
		}

		void ReadFile(const word& theFileName);
	};
}

#endif // !_IO_STEP_Header

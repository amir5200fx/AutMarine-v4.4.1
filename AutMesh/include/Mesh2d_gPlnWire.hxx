#pragma once
#ifndef _Mesh2d_gPlnWire_Header
#define _Mesh2d_gPlnWire_Header

#include <Mesh_PlnWire.hxx>
#include <Mesh2d_gPlnCurve.hxx>

namespace AutLib
{
	typedef Mesh_PlnWire<Mesh2d_gPlnCurve>
		Mesh2d_gPlnWire;

	template<>
	void Mesh2d_gPlnWire::ExportToPlt(OFstream& File) const;
}

#endif // !_Mesh2d_gPlnWire_Header

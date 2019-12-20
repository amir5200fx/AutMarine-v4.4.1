#pragma once
#ifndef _Mesh2d_PlnWire_Header
#define _Mesh2d_PlnWire_Header

#include <Mesh_PlnWire.hxx>
#include <Mesh2d_PlnCurve.hxx>

namespace AutLib
{
	typedef Mesh_PlnWire<Mesh2d_PlnCurve>
		Mesh2d_PlnWire;

	template<>
	void Mesh2d_PlnWire::ExportToPlt(OFstream& File) const;
}

#endif // !_Mesh2d_PlnWire_Header

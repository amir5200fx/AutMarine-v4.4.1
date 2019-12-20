#pragma once
#ifndef _Mesh3d_ElementAdaptor_Header
#define _Mesh3d_ElementAdaptor_Header

#include <Mesh_ElementAdaptor.hxx>

namespace AutLib
{

	// Forward Declarations
	class Mesh3d_Element;

	typedef Mesh_ElementAdaptor<Mesh3d_Element, 4>
		Mesh3d_ElementAdaptor;
}

#endif // !_Mesh3d_ElementAdaptor_Header

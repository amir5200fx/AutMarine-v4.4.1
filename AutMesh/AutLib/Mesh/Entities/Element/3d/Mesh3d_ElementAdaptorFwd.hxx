#pragma once
#ifndef _Mesh3d_ElementAdaptorFwd_Header
#define _Mesh3d_ElementAdaptorFwd_Header

namespace AutLib
{

	// Forward Declarations
	template<class ElementType, int nbEntities>
	class Mesh_ElementAdaptor;

	class Mesh3d_Element;

	typedef Mesh_ElementAdaptor<Mesh3d_Element, 4>
		Mesh3d_ElementAdaptor;
}

#endif // !_Mesh3d_ElementAdaptorFwd_Header

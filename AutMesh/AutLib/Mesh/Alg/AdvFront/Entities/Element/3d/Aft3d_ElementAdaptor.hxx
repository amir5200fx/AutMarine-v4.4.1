#pragma once
#ifndef _Aft3d_ElementAdaptor_Header
#define _Aft3d_ElementAdaptor_Header

#include <Mesh3d_ElementAdaptorTemplate.hxx>
#include <Aft3d_ElementFwd.hxx>

namespace AutLib
{

	class Aft3d_ElementAdaptor
		: public Mesh3d_ElementAdaptorTemplate<Aft3d_Element>
	{

		/*Private Data*/

	public:

		Aft3d_ElementAdaptor()
		{}
	};
}

#endif // !_Aft3d_ElementAdaptor_Header

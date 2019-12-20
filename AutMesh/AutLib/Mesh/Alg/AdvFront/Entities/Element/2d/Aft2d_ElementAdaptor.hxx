#pragma once
#ifndef _Aft2d_ElementAdaptor_Header
#define _Aft2d_ElementAdaptor_Header

#include <Mesh2d_ElementAdaptorTemplate.hxx>
#include <Aft2d_ElementFwd.hxx>

namespace AutLib
{

	class Aft2d_ElementAdaptor
		: public Mesh2d_ElementAdaptorTemplate<Aft2d_Element>
	{

		/*Private Data*/

	public:

		Aft2d_ElementAdaptor()
		{}
	};
}

#endif // !_Aft2d_ElementAdaptor_Header

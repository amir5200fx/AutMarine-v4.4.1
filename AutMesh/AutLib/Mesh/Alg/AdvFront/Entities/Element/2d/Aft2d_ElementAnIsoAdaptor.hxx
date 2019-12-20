#pragma once
#ifndef _Aft2d_ElementAnIsoAdaptor_Header
#define _Aft2d_ElementAnIsoAdaptor_Header

#include <Mesh2d_ElementAdaptorTemplate.hxx>
#include <Aft2d_ElementAnIsoFwd.hxx>

namespace AutLib
{

	class Aft2d_ElementAnIsoAdaptor
		: public Mesh2d_ElementAdaptorTemplate<Aft2d_ElementAnIso>
	{

		/*Private Data*/

	public:

		Aft2d_ElementAnIsoAdaptor()
		{}
	};
}

#endif // !_Aft2d_ElementAnIsoAdaptor_Header

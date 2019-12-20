#pragma once
#ifndef _Aft2d_Node_Header
#define _Aft2d_Node_Header

#include <Aft_Node.hxx>
#include <Aft_NodeIdentifier.hxx>
#include <Aft2d_NodeTraits.hxx>

namespace AutLib
{

	typedef Aft_Node<Aft2d_NodeTraits, Aft_NodeIdentifier>
		Aft2d_Node;
}

#endif // !_Aft2d_Node_Header

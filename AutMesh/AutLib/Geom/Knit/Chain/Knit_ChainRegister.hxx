#pragma once
#ifndef _Knit_ChainRegister_Header
#define _Knit_ChainRegister_Header

#include <Adt_AvlTree.hxx>
#include <Knit_ChainEdge.hxx>
#include <Knit_ChainNode.hxx>
#include <Mesh_RegisterEntityM_Avl.hxx>

namespace AutLib
{

	Mesh_RegisterEntity_Avl(Knit_ChainNode, NodeType);
	Mesh_RegisterEntity_Avl(Knit_ChainEdge, EdgeType);
}

#endif // !_Knit_ChainRegister_Header

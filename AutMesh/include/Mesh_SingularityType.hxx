#pragma once
#ifndef _Mesh_SingularityType_Header
#define _Mesh_SingularityType_Header

namespace AutLib
{

	enum  Mesh_SingularityType
	{
		SingularityType_Pole_Corner,
		SingularityType_Pole_Loop,
		SingularityType_Pole_PartialSide,
		SingularityType_Pole_WholeSide,
		SingularityType_Line_Corner,
		SingularityType_Line_Dangle,
		SingularityType_Line_Loop,
		SingularityType_Line_TwoSided,
		SingularityType_Line_WholeSide
	};
}

#endif // !_Mesh_SingularityType_Header

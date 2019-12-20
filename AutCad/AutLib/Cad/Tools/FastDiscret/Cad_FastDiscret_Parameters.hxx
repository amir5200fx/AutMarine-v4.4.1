#pragma once
#ifndef _Cad_FastDiscret_Parameters_Header
#define _Cad_FastDiscret_Parameters_Header

#include <Standard_TypeDef.hxx>

#include <memory>

namespace AutLib
{

	struct Cad_FastDiscret_Parameters
	{

		//! Angular deflection
		Standard_Real Angle;

		//! Deflection
		Standard_Real Deflection;

		//! Minimal allowed size of mesh element
		Standard_Real MinSize;

		//! Switches on/off multy thread computation
		Standard_Boolean InParallel;

		//! Switches on/off relative computation of edge tolerance<br>
		//! If true, deflection used for the polygonalisation of each edge will be 
		//! <defle> * Size of Edge. The deflection used for the faces will be the 
		//! maximum deflection of their edges.
		Standard_Boolean Relative;

		//! Adaptive parametric tolerance flag. <br>
		//! If this flag is set to true the minimal parametric tolerance
		//! is computed taking minimal parametric distance between vertices
		//! into account
		Standard_Boolean AdaptiveMin;

		//! Mode to take or not to take internal face vertices into account
		//! in triangulation process
		Standard_Boolean InternalVerticesMode;

		//! Parameter to check the deviation of triangulation and interior of
		//! the face
		Standard_Boolean  ControlSurfaceDeflection;
	};

	extern std::shared_ptr<Cad_FastDiscret_Parameters> cad_fast_discret_parameters;
}

#endif // !_Cad_FastDiscret_Parameters_Header

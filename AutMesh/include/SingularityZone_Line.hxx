#pragma once
#ifndef _SingularityZone_Line_Header
#define _SingularityZone_Line_Header

#include <Mesh_SingularityZone.hxx>

namespace AutLib
{

	template<class SurfPln>
	class SingularityZone_Line
		: public Mesh_SingularityZone<SurfPln>
	{

		/*Private Data*/

	protected:

		SingularityZone_Line()
		{}

	public:

		typedef Mesh_SingularityZone<SurfPln> base;
	};
}

#endif // !_SingularityZone_Line_Header

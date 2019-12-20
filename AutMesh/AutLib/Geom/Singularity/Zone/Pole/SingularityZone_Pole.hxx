#pragma once
#ifndef _SingularityZone_Pole_Header
#define _SingularityZone_Pole_Header

#include <Mesh_SingularityZone.hxx>

namespace AutLib
{

	template<class SurfPln>
	class SingularityZone_Pole
		: public Mesh_SingularityZone<SurfPln>
	{

		/*Private Data*/

		Pnt2d thePole_;

	protected:

		SingularityZone_Pole()
		{}

	public:

		typedef Mesh_SingularityZone<SurfPln> base;

		const Pnt2d& Pole() const
		{
			return thePole_;
		}

		void SetPole(const Pnt2d& theCoord)
		{
			thePole_ = theCoord;
		}
	};
}

#endif // !_SingularityZone_Pole_Header

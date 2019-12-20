#pragma once
#ifndef _Aft_NodeIdentifierSurface_Header
#define _Aft_NodeIdentifierSurface_Header

#include <Aft_NodeIdentifierAnIso.hxx>
#include <Pnt3d.hxx>

namespace AutLib
{

	class Aft_NodeIdentifierSurface
		: public Aft_NodeIdentifierAnIso
	{

		/*Private Data*/

		Pnt3d theCoord3d_;

	public:

		Aft_NodeIdentifierSurface()
		{}

		const Pnt3d& Coord3D() const
		{
			return theCoord3d_;
		}

		Pnt3d& Coord3D()
		{
			return theCoord3d_;
		}

		void SetCoord3D(const Pnt3d& theCoord)
		{
			theCoord3d_ = theCoord;
		}
	};
}

#endif // !_Aft_NodeIdentifierSurface_Header

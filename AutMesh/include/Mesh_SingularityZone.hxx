#pragma once
#ifndef _Mesh_SingularityZone_Header
#define _Mesh_SingularityZone_Header

#include <Global_Indexed.hxx>
#include <Entity2d_Box.hxx>
#include <Mesh_SingularityType.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	template<class SurfPln>
	class Mesh_SingularityZone
		: public Global_Indexed
	{

		typedef typename SurfPln::plnCurve plnCurve;

		/*Private Data*/

		std::shared_ptr<SurfPln> thePlane_;

		std::shared_ptr<Entity2d_Box> theBoundingBox_;

		std::vector<std::shared_ptr<plnCurve>> theBoundaries_;

	protected:

		Mesh_SingularityZone()
		{}

	public:

		virtual Mesh_SingularityType Type() const = 0;

		virtual const word& TypeName() const = 0;

		virtual Standard_Integer NbHorizons() const = 0;

		virtual const std::shared_ptr<plnCurve>& 
			Horizon
			(
				const Standard_Integer theIndex
			) const = 0;

		const std::shared_ptr<SurfPln>& Plane() const
		{
			return thePlane_;
		}

		const std::shared_ptr<Entity2d_Box>& BoundingBox() const
		{
			return theBoundingBox_;
		}

		const std::vector<std::shared_ptr<plnCurve>>& Boundaries() const
		{
			return theBoundaries_;
		}

		void InsertToBoundary(const std::shared_ptr<plnCurve>& theCurve)
		{
			theBoundaries_.push_back(theCurve);
		}

		void LoadPlane(const std::shared_ptr<SurfPln>& thePlane)
		{
			thePlane_ = thePlane;
		}
	};
}

#endif // !_Mesh_SingularityZone_Header

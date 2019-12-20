#pragma once
#ifndef _Model_Plane_Header
#define _Model_Plane_Header

#include <Model_PlnEntity.hxx>

namespace AutLib
{

	// Forward Declarations
	class Cad2d_Plane;

	class Model_Plane
		: public Model_PlnEntitySystem
		, public Model_PlnEntityID
		, public Model_PlnEntityDiscrete
	{

		/*Private Data*/

		std::shared_ptr<Cad2d_Plane> thePlane_;

	protected:

		std::shared_ptr<Cad2d_Plane>& ChangeEntity()
		{
			return thePlane_;
		}

		Model_Plane()
		{}

	public:

		const std::shared_ptr<Cad2d_Plane>& Entity() const
		{
			return thePlane_;
		}

		virtual void Make() = 0;

		void Transform(const gp_Trsf2d& theTrans);
	};
}

#endif // !_Model_Plane_Header

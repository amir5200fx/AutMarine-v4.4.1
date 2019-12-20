#include <Model_Plane.hxx>

#include <Cad2d_Plane.hxx>

void AutLib::Model_Plane::Transform(const gp_Trsf2d & theTrans)
{
	if (thePlane_)
	{
		thePlane_->Transform(theTrans);
	}
}
#include <Mesh2d_Surface.hxx>

namespace AutLib
{

	template<>
	Standard_Boolean Mesh2d_Surface::CheckAngle
	(
		const frontType & theFront,
		const nodeType & theNode,
		const Standard_Real CosAngle
	) const
	{
		const auto& sizeMap = *base::theSizeMap_;
		const auto clength = theFront.CharLength();

		const auto& vrtx0 = *theFront.Node0();
		const auto& vrtx1 = *theFront.Node1();

		const auto l0 = sizeMap.CalcLength3D(vrtx0.Coord3D(), theNode.Coord3D());
		const auto l1 = sizeMap.CalcLength3D(vrtx1.Coord3D(), theNode.Coord3D());

		const auto angN0 = (l0*l0 + clength * clength - l1 * l1) / (2.0*l0*clength);
		if (NOT INSIDE(angN0, -CosAngle, CosAngle))
		{
			return Standard_True;
		}

		const auto angN1 = (l1*l1 + clength * clength - l0 * l0) / (2.0*l1*clength);
		if (NOT INSIDE(angN1, -CosAngle, CosAngle))
		{
			return Standard_True;
		}
		return Standard_False;
	}
}
#include <Aft2d_CoreSurface.hxx>

namespace AutLib
{
	Aft2d_CoreSurface::mySort Aft2d_CoreSurface::Sort;

	template<>
	template<>
	void Aft2d_CoreSurface::UpdateFront<void>()
	{
		Debug_Null_Pointer(frontInfo::ValidNode());
		const auto& node = frontInfo::ValidNode();

		const auto& current = frontInfo::CurrentFront();

		frontInfo::PointCondition() = Aft_PointCondition_PickedUp;

		// check for updating the nodes tree
		if (node->Index() IS_EQUAL frontInfo::NodeCounter() + 1)
		{
			frontInfo::NodeCounter()++;
			
			const auto effect = theSizeMap_->CalcEffectiveMetric(node->Coord(), current->Centre());
			node->SetMetric(effect);

			node->SetCoord3D(theSizeMap_->CalcCoord3D(node->Coord()));

			frontInfo::PointCondition() = Aft_PointCondition_NewPoint;

			// insert the new node into the NODES TREE
			frontData::InsertToGeometry(frontInfo::ValidNode());
		}

		frontInfo::SetPaires();

		frontInfo::UpdatePaires(*theSizeMap_);

		frontInfo::CreateElement();

		frontInfo::UpdateElement();

		RemoveEntitiesFromGeometry();

		RegisterElement();
	}
}
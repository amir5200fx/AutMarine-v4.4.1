#pragma once
#ifndef _MeshAPI_Info_Model_Header
#define _MeshAPI_Info_Model_Header

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class MeshAPI_ModelInfo;

	namespace ModelLib
	{

		extern std::shared_ptr<MeshAPI_ModelInfo> mesh_api_model_info;

		void meshApi_model_init_runTime();
	}
}

#endif // !_MeshAPI_Info_Model_Header

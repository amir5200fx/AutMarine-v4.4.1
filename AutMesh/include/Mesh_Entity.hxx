#pragma once
#ifndef _Mesh_Entity_Header
#define _Mesh_Entity_Header

#include <Global_Indexed.hxx>

#include <memory>

namespace AutLib
{

	class Mesh_Entity
		: public Global_Indexed
		, public std::enable_shared_from_this<Mesh_Entity>
	{

		/*Private Data*/

	public:

		Mesh_Entity()
		{}

		Mesh_Entity(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
		{}

		virtual ~Mesh_Entity()
		{}
	};
}

#endif // !_Mesh_Entity_Header

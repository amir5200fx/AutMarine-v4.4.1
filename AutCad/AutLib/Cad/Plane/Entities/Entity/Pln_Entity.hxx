#pragma once
#ifndef _Pln_Entity_Header
#define _Pln_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <memory>

namespace AutLib
{

	class Pln_Entity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<Pln_Entity>
	{

		/*Private Data*/

	public:

		Pln_Entity()
		{}

		Pln_Entity
		(
			const Standard_Integer theIndex
		)
			: Global_Indexed(theIndex)
		{}

		Pln_Entity
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

		virtual ~Pln_Entity()
		{}
	};
}

#endif // !_Pln_Entity_Header

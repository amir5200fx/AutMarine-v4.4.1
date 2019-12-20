#pragma once
#ifndef _IO_Info_Header
#define _IO_Info_Header

#include <Standard_TypeDef.hxx>
#include <word.hxx>

namespace AutLib
{

	class IO_Info
	{

		/*Private Data*/

		Standard_Integer theNbIgesFaces_;
		Standard_Integer theNbTransFaces_;

		word theFileName_;

	protected:

		void SetNbIgesFaces(const Standard_Integer theNbFaces)
		{
			theNbIgesFaces_ = theNbFaces;
		}

		void SetNbTransFaces(const Standard_Integer theNbFaces)
		{
			theNbTransFaces_ = theNbFaces;
		}

		void SetFileName(const word& theName)
		{
			theFileName_ = theName;
		}

	public:

		IO_Info()
			: theNbIgesFaces_(0)
			, theNbTransFaces_(0)
		{}

		Standard_Integer NbIgesFaces() const
		{
			return theNbIgesFaces_;
		}

		Standard_Integer NbTransFaces() const
		{
			return theNbTransFaces_;
		}

		const word& FileName() const
		{
			return theFileName_;
		}
	};
}

#endif // !_IO_Info_Header

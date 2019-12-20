#pragma once
#ifndef _Aft_NodeIdentifier_Header
#define _Aft_NodeIdentifier_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{

	class Aft_NodeIdentifier
	{

		/*Private Data*/

		Standard_Real theRadius_;
		Standard_Real theMaxL_;

		Standard_Boolean IsOnCavity_;

	public:

		Aft_NodeIdentifier()
			: theRadius_(0)
			, theMaxL_(0)
			, IsOnCavity_(Standard_False)
		{}

		Standard_Real Radius() const
		{
			return theRadius_;
		}

		Standard_Real& Radius()
		{
			return theRadius_;
		}

		Standard_Real MaxL() const
		{
			return theMaxL_;
		}

		Standard_Real& MaxL()
		{
			return theMaxL_;
		}

		Standard_Boolean CavityStatus() const
		{
			return IsOnCavity_;
		}

		void SetRadius(const Standard_Real theRadius)
		{
			theRadius_ = theRadius;
		}

		void SetMaxAdjLength(const Standard_Real Value)
		{
			theMaxL_ = Value;
		}

		void SetCavityStatus(const Standard_Boolean status)
		{
			IsOnCavity_ = status;
		}
	};
}

#endif // !_Aft_NodeIdentifier_Header
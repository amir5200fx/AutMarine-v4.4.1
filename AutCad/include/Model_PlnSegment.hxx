#pragma once
#ifndef _Model_PlnSegment_Header
#define _Model_PlnSegment_Header

#include <Pnt2d.hxx>
#include <Model_PlnCurve.hxx>
#include <error.hxx>
#include <OSstream.hxx>

class Geom2d_Curve;

namespace AutLib
{

	// Forward Declarations
	class Pln_Curve;

	class Model_PlnSegment
		: public Model_PlnCurve
	{

		/*Private Data*/

		Standard_Real theLength_;

		void SetSystem(const gp_Ax22d& theSystem) override;

	public:

		Model_PlnSegment()
		{}

		Model_PlnSegment(const Standard_Real theLength)
			: theLength_(theLength)
		{
			if (theLength_ < gp::Resolution())
			{
				FatalErrorIn("Model_PlnSegment(const Standard_Real theLength)")
					<< "Null segment" << endl
					<< abort(FatalError);
			}

			Make();
		}

		Model_PlnSegment(const Pnt2d& theP0, const Pnt2d& theP1);

		std::shared_ptr<Pln_Curve> operator()(const Pnt2d& theP0, const Pnt2d& theP1);
		std::shared_ptr<Pln_Curve> operator()(const Standard_Real theLength);

		Standard_Real Length() const
		{
			return theLength_;
		}

		const gp_Pnt2d& P0() const
		{
			return System().Location();
		}

		gp_Pnt2d CalcP1() const;

		gp_Ax2d Axis() const
		{
			return System().XAxis();
		}

		void SetLength(const Standard_Real theLength)
		{
			theLength_ = theLength;

			if (theLength_ < gp::Resolution())
			{
				FatalErrorIn("void SetLength(const Standard_Real theLength)")
					<< "Null segment" << endl
					<< abort(FatalError);
			}

			Make();
		}

		void Make() override;

		void Discrete() override;
	};
}

#endif // !_Model_PlnSegment_Header

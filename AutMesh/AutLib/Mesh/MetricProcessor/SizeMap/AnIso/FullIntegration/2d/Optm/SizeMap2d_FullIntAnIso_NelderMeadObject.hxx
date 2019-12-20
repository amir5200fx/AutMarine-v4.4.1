#pragma once
#ifndef _SizeMap2d_FullIntAnIso_NelderMeadObject_Header
#define _SizeMap2d_FullIntAnIso_NelderMeadObject_Header

#include <Pnt2d.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class SizeMap2d_FullIntAnIso;

	struct SizeMap2d_FullIntAnIso_NelderMeadObjectCache
	{

	protected:

		mutable Standard_Real d0;
		mutable Standard_Real d1;

		SizeMap2d_FullIntAnIso_NelderMeadObjectCache()
		{}
	};

	class SizeMap2d_FullIntAnIso_NelderMeadObjectInfo
	{

		/*Private Data*/

		Standard_Real theTolerance_;

	public:

		static const Standard_Real DEFAULT_TOLERANCE;

		SizeMap2d_FullIntAnIso_NelderMeadObjectInfo()
			: theTolerance_(DEFAULT_TOLERANCE)
		{}

		Standard_Real Tolerance() const
		{
			return theTolerance_;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}
	};

	class SizeMap2d_FullIntAnIso_NelderMeadObject
		: public SizeMap2d_FullIntAnIso_NelderMeadObjectCache
	{

		typedef SizeMap2d_FullIntAnIso_NelderMeadObjectInfo info;

		/*Private Data*/

		std::shared_ptr<SizeMap2d_FullIntAnIso> theMap_;
		std::shared_ptr<info> theInfo_;

		Pnt2d theP0_;
		Pnt2d theP1_;
		Pnt2d theP2_;

		static Standard_Real EstimateError
		(
			const Standard_Real d0,
			const Standard_Real d1
		);

	public:

		static const int nbVariables;

		enum
		{
			dim = 2
		};

		typedef Pnt2d varType;

		SizeMap2d_FullIntAnIso_NelderMeadObject
		(
			const std::shared_ptr<info>& theInfo
		)
			: theInfo_(theInfo)
		{}

		const std::shared_ptr<SizeMap2d_FullIntAnIso>& SizeMap() const
		{
			return theMap_;
		}

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		const Pnt2d& P0() const
		{
			return theP0_;
		}

		const Pnt2d& P1() const
		{
			return theP1_;
		}

		const Pnt2d& P2() const
		{
			return theP2_;
		}

		Standard_Real Value(const Pnt2d& theCoord) const;

		Standard_Boolean IsConverged() const
		{
			auto tol = Info()->Tolerance();
			return (ABS(1.0 - d0) <= tol AND ABS(1.0 - d1) <= tol);
		}

		void LoadSizeMap(const std::shared_ptr<SizeMap2d_FullIntAnIso>& theMap)
		{
			theMap_ = theMap;
		}

		void SetP0(const Pnt2d& theP0)
		{
			theP0_ = theP0;
		}

		void SetP1(const Pnt2d& theP1)
		{
			theP1_ = theP1;
		}

		void SetP2(const Pnt2d& theP2)
		{
			theP2_ = theP2;
		}

		void Initial(Pnt2d var[3])
		{
			var[0] = P0();
			var[1] = P1();
			var[2] = P2();
		}

		static Standard_Real V(const Standard_Integer Dim, const Pnt2d& P)
		{
			return P.Coord(Dim);
		}

		static void SetV(const Standard_Integer Dim, const Standard_Real x, Pnt2d& P)
		{
			return P.SetCoord(Dim, x);
		}
	};

	extern std::shared_ptr<SizeMap2d_FullIntAnIso_NelderMeadObjectInfo>
		size_map2d_nelder_mead_info;
}

#include <SizeMap2d_FullIntAnIso_NelderMeadObjectI.hxx>

#endif // !_SizeMap2d_FullIntAnIso_NelderMeadObject_Header

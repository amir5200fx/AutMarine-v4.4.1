#pragma once
#ifndef _Mesh_SurfPlane_Header
#define _Mesh_SurfPlane_Header

#include <Mesh_PlnWire.hxx>
#include <Mesh_PlnCurve.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	template<class CrvEntity>
	class Mesh_PlnCurve;

	template<class SurfType>
	class Mesh_SurfPlane
		: public Global_Indexed
		, public Global_Named
	{

	public:

		typedef SurfType surfType;

		typedef typename SurfType::pCurveType pCurveType;
		typedef Mesh_PlnCurve<pCurveType> plnCurve;
		typedef Mesh_PlnWire<plnCurve> plnWire;

		typedef std::shared_ptr<plnWire> wire_ptr;
		typedef std::vector<wire_ptr> wireList;

		typedef wire_ptr outer;
		typedef std::shared_ptr<wireList> inner;

	private:

		/*Private Data*/

		outer theOutter_;
		inner theInner_;

		std::shared_ptr<SurfType> theSurface_;

	public:

		

		Mesh_SurfPlane
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SurfType>& theSurface,
			const outer& theOutter,
			const inner& theInner = nullptr
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, theSurface_(theSurface)
			, theOutter_(theOutter)
			, theInner_(theInner)
		{}

		Mesh_SurfPlane
		(
			const std::shared_ptr<SurfType>& theSurface,
			const outer& theOutter,
			const inner& theInner = nullptr
		)
			: theOutter_(theOutter)
			, theInner_(theInner)
			, theSurface_(theSurface)
		{}

		Standard_Boolean HasHole() const
		{
			return (Standard_Boolean)theInner_;
		}

		Standard_Integer NbHoles() const
		{
			if (!HasHole()) return 0;
			return (Standard_Integer)theInner_->size();
		}

		const inner& Inner() const
		{
			return theInner_;
		}

		const outer& Outer() const
		{
			return theOutter_;
		}

		const std::shared_ptr<SurfType>& Surface() const
		{
			return theSurface_;
		}

		void RetrieveWiresTo(wireList& theWires) const;

		void ExportToPlt(OFstream& File) const;


		//- Static functions and operators

		static std::shared_ptr<plnWire> GetWire(const typename SurfType::wireType& theWire);

		static std::shared_ptr<Mesh_SurfPlane>
			MakePlane(const std::shared_ptr<SurfType>& theSurface);
	};
}

#include <Mesh_SurfPlaneI.hxx>

#endif // !_Mesh_SurfPlane_Header


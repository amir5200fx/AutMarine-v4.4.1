#pragma once
#ifndef _Mesh2d_SurfPlane_Header
#define _Mesh2d_SurfPlane_Header

#include <Mesh_SurfPlane.hxx>
#include <Cad2d_Plane.hxx>
#include <Mesh2d_PlnWireFwd.hxx>

namespace AutLib
{

	// Forward Declarations
	class Pln_Wire;
	class Pln_Curve;

	template<>
	class Mesh_SurfPlane<Cad2d_Plane>
		: public Global_Indexed
		, public Global_Named
	{

		typedef std::vector<std::shared_ptr<Mesh2d_PlnWire>> wireList;

		typedef std::shared_ptr<wireList> inner;
		typedef std::shared_ptr<Mesh2d_PlnWire> outer;

		/*Private Data*/

		outer theOuter_;
		inner theInner_;

		std::shared_ptr<Cad2d_Plane> thePlane_;

	public:

		Mesh_SurfPlane
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Cad2d_Plane>& thePlane,
			const outer& theOuter, 
			const inner& theInner
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, thePlane_(thePlane)
			, theOuter_(theOuter)
			, theInner_(theInner)
		{}

		Mesh_SurfPlane
		(
			const std::shared_ptr<Cad2d_Plane>& thePlane,
			const outer& theOuter,
			const inner& theInner
		)
			: thePlane_(thePlane)
			, theOuter_(theOuter)
			, theInner_(theInner)
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
			return theOuter_;
		}

		const std::shared_ptr<Cad2d_Plane>& Plane() const
		{
			return thePlane_;
		}

		void RetrieveWiresTo(wireList& theWires) const;

		void ExportToPlt(OFstream& File) const;

		//- Static functions and operators

		static std::shared_ptr<Mesh2d_PlnWire> GetWire(const Pln_Wire& theWire);

		static std::shared_ptr<Mesh_SurfPlane>
			MakePlane(const std::shared_ptr<Cad2d_Plane>& thePlane);
	};

	typedef Mesh_SurfPlane<Cad2d_Plane>
		Mesh2d_SurfPlane;
}

#endif // !_Mesh2d_SurfPlane_Header

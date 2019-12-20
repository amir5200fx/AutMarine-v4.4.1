#pragma once
#ifndef _GModel_Plane_Header
#define _GModel_Plane_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <OFstream.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class GModel_parWire;
	class GModel_Surface;
	class GModel_parCurve;

	class GModel_Plane
		: public Global_Indexed
		, public Global_Named
	{

		typedef std::shared_ptr<GModel_parWire> wire_ptr;
		typedef std::vector<wire_ptr> wireList;

		typedef wire_ptr outer;
		typedef std::shared_ptr<wireList> inner;

		/*Private Data*/

		outer theOutter_;
		inner theInner_;

	public:

		//typedef GModel_PlaneTraits edgeType;
		typedef GModel_parCurve curveType;
		typedef GModel_parWire wireType;

		GModel_Plane
		(
			const Standard_Integer theIndex,
			const word& theName,
			const outer& theOutter,
			const inner& theInner = nullptr
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, theOutter_(theOutter)
			, theInner_(theInner)
		{}

		GModel_Plane
		(
			const outer& theOutter,
			const inner& theInner = nullptr
		)
			: theOutter_(theOutter)
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
			return theOutter_;
		}

		void RetrieveWiresTo(wireList& theWires) const;

		void ExportToPlt(OFstream& File) const;


		static std::shared_ptr<GModel_Plane>
			MakePlane(const GModel_Surface& theFace);
	};
}

#endif // !_GModel_Plane_Header

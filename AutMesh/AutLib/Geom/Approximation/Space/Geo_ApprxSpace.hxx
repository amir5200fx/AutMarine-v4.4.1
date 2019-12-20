#pragma once
#ifndef _Geo_ApprxSpace_Header
#define _Geo_ApprxSpace_Header

#include <Entity_Box.hxx>
#include <Geom_PrTree.hxx>
#include <Traits.hxx>

#include <list>
#include <memory>

namespace AutLib
{

	class Geo_ApprxSpaceNode
	{

		/*Private Data*/

	public:

		Geo_ApprxSpaceNode()
		{}

		virtual ~Geo_ApprxSpaceNode()
		{}
	};

	template<class Point, int Dim>
	class Geo_ApprxSpaceLeaf {};

	template<class Point>
	class Geo_ApprxSpaceLeaf<Point, 2>
		: public Geo_ApprxSpaceNode
	{

		typedef Entity_Box<Point> box;
		typedef std::list<Geo_ApprxSpaceLeaf*> leafList;

		/*Private Data*/

		std::shared_ptr<box> theRegion_;

		Standard_Integer theLevel_;

		leafList theSNeighbors_;
		leafList theENeighbors_;
		leafList theNNeighbors_;
		leafList theWNeighbors_;

		Geo_ApprxSpaceNode* theFather_;

	public:

		Geo_ApprxSpaceLeaf()
			: theFather_(0)
		{}

		Geo_ApprxSpaceLeaf
		(
			const std::shared_ptr<box>& theRegion,
			const Standard_Integer theLevel
		)
			: theRegion_(theRegion)
			, theLevel_(theLevel)
			, theFather_(0)
		{}

		Standard_Integer Level() const
		{
			return theLevel_;
		}

		Standard_Integer& Level()
		{
			return theLevel_;
		}

		const std::shared_ptr<box>& Region() const
		{
			return theRegion_;
		}

		std::shared_ptr<box>& Region()
		{
			return theRegion_;
		}

		const leafList& SNeighbors() const
		{
			return theSNeighbors_;
		}

		leafList& SNeighbors()
		{
			return theSNeighbors_;
		}

		const leafList& ENeighbors() const
		{
			return theENeighbors_;
		}

		leafList& ENeighbors()
		{
			return theENeighbors_;
		}

		const leafList& NNeighbors() const
		{
			return theNNeighbors_;
		}

		leafList& NNeighbors()
		{
			return theNNeighbors_;
		}

		const leafList& WNeighbors() const
		{
			return theWNeighbors_;
		}

		leafList& WNeighbors()
		{
			return theWNeighbors_;
		}

		Geo_ApprxSpaceNode* Father() const
		{
			return theFather_;
		}

		Geo_ApprxSpaceNode*& Father()
		{
			return theFather_;
		}
	};

	template<int Dim>
	class Geo_ApprxSpaceInternal {};

	template<>
	class Geo_ApprxSpaceInternal<2>
		: public Geo_ApprxSpaceNode
	{

		typedef Geo_ApprxSpaceNode node;

		/*Private Data*/

		node* theSwPtr_;
		node* theSePtr_;
		node* theNePtr_;
		node* theNwPtr_;

	public:

		Geo_ApprxSpaceInternal()
			: theSwPtr_(0)
			, theSePtr_(0)
			, theNePtr_(0)
			, theNwPtr_(0)
		{}

		node* Sw() const
		{
			return theSwPtr_;
		}

		node*& Sw()
		{
			return theSwPtr_;
		}

		node* Se() const
		{
			return theSePtr_;
		}

		node*& Se()
		{
			return theSePtr_;
		}

		node* Ne() const
		{
			return theNePtr_;
		}

		node*& Ne()
		{
			return theNePtr_;
		}

		node* Nw() const
		{
			return theNwPtr_;
		}

		node*& Nw()
		{
			return theNwPtr_;
		}
	};

	struct Geo_ApprxSpaceInfo
	{

		Standard_Integer Max_Level;
		Standard_Integer Min_Level;

		Standard_Integer Max_UnBalancing;

		Geo_ApprxSpaceInfo()
			: Max_Level(6)
			, Min_Level(2)
			, Max_UnBalancing(1)
		{}
	};

	template<class T>
	class Geo_ApprxSpace
	{

		typedef typename remove_pointer<T>::type Type;
		typedef typename Type::ptType Point;

		typedef Entity_Box<Point> box;
		typedef Geo_ApprxSpaceNode node;
		typedef Geo_ApprxSpaceLeaf<Point, (int)Point::dim> leafNode;
		typedef Geo_ApprxSpaceInternal<(int)Point::dim> internalNode;

		template< bool cond, typename U >
		using resolvedType = typename std::enable_if< cond, U >::type;

		/*Private Data*/

		node* theRoot_;

		std::shared_ptr<Type> theObject_;

		Standard_Boolean IsDone_;
		Standard_Boolean IsBalancing_;

		box theRegion_;

		Standard_Boolean(*Subdivide)(const box&, const std::shared_ptr<Type>&);

		std::shared_ptr<Geo_ApprxSpaceInfo> theInfo_;


		template<class U = void>
		resolvedType
			<
			is_two_dimension<(int)Point::dim>::value, U
			>
			SwitchToClear(internalNode*& t)
		{
			if (t->Sw()) Clear(t->Sw());
			if (t->Se()) Clear(t->Se());
			if (t->Ne()) Clear(t->Ne());
			if (t->Nw()) Clear(t->Nw());
		}

		template<class U = void>
		resolvedType
			<
			is_three_dimension<(int)Point::dim>::value, U
			>
			SwitchToClear(internalNode*& t);

		void Clear(node*& t)
		{
			leafNode* leaf =
				dynamic_cast<leafNode*>(t);

			if (leaf)
			{
				delete t;
				t = nullptr;
			}
			else
			{
				internalNode* Internal =
					dynamic_cast<internalNode*>(t);

				SwitchToClear(Internal);
				delete t;
				t = nullptr;
			}
		}

		template<class U = Standard_Boolean>
		resolvedType
			<
			is_two_dimension<(int)Point::dim>::value, U
			>
			IsUnBalanced(leafNode*& t) const
		{
			if (t->SNeighbors().size() > theInfo_->Max_UnBalancing + 1) return Standard_True;
			if (t->ENeighbors().size() > theInfo_->Max_UnBalancing + 1) return Standard_True;
			if (t->NNeighbors().size() > theInfo_->Max_UnBalancing + 1) return Standard_True;
			if (t->WNeighbors().size() > theInfo_->Max_UnBalancing + 1) return Standard_True;
			return Standard_False;
		}

		template<class U = Standard_Boolean>
		resolvedType
			<
			is_three_dimension<(int)Point::dim>::value, U
			>
			IsUnBalanced(leafNode*& t) const;

		template<class U = void>
		resolvedType
			<
			is_two_dimension<(int)Point::dim>::value, U
			>
			UpdateFather(leafNode* Node, node* Internal) const
		{
			if (NOT Node->Father()) return;
			auto father = dynamic_cast<internalNode*>(Node->Father());
			Debug_Null_Pointer(father);

			if (father->Sw() IS_EQUAL Node) father->Sw() = Internal;
			else if (father->Se() IS_EQUAL Node) father->Se() = Internal;
			else if (father->Ne() IS_EQUAL Node) father->Ne() = Internal;
			else if (father->Nw() IS_EQUAL Node) father->Nw() = Internal;
			else
			{
				FatalErrorIn("void UpdateFather(leafNode* Node, node* Internal) const")
					<< "Contradictory Data" << endl
					<< abort(FatalError);
			}
		}

		template<class U = void>
		resolvedType
			<
			is_two_dimension<(int)Point::dim>::value, U
			>
			InnerLinks(internalNode* t) const
		{
			auto swPtr = dynamic_cast<leafNode*>(t->Sw());
			auto sePtr = dynamic_cast<leafNode*>(t->Se());
			auto nePtr = dynamic_cast<leafNode*>(t->Ne());
			auto nwPtr = dynamic_cast<leafNode*>(t->Nw());

			Debug_Null_Pointer(swPtr);
			Debug_Null_Pointer(sePtr);
			Debug_Null_Pointer(nePtr);
			Debug_Null_Pointer(nwPtr);

			swPtr->ENeighbors().push_back(sePtr);
			swPtr->NNeighbors().push_back(nwPtr);

			sePtr->WNeighbors().push_back(swPtr);
			sePtr->NNeighbors().push_back(nePtr);

			nePtr->WNeighbors().push_back(nwPtr);
			nePtr->SNeighbors().push_back(sePtr);

			nwPtr->ENeighbors().push_back(nePtr);
			nwPtr->SNeighbors().push_back(swPtr);
		}

		template<class U = void>
		resolvedType
			<
			is_three_dimension<(int)Point::dim>::value, U
			>
			InnerLinks(internalNode* t) const;

		template<class U = void>
		resolvedType
			<
			is_two_dimension<(int)Point::dim>::value, U
			>
			RemoveLeafFromNeighbors(leafNode* old) const
		{
			const auto& SN = old->SNeighbors();
			const auto& EN = old->ENeighbors();
			const auto& NN = old->NNeighbors();
			const auto& WN = old->WNeighbors();

			for (const auto& x : SN)
				x->NNeighbors().remove(old);

			for (const auto& x : EN)
				x->WNeighbors().remove(old);

			for (const auto& x : NN)
				x->SNeighbors().remove(old);

			for (const auto& x : WN)
				x->ENeighbors().remove(old);
		}

		template<class U = void>
		resolvedType
			<
			is_three_dimension<(int)Point::dim>::value, U
			>
			RemoveLeafFromNeighbors(leafNode* old) const;

		template<class U = void>
		resolvedType
			<
			is_two_dimension<(int)Point::dim>::value, U
			>
			FillNeighbors
			(
				const Geo_Quadrant quadrant,
				leafNode* old,
				internalNode* father,
				leafNode* t
			) const
		{
			const auto& SN = old->SNeighbors();
			const auto& EN = old->ENeighbors();
			const auto& NN = old->NNeighbors();
			const auto& WN = old->WNeighbors();

			auto swPtr = dynamic_cast<leafNode*>(father->Sw());
			auto sePtr = dynamic_cast<leafNode*>(father->Se());
			auto nePtr = dynamic_cast<leafNode*>(father->Ne());
			auto nwPtr = dynamic_cast<leafNode*>(father->Nw());

			Debug_Null_Pointer(swPtr);
			Debug_Null_Pointer(sePtr);
			Debug_Null_Pointer(nePtr);
			Debug_Null_Pointer(nwPtr);

			const auto& region = old->Region();
			auto centre = region->CalcCentre();

			std::vector<leafNode*> QSn, QEn, QNn, QWn;

			if (quadrant IS_EQUAL Geo_Quadrant_SW)
			{
				if (WN.size() <= 1)
				{
					for (const auto& x : WN)
						QWn.push_back(x);
				}
				else
				{
					for (const auto& x : WN)
					{
						switch (CalcQuadrant(x->Region()->CalcCentre(), centre))
						{
						case Geo_Quadrant_SW: QWn.push_back(x); break;
						default: break;
						}
					}
				}

				if (SN.size() <= 1)
				{
					for (const auto& x : SN)
						QSn.push_back(x);
				}
				else
				{
					for (const auto& x : SN)
					{
						switch (CalcQuadrant(x->Region()->CalcCentre(), centre))
						{
						case Geo_Quadrant_SW: QSn.push_back(x); break;
						default: break;
						}
					}
				}
			}
			else if (quadrant IS_EQUAL Geo_Quadrant_SE)
			{
				if (SN.size() <= 1)
				{
					for (const auto& x : SN)
						QSn.push_back(x);
				}
				else
				{
					for (const auto& x : SN)
					{
						switch (CalcQuadrant(x->Region()->CalcCentre(), centre))
						{
						case Geo_Quadrant_SE: QSn.push_back(x); break;
						default: break;
						}
					}
				}

				if (EN.size() <= 1)
				{
					for (const auto& x : EN)
						QEn.push_back(x);
				}
				else
				{
					for (const auto& x : EN)
					{
						switch (CalcQuadrant(x->Region()->CalcCentre(), centre))
						{
						case Geo_Quadrant_SE: QEn.push_back(x); break;
						default: break;
						}
					}
				}
			}
			else if (quadrant IS_EQUAL Geo_Quadrant_NE)
			{
				if (EN.size() <= 1)
				{
					for (const auto& x : EN)
						QEn.push_back(x);
				}
				else
				{
					for (const auto& x : EN)
					{
						switch (CalcQuadrant(x->Region()->CalcCentre(), centre))
						{
						case Geo_Quadrant_NE: QEn.push_back(x); break;
						default: break;
						}
					}
				}

				if (NN.size() <= 1)
				{
					for (const auto& x : NN)
						QNn.push_back(x);
				}
				else
				{
					for (const auto& x : NN)
					{
						switch (CalcQuadrant(x->Region()->CalcCentre(), centre))
						{
						case Geo_Quadrant_NE: QNn.push_back(x); break;
						default: break;
						}
					}
				}
			}
			else
			{
				if (NN.size() <= 1)
				{
					for (const auto& x : NN)
						QNn.push_back(x);
				}
				else
				{
					for (const auto& x : NN)
					{
						switch (CalcQuadrant(x->Region()->CalcCentre(), centre))
						{
						case Geo_Quadrant_NW: QNn.push_back(x); break;
						default: break;
						}
					}
				}

				if (WN.size() <= 1)
				{
					for (const auto& x : WN)
						QWn.push_back(x);
				}
				else
				{
					for (const auto& x : WN)
					{
						switch (CalcQuadrant(x->Region()->CalcCentre(), centre))
						{
						case Geo_Quadrant_NW: QWn.push_back(x); break;
						default: break;
						}
					}
				}

			}

			for (const auto& x : QSn)
				x->NNeighbors().push_back(t);
			for (const auto& x : QEn)
				x->WNeighbors().push_back(t);
			for (const auto& x : QNn)
				x->SNeighbors().push_back(t);
			for (const auto& x : QWn)
				x->ENeighbors().push_back(t);

			for (const auto& x : QSn)
				t->SNeighbors().push_back(x);
			for (const auto& x : QEn)
				t->ENeighbors().push_back(x);
			for (const auto& x : QNn)
				t->NNeighbors().push_back(x);
			for (const auto& x : QWn)
				t->WNeighbors().push_back(x);
		}


		template<class U = void>
		resolvedType
			<
			is_three_dimension<(int)Point::dim>::value, U
			>
			FillNeighbors
			(
				const Geo_Quadrant quadrant,
				leafNode* old,
				internalNode* father,
				leafNode* t
			) const;

		template<class U = void>
		resolvedType
			<
			is_two_dimension<(int)Point::dim>::value, U
			>
			RetrieveTo
			(
				node* t,
				std::vector<std::shared_ptr<box>>& boxes
			) const
		{
			if (NOT t) return;
			auto leaf = dynamic_cast<leafNode*>(t);

			if (leaf)
			{
				boxes.push_back(leaf->Region());
			}
			else
			{
				auto Internal = dynamic_cast<internalNode*>(t);

				if (Internal->Sw()) RetrieveTo(Internal->Sw(), boxes);
				if (Internal->Se()) RetrieveTo(Internal->Se(), boxes);
				if (Internal->Ne()) RetrieveTo(Internal->Ne(), boxes);
				if (Internal->Nw()) RetrieveTo(Internal->Nw(), boxes);
			}
		}

		template<class U = void>
		resolvedType
			<
			is_two_dimension<(int)Point::dim>::value, U
			>
			RetrieveTo
			(
				node* t,
				std::vector<node*>& nodes
			) const
		{
			if (NOT t) return;
			auto leaf = dynamic_cast<leafNode*>(t);

			if (leaf)
			{
				nodes.push_back(t);
			}
			else
			{
				auto Internal = dynamic_cast<internalNode*>(t);

				if (Internal->Sw()) RetrieveTo(Internal->Sw(), nodes);
				if (Internal->Se()) RetrieveTo(Internal->Se(), nodes);
				if (Internal->Ne()) RetrieveTo(Internal->Ne(), nodes);
				if (Internal->Nw()) RetrieveTo(Internal->Nw(), nodes);
			}
		}

		template<class U = void>
		resolvedType
			<
			is_three_dimension<(int)Point::dim>::value, U
			>
			RetrieveTo
			(
				node* t,
				std::vector<node*>& nodes
			) const;

		template<class U = void>
		resolvedType
			<
			is_three_dimension<(int)Point::dim>::value, U
			>
			RetrieveTo
			(
				node* t,
				std::vector<std::shared_ptr<box>>& boxes
			) const;

		template<class U = void>
		resolvedType
			<
			is_two_dimension<(int)Point::dim>::value, U
			>
			doSubDivide
			(
				node*& t
			) const
		{
			auto leaf = dynamic_cast<leafNode*>(t);
			Debug_Null_Pointer(leaf);

			if (leaf->Level() > theInfo_->Max_Level) return;

			if (Subdivide(*leaf->Region(), theObject_))
			{
				auto level = leaf->Level();
				const auto& b = leaf->Region();

				auto Internal = new internalNode;

				auto swPtr =
					new leafNode(std::make_shared<box>(b->SubDivide(Box2d_SubDivideAlgorithm_Quad_SW)), level + 1);
				auto sePtr =
					new leafNode(std::make_shared<box>(b->SubDivide(Box2d_SubDivideAlgorithm_Quad_SE)), level + 1);
				auto nePtr =
					new leafNode(std::make_shared<box>(b->SubDivide(Box2d_SubDivideAlgorithm_Quad_NE)), level + 1);
				auto nwPtr =
					new leafNode(std::make_shared<box>(b->SubDivide(Box2d_SubDivideAlgorithm_Quad_NW)), level + 1);

				Debug_Null_Pointer(swPtr);
				Debug_Null_Pointer(sePtr);
				Debug_Null_Pointer(nePtr);
				Debug_Null_Pointer(nwPtr);

				swPtr->Father() = Internal;
				sePtr->Father() = Internal;
				nePtr->Father() = Internal;
				nwPtr->Father() = Internal;

				Internal->Sw() = swPtr;
				Internal->Se() = sePtr;
				Internal->Ne() = nePtr;
				Internal->Nw() = nwPtr;

				InnerLinks(Internal);

				// Remove Old Leaf from Neighbors
				RemoveLeafFromNeighbors(leaf);

				FillNeighbors(Geo_Quadrant_SW, leaf, Internal, swPtr);
				FillNeighbors(Geo_Quadrant_SE, leaf, Internal, sePtr);
				FillNeighbors(Geo_Quadrant_NE, leaf, Internal, nePtr);
				FillNeighbors(Geo_Quadrant_NW, leaf, Internal, nwPtr);

				UpdateFather(leaf, Internal);

				delete leaf;
				t = Internal;

				doSubDivide(Internal->Sw());
				doSubDivide(Internal->Se());
				doSubDivide(Internal->Ne());
				doSubDivide(Internal->Nw());
			}
		}

		template<class U = void>
		resolvedType
			<
			is_three_dimension<(int)Point::dim>::value, U
			>
			doSubDivide
			(
				node*& t
			) const;

		template<class U = void>
		resolvedType
			<
			is_two_dimension<(int)Point::dim>::value, U
			>
			ForceSubDivide
			(
				node*& t
			) const
		{
			auto leaf = dynamic_cast<leafNode*>(t);
			Debug_Null_Pointer(leaf);

			if (leaf->Level() > theInfo_->Min_Level) return;

			auto level = leaf->Level();
			const auto& b = leaf->Region();

			auto Internal = new internalNode;

			auto swPtr =
				new leafNode(std::make_shared<box>(b->SubDivide(Box2d_SubDivideAlgorithm_Quad_SW)), level + 1);
			auto sePtr =
				new leafNode(std::make_shared<box>(b->SubDivide(Box2d_SubDivideAlgorithm_Quad_SE)), level + 1);
			auto nePtr =
				new leafNode(std::make_shared<box>(b->SubDivide(Box2d_SubDivideAlgorithm_Quad_NE)), level + 1);
			auto nwPtr =
				new leafNode(std::make_shared<box>(b->SubDivide(Box2d_SubDivideAlgorithm_Quad_NW)), level + 1);

			Debug_Null_Pointer(swPtr);
			Debug_Null_Pointer(sePtr);
			Debug_Null_Pointer(nePtr);
			Debug_Null_Pointer(nwPtr);

			swPtr->Father() = Internal;
			sePtr->Father() = Internal;
			nePtr->Father() = Internal;
			nwPtr->Father() = Internal;

			Internal->Sw() = swPtr;
			Internal->Se() = sePtr;
			Internal->Ne() = nePtr;
			Internal->Nw() = nwPtr;

			InnerLinks(Internal);

			// Remove Old Leaf from Neighbors
			RemoveLeafFromNeighbors(leaf);

			FillNeighbors(Geo_Quadrant_SW, leaf, Internal, swPtr);
			FillNeighbors(Geo_Quadrant_SE, leaf, Internal, sePtr);
			FillNeighbors(Geo_Quadrant_NE, leaf, Internal, nePtr);
			FillNeighbors(Geo_Quadrant_NW, leaf, Internal, nwPtr);

			UpdateFather(leaf, Internal);

			delete leaf;
			t = Internal;

			ForceSubDivide(Internal->Sw());
			ForceSubDivide(Internal->Se());
			ForceSubDivide(Internal->Ne());
			ForceSubDivide(Internal->Nw());
		}

		template<class U = void>
		resolvedType
			<
			is_three_dimension<(int)Point::dim>::value, U
			>
			ForceSubDivide
			(
				node*& t
			) const;

		template<class U = void>
		resolvedType
			<
			is_two_dimension<(int)Point::dim>::value, U
			>
			Balancing
			(
				node*& t
			)
		{
			if (NOT t) return;
			auto leaf = dynamic_cast<leafNode*>(t);

			if (leaf)
			{
				if (NOT IsUnBalanced(leaf)) return;
				if (NOT IsBalancing_) IsBalancing_ = Standard_True;

				auto level = leaf->Level();
				const auto& b = leaf->Region();

				auto Internal = new internalNode;

				auto swPtr =
					new leafNode(std::make_shared<box>(b->SubDivide(Box2d_SubDivideAlgorithm_Quad_SW)), level + 1);
				auto sePtr =
					new leafNode(std::make_shared<box>(b->SubDivide(Box2d_SubDivideAlgorithm_Quad_SE)), level + 1);
				auto nePtr =
					new leafNode(std::make_shared<box>(b->SubDivide(Box2d_SubDivideAlgorithm_Quad_NE)), level + 1);
				auto nwPtr =
					new leafNode(std::make_shared<box>(b->SubDivide(Box2d_SubDivideAlgorithm_Quad_NW)), level + 1);

				Debug_Null_Pointer(swPtr);
				Debug_Null_Pointer(sePtr);
				Debug_Null_Pointer(nePtr);
				Debug_Null_Pointer(nwPtr);

				Internal->Sw() = swPtr;
				Internal->Se() = sePtr;
				Internal->Ne() = nePtr;
				Internal->Nw() = nwPtr;

				InnerLinks(Internal);

				// Remove Old Leaf from Neighbors
				RemoveLeafFromNeighbors(leaf);

				FillNeighbors(Geo_Quadrant_SW, leaf, Internal, swPtr);
				FillNeighbors(Geo_Quadrant_SE, leaf, Internal, sePtr);
				FillNeighbors(Geo_Quadrant_NE, leaf, Internal, nePtr);
				FillNeighbors(Geo_Quadrant_NW, leaf, Internal, nwPtr);

				delete t;
				t = Internal;

				Balancing(Internal->Sw());
				Balancing(Internal->Se());
				Balancing(Internal->Ne());
				Balancing(Internal->Nw());
			}
			else
			{
				auto Internal = dynamic_cast<internalNode*>(t);
				Debug_Null_Pointer(Internal);

				Balancing(Internal->Sw());
				Balancing(Internal->Se());
				Balancing(Internal->Ne());
				Balancing(Internal->Nw());
			}
		}

		template<class U = void>
		resolvedType
			<
			is_three_dimension<(int)Point::dim>::value, U
			>
			Balancing
			(
				node*& t
			);


	public:

		Geo_ApprxSpace(const std::shared_ptr<Geo_ApprxSpaceInfo>& theInfo)
			: theRoot_(nullptr)
			, IsDone_(Standard_False)
			, IsBalancing_(Standard_False)
			, theInfo_(theInfo)
		{}

		Geo_ApprxSpace
		(
			const box& theRegion,
			const std::shared_ptr<Type>& theObject,
			Standard_Boolean(*doSubdivide)(const box&, const std::shared_ptr<Type>&),
			const std::shared_ptr<Geo_ApprxSpaceInfo>& theInfo
		)
			: theRoot_(nullptr)
			, theRegion_(theRegion)
			, theObject_(theObject)
			, Subdivide(doSubdivide)
			, IsDone_(Standard_False)
			, IsBalancing_(Standard_False)
			, theInfo_(theInfo)
		{}

		~Geo_ApprxSpace()
		{
			Clear(theRoot_);
		}

		void SetRegion(const box& theRegion)
		{
			theRegion_ = theRegion;
		}

		void SetObject(const std::shared_ptr<Type>& theObject)
		{
			theObject_ = theObject;
		}

		void SubDivider(Standard_Boolean(*subdivider)(const box&, const std::shared_ptr<Type>&))
		{
			Subdivide = subdivider;
		}

		void Init()
		{
			theRoot_ = new leafNode(std::make_shared<box>(theRegion_), 0);
			ForceSubDivide(theRoot_);
		}

		void Perform(const std::vector<node*>& Nodes)
		{
			if (NOT Subdivide)
			{
				FatalErrorIn("void Perform(const std::vector<node*>& Nodes)")
					<< "No subdivider has been found!"
					<< abort(FatalError);
			}

			for (const auto& x : Nodes)
			{
				auto ptr = x;
				doSubDivide(ptr);
			}
		}

		void Perform()
		{
			std::vector<node*> nodes;
			RetrieveTo(nodes);

			if (NOT Subdivide)
			{
				FatalErrorIn("void Perform(const std::vector<node*>& Nodes)")
					<< "No subdivider has been found!"
					<< abort(FatalError);
			}

			for (const auto& x : nodes)
			{
				auto ptr = x;
				doSubDivide(ptr);
			}
		}

		void PostBalancing()
		{
			while (Standard_True)
			{
				IsBalancing_ = Standard_False;
				Balancing(theRoot_);
				if (NOT IsBalancing_) break;
			}
		}

		void RetrieveTo(std::vector<std::shared_ptr<box>>& boxes) const
		{
			RetrieveTo(theRoot_, boxes);
		}

		void RetrieveTo(std::vector<node*>& nodes) const
		{
			RetrieveTo(theRoot_, nodes);
		}

		void ExportToPlt(OFstream& File) const
		{
			std::vector<std::shared_ptr<box>> boxes;
			RetrieveTo(boxes);

			for (const auto& x : boxes)
			{
				x->ExportToPlt(File);
			}
		}
	};
}

#endif // !_Geo_ApprxSpace_Header

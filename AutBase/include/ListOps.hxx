#pragma once
#ifndef _ListOps_Header
#define _ListOps_Header

#include <labelList.hxx>

namespace AutLib
{

	//- Renumber the values (not the indices) of a list.
	//  Negative ListType elements are left as is.
	template<class ListType>
	ListType renumber(const UList<label>& oldToNew, const ListType&);

	//- Inplace renumber the values of a list.
	//  Negative ListType elements are left as is.
	template<class ListType>
	void inplaceRenumber(const UList<label>& oldToNew, ListType&);


	//- Reorder the elements (indices, not values) of a list.
	//  Negative ListType elements are left as is.
	template<class ListType>
	ListType reorder(const UList<label>& oldToNew, const ListType&);

	//- Inplace reorder the elements of a list.
	//  Negative ListType elements are left as is.
	template<class ListType>
	void inplaceReorder(const UList<label>& oldToNew, ListType&);


	// Variants to work with iterators and sparse tables.
	// Need to have iterators and insert()

	//- Map values. Do not map negative values.
	template<class Container>
	void inplaceMapValue(const UList<label>& oldToNew, Container&);

	//- Recreate with mapped keys. Do not map elements with negative key.
	template<class Container>
	void inplaceMapKey(const UList<label>& oldToNew, Container&);


	//- Generate the (stable) sort order for the list
	template<class T>
	void sortedOrder(const UList<T>&, labelList& order);

	//- Generate (sorted) indices corresponding to duplicate list values
	template<class T>
	void duplicateOrder(const UList<T>&, labelList& order);

	//- Generate (sorted) indices corresponding to unique list values
	template<class T>
	void uniqueOrder(const UList<T>&, labelList& order);

	//- Extract elements of List when select is a certain value.
	//  eg, to extract all selected elements:
	//    subset<bool, labelList>(selectedElems, true, lst);
	template<class T, class ListType>
	ListType subset(const UList<T>& select, const T& value, const ListType&);

	//- Inplace extract elements of List when select is a certain value.
	//  eg, to extract all selected elements:
	//    inplaceSubset<bool, labelList>(selectedElems, true, lst);
	template<class T, class ListType>
	void inplaceSubset(const UList<T>& select, const T& value, ListType&);

	//- Extract elements of List when select is true
	//  eg, to extract all selected elements:
	//    subset<boolList, labelList>(selectedElems, lst);
	//  Note a labelHashSet could also be used for the bool-list
	template<class BoolListType, class ListType>
	ListType subset(const BoolListType& select, const ListType&);

	//- Inplace extract elements of List when select is true
	//  eg, to extract all selected elements:
	//    inplaceSubset<boolList, labelList>(selectedElems, lst);
	//  Note a labelHashSet could also be used for the bool-list
	template<class BoolListType, class ListType>
	void inplaceSubset(const BoolListType& select, ListType&);

	//- Invert one-to-one map. Unmapped elements will be -1.
	labelList invert(const label len, const UList<label>&);

	//- Invert one-to-many map. Unmapped elements will be size 0.
	labelListList invertOneToMany(const label len, const UList<label>&);

	//- Invert many-to-many.
	//  Input and output types need to be inherited from List.
	//  eg, faces to pointFaces.
	template<class InList, class OutList>
	void invertManyToMany(const label len, const UList<InList>&, List<OutList>&);

	template<class InList, class OutList>
	List<OutList> invertManyToMany(const label len, const UList<InList>& in)
	{
		List<OutList> out;
		invertManyToMany<InList, OutList>(len, in, out);
		return out;
	}

	//- Create identity map (map[i] == i) of given length
	labelList identity(const label len);

	//- Find first occurence of given element and return index,
	//  return -1 if not found. Linear search.
	template<class ListType>
	label findIndex(const ListType&, typename ListType::const_reference, const label start = 0);

	//- Find all occurences of given element. Linear search.
	template<class ListType>
	labelList findIndices(const ListType&, typename ListType::const_reference, const label start = 0);

	//- Opposite of findIndices: set values at indices to given value
	template<class ListType>
	void setValues(ListType&, const UList<label>& indices, typename ListType::const_reference);

	//- Opposite of findIndices: set values at indices to given value
	template<class ListType>
	ListType createWithValues(const label sz, typename ListType::const_reference initValue, const UList<label>& indices, typename ListType::const_reference setValue);

	//- Find index of max element (and larger than given element).
	//  return -1 if not found. Linear search.
	template<class ListType>
	label findMax(const ListType&, const label start = 0);


	//- Find index of min element (and less than given element).
	//  return -1 if not found. Linear search.
	template<class ListType>
	label findMin(const ListType&, const label start = 0);


	//- Find first occurence of given element in sorted list and return index,
	//  return -1 if not found. Binary search.
	template<class ListType>
	label findSortedIndex(const ListType&, typename ListType::const_reference, const label start = 0);


	//- Find last element < given value in sorted list and return index,
	//  return -1 if not found. Binary search.
	template<class ListType>
	label findLower(const ListType&, typename ListType::const_reference, const label start = 0);


	//- To construct a List from a C array. Has extra Container type
	//  to initialise e.g. wordList from arrays of char*.
	template<class Container, class T, int nRows>
	List<Container> initList(const T[nRows]);


	//- To construct a (square) ListList from a C array. Has extra Container type
	//  to initialise e.g. faceList from arrays of labels.
	template<class Container, class T, int nRows, int nColumns>
	List<Container> initListList(const T[nRows][nColumns]);
}

#include <ListOpsI.hxx>

#endif // !_ListOps_Header

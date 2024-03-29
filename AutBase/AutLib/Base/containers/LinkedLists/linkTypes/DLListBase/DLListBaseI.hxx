#pragma once
#include <error.hxx>
#include <OSstream.hxx>

inline 
AutLib::DLListBase::link::link()
	: prev_(0)
	, next_(0)
{}


inline 
AutLib::DLListBase::DLListBase()
	: first_(0)
	, last_(0)
	, nElmts_(0)
{}


inline 
AutLib::DLListBase::DLListBase(link* a)
	: first_(a)
	, last_(a)
	, nElmts_(1)
{
	a->prev_ = a;
	a->next_ = a;
}

inline 
AutLib::DLListBase::~DLListBase()
{}

inline bool AutLib::DLListBase::link::registered() const
{
	return prev_ != 0 && next_ != 0;
}


inline void AutLib::DLListBase::link::deregister()
{
	prev_ = 0;
	next_ = 0;
}


inline AutLib::label AutLib::DLListBase::size() const
{
	return nElmts_;
}


inline bool AutLib::DLListBase::empty() const
{
	return !nElmts_;
}


inline AutLib::DLListBase::link*
AutLib::DLListBase::first()
{
	if (!nElmts_)
	{
		FatalErrorIn("DLListBase::first()")
			<< "list is empty"
			<< abort(FatalError);
	}
	return first_;
}


inline const AutLib::DLListBase::link*
AutLib::DLListBase::first() const
{
	if (!nElmts_)
	{
		FatalErrorIn("DLListBase::first() const")
			<< "list is empty"
			<< abort(FatalError);
	}
	return first_;
}


inline AutLib::DLListBase::link*
AutLib::DLListBase::last()
{
	if (!nElmts_)
	{
		FatalErrorIn("DLListBase::last()")
			<< "list is empty"
			<< abort(FatalError);
	}
	return last_;
}


inline const AutLib::DLListBase::link*
AutLib::DLListBase::last() const
{
	if (!nElmts_)
	{
		FatalErrorIn("DLListBase::last() const")
			<< "list is empty"
			<< abort(FatalError);
	}
	return last_;
}


inline void AutLib::DLListBase::clear()
{
	first_ = 0;
	last_ = 0;
	nElmts_ = 0;
}


inline void AutLib::DLListBase::transfer(DLListBase& lst)
{
	first_ = lst.first_;
	last_ = lst.last_;
	nElmts_ = lst.nElmts_;

	lst.clear();
}


inline AutLib::DLListBase::link*
AutLib::DLListBase::remove
(
	DLListBase::iterator& it
)
{
	return remove(it.curElmt_);
}


inline AutLib::DLListBase::link*
AutLib::DLListBase::replace
(
	DLListBase::iterator& oldIter,
	DLListBase::link* newLink
)
{
	return replace(oldIter.curElmt_, newLink);
}

inline AutLib::DLListBase::iterator::iterator(DLListBase& s, link* elmt)
	:
	curList_(s),
	curElmt_(elmt),
	curLink_(*curElmt_)
{
}


inline AutLib::DLListBase::iterator::iterator(DLListBase& s)
	:
	curList_(s),
	curElmt_(NULL),
	curLink_()
{
}


inline void AutLib::DLListBase::iterator::operator=(const iterator& iter)
{
	curElmt_ = iter.curElmt_;
	curLink_ = iter.curLink_;
}


inline bool AutLib::DLListBase::iterator::operator==(const iterator& iter) const
{
	return curElmt_ == iter.curElmt_;
}


inline bool AutLib::DLListBase::iterator::operator!=(const iterator& iter) const
{
	return curElmt_ != iter.curElmt_;
}


inline AutLib::DLListBase::link&
AutLib::DLListBase::iterator::operator*()
{
	return *curElmt_;
}


inline AutLib::DLListBase::iterator&
AutLib::DLListBase::iterator::operator++()
{
	// Check if the curElmt_ is the last element (if it points to itself)
	// or if the list is empty because the last element may have been removed
	if (curLink_.next_ == curElmt_ || curList_.last_ == 0)
	{
		curElmt_ = 0;
	}
	else
	{
		curElmt_ = curLink_.next_;
		curLink_ = *curElmt_;
	}

	return *this;
}


inline AutLib::DLListBase::iterator
AutLib::DLListBase::iterator::operator++(int)
{
	iterator tmp = *this;
	++*this;
	return tmp;
}


inline AutLib::DLListBase::iterator
AutLib::DLListBase::begin()
{
	if (size())
	{
		return iterator(*this, first());
	}
	else
	{
		return endIter_;
	}
}


inline const AutLib::DLListBase::iterator& AutLib::DLListBase::end()
{
	return endIter_;
}

inline AutLib::DLListBase::const_iterator::const_iterator
(
	const DLListBase& s,
	const link* elmt
)
	:
	curList_(s),
	curElmt_(elmt)
{
}


inline AutLib::DLListBase::const_iterator::const_iterator(const iterator& iter)
	:
	curList_(iter.curList_),
	curElmt_(iter.curElmt_)
{
}


inline void AutLib::DLListBase::const_iterator::operator=
(
	const const_iterator& iter
	)
{
	curElmt_ = iter.curElmt_;
}


inline bool AutLib::DLListBase::const_iterator::operator==
(
	const const_iterator& iter
	) const
{
	return curElmt_ == iter.curElmt_;
}


inline bool AutLib::DLListBase::const_iterator::operator!=
(
	const const_iterator& iter
	) const
{
	return curElmt_ != iter.curElmt_;
}


inline const AutLib::DLListBase::link&
AutLib::DLListBase::const_iterator::operator*()
{
	return *curElmt_;
}


inline AutLib::DLListBase::const_iterator&
AutLib::DLListBase::const_iterator::operator++()
{
	if (curElmt_ == curList_.last_)
	{
		curElmt_ = 0;
	}
	else
	{
		curElmt_ = curElmt_->next_;
	}

	return *this;
}


inline AutLib::DLListBase::const_iterator
AutLib::DLListBase::const_iterator::operator++(int)
{
	const_iterator tmp = *this;
	++*this;
	return tmp;
}


inline AutLib::DLListBase::const_iterator
AutLib::DLListBase::cbegin() const
{
	if (size())
	{
		return const_iterator(*this, first());
	}
	else
	{
		return endConstIter_;
	}
}


inline const AutLib::DLListBase::const_iterator&
AutLib::DLListBase::cend() const
{
	return endConstIter_;
}


inline AutLib::DLListBase::const_iterator
AutLib::DLListBase::begin() const
{
	return this->cbegin();
}


inline const AutLib::DLListBase::const_iterator&
AutLib::DLListBase::end() const
{
	return endConstIter_;
}
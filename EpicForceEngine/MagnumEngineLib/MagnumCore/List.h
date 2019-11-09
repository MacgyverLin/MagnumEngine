///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _List_h_
#define _List_h_

#include "Stage.h"
#include "Array.h"

namespace Magnum
{

template<class T> class List;
template<class T> class Link
{
	friend class List<T>;
	List<T> *_parent;
	Link<T> *_prev;
	Link<T> *_next;
	T *_owner;
public:
	operator T*() const
	{
		return _owner;
	}

	operator T&() const
	{
		assert(_owner!=0);
		return *_owner;
	}

	inline T &owner() const
	{
		assert(_owner!=0);
		return *_owner;
	}

	inline T &owner(T &owner_)
	{
		_owner=&owner_;
		return *_owner;
	}

	inline List<T> *parent()
	{
		return _parent;
	}

	inline Link<T> *prev()
	{
		return _prev;
	}

	inline Link<T> *next()
	{
		return _next;
	}

	inline const List<T> *const_parent() const
	{
		return _parent;
	}

	inline const Link<T> *const_prev() const
	{
		return _prev;
	}

	inline const Link<T> *const_next() const
	{
		return _next;
	}

	void link_first(List<T> &list)
	{
		if(list._first==this)
			return;

		if(list._first)
			link_prev(*list._first);
		else
		{	
			unlink();
			_parent=&list;
			_parent->_count++;
			_parent->_first=this;
			_parent->_last=this;
		}
	}

	void link_last(List<T> &list)
	{
		if(list._last==this)
			return;

		if(list._last)
		{
			link_next(*list._last);		
		}
		else
		{	
			unlink();
			_parent=&list;
			_parent->_count++;
			_parent->_first=this;
			_parent->_last=this;
		}
	}

	void link_prev(Link<T> &link)
	{
		assert(link._parent!=0);
		if(&link==this)
			return;

		unlink();

		_parent=link._parent;
		_parent->_count++;

		if(_parent->_first==&link)
			_parent->_first=this;

		if(_prev=link._prev)
			_prev->_next=this;

		_next=&link;
		link._prev=this;
	}

	void link_next(Link<T> &link)
	{
		assert(link._parent!=0);
		if(&link==this)
			return;
			
		unlink();

		_parent=link._parent;
		_parent->_count++;
		if(_parent->_last==&link)
			_parent->_last=this;

		if(_next=link._next)
			_next->_prev=this;

		_prev=&link;
		link._next=this;
	}

	void remove()
	{
		if(_parent)
		{
			_parent->remove(*this);
		}
	}

	void unlink()
	{
		if(_parent)
		{
			_parent->_count--;
			if(_parent->_count==0)
			{
				_parent->_first=_parent->_last=0;
			}
			else if(_parent->_count==1)
			{
				Link<T> *t=_prev?_prev:_next;
				_parent->_first=_parent->_last=t;
				t->_next=t->_prev=0;
			}
			else
			{
				if(_parent->_first==this)
					_parent->_first=_next;
				if(_parent->_last==this)
					_parent->_last=_prev;
				if(_prev)
					_prev->_next=_next;
				if(_next)
					_next->_prev=_prev;	
			}
		}

		_parent=0;
		_prev=0;
		_next=0;
	}

	Link(T &owner_)
	: _owner(&owner_)
	, _parent(0)
	, _prev(0)
	, _next(0)
	{
	}

	Link()
	: _owner(0)
	, _parent(0)
	, _prev(0)
	, _next(0)
	{
	}

	virtual ~Link()
	{
		unlink();
	}
};

template<class T> class List
{
	friend class Link<T>;
	void *_owner;
	Link<T> *_first;
	Link<T> *_last;
	int _count;

public:
	typedef int (*Compare)(const T &left, const T &right);
private:
	Compare compare;
public:
	inline void *owner()
	{
		return _owner;
	}
	
	inline int count() const
	{
		return _count;
	}

	inline Link<T> *first()
	{
		return _first;
	}

	inline Link<T> *last()
	{
		return _last;
	}

	Link<T> *find(int at)
	{
		assert(at>=0&&at<_count);

		for(Link<T> *n=_first;n!=0;n=n->next())
		{			
			if(at--==0) 
				return n;
		}

		return 0;
	}

	Link<T> *find(T &t)
	{
		for(Link<T> *n=_first;n!=0;n=n->next())
		{			
			if(&t==(T *)n)
				return n;
		}

		return 0;
	}

	const Link<T> *const_first() const
	{
		return _first;
	}

	const Link<T> *const_last() const
	{
		return _last;
	}

	const Link<T> *const_find(int at) const
	{
		assert(at>=0 && at<_count);

		for(const T *n=_first;n!=0;n=n->const_next())
		{			
			if(at--==0) 
				return n;
		}

		return 0;
	}

	void clear()
	{
		while(_first)
		{
			_first->unlink();
		}

		assert(_count==0);
	}

	void remove(Link<T> &link)
	{
		link.unlink();
	}

	void insert(Link<T> &link)
	{
		if(compare)
		for(Link<T> *n=first();n!=0;n=n->next())
		{
			if(0<compare(n->owner(),link.owner()))
			{
				link.link_prev(*n);
				return;
			}
		}
		link.link_last(*this);
	}

	void sort(void *compare_)
	{
		if(compare_)
			compare=(int (*)(const T &left, const T &right) )(compare_);

		if(!compare)
			return;
		if(count()<=1)
			return;

		List<T> temp;
		Link<T> *n;
		while(n=first())
		{
			n->link_last(temp);
		}

		while(n=temp.first())
		{
			insert(*n);
		}
	}

	void merge(List<T> &from)
	{
		if(this==&from)
			return;
		
		Link<T> *n;

		while(n=from.first())
		{
			insert(*n);
		}
	}

	List(void *owner_=0, Compare compare_=0)
	: _owner(owner_)
	, _count(0)
	, _first(0)
	, _last(0)
	, compare(compare_)
	{
	}

	virtual ~List()
	{
		clear();
	}
};

template<class T> class Pool
{
	Array<T> pool;
	Array<Link<T> > links;
public:
	List<T> list;

	void reset()
	{
		for(int i=0; i<pool.capacity(); i++)
		{
			list.insert(links[i]);
		}
	}

	Pool(int size)
	: pool(size)
	, links(size)
	{
		for(int i=0; i<pool.capacity(); i++)
		{
			links[i].owner(pool[i]);
			list.insert(links[i]);
		}
	}

	~Pool()
	{
	}
};

template<class T> class Post
{
public:
	List<T> list;
	List<T> post;
	Link<T> *cursor;
	int direction;
public:
	typedef void (T::*Callback)();

	void remove(Link<T> &link)
	{
		if(&link==cursor)
		{
			if(direction==1)
				cursor=link.next();
			else
				cursor=link.prev();
		}
		link.unlink();
	}

	void insert(Link<T> &link)
	{
		if(cursor)
			post.insert(link);
		else
			list.insert(link);
	}

	void clear()
	{
		cursor=0;
		direction=0;
		list.clear();
		post.clear();
	}

	void stop()
	{
		cursor=0;
		direction=0;
		for(Link<T> *n=post.first();n;n=n->next())
			list.insert(*n);
	}

	T &current()
	{
		return cursor->owner();
	}

	bool next()
	{
		return cursor && (cursor=cursor->next());
	}

	bool prev()
	{
		return cursor && (cursor=cursor->prev());
	}


	bool begin_forward()
	{
		assert(cursor==0);
		stop();
		cursor=list.first();
		if(!cursor)
			return false;

		direction=1;
		return true;
	}
		
	bool forward(Callback cb)
	{
		if(!begin_forward())
			return false;

		do
		{	T &t=current();
			assert(cb);
			(t.*cb)();

		}while(next());

		stop();
		return true;
	}

	bool begin_backward()
	{
		assert(cursor==0);
		stop();
		cursor=list.last();
		if(!cursor)
			return false;

		direction=1;
		return true;
	}

	bool backward(Callback cb)
	{
		if(!begin_backward())
			return false;

		do
		{	
			T &t=cursor->owner();
			(t.*cb)();

		}while(prev());

		stop();
		return true;
	}

	bool has(T &t)
	{
		if(list.find(t))
			return true;
		
		if(post.find(t))
			return true;
		
		return false;
	}


	Post(void *compare=0)
	: direction(0)
	, cursor(0)
	{
		if(compare)
			list.sort(compare);
	}

	~Post()
	{
		clear();
	}
};

}

#endif //_LIST_H_
///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Array_h_
#define _Array_h_

#include "Stage.h"

namespace EpicForce
{

template<class T> class Array
{
	T		*array;
	int		_length;
	int		_capacity;
public:
	typedef int (* Compare)(const void *left, const  void *right);
	
	inline int length() const
	{
		return _length;
	}

	inline int capacity() const
	{
		return _capacity;
	}

#ifndef _DEBUG
	void *get(int i)
	{
		return (void *)(&array[i]);
	}

	inline T &operator[](int i)
	{
		return array[i];
	}

	inline const T &operator[](int i) const
	{
		return array[i];
	}
#else
	void *get(int i)
	{
		if(!valid(i))
		{
			panic("Array[%d] of length %d index %d out of bounds!",_capacity,_length,i);
			assert( false );
		}

		return (void *)(&array[i]);
	}

	T &operator[](int i)
	{
		if(!valid(i))
		{
			panic("Array[%d] of length %d index %d out of bounds!",_capacity,_length,i);
			assert( false );
		}
		
		return array[i];
	}

	const T &operator[](int i) const
	{
		if(!valid(i))
		{
			panic("Array[%d] of length %d index %d out of bounds! (const)",_capacity,_length,i);
			assert( false );
		}
		
		return array[i];
	}
#endif
	inline bool full() const
	{
		return _length==capacity();
	}

	inline void clear()
	{
		_length=0;
	}

	inline bool empty()
	{
		return _length==0;
	}

	inline bool valid(int i) const
	{
		return i<_length&&i>=0;
	}

	const T& back() const
	{
		return array[_length - 1];
	}

	T& back()
	{
		return array[_length -1];
	}

	inline T &insert(int at)
	{
		assert(!full());
		assert(at<=_length);
		for(int i=_length;i>at;i--)
		{
			array[i]=array[i-1];
		}
		_length++;
		return array[at];
	}

	inline T &insert()
	{
		if(full())
			panic("Array<%d,%d> insert() full!",sizeof(T),_capacity);
		assert(!full());
		return array[_length++];
	}

	inline T &binaryInsert(const T &item) const
	{
		if(full())
			panic("Array<%d,%d> insert() full!",sizeof(T),_capacity);
		assert(!full());

		int min = 0;
		int max = _length - 1;
		int mid;
		do
		{
			mid = (min+max)>>1;

			if( item > array[mid] )
				min = mid+1;
			else
				max = mid-1;
		}while(min<=max);

		return insert(mid);
	}

	int binarySearch(const T &item) const
	{
		int min = 0;
		int max = _length - 1;
		int mid;
		bool found = false;
		do
		{
			mid = (min+max)>>1;

			if(item==array[mid])
				found = true;
			else if( item > array[mid] )
				min = mid+1;
			else
				max = mid-1;
		}while(!found && min<=max);

		if(found)
			return mid;
		else
			return -1;
	}

	int search(const T &item)
	{
		for(int i=0;i<_length;i++)
		{
			if(array[i]==item)
			{
				return i;
			}
		}
		return -1;
	}

	void remove(int index)
	{
		if(index<0) return;
		
		if(_length <= 0)
		{
			_length = 0;
			return;
		}
		if(index < 0 || index >= _length-1)
			--_length;
		else
		{
			// index lies in range of 0 to _length-2
			int i;
			for(i=index; i<_length-1; ++i)
				array[i]=array[i+1];
			--_length;
		}
		
		array[_length] = T();
	}

	T &push()
	{
		assert(_length<_capacity);
		return array[_length++];
	}

	T &pop()
	{
		assert(_length>0);
		return array[--_length];
	}

	void truncate(int length_)
	{
		assert(length_<=_capacity);
		_length=length_;
	}

	void resize(int length_)
	{
		assert(length_<=_capacity);
		_length=length_;
	}

	void sort(Compare method)
	{
		if(_length>1)
			qsort(array,_length,sizeof(T),method);
	}

	typedef bool (*Iterate)(int index, T &t);

	bool iterate(Iterate cb)
	{
		int i=0;
		for(int i=0;i<length();i++)
		{
			if(!cb(i,array[i]))
				return false;
		}
		return true;
	}

	T *getType()
	{
		return 0;
	}

	Array(int capacity_, int length_ = -1)
	{	
		if(length_==-1)
			_length = capacity_;
		else
			_length = length_;			

		_capacity = capacity_;

		assert(_length<=_capacity);
		
		array = new T[_capacity];
	}

	~Array()
	{
		if(array)
		{
			delete [] array;
			array = 0;
		}
	}
public:
};

template<class T> class Vector
{
	T *array;
	int _length;
	int _capacity;
public:
	typedef int (* Compare)(const void *left, const  void *right);
	
	inline int length() const
	{
		return _length;
	}

	inline int capacity() const
	{
		return _capacity;
	}
#ifndef _DEBUG
	void *get(int i)
	{
		return (void *)(&array[i]);
	}

	inline T &operator[](int i)
	{
		return array[i];
	}

	inline const T &operator[](int i) const
	{
		return array[i];
	}
#else
	void *get(int i)
	{
		if(!valid(i))
		{
			panic("Array[%d] of length %d index %d out of bounds!",_capacity,_length,i);
			assert( false );
		}

		return (void *)(&array[i]);
	}

	T &operator[](int i)
	{
		if(!valid(i))
		{
			panic("Vector[%d] of length %d index %d out of bounds!",_capacity,_length,i);
			assert( false );
		}
		
		return array[i];
	}
	const T &operator[](int i) const
	{
		if(!valid(i))
		{
			panic("Vector[%d] of length %d index %d out of bounds!",_capacity,_length,i);
			assert( false );
		}
		
		return array[i];
	}
#endif
	const T& back() const
	{
		return array[_length - 1];
	}

	T& back()
	{
		return array[_length -1];
	}

	inline bool full() const
	{
		return _length==_capacity;
	}

	inline void clear()
	{
		_length=0;
	}

	inline bool empty() const
	{
		return _length==0;
	}

	inline bool valid(int i) const
	{
		return i<_length&&i>=0;
	}

	inline void destroy()
	{
		delete [] array;
		array=0;
		_capacity=_length=0;
	}

	inline void resize(int length_)
	{
		assert(length_>=0);
		expand(length_);

		_length=length_;
	}

	void allocate(int length_)
	{
		assert(array==0);
		array=new T[length_];
		_length=_capacity=length_;
	}

	void expand(int new_capacity)
	{
		if(new_capacity < _capacity)
			return;

		int org_cap=_capacity;

		if(new_capacity==0)
		{
			_capacity+=(_capacity%8)*2;
			if(_capacity==0)
				_capacity=4;
		}
		else if(new_capacity<=_capacity) 
			return;		
		else
		{
			while ( _capacity < new_capacity )
				_capacity += _capacity / 2 > 1 ? _capacity / 2 : 1;
		}

		T *b=new T[_capacity];
		if(!b)
		{
			panic("Vector<%d> ALLOC FAILED! %d to %d",sizeof(T),org_cap,_capacity);
			_capacity=org_cap;
			assert(false);
			return;
		}

		for(int i=0;i<_length;i++)
			b[i]=array[i];

		delete [] array;
		array=b;
	}

	inline T &insert(int at)
	{
		expand(_length+1);

		for(int i=_length;i>at;i--)
		{
			array[i]=array[i-1];
		}
		_length++;
		return array[at];
	}

	inline T &insert()
	{
		expand(_length+1);

		return array[_length++];
	}

	int binarySearch(const T &item, Compare method) const
	{
		int min = 0;
		int max = _length - 1;
		int mid;
		bool found = false;
		do
		{
			mid = (min+max)>>1;

			if(item==array[mid])
				found = true;
			else if( item > array[mid] )
				min = mid+1;
			else
				max = mid-1;
		}while(!found && min<=max);

		if(found)
			return mid;
		else
			return -1;
	}

	int search(const T &item) const
	{
		for(int i=0;i<_length;i++)
		{
			if(array[i]==item)
			{
				return i;
			}
		}
		return -1;
	}

	void remove(int index)
	{
		if(index<0)
			return;

		if(_length <= 0)
		{
			_length = 0;
			return;
		}
		if(index < 0 || index >= _length-1)
			--_length;
		else
		{
			// index lies in range of 0 to _length-2
			int i;
			for(i=index; i<_length-1; ++i)
				array[i]=array[i+1];
			--_length;
		}
		array[_length] = T();
	}

	T &push()
	{
		expand(_length+1);
		_length++;

		return array[_length-1];
	}

	T &pop()
	{
		assert(_length>0);

		return array[--_length];
	}

	void sort(Compare method)
	{
		if(_length>1)
			qsort(array,_length,sizeof(T),method);
	}

	Vector(int capacity_=0, int length_=0)
	: array(0)
	, _length(0)
	, _capacity(0)
	{	
		assert(_length<=_capacity);
		if(capacity_>0)
		{
			expand(capacity_);
		}
		_length=length_;
	}

	Vector &operator=(const Vector &other)
	{
		if(this==&other)
			return *this;

		delete [] array;
		array		= 0;
		_length		= 0;
		_capacity	= 0;

		if(other._capacity==0)
			return *this;

		expand(other._capacity);
		
		_length = other._length;

		for(int i=0; i<_length; i++)
		{
			array[i] = other.array[i];
		}

		return *this;
	}

	T *getType()
	{
		return 0;
	}

	Vector(const Vector &other):
		array( 0 ),
		_length( 0 ),
		_capacity( 0 )
	{
		if(other._capacity>0)
		{
			expand(other._capacity);
			for( int i = 0; i < other._length; ++i )
			{
				array[i] = other.array[i];
			}
			_length = other._length;
		}
	}

	~Vector()
	{
		delete [] array;
		array=0;
	}
public:
};

template<class T, int size> class Stack
{
	Array<T> stack;
	int _length;
public:
	Stack() 
	: stack(size)
	, _length(0)
	{
	}

	~Stack()
	{
	}

	T &push()
	{
		assert(_length < stack.length());

		return stack[_length++];
	}

	T &pop()
	{
		assert(_length > 0);

		return stack[--_length];
	}

	T &top()
	{
		return stack[_length-1];
	}

	int length()
	{
		return _length;
	}
	
	bool full()
	{
		return stack.capacity()==length();
	}
	
	void clear()
	{
		_length=0;
	}
};

template<class T> class Queue
{
	Array<T> que;
	int _length;
	int _head;
public:
	T &put()
	{
		assert(_length<que.length());

		int i=(_head+_length)%que.length();
		_length++;
		
		return que[i];
	}

	T &get()
	{
		assert(_length>0);

		int i=_head++;
		if(_head==que.length())
			_head=0;
		_length--;
		
		return que[i];
	}

	int length()
	{
		return _length;
	}
	
	bool full()
	{
		return que.capacity()==length();
	}
	
	void clear()
	{
		_length=0;_head=0;
	}

	Queue(int size) 
	: que(size)
	, _length(0)
	, _head(0)
	{
	}

	~Queue()
	{
	}
};

template<class T, int size> class ArrayPool
{
	struct Entry
	{
		int index;
		bool available;
		T t;
	};

	Entry pool[size];
	int count;
public:
	T &element(int index)
	{
		assert(index>=0&&index<size);
		return pool[index].t;
	}

	bool valid(int index)
	{
		return !pool[index].available;
	}

	bool full()
	{
		return count==size;
	}

	int length()
	{
		return count;
	}

	int maximum()
	{
		return size;
	}

	int allocate()
	{
		for(int i=0;i<size;i++)
		{
			if(pool[i].available) 
			{
				pool[i].available=false;
				count++;
				return i;
			}
		}

		assert(!"ArrayPool overflow!");
		return -1;
	}

	void release(int index)
	{
		if(index<0)
			return;

		assert(count>0);
		assert(index<size);
		count--;
		pool[index].available=true;
	}

	ArrayPool():count(0)
	{
		for(int i=0;i<size;i++)
		{
			pool[i].index=i;
			pool[i].available=true;
		}
	}
};

};

#endif
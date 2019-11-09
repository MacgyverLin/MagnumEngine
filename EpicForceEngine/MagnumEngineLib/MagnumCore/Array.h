///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Array_h_
#define _Array_h_

#include "Stage.h"

namespace Magnum
{

/**
* Array class for a bound protected array class
*/
template<class T> class Array
{
	T		*array;
	int		_length;
	int		_capacity;
public:
	typedef int (* Compare)(const void *left, const  void *right);
	
	/**
	* Get the length of the Array. 
	* @return, int, the length of the array
	*/
	inline int length() const
	{
		return _length;
	}

	/**
	* Get the capacity of the Array. Capacity is number array element that is actually allocated.
	* @return, int, the length of the array
	*/
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

	/**
	* Get i-th element of the Array. 
	* @return, int, the length of the array
	*/
	void *get(int i)
	{
		if(!valid(i))
		{
			panic("Array[%d] of length %d index %d out of bounds!",_capacity,_length,i);
			assert( false );
		}

		return (void *)(&array[i]);
	}

	/**
	* Get i-th element of the Array. 
	* @return, T&, the reference at i-th position
	*/
	T &operator[](int i)
	{
		if(!valid(i))
		{
			panic("Array[%d] of length %d index %d out of bounds!",_capacity,_length,i);
			assert( false );
		}
		
		return array[i];
	}

	/**
	* Get i-th element of the Array. 
	* @return, const T&, the const reference at i-th position
	*/
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
	/**
	* Check if the array is full
	* @return, true if length is equal to capacity else return false
	*/
	inline bool full() const
	{
		return _length==capacity();
	}

	/**
	* Clear the array. Reset the Length of Array to zero
	*/
	inline void clear()
	{
		_length=0;
	}

	/**
	* Check if the array is empty
	* @return, true if length is equal to 0 else return false
	*/
	inline bool empty()
	{
		return _length==0;
	}

	/**
	* Check if the index is with the range of array
	* @return, true if i is within the length of the array 
	*/
	inline bool valid(int i) const
	{
		return i<_length&&i>=0;
	}

	/**
	* Get last element of the Array. 
	* @return, T&, the reference of last element
	*/
	T& back()
	{
		return array[_length -1];
	}

	/**
	* Get last element of the Array. 
	* @return, const T&, the const reference of last element
	*/
	const T& back() const
	{
		return array[_length - 1];
	}

	/**
	* insert an element at i-th position of the Array
	* @return, T&, the reference of newly inserted i-th element
	*/
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

	/**
	* This function behave same as back()
	* @see back()
	*/
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

	/**
	* search for an element and return its position index
	* @param, item, the item to be searched
	* @return, int, the index of the item. if item is not found return -1
	*/
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

	/**
	* remove the i-th element from the array
	* @param, index, the index of element
	*/
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

	/**
	* append an element at the end of the array
	* @return, T&, the reference of last element
	*/
	T &push()
	{
		assert(_length<_capacity);
		return array[_length++];
	}

	/**
	* remove an element at the end of the array
	* @return, T&, the reference of last element
	*/
	T &pop()
	{
		assert(_length>0);
		return array[--_length];
	}

	/**
	* truncate the array to length_
	*/
	void truncate(int length_)
	{
		assert(length_<=_capacity);
		_length=length_;
	}

	/**
	* resize the array to length_
	*/
	void resize(int length_)
	{
		assert(length_<=_capacity);
		_length=length_;
	}

	/**
	* sort the array
	* @param method, the Compare method of the array
	*/
	void sort(Compare method)
	{
		if(_length>1)
			qsort(array,_length,sizeof(T),method);
	}

	typedef bool (*Iterate)(int index, T &t);

	/**
	* iterate the array
	* @param cb, the Callback function of the iteration. It will be called for each element in the array
	*/
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

	/**
	* Get the Type
	* @return T*, a null pointer only.
	*/
	T *getType()
	{
		return 0;
	}

	/**
	* Array Constructor.
	* To Construct the Array
	* @param capacity_, the capcity of the array
	* @param length_, the optional parameter, the length of array
	*/
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

	/**
	* Array Destructor.
	* To Destruct Array
	*/
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

/**
* Vector class for a bound protected array class with variable size
*/
template<class T> class Vector
{
	T *array;
	int _length;
	int _capacity;
public:
	typedef int (* Compare)(const void *left, const  void *right);
	
	/**
	* Get the length of the Vector. 
	* @return, int, the length of the Vector
	*/
	inline int length() const
	{
		return _length;
	}

	/**
	* Get the capacity of the Vector. Capacity is number Vector element that is actually allocated.
	* @return, int, the length of the Vector
	*/
	inline int capacity() const
	{
		return _capacity;
	}
#ifndef _DEBUG
	void *get(int i)
	{
		return (void *)(&Vector[i]);
	}

	inline T &operator[](int i)
	{
		return Vector[i];
	}

	inline const T &operator[](int i) const
	{
		return array[i];
	}
#else
	/**
	* Get i-th element of the Vector. 
	* @return, int, the length of the Vector
	*/
	void *get(int i)
	{
		if(!valid(i))
		{
			panic("Array[%d] of length %d index %d out of bounds!",_capacity,_length,i);
			assert( false );
		}

		return (void *)(&array[i]);
	}

	/**
	* Get i-th element of the Vector. 
	* @return, T&, the reference at i-th position
	*/
	T &operator[](int i)
	{
		if(!valid(i))
		{
			panic("Vector[%d] of length %d index %d out of bounds!",_capacity,_length,i);
			assert( false );
		}
		
		return array[i];
	}

	/**
	* Get i-th element of the Vector. 
	* @return, const T&, the const reference at i-th position
	*/
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
	/**
	* Get last element of the Vector. 
	* @return, T&, the reference of last element
	*/
	T& back()
	{
		return array[_length -1];
	}

	/**
	* Get last element of the Vector. 
	* @return, const T&, the const reference of last element
	*/
	const T& back() const
	{
		return array[_length - 1];
	}

	/**
	* Check if the Vector is full
	* @return, true if length is equal to capacity else return false
	*/
	inline bool full() const
	{
		return _length==_capacity;
	}

	/**
	* Clear the Vector. Reset the Length of Vector to zero
	*/
	inline void clear()
	{
		_length=0;
	}

	/**
	* Check if the Vector is empty
	* @return, true if length is equal to 0 else return false
	*/
	inline bool empty() const
	{
		return _length==0;
	}

	/**
	* Check if the index is with the range of Vector
	* @return, true if i is within the length of the Vector 
	*/
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

	/**
	* resize the Vector to length_
	* @param length_, the new length of the Vector
	*/
	inline void resize(int length_)
	{
		assert(length_>=0);
		expand(length_);

		_length=length_;
	}

	/**
	* allocate buffer the Vector to length_. Therefore, both capacity and length_ of Vector will be adjusted
	* @param length_, the new length and new capacity of the Vector
	*/
	void allocate(int length_)
	{
		assert(array==0);
		array=new T[length_];
		_length=_capacity=length_;
	}

	/**
	* expand the Vector's capacity to new_capacity. 
	* @param new_capacity, the new capacity of the Vector
	*/
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

	/**
	* insert an element at i-th position of the Vector
	* @return, T&, the reference of newly inserted i-th element
	*/
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

	/**
	* This function behave same as back()
	* @see back()
	*/
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

	/**
	* search for an element and return its position index
	* @param, item, the item to be searched
	* @return, int, the index of the item. if item is not found return -1
	*/
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

	/**
	* remove the i-th element from the Vector
	* @param, index, the index of element
	*/
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

	/**
	* append an element at the end of the Vector
	* @return, T&, the reference of last element
	*/
	T &push()
	{
		expand(_length+1);
		_length++;

		return array[_length-1];
	}

	/**
	* remove an element at the end of the Vector
	* @return, T&, the reference of last element
	*/
	T &pop()
	{
		assert(_length>0);

		return array[--_length];
	}

	/**
	* sort the Vector
	* @param method, the Compare method of the Vector
	*/
	void sort(Compare method)
	{
		if(_length>1)
			qsort(array,_length,sizeof(T),method);
	}

	/**
	* Vector Constructor.
	* To Construct the Vector
	* @param capacity_, the capcity of the Vector
	* @param length_, the optional parameter, the length of Vector
	*/
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

	/**
	* Vector Destructor.
	* To Destruct Vector
	*/
	T *getType()
	{
		return 0;
	}

	/**
	* Vector Copy Constructor.
	* To Construct the Vector by copying the other Vector
	* @param other, the other Vector to be copied
	*/
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

	/**
	* Vector Destructor.
	* To Destruct Vector
	*/
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
	/**
	* Stack Constructor.
	* To Construct the Stack
	*/
	Stack() 
	: stack(size)
	, _length(0)
	{
	}

	/**
	* Stack Destructor.
	* To Destruct Stack
	*/
	~Stack()
	{
	}

	/**
	* push an element at the top of the Stack
	* @return, T&, the reference of stack top
	*/
	T &push()
	{
		assert(_length < stack.length());

		return stack[_length++];
	}

	/**
	* remove an element from the top of Stack
	* @return, T&, the reference of  top of Stack
	*/
	T &pop()
	{
		assert(_length > 0);

		return stack[--_length];
	}

	/**
	* Get the Stack Top item
	* @return, T&, the reference of Stack Top
	*/
	T &top()
	{
		return stack[_length-1];
	}

	/**
	* Get the size of the Stack
	* @return, int, the size of the Stack
	*/
	int length()
	{
		return _length;
	}
	
	/**
	* Check if the Stack is fulled
	* @return, true if the Stack is full, return alse otherwise
	*/
	bool full()
	{
		return stack.capacity()==length();
	}
	
	/**
	* Clear the Stack. 
	*/
	void clear()
	{
		_length=0;
	}
};
/*
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
*/
/*
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
*/
};

#endif
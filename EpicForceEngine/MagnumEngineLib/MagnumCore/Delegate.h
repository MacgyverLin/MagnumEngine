///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Delegate_h_
#define _Delegate_h_

#include "Stage.h"
#include "List.h"

namespace Magnum
{

//////////////////////////////////////////////////////////////////////////////////////
class Functor;

class Dispatch
{
	Post<Functor> _post;
	Functor *_capture;
	static int compare(const Functor &left, const Functor &right);
public:
	void insert(Functor &functor);
	void remove(Functor &functor);
	void capture(Functor &functor);
	void release();
	void stop();
	void clear();
	bool dispatch(const char *name=0);

	Dispatch();
	~Dispatch();
};

class Functor : public Link<Functor>
{
public:
	const char *name;
	virtual Functor *clone() const = 0;
	virtual void operator()()=0;
	
	void invoke()
	{
		(*this)();
	}
	
	Functor(const char *name_=0)
	: Link<Functor>(*this)
	, name(name_)
	{
	}
	
	virtual ~Functor()
	{
	}
};

template <class T> 
class Delegate : public Functor
{
public:
	typedef void (T::*Proc)();

protected:	
	Proc proc;
	T *who;

public:
	inline bool operator==(const Proc proc_) const
	{
		return proc==proc_;
	}

	inline bool operator!=(const Proc proc_) const
	{
		return proc!=proc_;
	}

	inline Proc &operator=(const Proc proc_)
	{
		return proc=proc_;
	}

	inline operator Proc &()
	{
		return proc;
	}

	Delegate(T *who, Proc proc=0)
	: Functor(0)
	, who(who)
	, proc(proc)
	{
	}

	Delegate(const char *name, T *who, Proc proc=0)
	: Functor(name)
	, who(who)
	, proc(proc)
	{
	}

	Delegate(Dispatch &dispatch, T *who, Proc proc)
	: Functor(0)
	, who(who)
	, proc(proc)
	{
		dispatch.insert(*this);
	}

	Delegate(Dispatch &dispatch, const char *name, T *who, Proc proc)
	: Functor(name)
	, who(who)
	, proc(proc)
	{
		dispatch.insert(*this);
	}

	Delegate<T> *clone() const
	{
		return new Delegate<T>(*this);
	}

	void operator()()
	{
		assert(who);
		if(proc)
			(*who.*proc)();
	}

	virtual ~Delegate()
	{
	}
};

//////////////////////////////////////////////////////////////////////////////////////
template <typename P1>
class Functor1 : public Link<Functor1<P1> >
{
public:
	virtual Functor1<P1> *clone() const = 0;
	virtual void invoke(const P1 &v1) = 0;
};

template <typename U, typename P1>
class Delegate1 : public Functor1<P1>
{
	typedef void (U::*MemFunc)(const P1 &);

	U *who;
	MemFunc func;
public:
	Delegate1(U *who, MemFunc func)
	: who(who)
	, func(func)
	{
		assert(who);
	}
	
	bool operator==(const MemFunc func_) const
	{
		return func == func_;
	}

	bool operator!=(const MemFunc func_) const
	{
		return func != func_;
	}

	Delegate1<U, P1> *clone() const
	{
		return new Delegate1<U, P1>(*this);
	}

	void operator=(const MemFunc func_)
	{
		func = func_;
	}

	virtual void invoke(const P1 &v1)
	{
		assert(who);
		if(func)
			(who->*func)(v1);
	}
};

//////////////////////////////////////////////////////////////////////////////////////
template <typename P1, typename P2>
class Functor2 : public Link<Functor2<P1, P2> >
{
public:
	virtual Functor2<P1, P2> *clone() const = 0;
	virtual void invoke(const P1 &v1, const P2 &v2) = 0;
};

template <typename U, typename P1, typename P2>
class Delegate2 : public Functor2<P1, P2>
{
	typedef void (U::*MemFunc)(const P1 &, const P2 &);

	U *who;
	MemFunc func;
public:
	Delegate2(U *who, MemFunc func)
	: who(who)
	, func(func)
	{
		assert(who);
	}
	
	bool operator==(const MemFunc func_) const
	{
		return func == func_;
	}

	bool operator!=(const MemFunc func_) const
	{
		return func != func_;
	}

	Delegate2<U, P1, P2> *clone() const
	{
		return new Delegate2<U, P1, P2>(*this);
	}

	void operator=(const MemFunc func_)
	{
		func = func_;
	}

	virtual void invoke(const P1 &p1, const P2 &p2)
	{
		assert(who);
		if(func)
			(who->*func)(p1, p2);
	}
};

//////////////////////////////////////////////////////////////////////////////////////
template <typename P1, typename P2, typename P3>
class Functor3 : public Link<Functor3<P1, P2, P3> >
{
public:
	virtual Functor3<P1, P2, P3> *clone() const = 0;
	virtual void invoke(const P1 &v1, const P2 &v2, const P3 &v3) = 0;
};

template <typename U, typename P1, typename P2, typename P3>
class Delegate3 : public Functor3<P1, P2, P3>
{
	typedef void (U::*MemFunc)(const P1 &, const P2 &, const P3 &);

	U *who;
	MemFunc func;
public:
	Delegate3(U *who, MemFunc func)
	: who(who)
	, func(func)
	{
		assert(who);
	}
	
	bool operator==(const MemFunc func_) const
	{
		return func == func_;
	}

	bool operator!=(const MemFunc func_) const
	{
		return func != func_;
	}

	Delegate3<U, P1, P2, P3> *clone() const
	{
		return new Delegate3<U, P1, P2, P3>(*this);
	}

	void operator=(const MemFunc func_)
	{
		func = func_;
	}

	virtual void invoke(const P1 &p1, const P2 &p2, const P3 &p3)
	{
		assert(who);
		if(func)
			(who->*func)(p1, p2, p3);
	}
};

//////////////////////////////////////////////////////////////////////////////////////
template <typename P1, typename P2, typename P3, typename P4>
class Functor4 : public Link<Functor4<P1, P2, P3, P4> >
{
public:
	virtual Functor4<P1, P2, P3, P4> *clone() const = 0;
	virtual void invoke(const P1 &v1, const P2 &v2, const P3 &v3, const P4 &v4) = 0;
};

template <typename U, typename P1, typename P2, typename P3, typename P4>
class Delegate4 : public Functor4<P1, P2, P3, P4>
{
	typedef void (U::*MemFunc)(const P1 &, const P2 &, const P3 &, const P4 &);

	U *who;
	MemFunc func;
public:
	Delegate4(U *who, MemFunc func)
	: who(who)
	, func(func)
	{
		assert(who);
	}
	
	bool operator==(const MemFunc func_) const
	{
		return func == func_;
	}

	bool operator!=(const MemFunc func_) const
	{
		return func != func_;
	}

	Delegate4<U, P1, P2, P3, P4> *clone() const
	{
		return new Delegate4<U, P1, P2, P3, P4>(*this);
	}

	void operator=(const MemFunc func_)
	{
		func = func_;
	}

	virtual void invoke(const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4)
	{
		assert(who);
		if(func)
			(who->*func)(p1, p2, p3, p4);
	}
};

//////////////////////////////////////////////////////////////////////////////////////
template <typename P1, typename P2, typename P3, typename P4, typename P5>
class Functor5 : public Link<Functor5<P1, P2, P3, P4, P5> >
{
public:
	virtual Functor5<P1, P2, P3, P4, P5> *clone() const = 0;
	virtual void invoke(const P1 &v1, const P2 &v2, const P3 &v3, const P4 &v4, const P5 &v5) = 0;
};

template <typename U, typename P1, typename P2, typename P3, typename P4, typename P5>
class Delegate5 : public Functor5<P1, P2, P3, P4, P5>
{
	typedef void (U::*MemFunc)(const P1 &, const P2 &, const P3 &, const P4 &, const P5 &);

	U *who;
	MemFunc func;
public:
	Delegate5(U *who, MemFunc func)
	: who(who)
	, func(func)
	{
		assert(who);
	}
	
	bool operator==(const MemFunc func_) const
	{
		return func == func_;
	}

	bool operator!=(const MemFunc func_) const
	{
		return func != func_;
	}

	Delegate5<U, P1, P2, P3, P4, P5> *clone() const
	{
		return new Delegate5<U, P1, P2, P3, P4, P5>(*this);
	}

	void operator=(const MemFunc func_)
	{
		func = func_;
	}

	virtual void invoke(const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5)
	{
		assert(who);
		if(func)
			(who->*func)(p1, p2, p3, p4, p5);
	}
};

};

#endif
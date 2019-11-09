/*
    AGM::LibReflection is a C++ reflection library.
    Version 0.8.
    Copyright (C) 2004 Achilleas Margaritis

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


#ifndef _Reflection_h
#define _Reflection_h


#pragma warning (disable: 4786)
#pragma warning (disable: 4003)

#include "ClassIndexMap.h"
#include <map>
#include <list>
#include <vector>
#include <string>
#include <typeinfo>
#include <iostream>
#include <stdexcept>
using namespace Magnum;

//repeaters
#define __REPEAT0(M)
#define __REPEAT1(M)         , M(1)
#define __REPEAT2(M)         __REPEAT1(M)  , M(2)
#define __REPEAT3(M)         __REPEAT2(M)  , M(3)
#define __REPEAT4(M)         __REPEAT3(M)  , M(4)
#define __REPEAT5(M)         __REPEAT4(M)  , M(5)
#define __REPEAT6(M)         __REPEAT5(M)  , M(6)
#define __REPEAT7(M)         __REPEAT6(M)  , M(7)
#define __REPEAT8(M)         __REPEAT7(M)  , M(8)
#define __REPEAT9(M)         __REPEAT8(M)  , M(9)
#define __REPEAT10(M)        __REPEAT9(M)  , M(10)
#define __REPEAT11(M)        __REPEAT10(M) , M(11)
#define __REPEAT12(M)        __REPEAT11(M) , M(12)
#define __REPEAT13(M)        __REPEAT12(M) , M(13)
#define __REPEAT14(M)        __REPEAT13(M) , M(14)
#define __REPEAT15(M)        __REPEAT14(M) , M(15)
#define __REPEAT16(M)        __REPEAT15(M) , M(16)
#define __REPEAT17(M)        __REPEAT16(M) , M(17)
#define __REPEAT18(M)        __REPEAT17(M) , M(18)
#define __REPEAT19(M)        __REPEAT18(M) , M(19)
#define __REPEAT20(M)        __REPEAT19(M) , M(20)
#define __REPEAT(N, M)       __REPEAT##N(M)

//repeaters nothing
#define __NREPEAT0(M)
#define __NREPEAT1(M)         M(1)
#define __NREPEAT2(M)         __NREPEAT1(M)  , M(2)
#define __NREPEAT3(M)         __NREPEAT2(M)  , M(3)
#define __NREPEAT4(M)         __NREPEAT3(M)  , M(4)
#define __NREPEAT5(M)         __NREPEAT4(M)  , M(5)
#define __NREPEAT6(M)         __NREPEAT5(M)  , M(6)
#define __NREPEAT7(M)         __NREPEAT6(M)  , M(7)
#define __NREPEAT8(M)         __NREPEAT7(M)  , M(8)
#define __NREPEAT9(M)         __NREPEAT8(M)  , M(9)
#define __NREPEAT10(M)        __NREPEAT9(M)  , M(10)
#define __NREPEAT11(M)        __NREPEAT10(M) , M(11)
#define __NREPEAT12(M)        __NREPEAT11(M) , M(12)
#define __NREPEAT13(M)        __NREPEAT12(M) , M(13)
#define __NREPEAT14(M)        __NREPEAT13(M) , M(14)
#define __NREPEAT15(M)        __NREPEAT14(M) , M(15)
#define __NREPEAT16(M)        __NREPEAT15(M) , M(16)
#define __NREPEAT17(M)        __NREPEAT16(M) , M(17)
#define __NREPEAT18(M)        __NREPEAT17(M) , M(18)
#define __NREPEAT19(M)        __NREPEAT18(M) , M(19)
#define __NREPEAT20(M)        __NREPEAT19(M) , M(20)
#define __NREPEAT(N, M)       __NREPEAT##N(M)

//various defs needed for parameters
#define __MAX_PARAMS__       20
#define __NOTHING__          
#define __COMMA__            ,
#define __TEMPLATE_ARG__(N)  class T##N
#define __TYPE_ARG__(N)      T##N 
#define __ARG__(N)           T##N t##N
#define __PARAM__(N)         t##N
#define __NOT_VIRTUAL__


//calculates the offset of a field
#define __OFFSET__(C, M)\
    ((unsigned long)(&((const C *)0)->M))

namespace agm { namespace reflection {


//root of all callables
struct __callable__ {
    virtual ~__callable__() {
    }
};


//callable class macro with return type
#define __CALLABLE__(N)\
template <class R, class C __REPEAT(N, __TEMPLATE_ARG__)> struct __callable##N##__ : public __callable__ {\
    typedef R (C::*MethodType)(__NREPEAT(N, __TYPE_ARG__));\
    MethodType method;\
    __callable##N##__(MethodType m) : method(m) {\
    }\
    R invoke(C *object __REPEAT(N, __ARG__)) const {\
        return (object->*method)(__NREPEAT(N, __PARAM__));\
    }\
};


//callable class macro with return type and const type
#define __CALLABLE_CONST__(N)\
template <class R, class C __REPEAT(N, __TEMPLATE_ARG__)> struct __callable_const##N##__ : public __callable__ {\
    typedef R (C::*MethodType)(__NREPEAT(N, __TYPE_ARG__)) const;\
    MethodType method;\
    __callable_const##N##__(MethodType m) : method(m) {\
    }\
    R invoke(C *object __REPEAT(N, __ARG__)) const {\
        return (object->*method)(__NREPEAT(N, __PARAM__));\
    }\
};


//callable class macro with void return type
#define __CALLABLE_VOID__(N)\
template <class C __REPEAT(N, __TEMPLATE_ARG__)> struct __callable_void##N##__ : public __callable__ {\
    typedef void (C::*MethodType)(__NREPEAT(N, __TYPE_ARG__));\
    MethodType method;\
    __callable_void##N##__(MethodType m) : method(m) {\
    }\
    void invoke(C *object __REPEAT(N, __ARG__)) const {\
        (object->*method)(__NREPEAT(N, __PARAM__));\
    }\
};


//callable class macro with void return type and const type
#define __CALLABLE_CONST_VOID__(N)\
template <class C __REPEAT(N, __TEMPLATE_ARG__)> struct __callable_const_void##N##__ : public __callable__ {\
    typedef void (C::*MethodType)(__NREPEAT(N, __TYPE_ARG__)) const;\
    MethodType method;\
    __callable_const_void##N##__(MethodType m) : method(m) {\
    }\
    void invoke(C *object __REPEAT(N, __ARG__)) const {\
        (object->*method)(__NREPEAT(N, __PARAM__));\
    }\
};


//static callable class macro with return type
#define __STATIC_CALLABLE__(N)\
template <class R __REPEAT(N, __TEMPLATE_ARG__)> struct __static_callable##N##__ : public __callable__ {\
    typedef R (*MethodType)(__NREPEAT(N, __TYPE_ARG__));\
    MethodType method;\
    __static_callable##N##__(MethodType m) : method(m) {\
    }\
    R invoke(__NREPEAT(N, __ARG__)) const {\
        return (*method)(__NREPEAT(N, __PARAM__));\
    }\
};


//void version for 0 params
struct __static_callable_void0__ : public __callable__ {
    typedef void (*MethodType)();
    MethodType method;
    __static_callable_void0__(MethodType m) : method(m) {
    }
    void invoke() const {
        (*method)();
    }
};


//void version
#define __STATIC_CALLABLE_VOID__(N)\
template <__NREPEAT(N, __TEMPLATE_ARG__)> struct __static_callable_void##N##__ : public __callable__ {\
    typedef void (*MethodType)(__NREPEAT(N, __TYPE_ARG__));\
    MethodType method;\
    __static_callable_void##N##__(MethodType m) : method(m) {\
    }\
    void invoke(__NREPEAT(N, __ARG__)) const {\
        (*method)(__NREPEAT(N, __PARAM__));\
    }\
};


//define callables
__CALLABLE__(0);
__CALLABLE__(1);
__CALLABLE__(2);
__CALLABLE__(3);
__CALLABLE__(4);
__CALLABLE__(5);
__CALLABLE__(6);
__CALLABLE__(7);
__CALLABLE__(8);
__CALLABLE__(9);
__CALLABLE__(10);
__CALLABLE__(11);
__CALLABLE__(12);
__CALLABLE__(13);
__CALLABLE__(14);
__CALLABLE__(15);
__CALLABLE__(16);
__CALLABLE__(17);
__CALLABLE__(18);
__CALLABLE__(19);
__CALLABLE__(20);


//define const callables
__CALLABLE_CONST__(0);
__CALLABLE_CONST__(1);
__CALLABLE_CONST__(2);
__CALLABLE_CONST__(3);
__CALLABLE_CONST__(4);
__CALLABLE_CONST__(5);
__CALLABLE_CONST__(6);
__CALLABLE_CONST__(7);
__CALLABLE_CONST__(8);
__CALLABLE_CONST__(9);
__CALLABLE_CONST__(10);
__CALLABLE_CONST__(11);
__CALLABLE_CONST__(12);
__CALLABLE_CONST__(13);
__CALLABLE_CONST__(14);
__CALLABLE_CONST__(15);
__CALLABLE_CONST__(16);
__CALLABLE_CONST__(17);
__CALLABLE_CONST__(18);
__CALLABLE_CONST__(19);
__CALLABLE_CONST__(20);


//define void callables
__CALLABLE_VOID__(0);
__CALLABLE_VOID__(1);
__CALLABLE_VOID__(2);
__CALLABLE_VOID__(3);
__CALLABLE_VOID__(4);
__CALLABLE_VOID__(5);
__CALLABLE_VOID__(6);
__CALLABLE_VOID__(7);
__CALLABLE_VOID__(8);
__CALLABLE_VOID__(9);
__CALLABLE_VOID__(10);
__CALLABLE_VOID__(11);
__CALLABLE_VOID__(12);
__CALLABLE_VOID__(13);
__CALLABLE_VOID__(14);
__CALLABLE_VOID__(15);
__CALLABLE_VOID__(16);
__CALLABLE_VOID__(17);
__CALLABLE_VOID__(18);
__CALLABLE_VOID__(19);
__CALLABLE_VOID__(20);


//define const void callables
__CALLABLE_CONST_VOID__(0);
__CALLABLE_CONST_VOID__(1);
__CALLABLE_CONST_VOID__(2);
__CALLABLE_CONST_VOID__(3);
__CALLABLE_CONST_VOID__(4);
__CALLABLE_CONST_VOID__(5);
__CALLABLE_CONST_VOID__(6);
__CALLABLE_CONST_VOID__(7);
__CALLABLE_CONST_VOID__(8);
__CALLABLE_CONST_VOID__(9);
__CALLABLE_CONST_VOID__(10);
__CALLABLE_CONST_VOID__(11);
__CALLABLE_CONST_VOID__(12);
__CALLABLE_CONST_VOID__(13);
__CALLABLE_CONST_VOID__(14);
__CALLABLE_CONST_VOID__(15);
__CALLABLE_CONST_VOID__(16);
__CALLABLE_CONST_VOID__(17);
__CALLABLE_CONST_VOID__(18);
__CALLABLE_CONST_VOID__(19);
__CALLABLE_CONST_VOID__(20);


//static callable classes
__STATIC_CALLABLE__(0)
__STATIC_CALLABLE__(1)
__STATIC_CALLABLE__(2)
__STATIC_CALLABLE__(3)
__STATIC_CALLABLE__(4)
__STATIC_CALLABLE__(5)
__STATIC_CALLABLE__(6)
__STATIC_CALLABLE__(7)
__STATIC_CALLABLE__(8)
__STATIC_CALLABLE__(9)
__STATIC_CALLABLE__(10)
__STATIC_CALLABLE__(11)
__STATIC_CALLABLE__(12)
__STATIC_CALLABLE__(13)
__STATIC_CALLABLE__(14)
__STATIC_CALLABLE__(15)
__STATIC_CALLABLE__(16)
__STATIC_CALLABLE__(17)
__STATIC_CALLABLE__(18)
__STATIC_CALLABLE__(19)
__STATIC_CALLABLE__(20)
__STATIC_CALLABLE_VOID__(1)
__STATIC_CALLABLE_VOID__(2)
__STATIC_CALLABLE_VOID__(3)
__STATIC_CALLABLE_VOID__(4)
__STATIC_CALLABLE_VOID__(5)
__STATIC_CALLABLE_VOID__(6)
__STATIC_CALLABLE_VOID__(7)
__STATIC_CALLABLE_VOID__(8)
__STATIC_CALLABLE_VOID__(9)
__STATIC_CALLABLE_VOID__(10)
__STATIC_CALLABLE_VOID__(11)
__STATIC_CALLABLE_VOID__(12)
__STATIC_CALLABLE_VOID__(13)
__STATIC_CALLABLE_VOID__(14)
__STATIC_CALLABLE_VOID__(15)
__STATIC_CALLABLE_VOID__(16)
__STATIC_CALLABLE_VOID__(17)
__STATIC_CALLABLE_VOID__(18)
__STATIC_CALLABLE_VOID__(19)
__STATIC_CALLABLE_VOID__(20)


//macro of a inline method that accepts a method pointer and creates a callable for it
#define __CREATE_CALLABLE__(N)\
    template <class C __REPEAT(N, __TEMPLATE_ARG__)> static inline __callable##N##__<R, C __REPEAT(N, __TYPE_ARG__)> *create(R (C::*method)(__NREPEAT(N, __TYPE_ARG__))) {\
        return new __callable##N##__<R, C __REPEAT(N, __TYPE_ARG__)>(method);\
    }


//macro of a inline method that accepts a method pointer and creates a const callable for it
#define __CREATE_CALLABLE_CONST__(N)\
    template <class C __REPEAT(N, __TEMPLATE_ARG__)> static inline __callable_const##N##__<R, C __REPEAT(N, __TYPE_ARG__)> *create(R (C::*method)(__NREPEAT(N, __TYPE_ARG__)) const) {\
        return new __callable_const##N##__<R, C __REPEAT(N, __TYPE_ARG__)>(method);\
    }


//void version
#define __CREATE_CALLABLE_VOID__(N)\
    template <class C __REPEAT(N, __TEMPLATE_ARG__)> static inline __callable_void##N##__<C __REPEAT(N, __TYPE_ARG__)> *create(void (C::*method)(__NREPEAT(N, __TYPE_ARG__))) {\
        return new __callable_void##N##__<C __REPEAT(N, __TYPE_ARG__)>(method);\
    }


//const void version
#define __CREATE_CALLABLE_CONST_VOID__(N)\
    template <class C __REPEAT(N, __TEMPLATE_ARG__)> static inline __callable_const_void##N##__<C __REPEAT(N, __TYPE_ARG__)> *create(void (C::*method)(__NREPEAT(N, __TYPE_ARG__)) const) {\
        return new __callable_const_void##N##__<C __REPEAT(N, __TYPE_ARG__)>(method);\
    }


//macro to create a static callable
#define __CREATE_STATIC_CALLABLE__(N)\
    template <class C __REPEAT(N, __TEMPLATE_ARG__)> static inline __static_callable##N##__<C __REPEAT(N, __TYPE_ARG__)> *create(C (*method)(__NREPEAT(N, __TYPE_ARG__))) {\
        return new __static_callable##N##__<R __REPEAT(N, __TYPE_ARG__)>(method);\
    }


//void version for 0 params
#define __CREATE_STATIC_CALLABLE_VOID__0\
    static inline __static_callable_void0__ *create(void (*method)()) {\
        return new __static_callable_void0__(method);\
    }


//void version
#define __CREATE_STATIC_CALLABLE_VOID__(N)\
    template <__NREPEAT(N, __TEMPLATE_ARG__)> static inline __static_callable_void##N##__<__NREPEAT(N, __TYPE_ARG__)> *create(void (*method)(__NREPEAT(N, __TYPE_ARG__))) {\
        return new __static_callable_void##N##__<__NREPEAT(N, __TYPE_ARG__)>(method);\
    }


//factory method for non-voids
template <class R> struct __callable_factory__ {
    __CREATE_CALLABLE__(0)
    __CREATE_CALLABLE__(1)
    __CREATE_CALLABLE__(2)
    __CREATE_CALLABLE__(3)
    __CREATE_CALLABLE__(4)
    __CREATE_CALLABLE__(5)
    __CREATE_CALLABLE__(6)
    __CREATE_CALLABLE__(7)
    __CREATE_CALLABLE__(8)
    __CREATE_CALLABLE__(9)
    __CREATE_CALLABLE__(10)
    __CREATE_CALLABLE__(11)
    __CREATE_CALLABLE__(12)
    __CREATE_CALLABLE__(13)
    __CREATE_CALLABLE__(14)
    __CREATE_CALLABLE__(15)
    __CREATE_CALLABLE__(16)
    __CREATE_CALLABLE__(17)
    __CREATE_CALLABLE__(18)
    __CREATE_CALLABLE__(19)
    __CREATE_CALLABLE__(20)
    __CREATE_CALLABLE_CONST__(0)
    __CREATE_CALLABLE_CONST__(1)
    __CREATE_CALLABLE_CONST__(2)
    __CREATE_CALLABLE_CONST__(3)
    __CREATE_CALLABLE_CONST__(4)
    __CREATE_CALLABLE_CONST__(5)
    __CREATE_CALLABLE_CONST__(6)
    __CREATE_CALLABLE_CONST__(7)
    __CREATE_CALLABLE_CONST__(8)
    __CREATE_CALLABLE_CONST__(9)
    __CREATE_CALLABLE_CONST__(10)
    __CREATE_CALLABLE_CONST__(11)
    __CREATE_CALLABLE_CONST__(12)
    __CREATE_CALLABLE_CONST__(13)
    __CREATE_CALLABLE_CONST__(14)
    __CREATE_CALLABLE_CONST__(15)
    __CREATE_CALLABLE_CONST__(16)
    __CREATE_CALLABLE_CONST__(17)
    __CREATE_CALLABLE_CONST__(18)
    __CREATE_CALLABLE_CONST__(19)
    __CREATE_CALLABLE_CONST__(20)
};


//factory method for non-voids
template <> struct __callable_factory__<void> {
    __CREATE_CALLABLE_VOID__(0)
    __CREATE_CALLABLE_VOID__(1)
    __CREATE_CALLABLE_VOID__(2)
    __CREATE_CALLABLE_VOID__(3)
    __CREATE_CALLABLE_VOID__(4)
    __CREATE_CALLABLE_VOID__(5)
    __CREATE_CALLABLE_VOID__(6)
    __CREATE_CALLABLE_VOID__(7)
    __CREATE_CALLABLE_VOID__(8)
    __CREATE_CALLABLE_VOID__(9)
    __CREATE_CALLABLE_VOID__(10)
    __CREATE_CALLABLE_VOID__(11)
    __CREATE_CALLABLE_VOID__(12)
    __CREATE_CALLABLE_VOID__(13)
    __CREATE_CALLABLE_VOID__(14)
    __CREATE_CALLABLE_VOID__(15)
    __CREATE_CALLABLE_VOID__(16)
    __CREATE_CALLABLE_VOID__(17)
    __CREATE_CALLABLE_VOID__(18)
    __CREATE_CALLABLE_VOID__(19)
    __CREATE_CALLABLE_VOID__(20)
    __CREATE_CALLABLE_CONST_VOID__(0)
    __CREATE_CALLABLE_CONST_VOID__(1)
    __CREATE_CALLABLE_CONST_VOID__(2)
    __CREATE_CALLABLE_CONST_VOID__(3)
    __CREATE_CALLABLE_CONST_VOID__(4)
    __CREATE_CALLABLE_CONST_VOID__(5)
    __CREATE_CALLABLE_CONST_VOID__(6)
    __CREATE_CALLABLE_CONST_VOID__(7)
    __CREATE_CALLABLE_CONST_VOID__(8)
    __CREATE_CALLABLE_CONST_VOID__(9)
    __CREATE_CALLABLE_CONST_VOID__(10)
    __CREATE_CALLABLE_CONST_VOID__(11)
    __CREATE_CALLABLE_CONST_VOID__(12)
    __CREATE_CALLABLE_CONST_VOID__(13)
    __CREATE_CALLABLE_CONST_VOID__(14)
    __CREATE_CALLABLE_CONST_VOID__(15)
    __CREATE_CALLABLE_CONST_VOID__(16)
    __CREATE_CALLABLE_CONST_VOID__(17)
    __CREATE_CALLABLE_CONST_VOID__(18)
    __CREATE_CALLABLE_CONST_VOID__(19)
    __CREATE_CALLABLE_CONST_VOID__(20)
};


//factory method for static non-voids
template <class R> struct __static_callable_factory__ {
    __CREATE_STATIC_CALLABLE__(0)
    __CREATE_STATIC_CALLABLE__(1)
    __CREATE_STATIC_CALLABLE__(2)
    __CREATE_STATIC_CALLABLE__(3)
    __CREATE_STATIC_CALLABLE__(4)
    __CREATE_STATIC_CALLABLE__(5)
    __CREATE_STATIC_CALLABLE__(6)
    __CREATE_STATIC_CALLABLE__(7)
    __CREATE_STATIC_CALLABLE__(8)
    __CREATE_STATIC_CALLABLE__(9)
    __CREATE_STATIC_CALLABLE__(10)
    __CREATE_STATIC_CALLABLE__(11)
    __CREATE_STATIC_CALLABLE__(12)
    __CREATE_STATIC_CALLABLE__(13)
    __CREATE_STATIC_CALLABLE__(14)
    __CREATE_STATIC_CALLABLE__(15)
    __CREATE_STATIC_CALLABLE__(16)
    __CREATE_STATIC_CALLABLE__(17)
    __CREATE_STATIC_CALLABLE__(18)
    __CREATE_STATIC_CALLABLE__(19)
    __CREATE_STATIC_CALLABLE__(20)
};


//factory method for static voids
template <> struct __static_callable_factory__<void> {
    __CREATE_STATIC_CALLABLE_VOID__0
    __CREATE_STATIC_CALLABLE_VOID__(1)
    __CREATE_STATIC_CALLABLE_VOID__(2)
    __CREATE_STATIC_CALLABLE_VOID__(3)
    __CREATE_STATIC_CALLABLE_VOID__(4)
    __CREATE_STATIC_CALLABLE_VOID__(5)
    __CREATE_STATIC_CALLABLE_VOID__(6)
    __CREATE_STATIC_CALLABLE_VOID__(7)
    __CREATE_STATIC_CALLABLE_VOID__(8)
    __CREATE_STATIC_CALLABLE_VOID__(9)
    __CREATE_STATIC_CALLABLE_VOID__(10)
    __CREATE_STATIC_CALLABLE_VOID__(11)
    __CREATE_STATIC_CALLABLE_VOID__(12)
    __CREATE_STATIC_CALLABLE_VOID__(13)
    __CREATE_STATIC_CALLABLE_VOID__(14)
    __CREATE_STATIC_CALLABLE_VOID__(15)
    __CREATE_STATIC_CALLABLE_VOID__(16)
    __CREATE_STATIC_CALLABLE_VOID__(17)
    __CREATE_STATIC_CALLABLE_VOID__(18)
    __CREATE_STATIC_CALLABLE_VOID__(19)
    __CREATE_STATIC_CALLABLE_VOID__(20)
};


//callable generator
#define __CALLABLE_GENERATOR__(N)\
    template <class R, class C __REPEAT(N, __TEMPLATE_ARG__)> inline __callable__ *__create_callable__(R (C::*method)(__NREPEAT(N, __TYPE_ARG__))) {\
        return __callable_factory__<R>::create(method);\
    }


//const callable generator
#define __CALLABLE_GENERATOR_CONST__(N)\
    template <class R, class C __REPEAT(N, __TEMPLATE_ARG__)> inline __callable__ *__create_callable__(R (C::*method)(__NREPEAT(N, __TYPE_ARG__)) const) {\
        return __callable_factory__<R>::create(method);\
    }


//static callable generator
#define __STATIC_CALLABLE_GENERATOR__(N)\
    template <class R __REPEAT(N, __TEMPLATE_ARG__)> inline __callable__ *__create_static_callable__(R (*method)(__NREPEAT(N, __TYPE_ARG__))) {\
        return __static_callable_factory__<R>::create(method);\
    }


//generators
__CALLABLE_GENERATOR__(0)
__CALLABLE_GENERATOR__(1)
__CALLABLE_GENERATOR__(2)
__CALLABLE_GENERATOR__(3)
__CALLABLE_GENERATOR__(4)
__CALLABLE_GENERATOR__(5)
__CALLABLE_GENERATOR__(6)
__CALLABLE_GENERATOR__(7)
__CALLABLE_GENERATOR__(8)
__CALLABLE_GENERATOR__(9)
__CALLABLE_GENERATOR__(10)
__CALLABLE_GENERATOR__(11)
__CALLABLE_GENERATOR__(12)
__CALLABLE_GENERATOR__(13)
__CALLABLE_GENERATOR__(14)
__CALLABLE_GENERATOR__(15)
__CALLABLE_GENERATOR__(16)
__CALLABLE_GENERATOR__(17)
__CALLABLE_GENERATOR__(18)
__CALLABLE_GENERATOR__(19)
__CALLABLE_GENERATOR__(20)
__CALLABLE_GENERATOR_CONST__(0)
__CALLABLE_GENERATOR_CONST__(1)
__CALLABLE_GENERATOR_CONST__(2)
__CALLABLE_GENERATOR_CONST__(3)
__CALLABLE_GENERATOR_CONST__(4)
__CALLABLE_GENERATOR_CONST__(5)
__CALLABLE_GENERATOR_CONST__(6)
__CALLABLE_GENERATOR_CONST__(7)
__CALLABLE_GENERATOR_CONST__(8)
__CALLABLE_GENERATOR_CONST__(9)
__CALLABLE_GENERATOR_CONST__(10)
__CALLABLE_GENERATOR_CONST__(11)
__CALLABLE_GENERATOR_CONST__(12)
__CALLABLE_GENERATOR_CONST__(13)
__CALLABLE_GENERATOR_CONST__(14)
__CALLABLE_GENERATOR_CONST__(15)
__CALLABLE_GENERATOR_CONST__(16)
__CALLABLE_GENERATOR_CONST__(17)
__CALLABLE_GENERATOR_CONST__(18)
__CALLABLE_GENERATOR_CONST__(19)
__CALLABLE_GENERATOR_CONST__(20)
__STATIC_CALLABLE_GENERATOR__(0)
__STATIC_CALLABLE_GENERATOR__(1)
__STATIC_CALLABLE_GENERATOR__(2)
__STATIC_CALLABLE_GENERATOR__(3)
__STATIC_CALLABLE_GENERATOR__(4)
__STATIC_CALLABLE_GENERATOR__(5)
__STATIC_CALLABLE_GENERATOR__(6)
__STATIC_CALLABLE_GENERATOR__(7)
__STATIC_CALLABLE_GENERATOR__(8)
__STATIC_CALLABLE_GENERATOR__(9)
__STATIC_CALLABLE_GENERATOR__(10)
__STATIC_CALLABLE_GENERATOR__(11)
__STATIC_CALLABLE_GENERATOR__(12)
__STATIC_CALLABLE_GENERATOR__(13)
__STATIC_CALLABLE_GENERATOR__(14)
__STATIC_CALLABLE_GENERATOR__(15)
__STATIC_CALLABLE_GENERATOR__(16)
__STATIC_CALLABLE_GENERATOR__(17)
__STATIC_CALLABLE_GENERATOR__(18)
__STATIC_CALLABLE_GENERATOR__(19)
__STATIC_CALLABLE_GENERATOR__(20)


//property handler base
struct __property_base__ {
    virtual ~__property_base__() {
    }
};


//property handler
template <class T> struct __property_handler__ : public __property_base__ {
    //get
    virtual T get(const void *object) const = 0;

    //set
    virtual void set(void *object, T value) const = 0;
};


//property handler class
template <class C, class T> struct __property__ : public __property_handler__<T> {
    //type of getters/setters
    typedef T (C::*Getter)() const;
    typedef void (C::*Setter)(T);

    //pointer to member getters/setters
    Getter getter;
    Setter setter;

    //default constructor
    __property__(Getter g, Setter s) : getter(g), setter(s) {
    }

    //get
    virtual T get(const void *object) const {
        const C *o = (const C *)(object);
        return (o->*getter)();
    }

    //set
    virtual void set(void *object, T value) const {
        C *o = (C *)(object);
        (o->*setter)(value);
    }
};


//declares a method
#define __METHOD__(ACCESS_ATTR, VIRTUAL, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)\
private:\
    struct __method_##METHOD_NAME##__ {\
        __method_##METHOD_NAME##__() {\
            static agm::reflection::__register_method__ reg(__create_callable__(&ClassType::METHOD_NAME), getClassDescStaticPtr(), ACCESS_##ACCESS_ATTR, #RETURN_TYPE, #METHOD_NAME, #METHOD_ARGS, #VIRTUAL);\
        }\
    } __method_##METHOD_NAME##__;\
    friend struct __method_##METHOD_NAME##__;\
ACCESS_ATTR :\
    VIRTUAL RETURN_TYPE METHOD_NAME METHOD_ARGS

#if 0
//macro that defines an 'invoke' method with a return type
#define __INVOKE__(N)\
    template <class R, class C __REPEAT(N, __TEMPLATE_ARG__)> void invoke(R &result, C *object __REPEAT(N, __ARG__)) const {\
        if (m_access != ACCESS_PUBLIC) throw IllegalAccessError(m_name);\
        typedef const __callable##N##__<R, C __REPEAT(N, __TYPE_ARG__)> CallableType1;\
        typedef const __callable_const##N##__<R, C __REPEAT(N, __TYPE_ARG__)> CallableType2;\
        CallableType1 *cb1 = reinterpret_cast<CallableType1 *>(m_callable);\
        if (cb1) {\
            result = cb1->invoke(object __REPEAT(N, __PARAM__));\
            return;\
        }\
        CallableType2 *cb2 = dynamic_cast<CallableType2 *>(m_callable);\
        if (cb2){\
            result = cb2->invoke(object __REPEAT(N, __PARAM__));\
            return;\
        }\
        throw TypeMismatchError(m_name);\
    }

//macro that defines an 'invoke' method without a return type
#define __INVOKE_VOID__(N)\
    template <class C __REPEAT(N, __TEMPLATE_ARG__)> void invokeVoid(C *object __REPEAT(N, __ARG__)) const {\
        if (m_access != ACCESS_PUBLIC) throw IllegalAccessError(m_name);\
        typedef const __callable_void##N##__<C __REPEAT(N, __TYPE_ARG__)> CallableType1;\
        typedef const __callable_const_void##N##__<C __REPEAT(N, __TYPE_ARG__)> CallableType2;\
        CallableType1 *cb1 = dynamic_cast<CallableType1 *>(m_callable);\
        if (cb1) {\
            cb1->invoke(object __REPEAT(N, __PARAM__));\
            return;\
        }\
        CallableType2 *cb2 = dynamic_cast<CallableType2 *>(m_callable);\
        if (cb2) {\
            cb2->invoke(object __REPEAT(N, __PARAM__));\
            return;\
        }\
        throw TypeMismatchError(m_name);\
    }
#endif

//macro that defines an 'invoke' method with a return type
#define __INVOKE__(N)\
    template <class R, class C __REPEAT(N, __TEMPLATE_ARG__)> void invoke(R &result, C *object __REPEAT(N, __ARG__)) const {\
        if (m_access != ACCESS_PUBLIC) throw IllegalAccessError(m_name);\
        typedef const __callable##N##__<R, C __REPEAT(N, __TYPE_ARG__)> CallableType1;\
        typedef const __callable_const##N##__<R, C __REPEAT(N, __TYPE_ARG__)> CallableType2;\
        CallableType1 *cb1 = reinterpret_cast<CallableType1 *>(m_callable);\
        if (cb1) {\
            result = cb1->invoke(object __REPEAT(N, __PARAM__));\
            return;\
        }\
        CallableType2 *cb2 = dynamic_cast<CallableType2 *>(m_callable);\
        if (cb2){\
            result = cb2->invoke(object __REPEAT(N, __PARAM__));\
            return;\
        }\
        throw TypeMismatchError(m_name);\
    }

//macro that defines an 'invoke' method without a return type
#define __INVOKE_VOID__(N)\
    template <class C __REPEAT(N, __TEMPLATE_ARG__)> void invokeVoid(C *object __REPEAT(N, __ARG__)) const {\
        if (m_access != ACCESS_PUBLIC) throw IllegalAccessError(m_name);\
        typedef const __callable_void##N##__<C __REPEAT(N, __TYPE_ARG__)> CallableType1;\
        typedef const __callable_const_void##N##__<C __REPEAT(N, __TYPE_ARG__)> CallableType2;\
        CallableType1 *cb1 = dynamic_cast<CallableType1 *>(m_callable);\
        if (cb1) {\
            cb1->invoke(object __REPEAT(N, __PARAM__));\
            return;\
        }\
        CallableType2 *cb2 = dynamic_cast<CallableType2 *>(m_callable);\
        if (cb2) {\
            cb2->invoke(object __REPEAT(N, __PARAM__));\
            return;\
        }\
        throw TypeMismatchError(m_name);\
    }


//static invoke void method with 0 params
#define __STATIC_INVOKE__0\
    template <class R> inline void invoke(R &result) const {\
        if (m_access != ACCESS_PUBLIC) throw IllegalAccessError(m_name);\
        typedef const __static_callable0__<R> CallableType;\
        CallableType *cb = dynamic_cast<CallableType *>(m_callable);\
        if (cb) {\
            result = cb->invoke();\
            return;\
        }\
        throw TypeMismatchError(m_name);\
    }


//static invoke non-void method
#define __STATIC_INVOKE__(N)\
    template <class R __REPEAT(N, __TEMPLATE_ARG__)> void invoke(R &result __REPEAT(N, __ARG__)) const {\
        if (m_access != ACCESS_PUBLIC) throw IllegalAccessError(m_name);\
        typedef const __static_callable##N##__<R __REPEAT(N, __TYPE_ARG__)> CallableType;\
        CallableType *cb = dynamic_cast<CallableType *>(m_callable);\
        if (cb) {\
            result = cb->invoke(__NREPEAT(N, __PARAM__));\
            return;\
        }\
        throw TypeMismatchError(m_name);\
    }


//static invoke void method with 0 params
#define __STATIC_INVOKE_VOID__0\
    inline void invokeVoid() const {\
        if (m_access != ACCESS_PUBLIC) throw IllegalAccessError(m_name);\
        typedef const __static_callable_void0__ CallableType;\
        CallableType *cb = dynamic_cast<CallableType *>(m_callable);\
        if (cb) {\
            cb->invoke();\
            return;\
        }\
        throw TypeMismatchError(m_name);\
    }


//static invoke void method
#define __STATIC_INVOKE_VOID__(N)\
    template <__NREPEAT(N, __TEMPLATE_ARG__)> void invokeVoid(__NREPEAT(N, __ARG__)) const {\
        if (m_access != ACCESS_PUBLIC) throw IllegalAccessError(m_name);\
        typedef const __static_callable_void##N##__<__NREPEAT(N, __TYPE_ARG__)> CallableType;\
        CallableType *cb = dynamic_cast<CallableType *>(m_callable);\
        if (cb) {\
            cb->invoke(__NREPEAT(N, __PARAM__));\
            return;\
        }\
        throw TypeMismatchError(m_name);\
    }


/** the CLASS macro is used to declare reflection support in a class. It must
    be placed on the public part of the class.
    @param CLASS_NAME name of this class.
    @param SUPER_CLASS_NAME name of the super class; if there is no base class,
           pass NullClass.
 */
#define CLASS(CLASS_NAME, SUPER_CLASS_NAME)\
protected:\
    typedef CLASS_NAME ClassType;\
    static const agm::reflection::ClassDesc *getClassDescStaticPtr() {\
        static agm::reflection::ClassDesc _class(#CLASS_NAME, SUPER_CLASS_NAME::getClassDescStaticPtr());\
        return &_class;\
    }\
public:\
    static const agm::reflection::ClassDesc &getClassDescStatic() {\
        return *CLASS_NAME::getClassDescStaticPtr();\
    }\
    virtual const agm::reflection::ClassDesc &getClassDesc() const {\
        return *CLASS_NAME::getClassDescStaticPtr();\
    }


/** The FIELD macro is used to declare a reflected field.
    @param ACCESS_ATTR access attribute (public, protected or private)
    @param FIELD_TYPE type of the field
    @param FIELD_NAME name of the field
 */
#define FIELD(ACCESS_ATTR, FIELD_TYPE, FIELD_NAME)\
private:\
    struct __field_##FIELD_NAME##__ {\
        __field_##FIELD_NAME##__() {\
            static agm::reflection::__register_field__ reg(__OFFSET__(ClassType, FIELD_NAME), ClassIndexMap::instance().getClassIndex(typeid(FIELD_TYPE).name()), getClassDescStaticPtr(), ACCESS_##ACCESS_ATTR, #FIELD_NAME);\
        }\
    } __field_##FIELD_NAME##__;\
    friend struct __field_##FIELD_NAME##__;\
ACCESS_ATTR :\
    FIELD_TYPE FIELD_NAME


/** The STATIC_FIELD macro is used to declare a reflected static field.
    @param ACCESS_ATTR access attribute (public, protected or private)
    @param FIELD_TYPE type of the field
    @param FIELD_NAME name of the field
 */
#define STATIC_FIELD(ACCESS_ATTR, FIELD_TYPE, FIELD_NAME)\
private:\
	struct __static_field_##FIELD_NAME##__ {\
		__static_field_##FIELD_NAME##__() {\
            static agm::reflection::__register_static_field__ reg((void *)&FIELD_NAME, ClassIndexMap::instance().getClassIndex(typeid(FIELD_TYPE).name()), getClassDescStaticPtr(), ACCESS_##ACCESS_ATTR, #FIELD_NAME);\
        }\
	} __static_field_##FIELD_NAME##__;\
	friend struct __static_field_##FIELD_NAME##__;\
ACCESS_ATTR :\
    static FIELD_TYPE FIELD_NAME


/** The METHOD macro is used to declare a reflected method.
    @param ACCESS_ATTR access attribute (public, protected or private)
    @param RETURN_TYPE the return type of the method
    @param METHOD_NAME name of the method
    @param METHOD_ARGS the method's arguments enclosed in parentheses
 */
#define METHOD(ACCESS_ATTR, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)\
    __METHOD__(ACCESS_ATTR, __NOT_VIRTUAL__, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)


/** The VIRTUAL_METHOD macro is used to declare a reflected method that is
    virtual, i.e. can be overloaded by subclasses.
    @param ACCESS_ATTR access attribute (public, protected or private)
    @param VIRTUAL pass virtual or no_virtual
    @param RETURN_TYPE the return type of the method
    @param METHOD_NAME name of the method
    @param METHOD_ARGS the method's arguments enclosed in parentheses
 */
#define VIRTUAL_METHOD(ACCESS_ATTR, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)\
    __METHOD__(ACCESS_ATTR, virtual, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)


/** The STATIC_METHOD macro is used to declare a reflected static method.
    @param ACCESS_ATTR access attribute (public, protected or private)
    @param RETURN_TYPE the return type of the method
    @param METHOD_NAME name of the method
    @param METHOD_ARGS the method's arguments enclosed in parentheses
 */
#define STATIC_METHOD(ACCESS_ATTR, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)\
private:\
    struct __static_method_##METHOD_NAME##__ {\
        __static_method_##METHOD_NAME##__() {\
            static agm::reflection::__register_static_method__ reg(__create_static_callable__(&ClassType::METHOD_NAME), getClassDescStaticPtr(), ACCESS_##ACCESS_ATTR, #RETURN_TYPE, #METHOD_NAME, #METHOD_ARGS);\
        }\
    } __static_method_##METHOD_NAME##__;\
    friend struct __static_method_##METHOD_NAME##__;\
ACCESS_ATTR :\
    static RETURN_TYPE METHOD_NAME METHOD_ARGS


/** The PROPERTY macro is used to declare an object's property. When used,
    the class must have two private methods in the form of TYPE get()/void set(TYPE)
    for setting and getting the property. By using this macro, the object 
    gets a property interface for managing the value is if it was a field.
    Arithmetic and other operators work as expected. The defined property
    is reflected: it can be examined and set in run-time. Properties do
    not define an access attribute: there are always public. The property
    does not add any extra bytes to the class, besides those needed for reflection.
    @param TYPE type of the property
    @param NAME name of the property
 */
#define PROPERTY_CORE(TYPE, NAME)\
private:\
    template <class T> class __property__##NAME {\
    public:\
        typedef __property__##NAME<T> Type;\
        __property__##NAME<T>() {\
            static agm::reflection::__register_property__ reg(new __property__<ClassType, T>(&ClassType::get##NAME, &ClassType::set##NAME), getClassDescStaticPtr(), ClassIndexMap::instance().getClassIndex(typeid(TYPE).name()), #NAME);\
        }\
        inline TYPE get() const {\
            return owner()->get##NAME();\
        }\
        inline void set(TYPE value) {\
            owner()->set##NAME(value);\
        }\
        inline operator TYPE () const {\
            return get();\
        }\
        inline bool operator == (TYPE value) const {\
            return get() == value;\
        }\
        inline bool operator != (TYPE value) const {\
            return get() != value;\
        }\
        inline bool operator < (TYPE value) const {\
            return get() < value;\
        }\
        inline bool operator > (TYPE value) const {\
            return get() > value;\
        }\
        inline bool operator <= (TYPE value) const {\
            return get() <= value;\
        }\
        inline bool operator >= (TYPE value) const {\
            return get() >= value;\
        }\
        inline Type &operator = (TYPE value) {\
            set(value);\
            return *this;\
        }\
        inline Type &operator = (const Type &prop) {\
            if (&prop != this) set(prop.get());\
            return *this;\
        }\
    private:\
        ClassType *owner() {\
            return (ClassType *)(((const char *)this) - __OFFSET__(ClassType, NAME));\
        }\
        const ClassType *owner() const {\
            return (const ClassType *)(((const char *)this) - __OFFSET__(ClassType, NAME));\
        }\
    };\
    friend class __property__##NAME< TYPE >;\
public:\
	__property__##NAME< TYPE > NAME

#define BEGIN_AUTODOC	/**
#define BEGIN_AUTODOC	/**
#define END_AUTODOC	*/

//! Brief description.

//! Detailed description 
//! starts here.
#define BEGIN_DOCGEN(x) #x
#define END_DOCGEN
#define DOCGEN_GET_PROPERTY(TYPE, NAME) Get the #NAME. @return value, #TYPE
#define DOCGEN_SET_PROPERTY(TYPE, NAME) Set the #NAME. @param value, #TYPE

#define PROPERTY(TYPE, NAME) \
PROPERTY_CORE(TYPE, NAME); \
	TYPE get##NAME() const \
	{ \
		return _##NAME; \
	} \
	void set##NAME(TYPE value) \
	{ \
		_##NAME = value; \
	} \
private: \
	TYPE _##NAME

#define PROPERTY_CUSTOM_FUNC(TYPE, NAME, GETTER, SETTER) \
PROPERTY_CORE(TYPE, NAME); \
	TYPE get##NAME() const \
	GETTER \
	void set##NAME(TYPE value) \
	SETTER

/** access type enumeration
 */
enum ACCESS_TYPE {
    ///public access
    ACCESS_PUBLIC = 0,

    ///protected access
    ACCESS_PROTECTED,

    ///private access
    ACCESS_PRIVATE
};


//access synonyms used in reflection
#define ACCESS_public        ACCESS_PUBLIC
#define ACCESS_protected     ACCESS_PROTECTED
#define ACCESS_private       ACCESS_PRIVATE


class ClassDesc;


class ClassBase
{
public:
	ClassBase(){}
	~ClassBase(){}
	virtual bool isRelative(const ClassDesc &cl) const {
		return false;
	}
private:
};
/** Exception thrown when there is a type mismatch.
 */
class TypeMismatchError : public std::runtime_error {
public:
    /** the default constructor
        @param what the item that caused the error
     */
    TypeMismatchError(const std::string &what) : runtime_error(what) {
    }
};


/** Exception thrown when there is an illegal access error.
 */
class IllegalAccessError : public std::runtime_error {
public:
    /** the default constructor
        @param what the item that caused the error
     */
    IllegalAccessError(const std::string &what) : runtime_error(what) {
    }
};


/** Exception thrown when an unknown field has been requested.
 */
class UnknownFieldError : public std::runtime_error {
public:
    /** the default constructor
        @param what the item that caused the error
     */
    UnknownFieldError(const std::string &what) : runtime_error(what) {
    }
};


/** Exception thrown when an unknown method has been requested.
 */
class UnknownMethodError : public std::runtime_error {
public:
    /** the default constructor
        @param what the item that caused the error
     */
    UnknownMethodError(const std::string &what) : runtime_error(what) {
    }
};


/** Exception thrown when an unknown property has been requested.
 */
class UnknownPropertyError : public std::runtime_error {
public:
    /** the default constructor
        @param what the item that caused the error
     */
    UnknownPropertyError(const std::string &what) : runtime_error(what) {
    }
};


/** Exception thrown when there the superclass of a class was asked to be
    returned but there was no superclass.
 */
class SuperClassError : public std::runtime_error {
public:
    /** the default constructor
        @param what the item that caused the error
     */
    SuperClassError(const std::string &what) : runtime_error(what) {
    }
};


/** The FieldDesc class represents an object's field.
 */
class FieldDesc {
public:
	unsigned int getOffset() const
	{
		return m_offset;
	}
	
	int getClassIndex() const
	{
		return m_classIdx;
	}

    /** returns the class that the member is declared into.
        @return the class that the member is declared into.
     */
    const ClassDesc &getClass() const 
	{
        return *(ClassDesc*) m_class;
    }

    /** returns the field's access.
        @return the field's access.
     */
    const ACCESS_TYPE getAccess() const 
	{
        return m_access;
    }

    /** returns the field's name.
        @return the field's name.
     */
    const char *getName() const 
	{
        return m_name;
    }

    /** retrieves the field of the given object.
        @param result variable to store the result of the field
        @param object object to set the field of
        @exception TypeMismatchError thrown if the object is of invalid class or 
                   the result is of the wrong type.
     */
    template <class Object, class Value> void get(Value &result, Object *object) const {
        if (m_access != ACCESS_PUBLIC) throw IllegalAccessError(m_name);
        if (!m_class->isRelative(object->getClassDesc())) throw TypeMismatchError("object");

		// if(typeid(Value)!=m_typeinfo) throw TypeMismatchError("result"); 
		if( ClassIndexMap::instance().getClassIndex(typeid(Value).name()) != m_classIdx) 
			throw TypeMismatchError("get"); 

        result = *(const Value *)(((const char *)object) + m_offset);
    }

    /** sets the field of the given object.
        @param object object to set the field of
        @param value new value of the field
        @exception TypeMismatchError thrown if the object is of invalid class or 
                   the value is of the wrong type.
        @exception IllegalAccessError thrown if the field's access is not public.
     */
    template <class Object, class Value> void set(Object *object, const Value &value) const {
        if (m_access != ACCESS_PUBLIC) throw IllegalAccessError(m_name);
        if(!m_class->isRelative(object->getClassDesc())) throw TypeMismatchError("object");

		// if(typeid(Value)!=m_typeinfo) throw TypeMismatchError("result"); 
		if( ClassIndexMap::instance().getClassIndex(typeid(Value).name()) != m_classIdx) 
			throw TypeMismatchError("set"); 

        *(Value *)(((char *)object) + m_offset) = value;
    }

private:
    unsigned int m_offset;
    int m_classIdx;
    const ClassBase *m_class;
    enum ACCESS_TYPE m_access;
    const char *m_name;

    //default constructor
    FieldDesc(unsigned int offset, int classIdx, const ClassBase *pclass, ACCESS_TYPE access, const char *name) 
	: m_offset(offset)
	, m_classIdx(classIdx)
	, m_class(pclass)
	, m_access(access)
	, m_name(name)
	{
    }

    friend class ClassDesc;
    friend class ClassBase;
    friend struct __register_field__;
};


/** The StaticFieldDesc class represents an object's static field.
 */
class StaticFieldDesc {
public:
	int getClassIndex() const
	{
		return m_classIdx;
	}

    /** returns the class that the member is declared into.
        @return the class that the member is declared into.
     */
    const ClassDesc &getClass() const {
        return *m_class;
    }

    /** returns the field's access.
        @return the field's access.
     */
    const ACCESS_TYPE getAccess() const {
        return m_access;
    }

    /** returns the field's name.
        @return the field's name.
     */
    const char *getName() const {
        return m_name;
    }

    /** retrieves the static field's value.
        @param value variable to store the value of the field
        @exception TypeMismatchError thrown if the object is of invalid class or 
                   the value is of the wrong type.
     */
    template <class Value> void get(Value &value) const {
        if (m_access != ACCESS_PUBLIC) throw IllegalAccessError(m_name);

		//if(typeid(Value)!=m_typeinfo) throw TypeMismatchError("result"); 
		if( ClassIndexMap::instance().getClassIndex(typeid(Value).name()) != m_classIdx) 
			throw TypeMismatchError("get"); 

        value = *(const Value *)(m_address);
    }

    /** sets the static field's value.
        @param value new value of the field
        @exception TypeMismatchError thrown if the object is of invalid class or 
                   the value is of the wrong type.
        @exception IllegalAccessError thrown if the field's access is not public.
     */
    template <class Value> void set(const Value &value) const {
        if (m_access != ACCESS_PUBLIC) throw IllegalAccessError(m_name);

		//if(typeid(Value)!=m_typeinfo) throw TypeMismatchError("result"); 
		if( ClassIndexMap::instance().getClassIndex(typeid(Value).name()) != m_classIdx) 
			throw TypeMismatchError("set"); 
		
        *(Value *)(m_address) = value;
    }

private:
    void *m_address;
	int m_classIdx;
    const ClassDesc *m_class;
    enum ACCESS_TYPE m_access;
    const char *m_name;

    //default constructor
    StaticFieldDesc(void *address, int classIdx, const ClassDesc *pclass, ACCESS_TYPE access, const char *name) 
	: m_address(address)
	, m_classIdx(classIdx)
	, m_class(pclass)
	, m_access(access)
    , m_name(name) 
	{
    }

    friend class ClassDesc;
    friend struct __register_static_field__;
};


/** The MethodDesc class represents an object's method.
 */
class MethodDesc {
public:
    ///destructor
    ~MethodDesc() {
        if (m_callable) delete m_callable;
    }

    /** returns the class that the member is declared into.
        @return the class that the member is declared into.
     */
    const ClassDesc &getClass() const {
        return *m_class;
    }

    /** returns the method's access.
        @return the method's access.
     */
    const ACCESS_TYPE getAccess() const {
        return m_access;
    }

    /** returns the method's type (return type).
        @return the method's type.
     */
    const char *getType() const {
        return m_type;
    }

    /** returns the method's name.
        @return the method's name.
     */
    const char *getName() const {
        return m_name;
    }

    /** returns the method's id (name + arguments).
        @return the method's name.
     */
    const char *getId() const {
        return m_id.c_str();
    }

    /** returns the method's arguments.
        @return the method's arguments.
     */
    const char *getArgs() const {
        return m_args;
    }

    /** returns true if the method is virtual.
        @return true if the method is virtual.
     */
    bool isVirtual() const {
        return m_virtual;
    }

    /** invokes a method that has a result
        @param result optional variable to store the result (if the method is non-void)
        @param object object to execute the method of
        @param t1...tn parameters of the invocation
        @exception IllegalAccessError if the method is not public
        @exception TypeMismatchError if the method has different arguments than
                   the ones passed to it
     */
    __INVOKE__(0)
    __INVOKE__(1)
    __INVOKE__(2)
    __INVOKE__(3)
    __INVOKE__(4)
    __INVOKE__(5)
    __INVOKE__(6)
    __INVOKE__(7)
    __INVOKE__(8)
    __INVOKE__(9)
    __INVOKE__(10)
    __INVOKE__(11)
    __INVOKE__(12)
    __INVOKE__(13)
    __INVOKE__(14)
    __INVOKE__(15)
    __INVOKE__(16)
    __INVOKE__(17)
    __INVOKE__(18)
    __INVOKE__(19)
    __INVOKE__(20)

    /** invokes a method that 'returns' void
        @param object object to execute the method of
        @param t1...tn parameters of the invocation
        @exception IllegalAccessError if the method is not public
        @exception TypeMismatchError if the method has different arguments than
                   the ones passed to it
     */
    __INVOKE_VOID__(0)
    __INVOKE_VOID__(1)
    __INVOKE_VOID__(2)
    __INVOKE_VOID__(3)
    __INVOKE_VOID__(4)
    __INVOKE_VOID__(5)
    __INVOKE_VOID__(6)
    __INVOKE_VOID__(7)
    __INVOKE_VOID__(8)
    __INVOKE_VOID__(9)
    __INVOKE_VOID__(10)
    __INVOKE_VOID__(11)
    __INVOKE_VOID__(12)
    __INVOKE_VOID__(13)
    __INVOKE_VOID__(14)
    __INVOKE_VOID__(15)
    __INVOKE_VOID__(16)
    __INVOKE_VOID__(17)
    __INVOKE_VOID__(18)
    __INVOKE_VOID__(19)
    __INVOKE_VOID__(20)

private:
    const ClassDesc *m_class;
    enum ACCESS_TYPE m_access;
    std::string m_id;
    const char *m_type;
    const char *m_name;
    const char *m_args;
    __callable__ *m_callable;
    bool m_virtual:1;

    //default constructor
    MethodDesc(const ClassDesc *pclass, ACCESS_TYPE access, const char *type, const char *name, const char *args, bool virt) :
        m_class(pclass),
        m_access(access),
        m_type(type), 
        m_name(name),
        m_args(args),
        m_virtual(virt),
        m_callable(0),
        m_id(name) {
        m_id += args;
    }

    friend class ClassDesc;
    friend struct __register_method__;
};


/** The StaticMethodDesc class represents an object's static method.
 */
class StaticMethodDesc {
public:
    ///destructor
    ~StaticMethodDesc() {
        if (m_callable) delete m_callable;
    }

    /** returns the class that the member is declared into.
        @return the class that the member is declared into.
     */
    const ClassDesc &getClass() const {
        return *m_class;
    }

    /** returns the method's access.
        @return the method's access.
     */
    const ACCESS_TYPE getAccess() const {
        return m_access;
    }

    /** returns the method's type (return type).
        @return the method's type.
     */
    const char *getType() const {
        return m_type;
    }

    /** returns the method's name.
        @return the method's name.
     */
    const char *getName() const {
        return m_name;
    }

    /** returns the method's id (name + arguments).
        @return the method's name.
     */
    const char *getId() const {
        return m_id.c_str();
    }

    /** returns the method's arguments.
        @return the method's arguments.
     */
    const char *getArgs() const {
        return m_args;
    }

    /** invokes the non-void method
        @param result optional variable to store the result (if the method is non-void)
        @param t1...tn parameters of the invocation
        @exception IllegalAccessError if the method is not public
        @exception TypeMismatchError if the method has different arguments than
                   the ones passed to it
     */
    __STATIC_INVOKE__0
    __STATIC_INVOKE__(1)
    __STATIC_INVOKE__(2)
    __STATIC_INVOKE__(3)
    __STATIC_INVOKE__(4)
    __STATIC_INVOKE__(5)
    __STATIC_INVOKE__(6)
    __STATIC_INVOKE__(7)
    __STATIC_INVOKE__(8)
    __STATIC_INVOKE__(9)
    __STATIC_INVOKE__(10)
    __STATIC_INVOKE__(11)
    __STATIC_INVOKE__(12)
    __STATIC_INVOKE__(13)
    __STATIC_INVOKE__(14)
    __STATIC_INVOKE__(15)
    __STATIC_INVOKE__(16)
    __STATIC_INVOKE__(17)
    __STATIC_INVOKE__(18)
    __STATIC_INVOKE__(19)
    __STATIC_INVOKE__(20)

    /** invokes the void method
        @param t1...tn parameters of the invocation
        @exception IllegalAccessError if the method is not public
        @exception TypeMismatchError if the method has different arguments than
                   the ones passed to it
     */
    __STATIC_INVOKE_VOID__0
    __STATIC_INVOKE_VOID__(1)
    __STATIC_INVOKE_VOID__(2)
    __STATIC_INVOKE_VOID__(3)
    __STATIC_INVOKE_VOID__(4)
    __STATIC_INVOKE_VOID__(5)
    __STATIC_INVOKE_VOID__(6)
    __STATIC_INVOKE_VOID__(7)
    __STATIC_INVOKE_VOID__(8)
    __STATIC_INVOKE_VOID__(9)
    __STATIC_INVOKE_VOID__(10)
    __STATIC_INVOKE_VOID__(11)
    __STATIC_INVOKE_VOID__(12)
    __STATIC_INVOKE_VOID__(13)
    __STATIC_INVOKE_VOID__(14)
    __STATIC_INVOKE_VOID__(15)
    __STATIC_INVOKE_VOID__(16)
    __STATIC_INVOKE_VOID__(17)
    __STATIC_INVOKE_VOID__(18)
    __STATIC_INVOKE_VOID__(19)
    __STATIC_INVOKE_VOID__(20)

private:
    const ClassDesc *m_class;
    enum ACCESS_TYPE m_access;
    std::string m_id;
    const char *m_type;
    const char *m_name;
    const char *m_args;
    __callable__ *m_callable;

    //default constructor
    StaticMethodDesc(const ClassDesc *pclass, ACCESS_TYPE access, const char *type, const char *name, const char *args) :
        m_class(pclass),
        m_access(access),
        m_type(type), 
        m_name(name),
        m_args(args),
        m_callable(0),
        m_id(name) {
        m_id += args;
    }

    friend class ClassDesc;
    friend struct __register_static_method__;
};


/** The PropertyDesc class holds information about an object's property.
 */
class PropertyDesc {
public:
    ///destructor
    ~PropertyDesc() {
        if (m_handler) delete m_handler;
    }

    /** returns the class that the member is declared into.
        @return the class that the member is declared into.
     */
    const ClassDesc &getClass() const {
        return *(ClassDesc*) m_class;
    }

    /** returns the property's type.
        @return the property's type.
     */
	int getClassIndex() const
	{
		return m_classIdx;
	}

    /** returns the property's name.
        @return the property's name.
     */
    const char *getName() const {
        return m_name;
    }

    /** returns the value of the property
        @param result result to store the value to
        @param object object to get the property of
        @exception TypeMismatchError thrown if there is a type mismatch
     */
    template <class Object, class Value> void get(Value &result, const Object *object) const {
        if (!m_class->isRelative(object->getClassDesc())) throw TypeMismatchError("object");
        typedef const __property_handler__<Value> PropertyType;
        PropertyType *prop = dynamic_cast<PropertyType *>(m_handler);
        if (!prop) throw TypeMismatchError(m_name);
        result = prop->get((const void *)object);
    }

    /** sets the property's value
        @param object object to set the property of
        @param value value of the object
        @exception TypeMismatchError thrown if there is a type mismatch
     */
    template <class Object, class Value> void set(Object *object, const Value &value) const {
       if (!m_class->isRelative( object->getClassDesc())) throw TypeMismatchError("object");
        typedef const __property_handler__<Value> PropertyType;
        PropertyType *prop = dynamic_cast<PropertyType *>(m_handler);
        if (!prop) throw TypeMismatchError(m_name);
        prop->set((void *)object, value);
    }

private:
    int m_classIdx;
    const char *m_name;
    __property_base__ *m_handler;
    const ClassBase *m_class;

    //default constructor
    PropertyDesc(const ClassBase *pclass, int classIdx, const char *name)
	: m_class(pclass)
	, m_classIdx(classIdx)
	, m_name(name)
	, m_handler(0) 
	{
    }
    
    friend class ClassBase;
    friend class ClassDesc;
    friend struct __register_property__;
};


/** The Class class is used as a placeholder for run-time information of an
    an object's class. A class can be used to query an object's fields, 
    methods, properties, events and super class.
 */
class ClassDesc : public ClassBase
{
public:
    ///type of list of fields
    typedef std::list<FieldDesc> FieldDescList;
	typedef std::list<FieldDesc>::iterator FieldDescListItr;
	typedef std::list<FieldDesc>::const_iterator FieldDescListCItr;

    ///type of list of static fields
    typedef std::list<StaticFieldDesc> StaticFieldDescList;
	typedef std::list<StaticFieldDesc>::iterator StaticFieldDescListItr;
	typedef std::list<StaticFieldDesc>::const_iterator StaticFieldDescListCItr;

    ///type of list of methods
    typedef std::list<MethodDesc> MethodDescList;
	typedef std::list<MethodDesc>::iterator MethodDescListItr;
	typedef std::list<MethodDesc>::const_iterator MethodDescListCItr;

    ///type of list of static methods
    typedef std::list<StaticMethodDesc> StaticMethodDescList;
	typedef std::list<StaticMethodDesc>::iterator StaticMethodDescListItr;
	typedef std::list<StaticMethodDesc>::const_iterator StaticMethodDescListCItr;

    ///type of list of properties
    typedef std::list<PropertyDesc> PropertyDescList;
	typedef std::list<PropertyDesc>::iterator PropertyDescListItr;
	typedef std::list<PropertyDesc>::const_iterator PropertyDescListCItr;

    //the default constructor
    ClassDesc(const char *name, const ClassDesc *super) 
	: m_name(name)
	, m_super(super) 
	{
    }

    /** returns the class name
        @return the class name
     */
    const char *getName() const 
	{
		return m_name;
    }

    /** checks if the class has a superclass
        @return true if the class has a superclass
     */
    const bool hasSuper() const 
	{
		return m_super != 0;
    }

    /** returns the superclass of the class
        @return the superclass of the class; the superclass must not be null
        @exception SuperClassError thrown if there is no super class
     */
    const ClassDesc &getSuper() const 
	{
        if (!m_super) 
			throw SuperClassError(m_name);

        return *m_super;
    }

    /** returns the collection of fields
        @return the collection of fields
     */
    const FieldDescList &getFields() const 
	{
        return m_fields;
    }

    /** returns the collection of static fields
        @return the collection of static fields
     */
    const StaticFieldDescList &getStaticFields() const 
	{
        return m_staticFields;
    }

    /** returns the list of methods
        @return the list of methods
     */
    const MethodDescList &getMethods() const 
	{
        return m_methods;
    }

    /** returns the collection of static methods
        @return the collection of static methods
     */
    const StaticMethodDescList &getStaticMethods() const 
	{
        return m_staticMethods;
    }

    /** returns the collection of properties
        @return the collection of properties
     */
    const PropertyDescList &getProperties() const 
	{
        return m_properties;
    }

    /** returns the collection of fields
        @return the collection of fields
     */
    void getFields(std::vector<const FieldDesc *> &fields, bool searchSuper = true) const 
	{
		if(searchSuper && m_super) 
			m_super->getFields(fields, searchSuper);

		for(FieldDescListCItr itr = m_fields.begin(); itr!=m_fields.end(); itr++)
		{
			fields.push_back(&(*itr));
		}
    }

    /** returns the collection of static fields
        @return the collection of static fields
     */
	void getStaticFields(std::vector<const StaticFieldDesc *> &staticFields, bool searchSuper = true) const 
	{
		if(searchSuper && m_super) 
			m_super->getStaticFields(staticFields, searchSuper);

		for(StaticFieldDescListCItr itr = m_staticFields.begin(); itr!=m_staticFields.end(); itr++)
		{
			staticFields.push_back(&(*itr));
		}
    }

    /** returns the list of methods
        @return the list of methods
     */
	void getMethods(std::vector<const MethodDesc *> &methods,bool searchSuper = true) const 
	{
		if(searchSuper && m_super) 
			m_super->getMethods(methods, searchSuper);

		for(MethodDescListCItr itr = m_methods.begin(); itr!=m_methods.end(); itr++)
		{
			methods.push_back(&(*itr));
		}
    }

    /** returns the collection of static methods
        @return the collection of static methods
     */
    void getStaticMethods(std::vector<const StaticMethodDesc *> &staticMethods, bool searchSuper = true) const 
	{
		if(searchSuper && m_super) 
			m_super->getStaticMethods(staticMethods, searchSuper);

		for(StaticMethodDescListCItr itr = m_staticMethods.begin(); itr!=m_staticMethods.end(); itr++)
		{
			staticMethods.push_back(&(*itr));
		}
    }

    /** returns the collection of properties
        @return the collection of properties
     */
	void getProperties(std::vector<const PropertyDesc *> &properties, bool searchSuper = true) const 
	{
		if(searchSuper && m_super) 
			m_super->getProperties(properties, searchSuper);

		for(PropertyDescListCItr itr = m_properties.begin(); itr!=m_properties.end(); itr++)
		{
			properties.push_back(&(*itr));
		}
	}

    /** checks if this class is a base class of the given class.
        @param cl class to check against
        @return true if this class is a base class of the given class.
     */
    bool isBase(const ClassDesc &cl) const 
	{
        for(const ClassDesc *c = cl.m_super; c; c = c->m_super) 
		{
            if(c == this)
				return true;
        }
        return false;
    }

    /** checks if this class is the super class of the given class.
        @param cl class to check against
        @return true if this class is the super class of the given class.
     */
    bool isSuper(const ClassDesc &cl) const 
	{
        return cl.m_super == this;
    }

    /** checks if this class is the same as given class
        @param cl class to check against
     */
    bool isSame(const ClassDesc &cl) const 
	{
        return &cl == this;
    }

    /** checks if the given class is relative to this class. In other words,
        it checks if this class is a base class of the given class, or if they
        are the same class or the given class is a base class of this class.
        @param cl class to check against
        @return true if this class is a base class of the given class or the
                same class.
     */
    bool isRelative(const ClassDesc &cl) const 
	{
        return isSame(cl) || isBase(cl) || cl.isBase(*this);
    }

    /** returns field from name
        @param name name of the field to search for
        @param searchSuper if true, super classes are searched if this class does not have the requested member
        @return the field of given name
        @exception UnknownFieldError
     */
    const FieldDesc &getField(const char *name, bool searchSuper = true) const 
	{
        _FieldDescMap::const_iterator it = m_fieldMap.find(name);
        if (it == m_fieldMap.end()) 
		{
            if(searchSuper && m_super) 
				return m_super->getField(name, true);
            throw UnknownFieldError(name);
        }
        return *it->second;
    }

    /** returns static field from name
        @param name name of the field to search for
        @param searchSuper if true, super classes are searched if this class does not have the requested member
        @return the field of given name
        @exception UnknownFieldError
     */
    const StaticFieldDesc &getStaticField(const char *name, bool searchSuper = true) const 
	{
        _StaticFieldDescMap::const_iterator it = m_staticFieldMap.find(name);
        if (it == m_staticFieldMap.end()) 
		{
            if (searchSuper && m_super) 
				return m_super->getStaticField(name, true);
            throw UnknownFieldError(name);
        }
        return *it->second;
    }

    /** returns method from name
        @param name name of the method to search for
        @param searchSuper if true, super classes are searched if this class does not have the requested member
        @return the method of given id
        @exception UnknownMethodError
     */
    const MethodDesc &getMethod(const char *name, bool searchSuper = true) const 
	{
        _MethodDescMap::const_iterator it = m_methodMap.find(name);
        if (it == m_methodMap.end()) 
		{
            if (searchSuper && m_super) 
				return m_super->getMethod(name, true);
            throw UnknownMethodError(name);
        }
        return *it->second;
    }

    /** returns static method from name
        @param name name of the method to search for
        @param searchSuper if true, super classes are searched if this class does not have the requested member
        @return the method of given name
        @exception UnknownMethodError
     */
    const StaticMethodDesc &getStaticMethod(const char *name, bool searchSuper = true) const 
	{
        _StaticMethodDescMap::const_iterator it = m_staticMethodMap.find(name);
        if (it == m_staticMethodMap.end()) 
		{
            if (searchSuper && m_super) 
				return m_super->getStaticMethod(name, true);
            throw UnknownMethodError(name);
        }
        return *it->second;
    }

    /** returns property from name
        @param name name of the property to search for
        @param searchSuper if true, super classes are searched if this class does not have the requested member
        @return the property of given name
        @exception UnknownPropertyError
     */
    const PropertyDesc &getProperty(const char *name, bool searchSuper = true) const 
	{
        _PropertyDescMap::const_iterator it = m_propertyMap.find(name);
        if (it == m_propertyMap.end()) 
		{
            if (searchSuper && m_super) 
				return m_super->getProperty(name, true);
            throw UnknownPropertyError(name);
        }
        return *it->second;
    }

private:
    typedef std::map<std::string, FieldDesc *>			_FieldDescMap;
    typedef std::map<std::string, StaticFieldDesc *>	_StaticFieldDescMap;
    typedef std::map<std::string, MethodDesc *>			_MethodDescMap;
    typedef std::map<std::string, StaticMethodDesc *>	_StaticMethodDescMap;
    typedef std::map<std::string, PropertyDesc *>		_PropertyDescMap;
    const char *m_name;
    const ClassDesc *m_super;
    FieldDescList						m_fields;
    _FieldDescMap						m_fieldMap;
    StaticFieldDescList					m_staticFields;
    _StaticFieldDescMap					m_staticFieldMap;
    MethodDescList						m_methods;
    _MethodDescMap						m_methodMap;
    StaticMethodDescList				m_staticMethods;
    _StaticMethodDescMap				m_staticMethodMap;
    PropertyDescList					m_properties;
    _PropertyDescMap					m_propertyMap;

    //adds a field
    void _addField(const FieldDesc &field) 
	{
        m_fields.push_back(field);
        m_fieldMap[field.m_name] = &m_fields.back();
    }

    //adds a static field
    void _addStaticField(const StaticFieldDesc &field) 
	{
        m_staticFields.push_back(field);
        m_staticFieldMap[field.m_name] = &m_staticFields.back();
    }

    //adds a method
    void _addMethod(const MethodDesc &method, __callable__ *cb) 
	{
        m_methods.push_back(method);
        MethodDesc &m = m_methods.back();
        m.m_callable = cb;
        m_methodMap[method.m_name] = &m;
    }

    //adds a static method
    void _addStaticMethod(const StaticMethodDesc &method, __callable__ *cb) 
	{
        m_staticMethods.push_back(method);
        StaticMethodDesc &m = m_staticMethods.back();
        m.m_callable = cb;
        m_staticMethodMap[method.m_name] = &m;
    }

    //adds a property
    void _addProperty(const PropertyDesc &prop, __property_base__ *handler) 
	{
        m_properties.push_back(prop);
        PropertyDesc &p = m_properties.back();
        p.m_handler = handler;
        m_propertyMap[prop.m_name] = &p;
    }

    friend struct __register_field__;
    friend struct __register_static_field__;
    friend struct __register_method__;
    friend struct __register_static_method__;
    friend struct __register_property__;
};


/** Pseudo-class used when a class does not inherit from another class. It
    can not be instantiated.
 */
class NullClass {
public:
    static const ClassDesc *getClassDescStaticPtr() { return 0; }
private:
    NullClass() {}
    ~NullClass() {}
};


//internal class for registering a field
struct __register_field__ {
    __register_field__(unsigned int offset, int classIdx, const ClassDesc *pclass, enum ACCESS_TYPE access, const char *name) {
        FieldDesc field(offset, classIdx, pclass, access, name);
        ((ClassDesc *)pclass)->_addField(field);
    }
};


//internal class for registering a static field
struct __register_static_field__ {
    __register_static_field__(void *address, int classIdx, const ClassDesc *pclass, enum ACCESS_TYPE access, const char *name) {
        StaticFieldDesc field(address, classIdx, pclass, access, name);
        ((ClassDesc *)pclass)->_addStaticField(field);
    }
};


//internal class for registering a method
struct __register_method__ {
    __register_method__(__callable__ *cb, const ClassDesc *pclass, enum ACCESS_TYPE access, const char *type, const char *name, const char *args, const char *virt) {
        MethodDesc method(pclass, access, type, name, args, virt[0] == 'v' ? true : false);
        ((ClassDesc *)pclass)->_addMethod(method, cb);
    }
};


//internal class for registering a static method
struct __register_static_method__ {
    __register_static_method__(__callable__ *cb, const ClassDesc *pclass, enum ACCESS_TYPE access, const char *type, const char *name, const char *args) {
        StaticMethodDesc method(pclass, access, type, name, args);
        ((ClassDesc *)pclass)->_addStaticMethod(method, cb);
    }
};

//internal class for registering a property
struct __register_property__ {
    __register_property__(__property_base__ *handler, const ClassDesc *pclass, int classIdx, const char *name) {
        PropertyDesc property(pclass, classIdx, name);
        ((ClassDesc *)pclass)->_addProperty(property, handler);
    }
};

struct ltstr
{
	bool operator()(const char* s1, const char* s2) const
	{
		return strcmp(s1, s2) < 0;
	}
};


}}


///alias to Null class for reflection
//typedef agm::reflection::NullClass NullClass;


/** operator that outputs the access type to the given stream
    @param str stream to output the access to
    @param access access type to output
    @return the given stream
    @exception std::range_error thrown if the access value is invalid
 */
inline std::ostream &operator << (std::ostream &str, agm::reflection::ACCESS_TYPE access)
{
    switch (access) {
        case agm::reflection::ACCESS_PUBLIC:
            str << "public";
            break;

        case agm::reflection::ACCESS_PROTECTED:
            str << "protected";
            break;

        case agm::reflection::ACCESS_PRIVATE:
            str << "private";
            break;

        default:
            throw std::range_error("access");
    }
	
    return str;
}


#endif //AGM_REFLECTION_HPP

///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _ESTRING_H
#define _ESTRING_H

#include "Stage.h"
#include "Array.h"
#include <string>
using namespace std;

namespace EpicForce
{

class String
{
public:
	String();
	explicit String(char ch);
	String(const String& str);
	explicit String(int size);
	String(const char *str, int size=0);
	~String();


	bool operator==(const String& other) const;
	bool operator==(const char *str) const;
	bool operator==(char ch) const;
	
	bool operator!=(const String& other) const;
	bool operator!=(const char *str) const;
	bool operator!=(char ch) const;

	bool operator>(const String& other) const;
	bool operator>(const char *str) const;
	bool operator>(char ch) const;

	bool operator>=(const String& other) const;
	bool operator>=(const char *str) const;
	bool operator>=(char ch) const;

	bool operator<(const String& other) const;
	bool operator<(const char *str) const;
	bool operator<(char ch) const;

	bool operator<=(const String& other) const;
	bool operator<=(const char *str) const;
	bool operator<=(char ch) const;

	//    String &operator=(const Data &src);
	String &operator=(const String &src);
	String &operator=(const char *str);
	String &operator=(char c);
	String &operator+=(const String& str);
	String &operator+=(char ch);
	String &operator+=(const char *str);

	String operator+(const String &right) const { String str= *this; str+=right; return str; }
	String operator+(const char *right) const { String str= *this; str+=right; return str; }
	String operator+(char right) const {  String str= *this; str+=right; return str; }
	friend String operator+(const char *left, const String& right){  String str=left; str+=right; return str;  }
	friend String operator+(char left, const String& right){  String str=String(left); str+=right; return str;  }

	char operator[](int at) const;
	char &operator[](int at);

	int trim(int direction=0);      // trims whitespace from string, trim left -1, trim right 1, both 0
	String extract(int start, int length) const;
	String &toLower();
	String &toUpper();

	int find_first_of(const char *delimiters) const;
	int find_first_not_of(const char *delimiters) const;
	int find_last_of(const char *delimiters) const;
	int find_last_not_of(const char *delimiters) const;

	int find_first_of(const char *delimiters, int pos) const;
	int find_first_not_of(const char *delimiters, int pos) const;
	int find_last_of(const char *delimiters, int pos) const;
	int find_last_not_of(const char *delimiters, int pos) const;
	String substr(int start, int count) const;

	const char *text(int at = 0) const;
	operator const char* () const;
	int length() const;

	const char *String::copy(const char *buffer_, int length_);
private:
	string buffer;
};

#if 0
class String
{
	char *data;

	struct Buffer
	{
		char *buffer;
		int &length;
		int &maximum;
		enum Flags{DIRTY=0x01};
		unsigned char &flags;
		unsigned char &block;
		unsigned short &index;
		static char *allocate(int length);
		static void release(char *buffer);
		Buffer(char *buffer);
	};

public:
	typedef char CharType;

	int length() const;
	static int length(const char *s);
	int capacity() const;
	const char *text(int off=0) const;

	char back() const;
	char& back();

	void release();
	char *allocate(int len);
	char *buffer(){return data;}    
	String &attach(char *buffer);//Must be allocated via Buffer::allocate()
	char *detach();//renders String null, you are taking ownership must use Buffer::release()
	int reset(); //use when manipulation the buffer directly, resets internal values based on the null terminator
	int reset(int len);
	bool dirty();
	void dirty(bool set);

public:
	//Manipulators non-const
	void empty();          // makes 0 length string
	bool grow(int len=0);   //adjusts string buffer size 
	const char *copy(const char *buffer_, int length_=0);   //copies buffer of length bytes to string data is sized if needed
	const char *line(const char *text, int max_=400); //copies a text line terminated by 0 or newline up to max_ to strings buffer
	int trim(int direction=0);      // trims whitespace from string, trim left -1, trim right 1, both 0
	int strip(const char *token);   // remove any char of list token found in string 
	String &pad(int length_);       //sizes string of length length_ by padding spaces or truncating, negative length_ left pads
	String &move(int from, int to, int len); //move substring of length len from offset from to offset to 
	String &erase(int index);             //removes character at index
	String &erase(int from, int to);      //removes characters 'from' index until but not including 'to'   
	String &insert(char ch, int off=0);   //insert char at offset off
	String &insert(const char *str, int at=0, int len=0);  //insert string at offset of length len 
	String &cat(const char *str, int len=0);    //concats text
	String &cat(const String &str);    //concats string
	String &cat(char c);               //concats char
	String &trunc(int off=1);          //truncates string from head (-off) or tail (off)
	String &chop(int at);
	String &replace(char from, char to);  //replaces all occurences of [from] with [to]
	inline char get(int at) const;
	inline char put(int at, char ch);
	char operator[](int at) const;
	char &operator[](int at);

	//Conversion
public:
	double toDouble() const;
	float toFloat() const;
	long toLong() const;
	unsigned long toDWord() const;  
	int toInteger() const; 
	short toShort() const;
	unsigned short toWord() const;
	char toChar() const;
	unsigned char toByte() const;
	bool toBool() const;
	String &from(double f);
	String &from(float f);
	String &from(long n);
	String &from(unsigned d);
	String &from(unsigned long d);
	String &from(int d);
	String &from(short d);
	String &from(unsigned short d);
	String &from(char c);
	String &from(unsigned char d);
	String &from(bool b);

public:
	int toMoney() const;
	String &fromMoney(int money);
	String &toLower();
	String &toUpper();

	//Analysis const methods
	int valid(int index) const;
	bool isSpace(int index) const;
	bool isNumberSpace(int index) const;
	bool isInteger() const;
	int isBlank() const;
	int token(const char *list, int start=0) const; // find first occurence of token in list, returns 0 for none or index after find
	int find(const char *str, int start=0) const; // returns 0 none or index after find
	int find(char ch, int start=0, int index=0) const; 
	//int find(const String &other, int start=0); //MRP* nobody wrote code for this and causes ambiguous compiler erros
	int count(char ch) const; 
	int countSequence(char ch, int start=0) const; // counts seq of same char starting at start
	int compare(char ch) const;
	int compare(const char *other, int stop=0) const; // return 0 for match or -+value for difference
	int compare(const String &other, int stop=0) const; // return 0 for match or -+value for difference
	int compareCase(const char *other, int stop=0) const; // return 0 for match or -+value for difference
	int compareCase(const String &other, int stop=0) const; // return 0 for match or -+value for difference

	//Extraction
	String word(char delim, int position=0) const; // extracts word delimeted by delim neg position will go from top n/i
	String extract(int from, int length=0) const; // extracts string at from of length, neg from will go from top n/i

	//Operators
public:
	operator const char *() const;
	bool operator==(const String& other) const;
	bool operator==(const char *str) const;
	bool operator==(char ch) const;
	//    friend bool String::operator==(const char *left, const String& right){return !right.compare(left);}
	//    friend bool String::operator==(char left, const String& right){return !right.compare(left);}

	bool operator!=(const String& other) const;
	bool operator!=(const char *str) const;
	bool operator!=(char ch) const;
	//    friend bool String::operator!=(const char *left, const String& right){return right.compare(left)!=0;} 
	//    friend bool String::operator!=(char left, const String& right){return right.compare(left)!=0;}

	bool operator>(const String& other) const;
	bool operator>(const char *str) const;
	bool operator>(char ch) const;
	//    friend bool String::operator>(const char *left, const String& right){return 0>right.compare(left);}
	//    friend bool String::operator>(char left, const String& right){return 0>right.compare(left);}

	bool operator>=(const String& other) const;
	bool operator>=(const char *str) const;
	bool operator>=(char ch) const;
	//    friend bool String::operator>=(const char *left, const String& right){return 0>=right.compare(left);}
	//    friend bool String::operator>=(char left, const String& right){return 0>=right.compare(left);}

	bool operator<(const String& other) const;
	bool operator<(const char *str) const;
	bool operator<(char ch) const;
	//    friend bool String::operator<(const char *left, const String& right){return 0<right.compare(left);}         
	//    friend bool String::operator<(char left, const String& right){return 0<right.compare(left);}

	bool operator<=(const String& other) const;
	bool operator<=(const char *str) const;
	bool operator<=(char ch) const;
	//    friend bool String::operator<=(const char *left, const String& right){return 0<=right.compare(left);}         
	//    friend bool String::operator<=(char left, const String& right){return 0<=right.compare(left);}

	//    String &operator=(const Data &src);
	String &operator=(const String &src);
	String &operator=(const char *str);
	String &operator=(char c);
	String &operator+=(const String& str);
	String &operator+=(char ch);
	String &operator+=(const char *str);

	String operator+(const String &right) const {return String(*this).cat(right);}
	String operator+(const char *right) const {return String(*this).cat(right);}
	String operator+(char right) const {return String(*this).cat(right);}
	friend String operator+(const char *left, const String& right){return String(left).cat(right);}
	friend String operator+(char left, const String& right){return String(left).cat(right);}

	String &format(const char *fmt,...);
	String &vformat(const char *fmt, va_list var);   

	//Utility
private:
	void init(int size=0, const char *str=0, int length=0);

	//Access
public:
	String();
	explicit String(char ch);
	String(const String& str);
	explicit String(int size);
	String(const char *str, int size=0);
	~String();
};

unsigned long HashKey(const char *str);
#endif

}

#endif
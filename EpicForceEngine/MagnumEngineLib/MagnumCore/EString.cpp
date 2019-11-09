///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "EString.h"
using namespace Magnum;

const int String_null_data[4]={0,0,0,0};
const char *String_null=(const char *)&String_null_data[3];
char String_chin[2];
const int HEADER_SIZE=sizeof(char *)+sizeof(int)+sizeof(int)+sizeof(unsigned int);
const int HEADER_OFFSET=HEADER_SIZE-sizeof(char *);

namespace{
inline int slic(const char *sub_string, int length, int &index, char string_char)
{
  return (length==(index=(sub_string[index]==string_char)?index+1:
      (toupper(sub_string[0])==toupper(string_char))));
}
}

char *String::Buffer::allocate(int length)
{
   assert(length>=0);
   if(!length) return (char *)String_null;
   char *mem=new char[HEADER_SIZE+length+1];
   Buffer buf(mem+HEADER_OFFSET);
   buf.length=0;
   buf.maximum=length;
   buf.flags=0;
   buf.block=0;
   buf.index=0;
   *buf.buffer=0;
   return buf.buffer; 
}

void String::Buffer::release(char *b)
{
   assert(b);
   Buffer buf(b);
   char *mem=b-HEADER_OFFSET;
   if(buf.maximum>0)
      delete [] mem;
}

bool String::dirty()
{
   Buffer buf(data);
   if(!buf.maximum)
     return false;
   return (buf.flags&Buffer::DIRTY)!=0;
}

void String::dirty(bool set)
{
   Buffer buf(data);
   if(!buf.maximum)
     return;
   if(set)
   {
      buf.flags|=Buffer::DIRTY;
   }
   else
   {
      buf.flags&=~Buffer::DIRTY;
   }
}

String::Buffer::Buffer(char *b):
   buffer(b),
   length(*(int *)(b-sizeof(char *))),
   maximum(*(int *)(b-sizeof(char *)-sizeof(int))),
   flags(*(unsigned char *)(b-sizeof(char *)-sizeof(int)-sizeof(int))),
   block(*(unsigned char *)(b-sizeof(char *)-sizeof(int)-sizeof(int)+sizeof(unsigned char))),
   index(*(unsigned short *)(b-sizeof(char *)-sizeof(int)-sizeof(int)+sizeof(unsigned char)+sizeof(unsigned char)))
{ 
   assert(b);
}

int String::reset()
{
   return reset((int)strlen(data));
}

int String::reset(int len)
{
   assert(len<=capacity());
   dirty(true);
   data[len]=0;
   Buffer b(data);  
   return b.length=len;
}

// these are taken out of the header, some may need to be inlined fro optimization

String &String::cat(const String &str){return cat(str.data,str.length());} 
String &String::cat(char c){String_chin[0]=c;cat(String_chin);return *this;} 
char String::operator[](int at) const {assert(valid(at)); return data[at];}
char &String::operator[](int at){assert(valid(at));return data[at];}
int String::length() const  {return *(int *)(data-sizeof(char *));}
int String::length(const char *s){return (int)strlen(s);}
int String::capacity() const  {return *(int *)(data-sizeof(char *)-sizeof(int));}
const char *String::text(int off) const {assert(off>=0&&off<=length()); return &data[off];}
int String::valid(int index) const {return (index<length()&&index>=0);}
char String::back() const {assert(length()); return data[length()-1];}
char& String::back() {assert(length()); return data[length()-1];}

bool String::isSpace(int index) const
{   
   assert(valid(index));
   return(data[index]==' '||data[index]=='\f'||data[index]=='\n'||
           data[index]=='\r'||data[index]=='\t'||data[index]=='\v');
}
bool String::isNumberSpace(int index) const
{
   assert(valid(index));
   return (isSpace(index)||
            data[index]=='0'||data[index]=='$'||data[index]=='%'||
            data[index]=='*'||data[index]=='('||data[index]=='@'||
            data[index]=='#');
}

bool String::isInteger() const
{
	if(length()==0)
		return false;

	if( !((data[0]>='0' && data[0]<='9') || data[0]=='+' || data[0]=='-') )
		return false;

	for(int i=1;i<length();i++)
	{
		if( !(data[i]>='0' && data[i]<='9') )
			return false;
	}

	return true;
}
//int String::find(const String &other, int start){return find((const char *)other.data,start);} 

double  String::toDouble()const{return atof(*this);}
float   String::toFloat()const{return (float)atof(*this);}
long    String::toLong()const{return toInteger();}
//unsigned long   String::toDWord() const;  
//int     String::toInteger() const; 
short   String::toShort()const{return (short)toInteger();}
unsigned short    String::toWord()const{return (unsigned short)toDWord();}
char    String::toChar()const{return get(0);}
unsigned char    String::toByte()const{return (unsigned char)toDWord();}
String &String::from(double f){return format("%f",f);}
String &String::from(float f){return format("%f",f);}
String &String::from(long n){return format("%d",n);}
String &String::from(unsigned d){return format("%x",d);}
String &String::from(unsigned long d){return format("%x",d);}
String &String::from(int d){return format("%d",d);}
String &String::from(short d){return format("%d",d);}
String &String::from(unsigned short d){return format("%x",d);}
String &String::from(char c){return format("%c",c);}
String &String::from(unsigned char d){return format("%x",d);}
String &String::from(bool b){copy(b?"true":"false");return *this;}

String::operator const char *() const {return data;}
bool String::operator==(const String& other) const {return !compare(other);}
bool String::operator==(const char *str) const {return !compare(str);}
bool String::operator==(char ch) const {return !compare(ch);}

bool String::operator!=(const String& other) const {return compare(other)!=0;}
bool String::operator!=(const char *str) const {return compare(str)!=0;}
bool String::operator!=(char ch) const {return compare(ch)!=0;}

bool String::operator>(const String& other) const {return 0<compare(other);}
bool String::operator>(const char *str) const {return 0<compare(str);}
bool String::operator>(char ch) const {return 0<compare(ch);}

bool String::operator>=(const String& other) const {return 0<=compare(other);}
bool String::operator>=(const char *str) const {return 0<=compare(str);}
bool String::operator>=(char ch) const {return 0<=compare(ch);}

bool String::operator<(const String& other) const {return 0>compare(other);}
bool String::operator<(const char *str) const {return 0>compare(str);}
bool String::operator<(char ch) const {return 0>compare(ch);}

bool String::operator<=(const String& other) const {return 0>=compare(other);}
bool String::operator<=(const char *str) const {return 0>=compare(str);}
bool String::operator<=(char ch) const {return 0>=compare(ch);}

//String &String::operator=(const Data &src){copy(src.text,src.text.length());return *this;}
String &String::operator=(const String &src){copy(src.data,src.length());return *this;}
String &String::operator=(const char *str){copy(str);return *this;}
String &String::operator=(char c){String_chin[0]=c;copy(String_chin,1);return *this;}
String &String::operator+=(const String& str){return cat(str);}
String &String::operator+=(char ch){return cat(ch);}
String &String::operator+=(const char *str){return cat(str);}

// end

String &String::toLower()
{
	for(int i=0;i<length();i++)
	{
		unsigned char d = (unsigned char)data[i];

		if (192 <= d && d <= 223 && d != 215) // if upper cased extended character
			data[i] += 32;
		else
			data[i]=(char)tolower(data[i]);
	}
	return *this;
}

String &String::toUpper()
{
	for(int i=0;i<length();i++)
	{
		unsigned char d = (unsigned char)data[i];

		if (224 <= d && d != 247) // if lower cased extended character
			data[i] -= 32;
		else
			data[i]=(char)toupper(data[i]);
	}
	return *this;
}

char String::get(int at) const {assert(valid(at));return data[at];}
char String::put(int at, char ch){assert(valid(at));return data[at]=ch;}

String &String::replace(char from, char to)
{  
   for(int i=0;i<length();i++)
       if(data[i]==from)
          data[i]=to;
   return *this;
}

void String::empty()
{  
   release();
   init();
}

void String::release()
{
   Buffer::release(data);
}

char *String::allocate(int len)
{
   return Buffer::allocate(len);
}

bool String::grow(int len)
{
   if(len<=capacity())
      return false;

   char *p=allocate(len);
   Buffer b(p);

   if(length())
   {
      memcpy(p,data,(unsigned int)length());
      b.length=length();
   }

   release();
   data=p;
   return true; 
}

String &String::attach(char *buffer_)
{
   release();
   if(buffer_)
      data=buffer_;
   return *this;
}

char *String::detach()
{  
   if(!capacity()) return 0;
   char *b=data;
   data=Buffer::allocate(0);
   return b;
}

String &String::pad(int length_)
{
   int len=length();
	if(len>=length_) return *this;
   grow(length_);
   memset(data+len,' ',(unsigned int)(length_-len));
   reset(length_);
   return *this;
}

String &String::trunc(int off)
{
   if(!off||!length()) 
      return *this;
   int len=length();
   if(off>0&&off<=len)
     len-=off;
   if(off<0&&off>=-len)
   {
     off=-off;
     for(int i=0;i<len-off;i++)
       data[i]=data[i+off];
     len-=off;
   }
   reset(len);
   return *this;
}

String &String::chop(int at)
{
   assert(valid(at));
   if(at==0) empty();
   else
   {
      Buffer b(data);
      data[at]=0;
      b.length=at;
   }
   return *this;
}

String &String::cat(const char *str, int cat_len_)
{
   if(!str)
      return *this;
   int len=length();
   int cat_len=cat_len_?cat_len_:length(str);
   int old_len=len;
   if(!cat_len) 
      return *this;
   grow(len=old_len+cat_len);
   memcpy(data+old_len,str,(unsigned int)cat_len);
   reset(len);
   return *this;
}

String &String::vformat(const char *fmt, va_list var)
{
   char buf[1600];
   int len = vsprintf(buf, fmt, var);
   if(!len) empty();
   else
   { 
     grow(len);
     memcpy(data,buf,(unsigned long)len);
     reset(len);
   }
   return *this; 
}

String &String::format(const char *fmt,...)
{
   va_list marker;
   va_start(marker,fmt);
   return vformat(fmt, marker);
}

const char *String::copy(const char *buffer_, int length_)
{
    if(!buffer_||buffer_==String_null) 
    {
      empty();
      return 0;
    }

    if(!*buffer_)
    {
      if(data==String_null)
        return 0;
      reset(0);
      return data;
    }

    if(!length_) 
      length_=length(buffer_);
    grow(length_);
    Buffer b(data);
    b.length=length_;
    
    memcpy(data,buffer_,(unsigned int)length_);

    reset(length_);
    return data;
}

int String::compare(const char *other, int e) const{return e?strncasecmp(*this,other,(unsigned int)e):strcasecmp(*this,other);}
int String::compare(const String &other, int e) const{return e?strncasecmp(*this,other,(unsigned int)e):strcasecmp(*this,other);}
int String::compareCase(const char *other, int e) const{return e?strncmp(*this,other,(unsigned int)e):strcmp(*this,other);}
int String::compareCase(const String &other, int e) const{return e?strncmp(*this,other,(unsigned int)e):strcmp(*this,other);}

int String::compare(char ch) const
{
   if(length()!=1)
     return length()-1;
   return data[0]-ch;
} 

unsigned long String::toDWord() const
{
   unsigned long t,n=0;
   //char *p=data;
   int i;
   for(i=0;i<length();i++)
     if(!isNumberSpace(i)) 
        break;
   if(i&&'X'==toupper(data[i])&&'0'==data[i-1])
   {
      for(i++;i<length();i++)
        if(!isNumberSpace(i))
           break;
      for(;i<length()&&isxdigit(data[i]);i++)
      {
        t=(unsigned int)(isdigit(data[i])?data[i]-'0':toupper(data[i])-'A');
        n=n*0x00000010+t;
      }
   }
   else
     for(;i<length()&&isdigit(data[i]);i++)
        n=n*10UL+data[i]-'0';
   return n;
}

const char *String::line(const char *text, int max_)
{
   if(!text||!*text) return 0;
   grow(max_+1);
   int i=0;
   for(;i<max_;i++)
     switch(data[i]=text[i])
     {
         case '\n':
           reset(i);		  
           return &text[i+1];

         case '\r': 
           reset(i);
           return &text[i+2];

         case '\0':
           reset(i);
           return &text[i];
     }
   reset(i);
   return &text[i];
}

int String::trim(int flag)
{
  int len=length();
  if(!len) return 0;
  if(flag>-1)
    while(len>0)
    {
       if(!isSpace(len-1))
          break;
       data[--len]='\0';
    }

  if(!len) 
  {
      empty();
      return 0;
  } 

  if(flag<1)
  {
     int off=0; 
     while(isSpace(off)) 
       off++;
     len-=off;
     memcpy(data,data+off,(unsigned int)len);
  }

  if(!len) empty();
  else reset(len);
  return len;
}

int String::strip(const char *token)
{
  if(!length()) return 0;
  int i=0,j=0;
  while(data[j])
  {
    int n=0;
    while(token[n]) if(data[j]==token[n]) break; else n++;
    data[token[n]?i:i++]=data[j++];
  }
  reset(i);
  return i;
}

int String::token(const char *str, int start) const
{
   for(int i=start;i<length();i++)
      for(int j=0;str[j];j++)
        if(str[j]==data[i])
           return i+1;
   return 0;
}

int String::find(const char *sub, int start) const
{
  if(!valid(start)) return 0;
  int index=0,len=length(sub);
  for(int i=start;i<length();i++)
    if(slic(sub,len,index,data[i]))
      return i+1;
  return 0;
}

int String::find(char ch, int start, int index) const 
{
   if(!valid(start)) return 0;
   for(int i=start;i<length();i++)
   {
      if(toupper(data[i])==toupper(ch))
      {
         if(index>0)
            return find(ch,i+1,index-1);
         return i+1;
      }
   }   
   return 0;
}

String String::word(char delim, int position) const
{
   int last,off=0;
   do 
     if(!(off=find(delim,last=off)))
	   if(position)
	      return (char *)0;
	   else break;
   while(position--);
   if(!off&&!last) 
     return *this;
   if(!off)
     return extract(last);
   if(off==1)
     return (char *)0;
   return extract(last,off-1);
}

String String::extract(int from, int length_) const
{
   if(from>length())
     return (char *)0;
   String s(length_);
   return s.copy(&data[from],length_);
}

int String::count(char ch) const
{ 
  int c,i;
  for(c=0,i=0;i<length();i++)
    if(ch==data[i])
      ++c;
  return c; 
}
int String::countSequence(char ch, int start) const
{ 
  int c,i;
  for(c=0,i=start;i<length();i++)
    if(ch==data[i])
	  c++;
	else if(c) break;
  return c;
}

int String::isBlank() const
{
   int i;
   for(i=0;i<length();i++) 
     //if(!isSpace(data[i]))
     if(!isSpace(i))
	   return 0;
   return 1;
} 

String &String::move(int from, int to, int len)
{
   if(len+to>length())
      grow(len+to);
   int length_=to+len;
   char *d=data+to,*s=data+from;
   if(s<d && d<s+len)
      for(d+=len,s+=len;0<len;--len)
         *--d=*--s; 
   else for(;0<len;--len)
           *d++=*s++;
   reset(length_);
   return *this;
}

String &String::erase(int from, int to)
{
    assert(!(from<0));
    assert(from<to);
    if(from<length())
    {
        while(to<length())
          data[from++]=data[to++];
        reset(from);
    }
    return *this;
}

String &String::erase(int index)
{
    return erase(index,index+1);
}

String &String::insert(char ch, int off)
{
   move(off,off+1,length()-off);
   data[off]=ch;
   return *this;
}

String &String::insert(const char *str, int at, int len)
{
   if(!str) 
     return *this;
   if(!len) 
     if(!(len=length(str)))
       return *this;
   move(at,at+len,length()-at);
   for(int i=at;i<at+len;i++)
      data[i]=*str++;
   return *this;
}

bool String::toBool() const
{
   if(!length()) return false;

   if(get(0)=='0') return false;

   if(toupper(get(0))=='N')
   {
      if(length()==1) return false;
      if(!compare("NO")) return false;
   }

   if(toupper(get(0))=='F')
   {
      if(length()==1) return false;
      if(!compare("FALSE")) return false;
   }

   return true;
 }

int String::toInteger() const
{
   return atoi(text());
}

int String::toMoney() const
{
   if(!length()) return 0;
   int i,neg;
   long val=0L;
   char *s=data;
   while(isNumberSpace(*s)) s++;
   s+=(neg=*s=='-');
   while(*s)
   { if(*s==',') {s++; continue;}
     if(!isdigit(*s)) break;
     val=val*10L+*s++-'0';
   }
   if(*s=='.') s++;
   for(i=0;i<2;i++)
     val=val*10L+(!isdigit(*s)?0L:*s++-'0');
   return neg?-val:val;
}

String &String::fromMoney(int money)
{
   grow(30);
   reset(sprintf(data,"%d",money));
   int i=3-length();
   if(i>0) while(i--) insert('0');
   insert('.',length()-2);
   return *this;
}

String::~String()
{
   release();
}

void String::init(int size, const char *str, int length)
{
   assert(size>=0);
   if(!size)
   {
      data=(char *)String_null;
      return;
   }
   data=Buffer::allocate(size);
   if(str)
   {
      if(length) memcpy(data,str,(unsigned int)length);    
      else length=(int)strlen(strcpy(data,str));
   }
   reset(length);
   dirty(false);
}

String::String(){init();}

String::String(char ch)
{
   if(!ch) init();
   else
   {
      String_chin[0]=ch; 
      init(1,String_chin,1);
   }
}

String::String(int size_)
{
   init(size_);
}

String::String(const char *str, int length)
{
   assert(length>=0);
   if(!str) init(); 
   else
   if(length) init(length,str,length); 
   else
   {
      int len=(int)strlen(str);
      init(len,str,len);
   }
}

String::String(const String &other)
{
   if(this==&other) return;
   init(other.length(),other.data,other.length());
}

unsigned long Magnum::HashKey(const char *str) 
{
	unsigned long i=0, j=0, k=0, key=0;
	
	for(;i = (long)tolower(str[j++]);)						
	{
		key = (key << 4) + i;
		if((k = key & 0xF0000000L) != 0)
			key = (key ^ (k >> 24)) & (~k);
	}	

	return (key & 0x7FFFFFFF);
}


CCC = g++
CCFLAGS= -O2
LEX = flex
LFLAGS= -8     
YACC= bison 
YFLAGS= -d -t -y

RM = /bin/rm -f

testparser: glsl.tab.o lex.yy.o tinystr.o tinyxml.o tinyxmlerror.o tinyxmlparser.o
		${CCC} ${CCFLAGS} glsl.tab.o lex.yy.o tinystr.o tinyxml.o tinyxmlerror.o tinyxmlparser.o -o testparser

tinystr.o: tinystr.cpp tinystr.h
		${CCC} -c tinystr.cpp

tinyxml.o: tinyxml.cpp tinyxml.h
		${CCC} -c tinyxml.cpp

tinyxmlerror.o: tinyxmlerror.cpp
		${CCC} -c tinyxmlerror.cpp

tinyxmlparser.o: tinyxmlparser.cpp
		${CCC} -c tinyxmlparser.cpp
		
glsl.tab.o: glsl.y
		${YACC} ${YFLAGS} glsl.y -o glsl.tab.c
		${CCC} ${CCFLAGS} glsl.tab.c -c 

lex.yy.o: glsl.l
	${LEX} $(LFLAGS) glsl.l
	${CCC} ${CCFLAGS} lex.yy.c -c
		
clean:
	/bin/rm -f glsl.yy.* glsl.tab.* *.o testparser
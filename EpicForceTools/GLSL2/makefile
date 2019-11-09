CCC = g++
CCFLAGS= -O2
LEX = flex
LFLAGS= 
YACC= bison 
YFLAGS= 

RM = /bin/rm -f

parser: Parser.cpp Lexer.cpp expression.cpp main.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp
		${CCC} ${CCFLAGS} Parser.cpp Lexer.cpp expression.cpp main.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp -o parser

Parser.cpp: Parser.y
		${YACC} ${YFLAGS} Parser.y

Lexer.cpp: Lexer.l
		${LEX} $(LFLAGS) Lexer.l

clean:
		/bin/rm -f Lexer.h Lexer.cpp Parser.h Parser.cpp *.o parser
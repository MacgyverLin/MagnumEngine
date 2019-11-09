%{
/*
 * Lexer.l file
 * To generate the lexical analyzer run: "flex Lexer.l"
 */
#include "tinyxml.h"
#include "Parser.h"
#include <stdio.h>

char *trim(char *src)
{
	int len = strlen(src);
	if(len<=2)
		return "";
	else
	{
		src[len-1] = 0;
		return &src[1];
	}
}
%}
 
%option outfile="Lexer.cpp" header-file="Lexer.h"
%option warn
%option reentrant noyywrap never-interactive nounistd
%option bison-bridge
%option yylineno

%%
"=="      																return EQ;
"!="     																return NE;
"<"      																return LT;
"<="     																return LE;
">"      																return GT;
">="     																return GE;
"+"      																return PLUS;
"-"      																return MINUS;
"*"      																return MULT;
"/"      																return DIVIDE;
"="     																return ASSIGN;
"&"																		return BITWISE_AND;
"|"																		return BITWISE_OR;
"~"																		return BITWISE_NOT;
"&&"																	return AND;
"||"																	return OR;
"!"																		return NOT;
cullmode				yylval->text=yytext;							return CULLMODE_TOKEN;
alphablendenable        yylval->text=yytext;							return ALPHABLENDENABLE_TOKEN;
blendop                 yylval->text=yytext;							return BLENDOP_TOKEN;
colorwriteenable        yylval->text=yytext;							return COLORWRITEENABLE_TOKEN;
destblend               yylval->text=yytext;							return DESTBLEND_TOKEN;
fillmode                yylval->text=yytext;							return FILLMODE_TOKEN;
shademode               yylval->text=yytext;							return SHADEMODE_TOKEN;
srcblend                yylval->text=yytext;							return SRCBLEND_TOKEN;
stencilenable           yylval->text=yytext;							return STENCILENABLE_TOKEN;
stencilfail             yylval->text=yytext;							return STENCILFAIL_TOKEN;
stencilfunc             yylval->text=yytext;							return STENCILFUNC_TOKEN;
stencilmask             yylval->text=yytext;							return STENCILMASK_TOKEN;
stencilzpass            yylval->text=yytext;							return STENCILZPASS_TOKEN;
stencilref              yylval->text=yytext;							return STENCILREF_TOKEN;
stencilwritemask        yylval->text=yytext;							return STENCILWRITEMASK_TOKEN;
stencilzfail            yylval->text=yytext;							return STENCILZFAIL_TOKEN;
zenable                 yylval->text=yytext;							return ZENABLE_TOKEN;
zfunc                   yylval->text=yytext;							return ZFUNC_TOKEN;
zwriteenable            yylval->text=yytext;							return ZWRITEENABLE_TOKEN;
vertexshader            yylval->text=yytext;							return VERTEXSHADER_TOKEN;
geometryshader	        yylval->text=yytext;							return GEOMETRYSHADER_TOKEN;
pixelshader	            yylval->text=yytext;							return PIXELSHADER_TOKEN;
Attributes				yylval->text=yytext; 							return ATTRIBUTES_TOKEN;
Uniforms				yylval->text=yytext; 							return UNIFORMS_TOKEN;
Technique				yylval->text=yytext;							return TECHNIQUE_TOKEN;
Pass					yylval->text=yytext;							return PASS_TOKEN;
attribute				yylval->text=yytext; 							return ATTRIBUTE_GLSL_TOKEN;
uniform					yylval->text=yytext; 							return UNIFORM_GLSL_TOKEN;
varying					yylval->text=yytext; 							return VARYING_GLSL_TOKEN;
lowp					yylval->text=yytext; 							return LOWP_GLSL_TOKEN;
midp					yylval->text=yytext; 							return MIDP_GLSL_TOKEN;
highp					yylval->text=yytext; 							return HIGHP_GLSL_TOKEN;
bool					yylval->text=yytext; 							return BOOL_GLSL_TOKEN;
bvec2					yylval->text=yytext; 							return BVEC2_GLSL_TOKEN;
bvec3					yylval->text=yytext; 							return BVEC3_GLSL_TOKEN;
bvec4					yylval->text=yytext; 							return BVEC4_GLSL_TOKEN;
int						yylval->text=yytext; 							return INT_GLSL_TOKEN;
ivec2					yylval->text=yytext; 							return IVEC2_GLSL_TOKEN;
ivec3					yylval->text=yytext; 							return IVEC3_GLSL_TOKEN;
ivec4					yylval->text=yytext; 							return IVEC4_GLSL_TOKEN;
float					yylval->text=yytext; 							return FLOAT_GLSL_TOKEN;
vec2					yylval->text=yytext; 							return VEC2_GLSL_TOKEN;
vec3					yylval->text=yytext; 							return VEC3_GLSL_TOKEN;
vec4					yylval->text=yytext; 							return VEC4_GLSL_TOKEN;
mat2					yylval->text=yytext; 							return MAT2_GLSL_TOKEN;
mat3					yylval->text=yytext; 							return MAT3_GLSL_TOKEN;
mat4					yylval->text=yytext; 							return MAT4_GLSL_TOKEN;
sampler2D				yylval->text=yytext; 							return SAMPLER2D_GLSL_TOKEN;
samplerCube 			yylval->text=yytext; 							return SAMPLERCUBE_GLSL_TOKEN;
[0][xX][a-fA-F0-9]+     yylval->iValue=strtol(yytext, 0, 16);			return HEXNUMBER;
[0-9]+					yylval->iValue=atoi(yytext); 		 			return NUMBER;
[0-9]+\.[0-9]+ 			yylval->fValue=atof(yytext); 					return FLOAT;
[a-zA-Z][a-zA-Z0-9]*    yylval->text=yytext;		 					return WORD;
[a-zA-Z0-9\/.-]+        yylval->text=yytext;		 					return FILENAME;
\".+\"					yylval->text=trim(yytext);						return STRING_LITERAL;
\{[0-9\.,]+[,]?\}		yylval->text=trim(yytext);						return INITIALIZER;
\"                      												return QUOTE;
\[[0-9]+\]              yylval=(YYSTYPE *)strdup(trim(yytext));			return ARRAYINDEX;
\{                      												return OBRACE;
\}                      												return EBRACE;
:                       												return COLON;
;                       												return SEMICOLON;
,                       												return COMMA;
\n
[ \t]+                  /* ignore whitespace */;
%%

int yyerror(TiXmlNode **node, yyscan_t scanner, const char *msg)
{
    fprintf(stderr,"Error:%s\n",msg); return 0;
}

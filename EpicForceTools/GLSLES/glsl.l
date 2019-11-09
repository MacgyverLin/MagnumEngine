%{
#include <stdio.h>
#include "glsl.tab.h"

extern int yylval;

extern "C"
{
	int yylex(void); 
}

int line_num = 1;

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

%%
"=="      														return EQ;
"!="     														return NE;
"<"      														return LT;
"<="     														return LE;
">"      														return GT;
">="     														return GE;
"+"      														return PLUS;
"-"      														return MINUS;
"*"      														return MULT;
"/"      														return DIVIDE;
"="     														return ASSIGN;
"&"																return BITWISE_AND;
"|"																return BITWISE_OR;
"~"																return BITWISE_NOT;
"&&"															return AND;
"||"															return OR;
"!"																return NOT;

blendenable						yylval=(int)strdup(yytext);		return BLENDENABLE_TOKEN					 ;
blendmodergb					yylval=(int)strdup(yytext);		return BLENDMODERGB_TOKEN					 ;
blendsrcfactorrgb				yylval=(int)strdup(yytext);		return BLENDSRCFACTORRGB_TOKEN				 ;
blenddstfactorrgb				yylval=(int)strdup(yytext);		return BLENDDSTFACTORRGB_TOKEN				 ;
blendmodealpha					yylval=(int)strdup(yytext);		return BLENDMODEALPHA_TOKEN					 ;
blendsrcfactoralpha				yylval=(int)strdup(yytext);		return BLENDSRCFACTORALPHA_TOKEN			 ;
blenddstfactoralpha				yylval=(int)strdup(yytext);		return BLENDDSTFACTORALPHA_TOKEN			 ;
blendmode						yylval=(int)strdup(yytext);		return BLENDMODE_TOKEN						 ;
blendsrcfactor					yylval=(int)strdup(yytext);		return BLENDSRCFACTOR_TOKEN					 ;
blenddstfactor					yylval=(int)strdup(yytext);		return BLENDDSTFACTOR_TOKEN					 ;
colormask						yylval=(int)strdup(yytext);		return COLORMASK_TOKEN						 ;
cullenable						yylval=(int)strdup(yytext);		return CULLENABLE_TOKEN						 ;
cullmode						yylval=(int)strdup(yytext);		return CULLMODE_TOKEN						 ;
depthtestenable					yylval=(int)strdup(yytext);		return DEPTHTESTENABLE_TOKEN				 ;
depthwriteenable				yylval=(int)strdup(yytext);		return DEPTHWRITEENABLE_TOKEN				 ;
depthtestmode					yylval=(int)strdup(yytext);		return DEPTHTESTMODE_TOKEN					 ;
linewidth						yylval=(int)strdup(yytext);		return LINEWIDTH_TOKEN						 ;
polygonoffsetfactor				yylval=(int)strdup(yytext);		return POLYGONOFFSETFACTOR_TOKEN			 ;
polygonoffsetunit				yylval=(int)strdup(yytext);		return POLYGONOFFSETUNIT_TOKEN				 ;
scissor							yylval=(int)strdup(yytext);		return SCISSOR_TOKEN						 ;
stenciltestenable				yylval=(int)strdup(yytext);		return STENCILTESTENABLE_TOKEN				 ;
stenciltestmodefront			yylval=(int)strdup(yytext);		return STENCILTESTMODEFRONT_TOKEN			 ;
stenciltestreffront				yylval=(int)strdup(yytext);		return STENCILTESTREFFRONT_TOKEN			 ;
stenciltestmaskfront			yylval=(int)strdup(yytext);		return STENCILTESTMASKFRONT_TOKEN			 ;
stenciltestwritemaskfront		yylval=(int)strdup(yytext);		return STENCILTESTWRITEMASKFRONT_TOKEN		 ;
stencilopfailfront				yylval=(int)strdup(yytext);		return STENCILOPFAILFRONT_TOKEN				 ;
stencilopzpassfront				yylval=(int)strdup(yytext);		return STENCILOPZPASSFRONT_TOKEN			 ;
stencilopzfailfront				yylval=(int)strdup(yytext);		return STENCILOPZFAILFRONT_TOKEN			 ;
stenciltestmodeback				yylval=(int)strdup(yytext);		return STENCILTESTMODEBACK_TOKEN			 ;
stenciltestrefback				yylval=(int)strdup(yytext);		return STENCILTESTREFBACK_TOKEN				 ;
stenciltestmaskback				yylval=(int)strdup(yytext);		return STENCILTESTMASKBACK_TOKEN			 ;
stenciltestwritemaskback		yylval=(int)strdup(yytext);		return STENCILTESTWRITEMASKBACK_TOKEN		 ;
stencilopfailback				yylval=(int)strdup(yytext);		return STENCILOPFAILBACK_TOKEN				 ;
stencilopzpassback				yylval=(int)strdup(yytext);		return STENCILOPZPASSBACK_TOKEN				 ;
stencilopzfailback				yylval=(int)strdup(yytext);		return STENCILOPZFAILBACK_TOKEN				 ;
stenciltestmode					yylval=(int)strdup(yytext);		return STENCILTESTMODE_TOKEN				 ;
stenciltestref					yylval=(int)strdup(yytext);		return STENCILTESTREF_TOKEN					 ;
stenciltestmask					yylval=(int)strdup(yytext);		return STENCILTESTMASK_TOKEN				 ;
stenciltestwritemask			yylval=(int)strdup(yytext);		return STENCILTESTWRITEMASK_TOKEN			 ;
stencilopfail					yylval=(int)strdup(yytext);		return STENCILOPFAIL_TOKEN					 ;
stencilopzpass					yylval=(int)strdup(yytext);		return STENCILOPZPASS_TOKEN					 ;
stencilopzfail					yylval=(int)strdup(yytext);		return STENCILOPZFAIL_TOKEN					 ;
viewport						yylval=(int)strdup(yytext);		return VIEWPORT_TOKEN						 ;
vertexshader					yylval=(int)strdup(yytext);		return VERTEXSHADER_TOKEN					 ;
geometryshader					yylval=(int)strdup(yytext);		return GEOMETRYSHADER_TOKEN					 ;
pixelshader						yylval=(int)strdup(yytext);		return PIXELSHADER_TOKEN					 ;

Attributes				yylval=(int)strdup(yytext); 			return ATTRIBUTES_TOKEN;
Uniforms				yylval=(int)strdup(yytext); 			return UNIFORMS_TOKEN;
Technique				yylval=(int)strdup(yytext);				return TECHNIQUE_TOKEN;
Pass					yylval=(int)strdup(yytext);				return PASS_TOKEN;
attribute				yylval=(int)strdup(yytext); 			return ATTRIBUTE_GLSL_TOKEN;
uniform					yylval=(int)strdup(yytext); 			return UNIFORM_GLSL_TOKEN;
varying					yylval=(int)strdup(yytext); 			return VARYING_GLSL_TOKEN;
lowp					yylval=(int)strdup(yytext); 			return LOWP_GLSL_TOKEN;
midp					yylval=(int)strdup(yytext); 			return MIDP_GLSL_TOKEN;
highp					yylval=(int)strdup(yytext); 			return HIGHP_GLSL_TOKEN;
bool					yylval=(int)strdup(yytext); 			return BOOL_GLSL_TOKEN;
bvec2					yylval=(int)strdup(yytext); 			return BVEC2_GLSL_TOKEN;
bvec3					yylval=(int)strdup(yytext); 			return BVEC3_GLSL_TOKEN;
bvec4					yylval=(int)strdup(yytext); 			return BVEC4_GLSL_TOKEN;
int						yylval=(int)strdup(yytext); 			return INT_GLSL_TOKEN;
ivec2					yylval=(int)strdup(yytext); 			return IVEC2_GLSL_TOKEN;
ivec3					yylval=(int)strdup(yytext); 			return IVEC3_GLSL_TOKEN;
ivec4					yylval=(int)strdup(yytext); 			return IVEC4_GLSL_TOKEN;
float					yylval=(int)strdup(yytext); 			return FLOAT_GLSL_TOKEN;
vec2					yylval=(int)strdup(yytext); 			return VEC2_GLSL_TOKEN;
vec3					yylval=(int)strdup(yytext); 			return VEC3_GLSL_TOKEN;
vec4					yylval=(int)strdup(yytext); 			return VEC4_GLSL_TOKEN;
mat2					yylval=(int)strdup(yytext); 			return MAT2_GLSL_TOKEN;
mat3					yylval=(int)strdup(yytext); 			return MAT3_GLSL_TOKEN;
mat4					yylval=(int)strdup(yytext); 			return MAT4_GLSL_TOKEN;
sampler2D				yylval=(int)strdup(yytext); 			return SAMPLER2D_GLSL_TOKEN;
samplerCube 			yylval=(int)strdup(yytext); 			return SAMPLERCUBE_GLSL_TOKEN;
[0][xX][a-fA-F0-9]+     yylval=(int)strtol(yytext, 0, 16);		return HEXNUMBER;
[0-9]+					yylval=atoi(yytext); 		 			return NUMBER;
[0-9]+\.[0-9]+ 			yylval=atof(yytext); 		 			return FLOAT;
[a-zA-Z][a-zA-Z0-9]*    yylval=(int)strdup(yytext);		 		return WORD;
[a-zA-Z0-9\/.-]+        yylval=(int)strdup(yytext);		 		return FILENAME;
\".+\"					yylval=(int)strdup(trim(yytext));		return STRING_LITERAL;
\{[0-9\.,]+[,]?\}		yylval=(int)strdup(trim(yytext));		return INITIALIZER;
\"                      										return QUOTE;
\[[0-9]+\]              yylval=(int)strdup(trim(yytext));		return ARRAYINDEX;
\{                      										return OBRACE;
\}                      										return EBRACE;
:                       										return COLON;
;                       										return SEMICOLON;
,                       										return COMMA;
\n
[ \t]+                  /* ignore whitespace */;
%%
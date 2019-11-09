%{
 
/*
 * Parser.y file
 * To generate the parser run: "bison Parser.y"
 */
 
#include "tinyxml.h"
#include "Parser.h"
#include "Lexer.h"
 
int yyerror(TiXmlNode **node, yyscan_t scanner, const char *msg);
 
%}
 
%output  "Parser.cpp"
%defines "Parser.h"
%define api.pure
%lex-param   { yyscan_t scanner }
%parse-param { TiXmlNode **node }
%parse-param { yyscan_t scanner }
 
%union {
    int iValue;
	float fValue;
	const char *text;
    TiXmlNode *node;
}
 

%start visualeffect

%token EQ NE LT LE GT GE PLUS MINUS MULT DIVIDE ASSIGN
		BITWISE_AND BITWISE_OR BITWISE_NOT AND OR NOT
		CULLMODE_TOKEN ALPHABLENDENABLE_TOKEN BLENDOP_TOKEN COLORWRITEENABLE_TOKEN
		DESTBLEND_TOKEN FILLMODE_TOKEN SHADEMODE_TOKEN SRCBLEND_TOKEN 
		STENCILENABLE_TOKEN STENCILFAIL_TOKEN STENCILFUNC_TOKEN STENCILMASK_TOKEN STENCILZPASS_TOKEN STENCILREF_TOKEN
		STENCILWRITEMASK_TOKEN STENCILZFAIL_TOKEN
		ZENABLE_TOKEN ZFUNC_TOKEN ZWRITEENABLE_TOKEN
		VERTEXSHADER_TOKEN GEOMETRYSHADER_TOKEN PIXELSHADER_TOKEN
		VISUALEFFECT_TOKEN ATTRIBUTES_TOKEN UNIFORMS_TOKEN TECHNIQUE_TOKEN PASS_TOKEN
		ATTRIBUTE_GLSL_TOKEN UNIFORM_GLSL_TOKEN VARYING_GLSL_TOKEN
		LOWP_GLSL_TOKEN MIDP_GLSL_TOKEN HIGHP_GLSL_TOKEN
		BOOL_GLSL_TOKEN BVEC2_GLSL_TOKEN BVEC3_GLSL_TOKEN BVEC4_GLSL_TOKEN
		INT_GLSL_TOKEN IVEC2_GLSL_TOKEN IVEC3_GLSL_TOKEN IVEC4_GLSL_TOKEN
		FLOAT_GLSL_TOKEN VEC2_GLSL_TOKEN VEC3_GLSL_TOKEN VEC4_GLSL_TOKEN
		MAT2_GLSL_TOKEN MAT3_GLSL_TOKEN MAT4_GLSL_TOKEN 
		SAMPLER2D_GLSL_TOKEN SAMPLERCUBE_GLSL_TOKEN
		HEXNUMBER NUMBER FLOAT WORD FILENAME
		QUOTE OBRACE EBRACE SEMICOLON COLON COMMA ENDL STRING_LITERAL INITIALIZER ARRAYINDEX
 
%type<val> 	exp NUM
%type<name> ID

%%
 
visualeffect: visualeffectStatements
        {
			$$ = new TiXmlNode();
				
			$$->LinkEndChild($1);
	
			printf("visualeffect\n");
        }
        ;
		
visualeffectStatements:
		/* empty*/
		{
			$$ = new TiXmlNode();

			printf("visualeffectStatements\n");
		}
		| visualeffectStatements visualeffectStatement
		{
			$$ = $1;
			
			$1->LinkEndChild(new TiXmlNode());
			
			printf("visualeffectStatements\n");
		}
		;

visualeffectStatement: 
		/* empty*/
		| attributes
		;		
 
/* -------------------------------- Attributes -------------------------------- */
attributes:
        ATTRIBUTES_TOKEN attributeContent
        {
			printf("attributes\n");
        }
        ;

attributeContent:
        OBRACE validAttributeStatements EBRACE 
		{
		}
		
validAttributeStatements:	
		/* empty*/
        | validAttributeStatements validAttributeStatement
		{
			printf("validAttributeStatements\n");
		}
        ;

validAttributeStatement: 
		ATTRIBUTE_GLSL_TOKEN variableTypeTokens WORD SEMICOLON
        {
			printf("validAttributeStatement\n");
        }
		;
		

/* -------------------------------- Misc  -------------------------------- */
precisionTypeTokens:
		LOWP_GLSL_TOKEN
		| MIDP_GLSL_TOKEN
		| HIGHP_GLSL_TOKEN

variableTypeTokens:
		BOOL_GLSL_TOKEN
		| BVEC2_GLSL_TOKEN
		| BVEC3_GLSL_TOKEN
		| BVEC4_GLSL_TOKEN
		| INT_GLSL_TOKEN
		| IVEC2_GLSL_TOKEN
		| IVEC3_GLSL_TOKEN
		| IVEC4_GLSL_TOKEN
		| FLOAT_GLSL_TOKEN
		| VEC2_GLSL_TOKEN
		| VEC3_GLSL_TOKEN
		| VEC4_GLSL_TOKEN
		| MAT2_GLSL_TOKEN
		| MAT3_GLSL_TOKEN
		| MAT4_GLSL_TOKEN
		| SAMPLER2D_GLSL_TOKEN
		| SAMPLERCUBE_GLSL_TOKEN		
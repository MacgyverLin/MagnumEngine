%{
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <string>
#include <vector>
#include <list>
using namespace std;

extern int line_num;

void yyerror(const char *str)
{
	fprintf(stderr,"error: %s\n",str);
}

extern "C" int yyparse(void); 
extern "C" int yylex(void);   
extern "C" int yywrap() 
{ 
	return 1;
} 
 
extern FILE *yyin;

#include <sstream>
#include <iostream>
using namespace std;

list<string> tempStrings;
char buf[100000];

const char *prepareString(const char *a_fmtstr, ...)
{
	va_list argptr;
	va_start(argptr, a_fmtstr);

	vsnprintf(buf, 100000, a_fmtstr, argptr);
	
	va_end(argptr);
	
	tempStrings.push_back(buf);
	
	return tempStrings.back().c_str();
}

int main(int argc, char **argv) 
{
	if(argc!=2)
	{
		printf("testlex infile\n");
		return -1;
	}
	
	// open a file handle to a particular file:
	FILE *fptr = fopen(argv[1], "rt");
	// make sure it's valid:
	if (!fptr) 
	{
		printf("I can't open %s!\n", argv[1]);
		return -1;
	}

	// set lex to read from it instead of defaulting to STDIN:
	yyin = fptr;
	
	// lex through the input:
	yyparse();
	// yylex();

	fclose(fptr);

	return 0;
}

%}

%start visualeffect

%token	EQ NE LT LE GT GE PLUS MINUS MULT DIVIDE ASSIGN
		BITWISE_AND BITWISE_OR BITWISE_NOT AND OR NOT
		BLENDENABLE_TOKEN 
		BLENDMODERGB_TOKEN BLENDSRCFACTORRGB_TOKEN BLENDDSTFACTORRGB_TOKEN
		BLENDMODEALPHA_TOKEN BLENDSRCFACTORALPHA_TOKEN BLENDDSTFACTORALPHA_TOKEN
		BLENDMODE_TOKEN BLENDSRCFACTOR_TOKEN BLENDDSTFACTOR_TOKEN
		COLORMASK_TOKEN
		CULLENABLE_TOKEN CULLMODE_TOKEN
		DEPTHTESTENABLE_TOKEN DEPTHWRITEENABLE_TOKEN DEPTHTESTMODE_TOKEN
		LINEWIDTH_TOKEN
		POLYGONOFFSETFACTOR_TOKEN POLYGONOFFSETUNIT_TOKEN
		SCISSOR_TOKEN
		STENCILTESTENABLE_TOKEN
		STENCILTESTMODEFRONT_TOKEN STENCILTESTREFFRONT_TOKEN STENCILTESTMASKFRONT_TOKEN STENCILTESTWRITEMASKFRONT_TOKEN	
		STENCILOPFAILFRONT_TOKEN STENCILOPZPASSFRONT_TOKEN STENCILOPZFAILFRONT_TOKEN 
		STENCILTESTMODEBACK_TOKEN STENCILTESTREFBACK_TOKEN STENCILTESTMASKBACK_TOKEN STENCILTESTWRITEMASKBACK_TOKEN
		STENCILOPFAILBACK_TOKEN STENCILOPZPASSBACK_TOKEN STENCILOPZFAILBACK_TOKEN STENCILTESTMODE_TOKEN	
		STENCILTESTREF_TOKEN STENCILTESTMASK_TOKEN STENCILTESTWRITEMASK_TOKEN 
		STENCILOPFAIL_TOKEN STENCILOPZPASS_TOKEN STENCILOPZFAIL_TOKEN
		VIEWPORT_TOKEN
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
%%

visualeffect: visualeffectStatements
        {
			//const char *str = prepareString("<VisualEffect>\n%s</VisualEffect>", $1);
			const char *str = prepareString("<VisualEffect>\n%s</VisualEffect>", $1);
			
			$$ = (YYSTYPE)str;
			
			printf(str);
        }
        ;
		
visualContent:
        OBRACE visualeffectStatements EBRACE
		{
			$$ = $2;
		}
		
visualeffectStatements:
		/* empty*/
		{
			$$ = (YYSTYPE)"";
		}
		| visualeffectStatements visualeffectStatement
		{
			$$ = (YYSTYPE)prepareString("%s%s", $1, $2);
		}
		;

visualeffectStatement: 
		/* empty*/
		{
			$$ = (YYSTYPE)"";
		}		
		| attributes		
		| uniforms
		| technique		
		;

/* -------------------------------- Attributes -------------------------------- */
attributes:
        ATTRIBUTES_TOKEN attributeContent
        {
			$$ = (YYSTYPE)prepareString("\t<Attributes>\n%s\t</Attributes>\n", $2);
        }
        ;

attributeContent:
        OBRACE validAttributeStatements EBRACE 
		{
			$$ = $2;
		}
		
validAttributeStatements:	
		/* empty*/
		{
			$$ = (YYSTYPE)"";
		}
        | validAttributeStatements validAttributeStatement
		{
			$$ = (YYSTYPE)prepareString("%s%s", $1, $2);
		}
        ;

validAttributeStatement: 
		ATTRIBUTE_GLSL_TOKEN variableTypeTokens WORD COLON WORD SEMICOLON
        {
			$$ = (YYSTYPE)prepareString("\t\t<Attribute type=\"%s\" format=\"%s\" name=\"%s\" semantic=\"%s\" />\n", $2, $2, $3, $5);
        }
		;			
		
/* -------------------------------- Uniforms -------------------------------- */
uniforms:
        UNIFORMS_TOKEN uniformContent
        {
			$$ = (YYSTYPE)prepareString("\t<Uniforms>\n%s\t</Uniforms>\n", $2);
        }
        ;

uniformContent:
        OBRACE validUniformStatements EBRACE
		{
			$$ = $2;
		}		

validUniformStatements:	
		/* empty*/
		{
			$$ = (YYSTYPE)"";
		}		
        | validUniformStatements validUniformStatement
		{
			$$ = (YYSTYPE)prepareString("%s%s", $1, $2);
		}
        ;

validUniformStatement:
		UNIFORM_GLSL_TOKEN variableTypeTokens WORD ARRAYINDEX SEMICOLON
        {
			$$ = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", $2, $3, $4, "", "");
        }                                                                                                                     
		| UNIFORM_GLSL_TOKEN precisionTypeTokens variableTypeTokens WORD ARRAYINDEX SEMICOLON                                 
        {   
			$$ = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", $2, $3, $4, $5, "", "");
        }                                                                                                                     
		| UNIFORM_GLSL_TOKEN variableTypeTokens WORD ARRAYINDEX COLON WORD SEMICOLON                                          
        {                    
			$$ = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", $2, $3, $4, $6, "");
        }                                                                                                                     
		| UNIFORM_GLSL_TOKEN precisionTypeTokens variableTypeTokens WORD ARRAYINDEX COLON WORD SEMICOLON                      
        {   
			$$ = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", $2, $3, $4, $5, $7, "");
        }                                                                                                                     
		| UNIFORM_GLSL_TOKEN variableTypeTokens WORD ARRAYINDEX ASSIGN INITIALIZER SEMICOLON                                  
        {                        
			$$ = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", $2, $3, $4, "", $6);
        }                                                                                                                     
		| UNIFORM_GLSL_TOKEN precisionTypeTokens variableTypeTokens WORD ARRAYINDEX ASSIGN INITIALIZER SEMICOLON              
        {
			$$ = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", $2, $3, $4, $5, "", $7);
        }                                                                                                                     
		| UNIFORM_GLSL_TOKEN variableTypeTokens WORD ARRAYINDEX COLON WORD ASSIGN INITIALIZER SEMICOLON                       
        {
			$$ = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", $2, $3, $4, $6, $8);
        }                                                                                                                     
		| UNIFORM_GLSL_TOKEN precisionTypeTokens variableTypeTokens WORD ARRAYINDEX COLON WORD ASSIGN INITIALIZER SEMICOLON   
        {
			$$ = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", $2, $3, $4, $5, $7, $9);
        }                                                                                                                     
		| UNIFORM_GLSL_TOKEN variableTypeTokens WORD SEMICOLON                                                                
        {
			$$ = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", $2, $3, "1", "", "");
        }                                                                                                                     
		| UNIFORM_GLSL_TOKEN precisionTypeTokens variableTypeTokens WORD SEMICOLON                                            
        {
			$$ = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", $2, $3, $4, "1", "", "");
        }                                                                                                                     
		| UNIFORM_GLSL_TOKEN variableTypeTokens WORD COLON WORD SEMICOLON                                                     
        {
			$$ = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", $2, $3, "1", $5, "");
        }                                                                                                                     
		| UNIFORM_GLSL_TOKEN precisionTypeTokens variableTypeTokens WORD COLON WORD SEMICOLON                                 
        {
			$$ = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", $2, $3, $4, "1", $6, "");
        }                                                                                                                     
		| UNIFORM_GLSL_TOKEN variableTypeTokens WORD ASSIGN INITIALIZER SEMICOLON                                             
        {
			$$ = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", $2, $3, "1", "", $5);
        }                                                                                                                     
		| UNIFORM_GLSL_TOKEN precisionTypeTokens variableTypeTokens WORD ASSIGN INITIALIZER SEMICOLON                         
        {
			$$ = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", $2, $3, $4, "1", "", $6);
        }                                                                                                                     
		| UNIFORM_GLSL_TOKEN variableTypeTokens WORD COLON WORD ASSIGN INITIALIZER SEMICOLON                                  
        {
			$$ = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", $2, $3, "1", $5, $7);
        }                                                                                                                     
		| UNIFORM_GLSL_TOKEN precisionTypeTokens variableTypeTokens WORD COLON WORD ASSIGN INITIALIZER SEMICOLON              
        {
			$$ = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", $2, $3, $4, "1", $6, $8);
        }
		;
		
precisionTypeTokens:
		| LOWP_GLSL_TOKEN
		| MIDP_GLSL_TOKEN
		| HIGHP_GLSL_TOKEN

variableTypeTokens:
		| BOOL_GLSL_TOKEN
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
		
/* -------------------------------- Technique -------------------------------- */
technique:
        TECHNIQUE_TOKEN WORD techniqueContent
        {
			$$ = (YYSTYPE)prepareString("\t<Technique name=\"%s\">\n%s\t</Technique>\n", $2, $3);
        }
        ;
		
techniqueContent:
        OBRACE passeStatements EBRACE 
		{
			$$ = $2;
		}				

passeStatements:
		/* empty*/
		{
			$$ = (YYSTYPE)"";
		}		
        | passeStatements passeStatement
		{
			$$ = (YYSTYPE)prepareString("%s%s", $1, $2);
		}
        ;

passeStatement:
        PASS_TOKEN WORD passContent
        {
			$$ = (YYSTYPE)prepareString("\t\t<Pass name=\"%s\">\n%s\t\t</Pass>\n", $2, $3);
        }
        ;
		
passContent:
		OBRACE validRenderStateStatements vertexShaderStatement pixelShaderStatement EBRACE
		{
			$$ = (YYSTYPE)prepareString("\t\t\t<RenderStates>\n%s\t\t\t</RenderStates>\n%s%s", $2, $3, $4);
		}

validRenderStateStatements:
		/* empty*/
		{
			$$ = (YYSTYPE)"";
		}			
        | validRenderStateStatements validRenderStateStatement
		{
			$$ = (YYSTYPE)prepareString("%s%s", $1, $2);
		}		
        ;

validRenderStateStatement: 
		/* empty*/
		| blendEnableStatement 
		| blendModeRgbStatement | blendSrcFactorRgbStatement | blendDstfactorRgbStatement
		| blendModeAlphaStatement | blendSrcFactorAlphaStatement | blendDstFactorAlphaStatement
		| blendModeStatement | blendSrcFactorStatement | blendDstFactorStatement
		| colorMaskStatement
		| cullEnableStatement | cullModeStatement
		| depthTestEnableStatement | depthWriteEnableStatement | depthTestModeStatement
		| lineWidthStatement
		| polygonOffsetFactorStatement | polygonOffsetUnitStatement
		| scissorStatement
		| stencilTestEnableStatement
		| stencilTestmodeFrontStatement | stencilTestRefFrontStatement | stencilTestMaskFrontStatement | stencilTestWriteMaskFrontStatement	
		| stencilOpFailFrontStatement | stencilOpZPassFrontStatement | stencilopZFailFrontStatement 
		| stencilTestModeBackStatement | stencilTestRefBackStatement | stencilTestMaskBackStatement | stencilTestWriteMaskBackStatement
		| stencilOpFailBackStatement | stencilOpZPassBackStatement | stencilOpZFailBackStatement 
		| stencilTestModeStatement | stencilTestRefStatement | stencilTestMaskStatement | stencilTestWriteMaskStatement
		| stencilOpFailStatement | stencilOpZPassStatement | stencilOpZFailStatement 
		| viewportStatement
		| vertexShaderStatement | geometryShaderStatement | pixelShaderStatement
		;

/*--------------------------- Render State -------------------------------------------*/
blendEnableStatement:					BLENDENABLE_TOKEN				 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
blendModeRgbStatement:					BLENDMODERGB_TOKEN				 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
blendSrcFactorRgbStatement:				BLENDSRCFACTORRGB_TOKEN			 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
blendDstfactorRgbStatement:				BLENDDSTFACTORRGB_TOKEN			 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
blendModeAlphaStatement:				BLENDMODEALPHA_TOKEN			 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
blendSrcFactorAlphaStatement:			BLENDSRCFACTORALPHA_TOKEN		 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
blendDstFactorAlphaStatement:			BLENDDSTFACTORALPHA_TOKEN		 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
blendModeStatement:						BLENDMODE_TOKEN					 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
blendSrcFactorStatement:				BLENDSRCFACTOR_TOKEN			 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
blendDstFactorStatement:				BLENDDSTFACTOR_TOKEN			 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
colorMaskStatement:						COLORMASK_TOKEN					 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
cullEnableStatement:					CULLENABLE_TOKEN				 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
cullModeStatement:						CULLMODE_TOKEN					 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
depthTestEnableStatement:				DEPTHTESTENABLE_TOKEN			 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
depthWriteEnableStatement:				DEPTHWRITEENABLE_TOKEN			 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
depthTestModeStatement:					DEPTHTESTMODE_TOKEN				 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
lineWidthStatement:						LINEWIDTH_TOKEN					 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
polygonOffsetFactorStatement:			POLYGONOFFSETFACTOR_TOKEN		 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
polygonOffsetUnitStatement:				POLYGONOFFSETUNIT_TOKEN			 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
scissorStatement:						SCISSOR_TOKEN					 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
stencilTestEnableStatement:				STENCILTESTENABLE_TOKEN			 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
stencilTestmodeFrontStatement:			STENCILTESTMODEFRONT_TOKEN		 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
stencilTestRefFrontStatement:			STENCILTESTREFFRONT_TOKEN		 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
stencilTestMaskFrontStatement:			STENCILTESTMASKFRONT_TOKEN		 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
stencilTestWriteMaskFrontStatement:		STENCILTESTWRITEMASKFRONT_TOKEN	 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
stencilOpFailFrontStatement:			STENCILOPFAILFRONT_TOKEN		 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
stencilOpZPassFrontStatement:			STENCILOPZPASSFRONT_TOKEN		 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
stencilopZFailFrontStatement:			STENCILOPZFAILFRONT_TOKEN		 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
stencilTestModeBackStatement:			STENCILTESTMODEBACK_TOKEN		 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
stencilTestRefBackStatement:			STENCILTESTREFBACK_TOKEN		 ASSIGN hexORInteger SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=0x%08lx/>\n", $1, $3);
        }
		;	
stencilTestMaskBackStatement:			STENCILTESTMASKBACK_TOKEN		 ASSIGN hexORInteger SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=0x%08lx/>\n", $1, $3);
        }
		;	
stencilTestWriteMaskBackStatement:		STENCILTESTWRITEMASKBACK_TOKEN	 ASSIGN hexORInteger SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=0x%08lx/>\n", $1, $3);
        }
		;	
stencilOpFailBackStatement:				STENCILOPFAILBACK_TOKEN			 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
stencilOpZPassBackStatement:			STENCILOPZPASSBACK_TOKEN		 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
stencilOpZFailBackStatement:			STENCILOPZFAILBACK_TOKEN		 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
stencilTestModeStatement:				STENCILTESTMODE_TOKEN			 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
stencilTestRefStatement:				STENCILTESTREF_TOKEN			 ASSIGN hexORInteger SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=0x%08lx/>\n", $1, $3);
        }
		;	
stencilTestMaskStatement:				STENCILTESTMASK_TOKEN			 ASSIGN hexORInteger SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=0x%08lx/>\n", $1, $3);
        }
		;	
stencilTestWriteMaskStatement:			STENCILTESTWRITEMASK_TOKEN		 ASSIGN hexORInteger SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=0x%08lx/>\n", $1, $3);
        }
		;	
stencilOpFailStatement:					STENCILOPFAIL_TOKEN				 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
stencilOpZPassStatement:				STENCILOPZPASS_TOKEN			 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
stencilOpZFailStatement:				STENCILOPZFAIL_TOKEN			 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
viewportStatement:						VIEWPORT_TOKEN					 ASSIGN WORD SEMICOLON
        {
				$$ = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", $1, $3);
        }
		;
vertexShaderStatement:					VERTEXSHADER_TOKEN OBRACE STRING_LITERAL SEMICOLON EBRACE
        {
                $$ = (YYSTYPE)prepareString("\t\t\t<VertexShader code=\"%s\">\n\t\t\t</VertexShader>\n", $4);
        }
		;	
geometryShaderStatement:				GEOMETRYSHADER_TOKEN OBRACE STRING_LITERAL SEMICOLON EBRACE
        {
                $$ = (YYSTYPE)prepareString("\t\t\t<GeometryShader code=\"%s\">\n\t\t\t</GeometryShader>\n", $4);
        }
		;	
pixelShaderStatement:					PIXELSHADER_TOKEN OBRACE STRING_LITERAL SEMICOLON EBRACE
        {
                $$ = (YYSTYPE)prepareString("\t\t\t<PixelShader code=\"%s\">\n\t\t\t</PixelShader>\n", $4);
        }
		;	

/* --------- Util --------- */
hexORInteger:
		/* empty*/
		| NUMBER
		| HEXNUMBER	
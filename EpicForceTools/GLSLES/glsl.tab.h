/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     EQ = 258,
     NE = 259,
     LT = 260,
     LE = 261,
     GT = 262,
     GE = 263,
     PLUS = 264,
     MINUS = 265,
     MULT = 266,
     DIVIDE = 267,
     ASSIGN = 268,
     BITWISE_AND = 269,
     BITWISE_OR = 270,
     BITWISE_NOT = 271,
     AND = 272,
     OR = 273,
     NOT = 274,
     BLENDENABLE_TOKEN = 275,
     BLENDMODERGB_TOKEN = 276,
     BLENDSRCFACTORRGB_TOKEN = 277,
     BLENDDSTFACTORRGB_TOKEN = 278,
     BLENDMODEALPHA_TOKEN = 279,
     BLENDSRCFACTORALPHA_TOKEN = 280,
     BLENDDSTFACTORALPHA_TOKEN = 281,
     BLENDMODE_TOKEN = 282,
     BLENDSRCFACTOR_TOKEN = 283,
     BLENDDSTFACTOR_TOKEN = 284,
     COLORMASK_TOKEN = 285,
     CULLENABLE_TOKEN = 286,
     CULLMODE_TOKEN = 287,
     DEPTHTESTENABLE_TOKEN = 288,
     DEPTHWRITEENABLE_TOKEN = 289,
     DEPTHTESTMODE_TOKEN = 290,
     LINEWIDTH_TOKEN = 291,
     POLYGONOFFSETFACTOR_TOKEN = 292,
     POLYGONOFFSETUNIT_TOKEN = 293,
     SCISSOR_TOKEN = 294,
     STENCILTESTENABLE_TOKEN = 295,
     STENCILTESTMODEFRONT_TOKEN = 296,
     STENCILTESTREFFRONT_TOKEN = 297,
     STENCILTESTMASKFRONT_TOKEN = 298,
     STENCILTESTWRITEMASKFRONT_TOKEN = 299,
     STENCILOPFAILFRONT_TOKEN = 300,
     STENCILOPZPASSFRONT_TOKEN = 301,
     STENCILOPZFAILFRONT_TOKEN = 302,
     STENCILTESTMODEBACK_TOKEN = 303,
     STENCILTESTREFBACK_TOKEN = 304,
     STENCILTESTMASKBACK_TOKEN = 305,
     STENCILTESTWRITEMASKBACK_TOKEN = 306,
     STENCILOPFAILBACK_TOKEN = 307,
     STENCILOPZPASSBACK_TOKEN = 308,
     STENCILOPZFAILBACK_TOKEN = 309,
     STENCILTESTMODE_TOKEN = 310,
     STENCILTESTREF_TOKEN = 311,
     STENCILTESTMASK_TOKEN = 312,
     STENCILTESTWRITEMASK_TOKEN = 313,
     STENCILOPFAIL_TOKEN = 314,
     STENCILOPZPASS_TOKEN = 315,
     STENCILOPZFAIL_TOKEN = 316,
     VIEWPORT_TOKEN = 317,
     VERTEXSHADER_TOKEN = 318,
     GEOMETRYSHADER_TOKEN = 319,
     PIXELSHADER_TOKEN = 320,
     VISUALEFFECT_TOKEN = 321,
     ATTRIBUTES_TOKEN = 322,
     UNIFORMS_TOKEN = 323,
     TECHNIQUE_TOKEN = 324,
     PASS_TOKEN = 325,
     ATTRIBUTE_GLSL_TOKEN = 326,
     UNIFORM_GLSL_TOKEN = 327,
     VARYING_GLSL_TOKEN = 328,
     LOWP_GLSL_TOKEN = 329,
     MIDP_GLSL_TOKEN = 330,
     HIGHP_GLSL_TOKEN = 331,
     BOOL_GLSL_TOKEN = 332,
     BVEC2_GLSL_TOKEN = 333,
     BVEC3_GLSL_TOKEN = 334,
     BVEC4_GLSL_TOKEN = 335,
     INT_GLSL_TOKEN = 336,
     IVEC2_GLSL_TOKEN = 337,
     IVEC3_GLSL_TOKEN = 338,
     IVEC4_GLSL_TOKEN = 339,
     FLOAT_GLSL_TOKEN = 340,
     VEC2_GLSL_TOKEN = 341,
     VEC3_GLSL_TOKEN = 342,
     VEC4_GLSL_TOKEN = 343,
     MAT2_GLSL_TOKEN = 344,
     MAT3_GLSL_TOKEN = 345,
     MAT4_GLSL_TOKEN = 346,
     SAMPLER2D_GLSL_TOKEN = 347,
     SAMPLERCUBE_GLSL_TOKEN = 348,
     HEXNUMBER = 349,
     NUMBER = 350,
     FLOAT = 351,
     WORD = 352,
     FILENAME = 353,
     QUOTE = 354,
     OBRACE = 355,
     EBRACE = 356,
     SEMICOLON = 357,
     COLON = 358,
     COMMA = 359,
     ENDL = 360,
     STRING_LITERAL = 361,
     INITIALIZER = 362,
     ARRAYINDEX = 363
   };
#endif
/* Tokens.  */
#define EQ 258
#define NE 259
#define LT 260
#define LE 261
#define GT 262
#define GE 263
#define PLUS 264
#define MINUS 265
#define MULT 266
#define DIVIDE 267
#define ASSIGN 268
#define BITWISE_AND 269
#define BITWISE_OR 270
#define BITWISE_NOT 271
#define AND 272
#define OR 273
#define NOT 274
#define BLENDENABLE_TOKEN 275
#define BLENDMODERGB_TOKEN 276
#define BLENDSRCFACTORRGB_TOKEN 277
#define BLENDDSTFACTORRGB_TOKEN 278
#define BLENDMODEALPHA_TOKEN 279
#define BLENDSRCFACTORALPHA_TOKEN 280
#define BLENDDSTFACTORALPHA_TOKEN 281
#define BLENDMODE_TOKEN 282
#define BLENDSRCFACTOR_TOKEN 283
#define BLENDDSTFACTOR_TOKEN 284
#define COLORMASK_TOKEN 285
#define CULLENABLE_TOKEN 286
#define CULLMODE_TOKEN 287
#define DEPTHTESTENABLE_TOKEN 288
#define DEPTHWRITEENABLE_TOKEN 289
#define DEPTHTESTMODE_TOKEN 290
#define LINEWIDTH_TOKEN 291
#define POLYGONOFFSETFACTOR_TOKEN 292
#define POLYGONOFFSETUNIT_TOKEN 293
#define SCISSOR_TOKEN 294
#define STENCILTESTENABLE_TOKEN 295
#define STENCILTESTMODEFRONT_TOKEN 296
#define STENCILTESTREFFRONT_TOKEN 297
#define STENCILTESTMASKFRONT_TOKEN 298
#define STENCILTESTWRITEMASKFRONT_TOKEN 299
#define STENCILOPFAILFRONT_TOKEN 300
#define STENCILOPZPASSFRONT_TOKEN 301
#define STENCILOPZFAILFRONT_TOKEN 302
#define STENCILTESTMODEBACK_TOKEN 303
#define STENCILTESTREFBACK_TOKEN 304
#define STENCILTESTMASKBACK_TOKEN 305
#define STENCILTESTWRITEMASKBACK_TOKEN 306
#define STENCILOPFAILBACK_TOKEN 307
#define STENCILOPZPASSBACK_TOKEN 308
#define STENCILOPZFAILBACK_TOKEN 309
#define STENCILTESTMODE_TOKEN 310
#define STENCILTESTREF_TOKEN 311
#define STENCILTESTMASK_TOKEN 312
#define STENCILTESTWRITEMASK_TOKEN 313
#define STENCILOPFAIL_TOKEN 314
#define STENCILOPZPASS_TOKEN 315
#define STENCILOPZFAIL_TOKEN 316
#define VIEWPORT_TOKEN 317
#define VERTEXSHADER_TOKEN 318
#define GEOMETRYSHADER_TOKEN 319
#define PIXELSHADER_TOKEN 320
#define VISUALEFFECT_TOKEN 321
#define ATTRIBUTES_TOKEN 322
#define UNIFORMS_TOKEN 323
#define TECHNIQUE_TOKEN 324
#define PASS_TOKEN 325
#define ATTRIBUTE_GLSL_TOKEN 326
#define UNIFORM_GLSL_TOKEN 327
#define VARYING_GLSL_TOKEN 328
#define LOWP_GLSL_TOKEN 329
#define MIDP_GLSL_TOKEN 330
#define HIGHP_GLSL_TOKEN 331
#define BOOL_GLSL_TOKEN 332
#define BVEC2_GLSL_TOKEN 333
#define BVEC3_GLSL_TOKEN 334
#define BVEC4_GLSL_TOKEN 335
#define INT_GLSL_TOKEN 336
#define IVEC2_GLSL_TOKEN 337
#define IVEC3_GLSL_TOKEN 338
#define IVEC4_GLSL_TOKEN 339
#define FLOAT_GLSL_TOKEN 340
#define VEC2_GLSL_TOKEN 341
#define VEC3_GLSL_TOKEN 342
#define VEC4_GLSL_TOKEN 343
#define MAT2_GLSL_TOKEN 344
#define MAT3_GLSL_TOKEN 345
#define MAT4_GLSL_TOKEN 346
#define SAMPLER2D_GLSL_TOKEN 347
#define SAMPLERCUBE_GLSL_TOKEN 348
#define HEXNUMBER 349
#define NUMBER 350
#define FLOAT 351
#define WORD 352
#define FILENAME 353
#define QUOTE 354
#define OBRACE 355
#define EBRACE 356
#define SEMICOLON 357
#define COLON 358
#define COMMA 359
#define ENDL 360
#define STRING_LITERAL 361
#define INITIALIZER 362
#define ARRAYINDEX 363




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;



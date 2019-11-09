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
     CULLMODE_TOKEN = 275,
     ALPHABLENDENABLE_TOKEN = 276,
     BLENDOP_TOKEN = 277,
     COLORWRITEENABLE_TOKEN = 278,
     DESTBLEND_TOKEN = 279,
     FILLMODE_TOKEN = 280,
     SHADEMODE_TOKEN = 281,
     SRCBLEND_TOKEN = 282,
     STENCILENABLE_TOKEN = 283,
     STENCILFAIL_TOKEN = 284,
     STENCILFUNC_TOKEN = 285,
     STENCILMASK_TOKEN = 286,
     STENCILZPASS_TOKEN = 287,
     STENCILREF_TOKEN = 288,
     STENCILWRITEMASK_TOKEN = 289,
     STENCILZFAIL_TOKEN = 290,
     ZENABLE_TOKEN = 291,
     ZFUNC_TOKEN = 292,
     ZWRITEENABLE_TOKEN = 293,
     VERTEXSHADER_TOKEN = 294,
     GEOMETRYSHADER_TOKEN = 295,
     PIXELSHADER_TOKEN = 296,
     VISUALEFFECT_TOKEN = 297,
     ATTRIBUTES_TOKEN = 298,
     UNIFORMS_TOKEN = 299,
     TECHNIQUE_TOKEN = 300,
     PASS_TOKEN = 301,
     ATTRIBUTE_GLSL_TOKEN = 302,
     UNIFORM_GLSL_TOKEN = 303,
     VARYING_GLSL_TOKEN = 304,
     LOWP_GLSL_TOKEN = 305,
     MIDP_GLSL_TOKEN = 306,
     HIGHP_GLSL_TOKEN = 307,
     BOOL_GLSL_TOKEN = 308,
     BVEC2_GLSL_TOKEN = 309,
     BVEC3_GLSL_TOKEN = 310,
     BVEC4_GLSL_TOKEN = 311,
     INT_GLSL_TOKEN = 312,
     IVEC2_GLSL_TOKEN = 313,
     IVEC3_GLSL_TOKEN = 314,
     IVEC4_GLSL_TOKEN = 315,
     FLOAT_GLSL_TOKEN = 316,
     VEC2_GLSL_TOKEN = 317,
     VEC3_GLSL_TOKEN = 318,
     VEC4_GLSL_TOKEN = 319,
     MAT2_GLSL_TOKEN = 320,
     MAT3_GLSL_TOKEN = 321,
     MAT4_GLSL_TOKEN = 322,
     SAMPLER2D_GLSL_TOKEN = 323,
     SAMPLERCUBE_GLSL_TOKEN = 324,
     HEXNUMBER = 325,
     NUMBER = 326,
     FLOAT = 327,
     WORD = 328,
     FILENAME = 329,
     QUOTE = 330,
     OBRACE = 331,
     EBRACE = 332,
     SEMICOLON = 333,
     COLON = 334,
     COMMA = 335,
     ENDL = 336,
     STRING_LITERAL = 337,
     INITIALIZER = 338,
     ARRAYINDEX = 339
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
#define CULLMODE_TOKEN 275
#define ALPHABLENDENABLE_TOKEN 276
#define BLENDOP_TOKEN 277
#define COLORWRITEENABLE_TOKEN 278
#define DESTBLEND_TOKEN 279
#define FILLMODE_TOKEN 280
#define SHADEMODE_TOKEN 281
#define SRCBLEND_TOKEN 282
#define STENCILENABLE_TOKEN 283
#define STENCILFAIL_TOKEN 284
#define STENCILFUNC_TOKEN 285
#define STENCILMASK_TOKEN 286
#define STENCILZPASS_TOKEN 287
#define STENCILREF_TOKEN 288
#define STENCILWRITEMASK_TOKEN 289
#define STENCILZFAIL_TOKEN 290
#define ZENABLE_TOKEN 291
#define ZFUNC_TOKEN 292
#define ZWRITEENABLE_TOKEN 293
#define VERTEXSHADER_TOKEN 294
#define GEOMETRYSHADER_TOKEN 295
#define PIXELSHADER_TOKEN 296
#define VISUALEFFECT_TOKEN 297
#define ATTRIBUTES_TOKEN 298
#define UNIFORMS_TOKEN 299
#define TECHNIQUE_TOKEN 300
#define PASS_TOKEN 301
#define ATTRIBUTE_GLSL_TOKEN 302
#define UNIFORM_GLSL_TOKEN 303
#define VARYING_GLSL_TOKEN 304
#define LOWP_GLSL_TOKEN 305
#define MIDP_GLSL_TOKEN 306
#define HIGHP_GLSL_TOKEN 307
#define BOOL_GLSL_TOKEN 308
#define BVEC2_GLSL_TOKEN 309
#define BVEC3_GLSL_TOKEN 310
#define BVEC4_GLSL_TOKEN 311
#define INT_GLSL_TOKEN 312
#define IVEC2_GLSL_TOKEN 313
#define IVEC3_GLSL_TOKEN 314
#define IVEC4_GLSL_TOKEN 315
#define FLOAT_GLSL_TOKEN 316
#define VEC2_GLSL_TOKEN 317
#define VEC3_GLSL_TOKEN 318
#define VEC4_GLSL_TOKEN 319
#define MAT2_GLSL_TOKEN 320
#define MAT3_GLSL_TOKEN 321
#define MAT4_GLSL_TOKEN 322
#define SAMPLER2D_GLSL_TOKEN 323
#define SAMPLERCUBE_GLSL_TOKEN 324
#define HEXNUMBER 325
#define NUMBER 326
#define FLOAT 327
#define WORD 328
#define FILENAME 329
#define QUOTE 330
#define OBRACE 331
#define EBRACE 332
#define SEMICOLON 333
#define COLON 334
#define COMMA 335
#define ENDL 336
#define STRING_LITERAL 337
#define INITIALIZER 338
#define ARRAYINDEX 339




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;



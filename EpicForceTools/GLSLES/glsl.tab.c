/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "glsl.y"

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



/* Line 189 of yacc.c  */
#line 150 "glsl.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 408 "glsl.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   344

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  109
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  68
/* YYNRULES -- Number of rules.  */
#define YYNRULES  159
/* YYNRULES -- Number of states.  */
#define YYNSTATES  344

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   363

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    10,    12,    14,    16,
      19,    23,    24,    27,    34,    37,    41,    42,    45,    51,
      58,    66,    75,    83,    92,   102,   113,   118,   124,   131,
     139,   146,   154,   163,   173,   174,   176,   178,   180,   181,
     183,   185,   187,   189,   191,   193,   195,   197,   199,   201,
     203,   205,   207,   209,   211,   213,   215,   219,   223,   224,
     227,   231,   237,   238,   241,   242,   244,   246,   248,   250,
     252,   254,   256,   258,   260,   262,   264,   266,   268,   270,
     272,   274,   276,   278,   280,   282,   284,   286,   288,   290,
     292,   294,   296,   298,   300,   302,   304,   306,   308,   310,
     312,   314,   316,   318,   320,   322,   324,   326,   328,   330,
     332,   334,   339,   344,   349,   354,   359,   364,   369,   374,
     379,   384,   389,   394,   399,   404,   409,   414,   419,   424,
     429,   434,   439,   444,   449,   454,   459,   464,   469,   474,
     479,   484,   489,   494,   499,   504,   509,   514,   519,   524,
     529,   534,   539,   544,   549,   555,   561,   567,   568,   570
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     110,     0,    -1,   111,    -1,    -1,   111,   112,    -1,    -1,
     113,    -1,   117,    -1,   123,    -1,    67,   114,    -1,   100,
     115,   101,    -1,    -1,   115,   116,    -1,    71,   122,    97,
     103,    97,   102,    -1,    68,   118,    -1,   100,   119,   101,
      -1,    -1,   119,   120,    -1,    72,   122,    97,   108,   102,
      -1,    72,   121,   122,    97,   108,   102,    -1,    72,   122,
      97,   108,   103,    97,   102,    -1,    72,   121,   122,    97,
     108,   103,    97,   102,    -1,    72,   122,    97,   108,    13,
     107,   102,    -1,    72,   121,   122,    97,   108,    13,   107,
     102,    -1,    72,   122,    97,   108,   103,    97,    13,   107,
     102,    -1,    72,   121,   122,    97,   108,   103,    97,    13,
     107,   102,    -1,    72,   122,    97,   102,    -1,    72,   121,
     122,    97,   102,    -1,    72,   122,    97,   103,    97,   102,
      -1,    72,   121,   122,    97,   103,    97,   102,    -1,    72,
     122,    97,    13,   107,   102,    -1,    72,   121,   122,    97,
      13,   107,   102,    -1,    72,   122,    97,   103,    97,    13,
     107,   102,    -1,    72,   121,   122,    97,   103,    97,    13,
     107,   102,    -1,    -1,    74,    -1,    75,    -1,    76,    -1,
      -1,    77,    -1,    78,    -1,    79,    -1,    80,    -1,    81,
      -1,    82,    -1,    83,    -1,    84,    -1,    85,    -1,    86,
      -1,    87,    -1,    88,    -1,    89,    -1,    90,    -1,    91,
      -1,    92,    -1,    93,    -1,    69,    97,   124,    -1,   100,
     125,   101,    -1,    -1,   125,   126,    -1,    70,    97,   127,
      -1,   100,   128,   173,   175,   101,    -1,    -1,   128,   129,
      -1,    -1,   130,    -1,   131,    -1,   132,    -1,   133,    -1,
     134,    -1,   135,    -1,   136,    -1,   137,    -1,   138,    -1,
     139,    -1,   140,    -1,   141,    -1,   142,    -1,   143,    -1,
     144,    -1,   145,    -1,   146,    -1,   147,    -1,   148,    -1,
     149,    -1,   150,    -1,   151,    -1,   152,    -1,   153,    -1,
     154,    -1,   155,    -1,   156,    -1,   157,    -1,   158,    -1,
     159,    -1,   160,    -1,   161,    -1,   162,    -1,   163,    -1,
     164,    -1,   165,    -1,   166,    -1,   167,    -1,   168,    -1,
     169,    -1,   170,    -1,   171,    -1,   172,    -1,   173,    -1,
     174,    -1,   175,    -1,    20,    13,    97,   102,    -1,    21,
      13,    97,   102,    -1,    22,    13,    97,   102,    -1,    23,
      13,    97,   102,    -1,    24,    13,    97,   102,    -1,    25,
      13,    97,   102,    -1,    26,    13,    97,   102,    -1,    27,
      13,    97,   102,    -1,    28,    13,    97,   102,    -1,    29,
      13,    97,   102,    -1,    30,    13,    97,   102,    -1,    31,
      13,    97,   102,    -1,    32,    13,    97,   102,    -1,    33,
      13,    97,   102,    -1,    34,    13,    97,   102,    -1,    35,
      13,    97,   102,    -1,    36,    13,    97,   102,    -1,    37,
      13,    97,   102,    -1,    38,    13,    97,   102,    -1,    39,
      13,    97,   102,    -1,    40,    13,    97,   102,    -1,    41,
      13,    97,   102,    -1,    42,    13,    97,   102,    -1,    43,
      13,    97,   102,    -1,    44,    13,    97,   102,    -1,    45,
      13,    97,   102,    -1,    46,    13,    97,   102,    -1,    47,
      13,    97,   102,    -1,    48,    13,    97,   102,    -1,    49,
      13,   176,   102,    -1,    50,    13,   176,   102,    -1,    51,
      13,   176,   102,    -1,    52,    13,    97,   102,    -1,    53,
      13,    97,   102,    -1,    54,    13,    97,   102,    -1,    55,
      13,    97,   102,    -1,    56,    13,   176,   102,    -1,    57,
      13,   176,   102,    -1,    58,    13,   176,   102,    -1,    59,
      13,    97,   102,    -1,    60,    13,    97,   102,    -1,    61,
      13,    97,   102,    -1,    62,    13,    97,   102,    -1,    63,
     100,   106,   102,   101,    -1,    64,   100,   106,   102,   101,
      -1,    65,   100,   106,   102,   101,    -1,    -1,    95,    -1,
      94,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   113,   113,   132,   135,   143,   146,   147,   148,   153,
     160,   167,   170,   177,   185,   192,   199,   202,   209,   213,
     217,   221,   225,   229,   233,   237,   241,   245,   249,   253,
     257,   261,   265,   269,   275,   276,   277,   278,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   301,   308,   315,   318,
     325,   332,   339,   342,   348,   350,   351,   351,   351,   352,
     352,   352,   353,   353,   353,   354,   355,   355,   356,   356,
     356,   357,   358,   358,   359,   360,   361,   361,   361,   361,
     362,   362,   362,   363,   363,   363,   363,   364,   364,   364,
     365,   365,   365,   365,   366,   366,   366,   367,   368,   368,
     368,   372,   377,   382,   387,   392,   397,   402,   407,   412,
     417,   422,   427,   432,   437,   442,   447,   452,   457,   462,
     467,   472,   477,   482,   487,   492,   497,   502,   507,   512,
     517,   522,   527,   532,   537,   542,   547,   552,   557,   562,
     567,   572,   577,   582,   587,   592,   597,   604,   606,   607
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EQ", "NE", "LT", "LE", "GT", "GE",
  "PLUS", "MINUS", "MULT", "DIVIDE", "ASSIGN", "BITWISE_AND", "BITWISE_OR",
  "BITWISE_NOT", "AND", "OR", "NOT", "BLENDENABLE_TOKEN",
  "BLENDMODERGB_TOKEN", "BLENDSRCFACTORRGB_TOKEN",
  "BLENDDSTFACTORRGB_TOKEN", "BLENDMODEALPHA_TOKEN",
  "BLENDSRCFACTORALPHA_TOKEN", "BLENDDSTFACTORALPHA_TOKEN",
  "BLENDMODE_TOKEN", "BLENDSRCFACTOR_TOKEN", "BLENDDSTFACTOR_TOKEN",
  "COLORMASK_TOKEN", "CULLENABLE_TOKEN", "CULLMODE_TOKEN",
  "DEPTHTESTENABLE_TOKEN", "DEPTHWRITEENABLE_TOKEN", "DEPTHTESTMODE_TOKEN",
  "LINEWIDTH_TOKEN", "POLYGONOFFSETFACTOR_TOKEN",
  "POLYGONOFFSETUNIT_TOKEN", "SCISSOR_TOKEN", "STENCILTESTENABLE_TOKEN",
  "STENCILTESTMODEFRONT_TOKEN", "STENCILTESTREFFRONT_TOKEN",
  "STENCILTESTMASKFRONT_TOKEN", "STENCILTESTWRITEMASKFRONT_TOKEN",
  "STENCILOPFAILFRONT_TOKEN", "STENCILOPZPASSFRONT_TOKEN",
  "STENCILOPZFAILFRONT_TOKEN", "STENCILTESTMODEBACK_TOKEN",
  "STENCILTESTREFBACK_TOKEN", "STENCILTESTMASKBACK_TOKEN",
  "STENCILTESTWRITEMASKBACK_TOKEN", "STENCILOPFAILBACK_TOKEN",
  "STENCILOPZPASSBACK_TOKEN", "STENCILOPZFAILBACK_TOKEN",
  "STENCILTESTMODE_TOKEN", "STENCILTESTREF_TOKEN", "STENCILTESTMASK_TOKEN",
  "STENCILTESTWRITEMASK_TOKEN", "STENCILOPFAIL_TOKEN",
  "STENCILOPZPASS_TOKEN", "STENCILOPZFAIL_TOKEN", "VIEWPORT_TOKEN",
  "VERTEXSHADER_TOKEN", "GEOMETRYSHADER_TOKEN", "PIXELSHADER_TOKEN",
  "VISUALEFFECT_TOKEN", "ATTRIBUTES_TOKEN", "UNIFORMS_TOKEN",
  "TECHNIQUE_TOKEN", "PASS_TOKEN", "ATTRIBUTE_GLSL_TOKEN",
  "UNIFORM_GLSL_TOKEN", "VARYING_GLSL_TOKEN", "LOWP_GLSL_TOKEN",
  "MIDP_GLSL_TOKEN", "HIGHP_GLSL_TOKEN", "BOOL_GLSL_TOKEN",
  "BVEC2_GLSL_TOKEN", "BVEC3_GLSL_TOKEN", "BVEC4_GLSL_TOKEN",
  "INT_GLSL_TOKEN", "IVEC2_GLSL_TOKEN", "IVEC3_GLSL_TOKEN",
  "IVEC4_GLSL_TOKEN", "FLOAT_GLSL_TOKEN", "VEC2_GLSL_TOKEN",
  "VEC3_GLSL_TOKEN", "VEC4_GLSL_TOKEN", "MAT2_GLSL_TOKEN",
  "MAT3_GLSL_TOKEN", "MAT4_GLSL_TOKEN", "SAMPLER2D_GLSL_TOKEN",
  "SAMPLERCUBE_GLSL_TOKEN", "HEXNUMBER", "NUMBER", "FLOAT", "WORD",
  "FILENAME", "QUOTE", "OBRACE", "EBRACE", "SEMICOLON", "COLON", "COMMA",
  "ENDL", "STRING_LITERAL", "INITIALIZER", "ARRAYINDEX", "$accept",
  "visualeffect", "visualeffectStatements", "visualeffectStatement",
  "attributes", "attributeContent", "validAttributeStatements",
  "validAttributeStatement", "uniforms", "uniformContent",
  "validUniformStatements", "validUniformStatement", "precisionTypeTokens",
  "variableTypeTokens", "technique", "techniqueContent", "passeStatements",
  "passeStatement", "passContent", "validRenderStateStatements",
  "validRenderStateStatement", "blendEnableStatement",
  "blendModeRgbStatement", "blendSrcFactorRgbStatement",
  "blendDstfactorRgbStatement", "blendModeAlphaStatement",
  "blendSrcFactorAlphaStatement", "blendDstFactorAlphaStatement",
  "blendModeStatement", "blendSrcFactorStatement",
  "blendDstFactorStatement", "colorMaskStatement", "cullEnableStatement",
  "cullModeStatement", "depthTestEnableStatement",
  "depthWriteEnableStatement", "depthTestModeStatement",
  "lineWidthStatement", "polygonOffsetFactorStatement",
  "polygonOffsetUnitStatement", "scissorStatement",
  "stencilTestEnableStatement", "stencilTestmodeFrontStatement",
  "stencilTestRefFrontStatement", "stencilTestMaskFrontStatement",
  "stencilTestWriteMaskFrontStatement", "stencilOpFailFrontStatement",
  "stencilOpZPassFrontStatement", "stencilopZFailFrontStatement",
  "stencilTestModeBackStatement", "stencilTestRefBackStatement",
  "stencilTestMaskBackStatement", "stencilTestWriteMaskBackStatement",
  "stencilOpFailBackStatement", "stencilOpZPassBackStatement",
  "stencilOpZFailBackStatement", "stencilTestModeStatement",
  "stencilTestRefStatement", "stencilTestMaskStatement",
  "stencilTestWriteMaskStatement", "stencilOpFailStatement",
  "stencilOpZPassStatement", "stencilOpZFailStatement",
  "viewportStatement", "vertexShaderStatement", "geometryShaderStatement",
  "pixelShaderStatement", "hexORInteger", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   109,   110,   111,   111,   112,   112,   112,   112,   113,
     114,   115,   115,   116,   117,   118,   119,   119,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   121,   121,   121,   121,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   123,   124,   125,   125,
     126,   127,   128,   128,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   176,   176
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     0,     1,     1,     1,     2,
       3,     0,     2,     6,     2,     3,     0,     2,     5,     6,
       7,     8,     7,     8,     9,    10,     4,     5,     6,     7,
       6,     7,     8,     9,     0,     1,     1,     1,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     0,     2,
       3,     5,     0,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     5,     5,     5,     0,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,     0,     0,     0,     4,     6,     7,
       8,    11,     9,    16,    14,     0,     0,     0,    58,    56,
      38,    10,    12,    34,    15,    17,     0,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,     0,    35,    36,    37,    38,     0,
       0,    57,    59,     0,     0,     0,     0,     0,     0,     0,
      26,     0,     0,    62,    60,     0,     0,    27,     0,     0,
       0,     0,     0,    18,     0,     0,    13,     0,     0,     0,
      19,     0,    30,     0,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    63,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
      31,     0,    29,     0,     0,     0,    22,     0,    20,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   157,   157,
     157,     0,     0,     0,     0,   157,   157,   157,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    23,     0,    21,
      32,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   159,   158,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      61,    33,     0,    24,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,     0,     0,     0,
      25,   154,   155,   156
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     7,     8,    12,    16,    22,     9,    14,
      17,    25,    48,    44,    10,    19,    26,    52,    64,    75,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   273
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -158
static const yytype_int16 yypact[] =
{
    -158,     1,    -3,  -158,   -97,   -92,   -87,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,  -158,   -86,     3,     4,  -158,  -158,
      49,  -158,  -158,    32,  -158,  -158,     2,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,   -30,  -158,  -158,  -158,    49,   -26,
     -24,  -158,  -158,   -28,   -20,   -13,   -22,   -18,   -11,   -27,
    -158,   -16,    -9,  -158,  -158,   -19,   -25,  -158,   -12,    -4,
     -15,    -6,   -23,  -158,    46,    -5,  -158,   -14,    -2,    37,
    -158,    48,  -158,    39,  -158,    45,    -1,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
      91,    92,    93,  -158,  -158,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,  -158,  -158,  -158,   129,  -158,  -158,
    -158,    88,  -158,    94,     0,    95,  -158,    96,  -158,   101,
     102,   103,   104,   105,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   130,   131,   -89,   -89,
     -89,   132,   133,   134,   178,   -89,   -89,   -89,   179,   180,
     181,   182,   183,   184,   185,   186,   190,  -158,   187,  -158,
    -158,   191,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,  -158,  -158,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
    -158,  -158,   239,  -158,  -158,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,  -158,  -158,  -158,   241,   242,   243,
    -158,  -158,  -158,  -158
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -158,    38,  -158,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,  -158,  -158,    55,  -157
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      59,     3,    66,    11,    72,   271,   272,    83,    13,    79,
      15,   181,   187,   238,    18,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,    49,   274,   275,     4,     5,     6,    53,   280,   281,
     282,    55,    50,    56,    20,    57,    23,    58,    63,    65,
      70,    71,    77,    76,    85,    78,    54,    82,   180,    60,
      61,    67,    68,    73,    74,    62,    84,    69,    80,    81,
     182,   188,   239,    51,    21,    24,    45,    46,    47,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    86,   183,   184,   185,   186,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   132,   236,   237,   240,   242,   243,
     244,   245,   246,   241,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,     0,   269,   270,   276,
     277,   278,   235,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   279,   283,   284,   285,   286,
       0,     0,     0,     0,     0,     0,     0,   290,     0,   287,
     288,   289,   291,   293,   292,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343
};

static const yytype_int16 yycheck[] =
{
      13,     0,    13,   100,    13,    94,    95,    13,   100,    13,
      97,    13,    13,    13,   100,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    23,   219,   220,    67,    68,    69,    97,   225,   226,
     227,    97,    70,    97,    71,   103,    72,    97,   100,    97,
     107,    97,   107,   102,   107,    97,    48,   102,   102,   102,
     103,   102,   103,   102,   103,   108,   102,   108,   102,   103,
     102,   102,   102,   101,   101,   101,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    97,   107,    97,   107,   102,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,   100,   100,   100,    65,   107,   102,   102,    97,    97,
      97,    97,    97,   107,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    -1,    97,    97,    97,
      97,    97,   177,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    97,    97,    97,    97,    97,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,   106,
     106,   106,   102,   102,   107,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   101,   101,   101
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   110,   111,     0,    67,    68,    69,   112,   113,   117,
     123,   100,   114,   100,   118,    97,   115,   119,   100,   124,
      71,   101,   116,    72,   101,   120,   125,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,   122,    74,    75,    76,   121,   122,
      70,   101,   126,    97,   122,    97,    97,   103,    97,    13,
     102,   103,   108,   100,   127,    97,    13,   102,   103,   108,
     107,    97,    13,   102,   103,   128,   102,   107,    97,    13,
     102,   103,   102,    13,   102,   107,    97,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     102,    13,   102,   107,    97,   107,   102,    13,   102,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,    13,   100,   100,   100,   175,   107,   102,    13,   102,
     102,   107,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    94,    95,   176,   176,   176,    97,    97,    97,    97,
     176,   176,   176,    97,    97,    97,    97,   106,   106,   106,
     101,   102,   107,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   101,   101,   101
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1464 of yacc.c  */
#line 114 "glsl.y"
    {
			//const char *str = prepareString("<VisualEffect>\n%s</VisualEffect>", $1);
			const char *str = prepareString("<VisualEffect>\n%s</VisualEffect>", (yyvsp[(1) - (1)]));
			
			(yyval) = (YYSTYPE)str;
			
			printf(str);
        }
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 132 "glsl.y"
    {
			(yyval) = (YYSTYPE)"";
		}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 136 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("%s%s", (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
		}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 143 "glsl.y"
    {
			(yyval) = (YYSTYPE)"";
		}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 154 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t<Attributes>\n%s\t</Attributes>\n", (yyvsp[(2) - (2)]));
        }
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 161 "glsl.y"
    {
			(yyval) = (yyvsp[(2) - (3)]);
		}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 167 "glsl.y"
    {
			(yyval) = (YYSTYPE)"";
		}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 171 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("%s%s", (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
		}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 178 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Attribute type=\"%s\" format=\"%s\" name=\"%s\" semantic=\"%s\" />\n", (yyvsp[(2) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]));
        }
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 186 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t<Uniforms>\n%s\t</Uniforms>\n", (yyvsp[(2) - (2)]));
        }
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 193 "glsl.y"
    {
			(yyval) = (yyvsp[(2) - (3)]);
		}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 199 "glsl.y"
    {
			(yyval) = (YYSTYPE)"";
		}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 203 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("%s%s", (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
		}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 210 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]), "", "");
        }
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 214 "glsl.y"
    {   
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", (yyvsp[(2) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(5) - (6)]), "", "");
        }
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 218 "glsl.y"
    {                    
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", (yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(6) - (7)]), "");
        }
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 222 "glsl.y"
    {   
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", (yyvsp[(2) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), "");
        }
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 226 "glsl.y"
    {                        
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", (yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), "", (yyvsp[(6) - (7)]));
        }
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 230 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", (yyvsp[(2) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), "", (yyvsp[(7) - (8)]));
        }
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 234 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", (yyvsp[(2) - (9)]), (yyvsp[(3) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(8) - (9)]));
        }
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 238 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", (yyvsp[(2) - (10)]), (yyvsp[(3) - (10)]), (yyvsp[(4) - (10)]), (yyvsp[(5) - (10)]), (yyvsp[(7) - (10)]), (yyvsp[(9) - (10)]));
        }
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 242 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), "1", "", "");
        }
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 246 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]), "1", "", "");
        }
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 250 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", (yyvsp[(2) - (6)]), (yyvsp[(3) - (6)]), "1", (yyvsp[(5) - (6)]), "");
        }
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 254 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", (yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), "1", (yyvsp[(6) - (7)]), "");
        }
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 258 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", (yyvsp[(2) - (6)]), (yyvsp[(3) - (6)]), "1", "", (yyvsp[(5) - (6)]));
        }
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 262 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", (yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), "1", "", (yyvsp[(6) - (7)]));
        }
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 266 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", (yyvsp[(2) - (8)]), (yyvsp[(3) - (8)]), "1", (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
        }
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 270 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" format=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", (yyvsp[(2) - (9)]), (yyvsp[(3) - (9)]), (yyvsp[(4) - (9)]), "1", (yyvsp[(6) - (9)]), (yyvsp[(8) - (9)]));
        }
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 302 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t<Technique name=\"%s\">\n%s\t</Technique>\n", (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
        }
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 309 "glsl.y"
    {
			(yyval) = (yyvsp[(2) - (3)]);
		}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 315 "glsl.y"
    {
			(yyval) = (YYSTYPE)"";
		}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 319 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("%s%s", (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
		}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 326 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Pass name=\"%s\">\n%s\t\t</Pass>\n", (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
        }
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 333 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t\t<RenderStates>\n%s\t\t\t</RenderStates>\n%s%s", (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]));
		}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 339 "glsl.y"
    {
			(yyval) = (YYSTYPE)"";
		}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 343 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("%s%s", (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
		}
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 373 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 378 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 383 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 388 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 393 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 398 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 403 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 408 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 413 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 418 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 423 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 428 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 433 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 438 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 443 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 448 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 453 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 458 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 463 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 468 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 473 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 478 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 483 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 488 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 493 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 498 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 503 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 508 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 513 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 518 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=0x%08lx/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 523 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=0x%08lx/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 528 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=0x%08lx/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 533 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 538 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 543 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 548 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 553 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=0x%08lx/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 558 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=0x%08lx/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 563 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=0x%08lx/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 568 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 573 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 578 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 583 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 588 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t<VertexShader code=\"%s\">\n\t\t\t</VertexShader>\n", (yyvsp[(4) - (5)]));
        }
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 593 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t<GeometryShader code=\"%s\">\n\t\t\t</GeometryShader>\n", (yyvsp[(4) - (5)]));
        }
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 598 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t<PixelShader code=\"%s\">\n\t\t\t</PixelShader>\n", (yyvsp[(4) - (5)]));
        }
    break;



/* Line 1464 of yacc.c  */
#line 2727 "glsl.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}




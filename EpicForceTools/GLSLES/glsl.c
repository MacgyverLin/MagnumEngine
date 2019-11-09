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
#line 150 "glsl.c"

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


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 360 "glsl.c"

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
#define YYLAST   213

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNRULES -- Number of states.  */
#define YYNSTATES  213

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   339

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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    10,    12,    14,    16,
      19,    23,    24,    27,    32,    35,    39,    40,    43,    49,
      56,    64,    73,    81,    90,   100,   111,   116,   122,   129,
     137,   144,   152,   161,   171,   172,   174,   176,   178,   179,
     181,   183,   185,   187,   189,   191,   193,   195,   197,   199,
     201,   203,   205,   207,   209,   211,   213,   217,   221,   222,
     225,   229,   233,   234,   237,   238,   240,   242,   244,   246,
     248,   250,   252,   254,   256,   258,   260,   262,   264,   266,
     268,   270,   272,   274,   276,   278,   280,   285,   290,   295,
     300,   305,   310,   315,   320,   325,   330,   335,   340,   345,
     350,   355,   360,   365,   370,   375,   380,   385,   386,   388
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      86,     0,    -1,    87,    -1,    -1,    87,    88,    -1,    -1,
      89,    -1,    93,    -1,    99,    -1,    43,    90,    -1,    76,
      91,    77,    -1,    -1,    91,    92,    -1,    47,    98,    73,
      78,    -1,    44,    94,    -1,    76,    95,    77,    -1,    -1,
      95,    96,    -1,    48,    98,    73,    84,    78,    -1,    48,
      97,    98,    73,    84,    78,    -1,    48,    98,    73,    84,
      79,    73,    78,    -1,    48,    97,    98,    73,    84,    79,
      73,    78,    -1,    48,    98,    73,    84,    13,    83,    78,
      -1,    48,    97,    98,    73,    84,    13,    83,    78,    -1,
      48,    98,    73,    84,    79,    73,    13,    83,    78,    -1,
      48,    97,    98,    73,    84,    79,    73,    13,    83,    78,
      -1,    48,    98,    73,    78,    -1,    48,    97,    98,    73,
      78,    -1,    48,    98,    73,    79,    73,    78,    -1,    48,
      97,    98,    73,    79,    73,    78,    -1,    48,    98,    73,
      13,    83,    78,    -1,    48,    97,    98,    73,    13,    83,
      78,    -1,    48,    98,    73,    79,    73,    13,    83,    78,
      -1,    48,    97,    98,    73,    79,    73,    13,    83,    78,
      -1,    -1,    50,    -1,    51,    -1,    52,    -1,    -1,    53,
      -1,    54,    -1,    55,    -1,    56,    -1,    57,    -1,    58,
      -1,    59,    -1,    60,    -1,    61,    -1,    62,    -1,    63,
      -1,    64,    -1,    65,    -1,    66,    -1,    67,    -1,    68,
      -1,    69,    -1,    45,    73,   100,    -1,    76,   101,    77,
      -1,    -1,   101,   102,    -1,    46,    73,   103,    -1,    76,
     104,    77,    -1,    -1,   104,   105,    -1,    -1,   106,    -1,
     107,    -1,   108,    -1,   109,    -1,   110,    -1,   111,    -1,
     112,    -1,   113,    -1,   114,    -1,   115,    -1,   116,    -1,
     117,    -1,   118,    -1,   119,    -1,   120,    -1,   121,    -1,
     122,    -1,   123,    -1,   124,    -1,   125,    -1,   126,    -1,
      20,    13,    73,    78,    -1,    21,    13,    73,    78,    -1,
      22,    13,    73,    78,    -1,    23,    13,    73,    78,    -1,
      24,    13,    73,    78,    -1,    25,    13,    73,    78,    -1,
      26,    13,    73,    78,    -1,    27,    13,    73,    78,    -1,
      28,    13,    73,    78,    -1,    29,    13,    73,    78,    -1,
      30,    13,    73,    78,    -1,    31,    13,   127,    78,    -1,
      32,    13,    73,    78,    -1,    33,    13,   127,    78,    -1,
      34,    13,   127,    78,    -1,    35,    13,    73,    78,    -1,
      36,    13,    73,    78,    -1,    37,    13,    73,    78,    -1,
      38,    13,    73,    78,    -1,    39,    13,    82,    78,    -1,
      41,    13,    82,    78,    -1,    -1,    71,    -1,    70,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   100,   100,   119,   122,   130,   133,   134,   135,   140,
     147,   154,   157,   164,   172,   179,   186,   189,   196,   200,
     204,   208,   212,   216,   220,   224,   228,   232,   236,   240,
     244,   248,   252,   256,   262,   263,   264,   265,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   288,   295,   302,   305,
     312,   319,   326,   329,   335,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   361,   367,   373,   379,
     385,   391,   397,   403,   409,   415,   421,   427,   433,   439,
     445,   451,   457,   463,   469,   475,   481,   488,   490,   491
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EQ", "NE", "LT", "LE", "GT", "GE",
  "PLUS", "MINUS", "MULT", "DIVIDE", "ASSIGN", "BITWISE_AND", "BITWISE_OR",
  "BITWISE_NOT", "AND", "OR", "NOT", "CULLMODE_TOKEN",
  "ALPHABLENDENABLE_TOKEN", "BLENDOP_TOKEN", "COLORWRITEENABLE_TOKEN",
  "DESTBLEND_TOKEN", "FILLMODE_TOKEN", "SHADEMODE_TOKEN", "SRCBLEND_TOKEN",
  "STENCILENABLE_TOKEN", "STENCILFAIL_TOKEN", "STENCILFUNC_TOKEN",
  "STENCILMASK_TOKEN", "STENCILZPASS_TOKEN", "STENCILREF_TOKEN",
  "STENCILWRITEMASK_TOKEN", "STENCILZFAIL_TOKEN", "ZENABLE_TOKEN",
  "ZFUNC_TOKEN", "ZWRITEENABLE_TOKEN", "VERTEXSHADER_TOKEN",
  "GEOMETRYSHADER_TOKEN", "PIXELSHADER_TOKEN", "VISUALEFFECT_TOKEN",
  "ATTRIBUTES_TOKEN", "UNIFORMS_TOKEN", "TECHNIQUE_TOKEN", "PASS_TOKEN",
  "ATTRIBUTE_GLSL_TOKEN", "UNIFORM_GLSL_TOKEN", "VARYING_GLSL_TOKEN",
  "LOWP_GLSL_TOKEN", "MIDP_GLSL_TOKEN", "HIGHP_GLSL_TOKEN",
  "BOOL_GLSL_TOKEN", "BVEC2_GLSL_TOKEN", "BVEC3_GLSL_TOKEN",
  "BVEC4_GLSL_TOKEN", "INT_GLSL_TOKEN", "IVEC2_GLSL_TOKEN",
  "IVEC3_GLSL_TOKEN", "IVEC4_GLSL_TOKEN", "FLOAT_GLSL_TOKEN",
  "VEC2_GLSL_TOKEN", "VEC3_GLSL_TOKEN", "VEC4_GLSL_TOKEN",
  "MAT2_GLSL_TOKEN", "MAT3_GLSL_TOKEN", "MAT4_GLSL_TOKEN",
  "SAMPLER2D_GLSL_TOKEN", "SAMPLERCUBE_GLSL_TOKEN", "HEXNUMBER", "NUMBER",
  "FLOAT", "WORD", "FILENAME", "QUOTE", "OBRACE", "EBRACE", "SEMICOLON",
  "COLON", "COMMA", "ENDL", "STRING_LITERAL", "INITIALIZER", "ARRAYINDEX",
  "$accept", "visualeffect", "visualeffectStatements",
  "visualeffectStatement", "attributes", "attributeContent",
  "validAttributeStatements", "validAttributeStatement", "uniforms",
  "uniformContent", "validUniformStatements", "validUniformStatement",
  "precisionTypeTokens", "variableTypeTokens", "technique",
  "techniqueContent", "passeStatements", "passeStatement", "passContent",
  "validRenderStateStatements", "validRenderStateStatement",
  "cullModeStatement", "alphaBlendEnableStatement", "blendOpStatement",
  "colorWriteEnableStatement", "destBlendStatement", "fillModeStatement",
  "shadeModeStatement", "srcBlendStatement", "stencilEnableStatement",
  "stencilFailStatement", "stencilFuncStatement", "stencilMaskStatement",
  "stencilzPassStatement", "stencilRefStatement",
  "stencilWriteMaskStatement", "stencilZFailStatement", "zEnableStatement",
  "zFuncStatement", "zWriteEnableStatement", "vertexShaderStatement",
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
     335,   336,   337,   338,   339
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    87,    87,    88,    88,    88,    88,    89,
      90,    91,    91,    92,    93,    94,    95,    95,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    97,    97,    97,    97,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    99,   100,   101,   101,
     102,   103,   104,   104,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   127,   127
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     0,     1,     1,     1,     2,
       3,     0,     2,     4,     2,     3,     0,     2,     5,     6,
       7,     8,     7,     8,     9,    10,     4,     5,     6,     7,
       6,     7,     8,     9,     0,     1,     1,     1,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     0,     2,
       3,     3,     0,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     0,     1,     1
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
       0,    57,    59,     0,     0,     0,     0,    13,     0,     0,
      26,     0,     0,    62,    60,     0,    27,     0,     0,     0,
       0,     0,    18,     0,     0,     0,     0,     0,    19,     0,
      30,     0,    28,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,    63,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    31,
       0,    29,     0,     0,     0,    22,     0,    20,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   107,
       0,   107,   107,     0,     0,     0,     0,     0,     0,     0,
      23,     0,    21,    32,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   109,   108,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    33,     0,
      24,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,    25
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     7,     8,    12,    16,    22,     9,    14,
      17,    25,    48,    44,    10,    19,    26,    52,    64,    74,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   178
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -132
static const yytype_int16 yypact[] =
{
    -132,     1,   -26,  -132,   -73,   -68,   -63,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,  -132,   -34,   -31,   -33,  -132,  -132,
      48,  -132,  -132,    31,  -132,  -132,   -32,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,   -25,  -132,  -132,  -132,    48,   -24,
     -23,  -132,  -132,   -27,   -21,   -13,   -29,  -132,   -11,   -30,
    -132,   -19,    -9,  -132,  -132,   -22,  -132,   -17,    -4,   -20,
      -6,    35,  -132,   -16,     2,   -18,    -2,    36,  -132,   -14,
    -132,    37,  -132,   -15,    -1,    49,    51,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,  -132,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,
      57,  -132,    63,     0,    64,  -132,    60,  -132,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,   -65,
      82,   -65,   -65,    83,    84,    85,    86,    87,    88,    89,
    -132,    90,  -132,  -132,    93,    94,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,  -132,  -132,   106,   107,
     127,   128,   129,   130,   131,   132,   133,   134,  -132,   135,
    -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,
    -132,  -132,  -132
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,
    -132,  -132,  -132,    32,  -132,  -132,  -132,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,
    -132,  -132,  -131
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      59,     3,    65,    11,    71,   176,   177,    81,    13,    77,
      15,   130,   136,   161,    50,    23,    20,     4,     5,     6,
     180,   181,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,    18,   105,    24,    51,    21,    63,    53,    55,
      56,    57,    58,    69,    70,    49,    76,    84,    80,   133,
     129,    75,   138,   135,   139,    60,    61,    66,    67,    72,
      73,    62,    82,    68,    78,    79,   131,   137,   162,   106,
      54,    45,    46,    47,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    83,   132,
     134,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   179,   182,   183,   184,   185,
       0,     0,     0,     0,     0,     0,     0,   188,     0,   186,
     187,   190,   191,   189,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   204,   205,   206,   207,   208,
     209,   210,   211,   212
};

static const yytype_int16 yycheck[] =
{
      13,     0,    13,    76,    13,    70,    71,    13,    76,    13,
      73,    13,    13,    13,    46,    48,    47,    43,    44,    45,
     151,   152,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    76,    41,    77,    77,    77,    76,    73,    73,
      73,    78,    73,    83,    73,    23,    73,    73,    78,    73,
      78,    83,    13,    78,    13,    78,    79,    78,    79,    78,
      79,    84,    78,    84,    78,    79,    78,    78,    78,    77,
      48,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    83,    83,
      83,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      83,    78,    78,    83,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    82,
      82,    78,    78,    83,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    78,    78,    78,    78,
      78,    78,    78,    78
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    86,    87,     0,    43,    44,    45,    88,    89,    93,
      99,    76,    90,    76,    94,    73,    91,    95,    76,   100,
      47,    77,    92,    48,    77,    96,   101,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    98,    50,    51,    52,    97,    98,
      46,    77,   102,    73,    98,    73,    73,    78,    73,    13,
      78,    79,    84,    76,   103,    13,    78,    79,    84,    83,
      73,    13,    78,    79,   104,    83,    73,    13,    78,    79,
      78,    13,    78,    83,    73,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    41,    77,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,    78,
      13,    78,    83,    73,    83,    78,    13,    78,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    83,
      78,    13,    78,    78,    83,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    70,    71,   127,    73,
     127,   127,    73,    73,    73,    73,    82,    82,    78,    83,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78
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
#line 101 "glsl.y"
    {
			//const char *str = prepareString("<VisualEffect>\n%s</VisualEffect>", $1);
			const char *str = prepareString("<VisualEffect>\n%s</VisualEffect>", (yyvsp[(1) - (1)]));
			
			(yyval) = (YYSTYPE)str;
			
			printf(str);
        }
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 119 "glsl.y"
    {
			(yyval) = (YYSTYPE)"";
		}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 123 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("%s%s", (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
		}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 130 "glsl.y"
    {
			(yyval) = (YYSTYPE)"";
		}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 141 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t<Attributes>\n%s\t</Attributes>\n", (yyvsp[(2) - (2)]));
        }
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 148 "glsl.y"
    {
			(yyval) = (yyvsp[(2) - (3)]);
		}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 154 "glsl.y"
    {
			(yyval) = (YYSTYPE)"";
		}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 158 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("%s%s", (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
		}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 165 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Attribute type=\"%s\" name=\"%s\"/>\n", (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 173 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t<Uniforms>\n%s\t</Uniforms>\n", (yyvsp[(2) - (2)]));
        }
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 180 "glsl.y"
    {
			(yyval) = (yyvsp[(2) - (3)]);
		}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 186 "glsl.y"
    {
			(yyval) = (YYSTYPE)"";
		}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 190 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("%s%s", (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
		}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 197 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" type=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]), "", "");
        }
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 201 "glsl.y"
    {   
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" type=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", (yyvsp[(2) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(5) - (6)]), "", "");
        }
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 205 "glsl.y"
    {                    
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" type=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", (yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(6) - (7)]), "");
        }
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 209 "glsl.y"
    {   
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" type=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", (yyvsp[(2) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]), "");
        }
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 213 "glsl.y"
    {                        
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" type=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", (yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), "", (yyvsp[(6) - (7)]));
        }
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 217 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" type=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", (yyvsp[(2) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(5) - (8)]), "", (yyvsp[(7) - (8)]));
        }
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 221 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" type=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", (yyvsp[(2) - (9)]), (yyvsp[(3) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(8) - (9)]));
        }
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 225 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" type=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", (yyvsp[(2) - (10)]), (yyvsp[(3) - (10)]), (yyvsp[(4) - (10)]), (yyvsp[(5) - (10)]), (yyvsp[(7) - (10)]), (yyvsp[(9) - (10)]));
        }
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 229 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" type=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), "1", "", "");
        }
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 233 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" type=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]), "1", "", "");
        }
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 237 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" type=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", (yyvsp[(2) - (6)]), (yyvsp[(3) - (6)]), "1", (yyvsp[(5) - (6)]), "");
        }
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 241 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" type=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", (yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), "1", (yyvsp[(6) - (7)]), "");
        }
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 245 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" type=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", (yyvsp[(2) - (6)]), (yyvsp[(3) - (6)]), "1", "", (yyvsp[(5) - (6)]));
        }
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 249 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" type=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", (yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), "1", "", (yyvsp[(6) - (7)]));
        }
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 253 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" type=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", "", (yyvsp[(2) - (8)]), (yyvsp[(3) - (8)]), "1", (yyvsp[(5) - (8)]), (yyvsp[(7) - (8)]));
        }
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 257 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Uniform precision=\"%s\" type=\"%s\" name=\"%s\" arraysize=\"%s\" semantic=\"%s\" initializer=\"%s\"/>\n", (yyvsp[(2) - (9)]), (yyvsp[(3) - (9)]), (yyvsp[(4) - (9)]), "1", (yyvsp[(6) - (9)]), (yyvsp[(8) - (9)]));
        }
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 289 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t<Technique name=\"%s\">\n%s\t</Technique>\n", (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
        }
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 296 "glsl.y"
    {
			(yyval) = (yyvsp[(2) - (3)]);
		}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 302 "glsl.y"
    {
			(yyval) = (YYSTYPE)"";
		}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 306 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("%s%s", (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
		}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 313 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t<Pass name=\"%s\">\n%s\t\t</Pass>\n", (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
        }
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 320 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("\t\t\t<RenderStates>\n%s\t\t\t</RenderStates>\n", (yyvsp[(2) - (3)]));
		}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 326 "glsl.y"
    {
			(yyval) = (YYSTYPE)"";
		}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 330 "glsl.y"
    {
			(yyval) = (YYSTYPE)prepareString("%s%s", (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
		}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 362 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\">\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 368 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\">\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 374 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\">\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 380 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\">\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 386 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\">\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 392 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\">\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 398 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\">\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 404 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\">\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 410 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\">\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 416 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\">\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 422 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\">\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 428 "glsl.y"
    {
				(yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=0x%08lx>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 434 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\">\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 440 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=0x%08lx>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 446 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=0x%08lx>\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 452 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\">\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 458 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\">\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 464 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\">\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 470 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\">\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 476 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\">\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 482 "glsl.y"
    {
                (yyval) = (YYSTYPE)prepareString("\t\t\t\t<RenderState type=\"%s\" value=\"%s\">\n", (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;



/* Line 1464 of yacc.c  */
#line 2314 "glsl.c"
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




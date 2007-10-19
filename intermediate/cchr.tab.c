/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOK_CONSTRAINT = 258,
     TOK_TRUE = 259,
     TOK_LCBRAC = 260,
     TOK_RCBRAC = 261,
     TOK_SEMI = 262,
     TOK_COMMA = 263,
     TOK_AT = 264,
     TOK_SIMP = 265,
     TOK_PROP = 266,
     TOK_SPIPE = 267,
     TOK_BSLASH = 268,
     TOK_LRBRAC = 269,
     TOK_RRBRAC = 270,
     TOK_FUNC = 271,
     TOK_SYMBAT = 272,
     TOK_CONST = 273,
     TOK_SYMB = 274,
     TOK_OP = 275,
     TOK_EXTERN = 276,
     TOK_BSTRING = 277,
     TOK_STRING = 278,
     TOK_ESTRING = 279,
     TOK_MACRO = 280,
     TOK_ASTER = 281,
     TOK_BCHAR = 282,
     TOK_CHAR = 283,
     TOK_ECHAR = 284,
     TOK_LOGICAL = 285,
     TOK_ERROR = 286,
     PRE_ENDALIST = 287,
     PRE_ELIST = 288,
     PRE_ETLIST = 289
   };
#endif
/* Tokens.  */
#define TOK_CONSTRAINT 258
#define TOK_TRUE 259
#define TOK_LCBRAC 260
#define TOK_RCBRAC 261
#define TOK_SEMI 262
#define TOK_COMMA 263
#define TOK_AT 264
#define TOK_SIMP 265
#define TOK_PROP 266
#define TOK_SPIPE 267
#define TOK_BSLASH 268
#define TOK_LRBRAC 269
#define TOK_RRBRAC 270
#define TOK_FUNC 271
#define TOK_SYMBAT 272
#define TOK_CONST 273
#define TOK_SYMB 274
#define TOK_OP 275
#define TOK_EXTERN 276
#define TOK_BSTRING 277
#define TOK_STRING 278
#define TOK_ESTRING 279
#define TOK_MACRO 280
#define TOK_ASTER 281
#define TOK_BCHAR 282
#define TOK_CHAR 283
#define TOK_ECHAR 284
#define TOK_LOGICAL 285
#define TOK_ERROR 286
#define PRE_ENDALIST 287
#define PRE_ELIST 288
#define PRE_ETLIST 289




/* Copy the first part of user declarations.  */
#line 1 "cchr.y"

/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| cchr.y - YACC parser for CHR-in-C code                                     |
| written by Pieter Wuille                                                   |
\****************************************************************************/ 

#ifndef _cchr_y_
#define _cchr_y_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsestr.h"
#include "cchr.tab.h"

#ifdef USE_EFENCE
#include <efence.h>
#endif

typedef void *yyscan_t;

int static yyerror(YYLTYPE *loc,yyscan_t scanner,cchr_t *output,char *msg);
int yylex ( YYSTYPE * lvalp, YYLTYPE * llocp, yyscan_t scanner );

void cchr_init(cchr_t *cchr);
void cchr_merge(cchr_t *out,cchr_t *in);
void cchr_genrule(cchr_t *cchr,char *name,exprlist_t *kept,exprlist_t *removed,
                  exprlist_t *guard,exprlist_t *body);

#endif

#define YYLEX_PARAM scanner



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 45 "cchr.y"
{
  char *lit;
  expr_t expr;
  token_t token;
  constr_t constr;
  cchr_t cchr;
  exprlist_t elist;
}
/* Line 187 of yacc.c.  */
#line 210 "intermediate/cchr.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 235 "intermediate/cchr.tab.c"

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
# if YYENABLE_NLS
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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   127

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNRULES -- Number of states.  */
#define YYNSTATES  107

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    12,    15,    16,    19,
      20,    23,    24,    28,    31,    33,    35,    37,    39,    43,
      45,    48,    52,    54,    56,    58,    60,    62,    64,    66,
      70,    74,    78,    79,    82,    83,    86,    88,    92,    94,
      98,   100,   102,   104,   106,   108,   110,   111,   121,   129,
     137,   145,   151,   157,   161,   165,   170,   175,   177,   180,
     185,   186,   189,   193,   194,   196,   198,   202,   204,   207
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      36,     0,    -1,    37,    -1,    37,     6,    -1,    -1,    37,
      55,    -1,    38,    42,    -1,    -1,    39,    43,    -1,    -1,
      40,    44,    -1,    -1,    16,    50,    15,    -1,    16,    15,
      -1,    52,    -1,    41,    -1,    46,    -1,    47,    -1,     5,
      40,     6,    -1,    19,    -1,    14,    15,    -1,    14,    50,
      15,    -1,    42,    -1,    12,    -1,    17,    -1,    43,    -1,
       7,    -1,     4,    -1,    38,    -1,    45,     8,    38,    -1,
      22,    48,    24,    -1,    27,    49,    29,    -1,    -1,    48,
      23,    -1,    -1,    49,    28,    -1,    39,    -1,    50,     8,
      39,    -1,    19,    -1,    51,     8,    19,    -1,     8,    -1,
      18,    -1,    20,    -1,     9,    -1,    26,    -1,    17,    -1,
      -1,    53,    45,    13,    45,    10,    45,    12,    45,     7,
      -1,    53,    45,    10,    45,    12,    45,     7,    -1,    53,
      45,    11,    45,    12,    45,     7,    -1,    53,    45,    13,
      45,    10,    45,     7,    -1,    53,    45,    10,    45,     7,
      -1,    53,    45,    11,    45,     7,    -1,     3,    56,     7,
      -1,    21,    51,     7,    -1,    25,    58,    39,     7,    -1,
      30,    61,    19,     7,    -1,    54,    -1,    58,    57,    -1,
      56,     8,    58,    57,    -1,    -1,    57,    41,    -1,    16,
      59,    15,    -1,    -1,    60,    -1,    61,    -1,    60,     8,
      61,    -1,    19,    -1,    61,    19,    -1,    61,    26,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    89,    89,    90,    95,    96,    99,   100,   103,   104,
     107,   108,   111,   117,   127,   128,   129,   130,   131,   132,
     141,   151,   160,   161,   162,   165,   166,   169,   170,   171,
     174,   177,   180,   181,   190,   191,   200,   201,   203,   204,
     206,   207,   208,   209,   210,   213,   214,   217,   218,   219,
     220,   221,   222,   226,   227,   228,   229,   230,   234,   235,
     238,   239,   242,   245,   246,   249,   250,   253,   254,   255
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_CONSTRAINT", "TOK_TRUE",
  "TOK_LCBRAC", "TOK_RCBRAC", "TOK_SEMI", "TOK_COMMA", "TOK_AT",
  "TOK_SIMP", "TOK_PROP", "TOK_SPIPE", "TOK_BSLASH", "TOK_LRBRAC",
  "TOK_RRBRAC", "TOK_FUNC", "TOK_SYMBAT", "TOK_CONST", "TOK_SYMB",
  "TOK_OP", "TOK_EXTERN", "TOK_BSTRING", "TOK_STRING", "TOK_ESTRING",
  "TOK_MACRO", "TOK_ASTER", "TOK_BCHAR", "TOK_CHAR", "TOK_ECHAR",
  "TOK_LOGICAL", "TOK_ERROR", "PRE_ENDALIST", "PRE_ELIST", "PRE_ETLIST",
  "$accept", "main", "input", "tokenlist", "etokenlist", "stokenlist",
  "functio", "token", "etoken", "stoken", "exprlist", "string", "char",
  "stringparts", "charparts", "arglist", "extlist", "literal", "rname",
  "rule", "stmt", "constrlist", "carglist", "constr", "typelist",
  "typelistc", "type", 0
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
     285,   286,   287,   288,   289
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    36,    37,    37,    38,    38,    39,    39,
      40,    40,    41,    41,    42,    42,    42,    42,    42,    42,
      42,    42,    43,    43,    43,    44,    44,    45,    45,    45,
      46,    47,    48,    48,    49,    49,    50,    50,    51,    51,
      52,    52,    52,    52,    52,    53,    53,    54,    54,    54,
      54,    54,    54,    55,    55,    55,    55,    55,    56,    56,
      57,    57,    58,    59,    59,    60,    60,    61,    61,    61
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     2,     0,     2,     0,
       2,     0,     3,     2,     1,     1,     1,     1,     3,     1,
       2,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     0,     2,     0,     2,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     1,     0,     9,     7,     7,
       7,     5,     5,     3,     3,     4,     4,     1,     2,     4,
       0,     2,     3,     0,     1,     1,     3,     1,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,    46,     1,     0,     3,    45,     0,     0,     0,
       7,    57,     5,    63,     0,    60,    38,     0,     9,    67,
       0,    27,    28,     0,     0,    64,    65,    53,     0,    58,
      54,     0,     0,    68,    69,    11,    40,    43,     9,     9,
      41,    19,    42,    32,    44,    34,    15,     6,    16,    17,
      14,     7,     7,     7,     7,    62,     0,    68,    60,    61,
      39,    55,    23,    24,    22,     8,    56,     0,    20,    36,
       0,    13,     0,     0,     0,    29,     0,     0,     0,    66,
      59,    18,    26,    25,    10,     9,    21,    12,    33,    30,
      35,    31,    51,     7,    52,     7,     7,    37,     0,     0,
       0,    48,    49,    50,     7,     0,    47
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    22,    69,    67,    46,    64,    65,    84,
      23,    48,    49,    73,    74,    70,    17,    50,    10,    11,
      12,    14,    29,    15,    24,    25,    20
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -50
static const yytype_int8 yypact[] =
{
     -50,    27,     7,   -50,    34,   -50,   -50,    29,    34,    46,
      77,   -50,   -50,    46,    28,   -50,   -50,    55,   -50,   -50,
     -10,   -50,    84,    32,    94,    75,    -8,   -50,    34,    83,
     -50,    86,    68,   114,   -50,   -50,   -50,   -50,   107,   109,
     -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,
     -50,   -50,    77,    77,    77,   -50,    46,   -50,   -50,   -50,
     -50,   -50,   -50,   -50,   -50,   -50,   -50,    52,   -50,     3,
      18,   -50,    23,    90,    63,    84,    44,    89,    31,    -8,
      83,   -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,
     -50,   -50,   -50,    77,   -50,    77,    77,     3,   108,   110,
     100,   -50,   -50,   -50,    77,   112,   -50
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -50,   -50,   -50,    72,   -18,   -50,   -27,   -21,    58,   -50,
     -49,   -50,   -50,   -50,   -50,    87,   -50,   -50,   -50,   -50,
     -50,   -50,    69,     6,   -50,   -50,    -7
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int8 yytable[] =
{
      32,    47,    59,    76,    77,    78,    26,    -2,    35,    33,
       4,    57,    37,     5,    18,    62,    34,    38,    34,    39,
      63,    40,    41,    42,     6,    43,    85,     3,     7,    44,
      45,    85,     8,    86,    58,    27,    28,     9,    87,    51,
      51,    96,    52,    53,    98,    54,    99,   100,    16,    79,
      13,    92,    51,    59,    47,   105,    93,    35,    81,    82,
      36,    37,    30,    31,    62,    19,    38,    97,    39,    63,
      40,    41,    42,    35,    43,    61,    36,    37,    44,    45,
      62,    21,    38,    56,    39,    63,    40,    41,    42,    35,
      43,    90,    91,    37,    44,    45,    94,    51,    38,    39,
      39,    95,    40,    41,    42,    60,    43,   103,    51,    55,
      44,    45,   104,    88,    89,   101,    51,   102,    51,   106,
      51,    66,    68,    75,    71,    83,    72,    80
};

static const yytype_uint8 yycheck[] =
{
      18,    22,    29,    52,    53,    54,    13,     0,     5,    19,
       3,    19,     9,     6,     8,    12,    26,    14,    26,    16,
      17,    18,    19,    20,    17,    22,     8,     0,    21,    26,
      27,     8,    25,    15,    28,     7,     8,    30,    15,     8,
       8,    10,    10,    11,    93,    13,    95,    96,    19,    56,
      16,     7,     8,    80,    75,   104,    12,     5,     6,     7,
       8,     9,     7,     8,    12,    19,    14,    85,    16,    17,
      18,    19,    20,     5,    22,     7,     8,     9,    26,    27,
      12,     4,    14,     8,    16,    17,    18,    19,    20,     5,
      22,    28,    29,     9,    26,    27,     7,     8,    14,    16,
      16,    12,    18,    19,    20,    19,    22,     7,     8,    15,
      26,    27,    12,    23,    24,     7,     8,     7,     8,     7,
       8,     7,    15,    51,    15,    67,    39,    58
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    36,    37,     0,     3,     6,    17,    21,    25,    30,
      53,    54,    55,    16,    56,    58,    19,    51,    58,    19,
      61,     4,    38,    45,    59,    60,    61,     7,     8,    57,
       7,     8,    39,    19,    26,     5,     8,     9,    14,    16,
      18,    19,    20,    22,    26,    27,    41,    42,    46,    47,
      52,     8,    10,    11,    13,    15,     8,    19,    58,    41,
      19,     7,    12,    17,    42,    43,     7,    40,    15,    39,
      50,    15,    50,    48,    49,    38,    45,    45,    45,    61,
      57,     6,     7,    43,    44,     8,    15,    15,    23,    24,
      28,    29,     7,    12,     7,    12,    10,    39,    45,    45,
      45,     7,     7,     7,    12,    45,     7
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

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
      yyerror (&yylloc, scanner, output, YY_("syntax error: cannot back up")); \
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
# if YYLTYPE_IS_TRIVIAL
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
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc)
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
		  Type, Value, Location, scanner, output); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, cchr_t *output)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, output)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    yyscan_t scanner;
    cchr_t *output;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (scanner);
  YYUSE (output);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, cchr_t *output)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, output)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    yyscan_t scanner;
    cchr_t *output;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, output);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, yyscan_t scanner, cchr_t *output)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, scanner, output)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    yyscan_t scanner;
    cchr_t *output;
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , scanner, output);
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, scanner, output); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, yyscan_t scanner, cchr_t *output)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, scanner, output)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    yyscan_t scanner;
    cchr_t *output;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (scanner);
  YYUSE (output);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 3: /* "TOK_CONSTRAINT" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1249 "intermediate/cchr.tab.c"
	break;
      case 4: /* "TOK_TRUE" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1254 "intermediate/cchr.tab.c"
	break;
      case 5: /* "TOK_LCBRAC" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1259 "intermediate/cchr.tab.c"
	break;
      case 6: /* "TOK_RCBRAC" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1264 "intermediate/cchr.tab.c"
	break;
      case 7: /* "TOK_SEMI" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1269 "intermediate/cchr.tab.c"
	break;
      case 8: /* "TOK_COMMA" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1274 "intermediate/cchr.tab.c"
	break;
      case 9: /* "TOK_AT" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1279 "intermediate/cchr.tab.c"
	break;
      case 10: /* "TOK_SIMP" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1284 "intermediate/cchr.tab.c"
	break;
      case 11: /* "TOK_PROP" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1289 "intermediate/cchr.tab.c"
	break;
      case 12: /* "TOK_SPIPE" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1294 "intermediate/cchr.tab.c"
	break;
      case 13: /* "TOK_BSLASH" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1299 "intermediate/cchr.tab.c"
	break;
      case 14: /* "TOK_LRBRAC" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1304 "intermediate/cchr.tab.c"
	break;
      case 15: /* "TOK_RRBRAC" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1309 "intermediate/cchr.tab.c"
	break;
      case 16: /* "TOK_FUNC" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1314 "intermediate/cchr.tab.c"
	break;
      case 17: /* "TOK_SYMBAT" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1319 "intermediate/cchr.tab.c"
	break;
      case 18: /* "TOK_CONST" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1324 "intermediate/cchr.tab.c"
	break;
      case 19: /* "TOK_SYMB" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1329 "intermediate/cchr.tab.c"
	break;
      case 20: /* "TOK_OP" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1334 "intermediate/cchr.tab.c"
	break;
      case 21: /* "TOK_EXTERN" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1339 "intermediate/cchr.tab.c"
	break;
      case 22: /* "TOK_BSTRING" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1344 "intermediate/cchr.tab.c"
	break;
      case 23: /* "TOK_STRING" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1349 "intermediate/cchr.tab.c"
	break;
      case 24: /* "TOK_ESTRING" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1354 "intermediate/cchr.tab.c"
	break;
      case 26: /* "TOK_ASTER" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1359 "intermediate/cchr.tab.c"
	break;
      case 27: /* "TOK_BCHAR" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1364 "intermediate/cchr.tab.c"
	break;
      case 28: /* "TOK_CHAR" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1369 "intermediate/cchr.tab.c"
	break;
      case 29: /* "TOK_ECHAR" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1374 "intermediate/cchr.tab.c"
	break;
      case 30: /* "TOK_LOGICAL" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1379 "intermediate/cchr.tab.c"
	break;
      case 37: /* "input" */
#line 73 "cchr.y"
	{ destruct_cchr_t(&(yyvaluep->cchr)); };
#line 1384 "intermediate/cchr.tab.c"
	break;
      case 38: /* "tokenlist" */
#line 67 "cchr.y"
	{ destruct_expr_t(&(yyvaluep->expr)); };
#line 1389 "intermediate/cchr.tab.c"
	break;
      case 39: /* "etokenlist" */
#line 67 "cchr.y"
	{ destruct_expr_t(&(yyvaluep->expr)); };
#line 1394 "intermediate/cchr.tab.c"
	break;
      case 41: /* "functio" */
#line 67 "cchr.y"
	{ destruct_expr_t(&(yyvaluep->expr)); };
#line 1399 "intermediate/cchr.tab.c"
	break;
      case 42: /* "token" */
#line 67 "cchr.y"
	{ destruct_expr_t(&(yyvaluep->expr)); };
#line 1404 "intermediate/cchr.tab.c"
	break;
      case 43: /* "etoken" */
#line 67 "cchr.y"
	{ destruct_expr_t(&(yyvaluep->expr)); };
#line 1409 "intermediate/cchr.tab.c"
	break;
      case 45: /* "exprlist" */
#line 76 "cchr.y"
	{ destruct_exprlist_t(&(yyvaluep->elist)); };
#line 1414 "intermediate/cchr.tab.c"
	break;
      case 50: /* "arglist" */
#line 70 "cchr.y"
	{ destruct_token_t(&(yyvaluep->token)); };
#line 1419 "intermediate/cchr.tab.c"
	break;
      case 51: /* "extlist" */
#line 73 "cchr.y"
	{ destruct_cchr_t(&(yyvaluep->cchr)); };
#line 1424 "intermediate/cchr.tab.c"
	break;
      case 52: /* "literal" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1429 "intermediate/cchr.tab.c"
	break;
      case 53: /* "rname" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1434 "intermediate/cchr.tab.c"
	break;
      case 54: /* "rule" */
#line 73 "cchr.y"
	{ destruct_cchr_t(&(yyvaluep->cchr)); };
#line 1439 "intermediate/cchr.tab.c"
	break;
      case 55: /* "stmt" */
#line 73 "cchr.y"
	{ destruct_cchr_t(&(yyvaluep->cchr)); };
#line 1444 "intermediate/cchr.tab.c"
	break;
      case 56: /* "constrlist" */
#line 73 "cchr.y"
	{ destruct_cchr_t(&(yyvaluep->cchr)); };
#line 1449 "intermediate/cchr.tab.c"
	break;
      case 57: /* "carglist" */
#line 64 "cchr.y"
	{ destruct_constr_t(&(yyvaluep->constr)); };
#line 1454 "intermediate/cchr.tab.c"
	break;
      case 58: /* "constr" */
#line 64 "cchr.y"
	{ destruct_constr_t(&(yyvaluep->constr)); };
#line 1459 "intermediate/cchr.tab.c"
	break;
      case 59: /* "typelist" */
#line 64 "cchr.y"
	{ destruct_constr_t(&(yyvaluep->constr)); };
#line 1464 "intermediate/cchr.tab.c"
	break;
      case 60: /* "typelistc" */
#line 64 "cchr.y"
	{ destruct_constr_t(&(yyvaluep->constr)); };
#line 1469 "intermediate/cchr.tab.c"
	break;
      case 61: /* "type" */
#line 61 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1474 "intermediate/cchr.tab.c"
	break;

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
int yyparse (yyscan_t scanner, cchr_t *output);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

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
yyparse (yyscan_t scanner, cchr_t *output)
#else
int
yyparse (scanner, output)
    yyscan_t scanner;
    cchr_t *output;
#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;

  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

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
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 89 "cchr.y"
    { *output=(yyvsp[(1) - (1)].cchr); ;}
    break;

  case 3:
#line 90 "cchr.y"
    { *output=(yyvsp[(1) - (2)].cchr); 
	   free((yyvsp[(2) - (2)].lit)); /* dumpCHR(output, 1); */ 
	   YYACCEPT; ;}
    break;

  case 4:
#line 95 "cchr.y"
    { cchr_init(&(yyval.cchr)); ;}
    break;

  case 5:
#line 96 "cchr.y"
    { (yyval.cchr)=(yyvsp[(1) - (2)].cchr); cchr_merge(&(yyval.cchr),&(yyvsp[(2) - (2)].cchr)); ;}
    break;

  case 6:
#line 99 "cchr.y"
    { (yyval.expr).list=(yyvsp[(1) - (2)].expr).list; alist_addall((yyval.expr).list,(yyvsp[(2) - (2)].expr).list); alist_free((yyvsp[(2) - (2)].expr).list); ;}
    break;

  case 7:
#line 100 "cchr.y"
    { alist_init((yyval.expr).list); ;}
    break;

  case 8:
#line 103 "cchr.y"
    { (yyval.expr).list=(yyvsp[(1) - (2)].expr).list; alist_addall((yyval.expr).list,(yyvsp[(2) - (2)].expr).list); alist_free((yyvsp[(2) - (2)].expr).list); ;}
    break;

  case 9:
#line 104 "cchr.y"
    { alist_init((yyval.expr).list); ;}
    break;

  case 10:
#line 107 "cchr.y"
    { (yyval.expr).list=(yyvsp[(1) - (2)].expr).list; alist_addall((yyval.expr).list,(yyvsp[(2) - (2)].expr).list); alist_free((yyvsp[(2) - (2)].expr).list); ;}
    break;

  case 11:
#line 108 "cchr.y"
    { alist_init((yyval.expr).list); ;}
    break;

  case 12:
#line 111 "cchr.y"
    { 
    		alist_init((yyval.expr).list);
		    (yyvsp[(2) - (3)].token).data=(yyvsp[(1) - (3)].lit);
		    alist_add((yyval.expr).list,(yyvsp[(2) - (3)].token));
		    free((yyvsp[(3) - (3)].lit));
		;}
    break;

  case 13:
#line 117 "cchr.y"
    { 
   		    alist_init((yyval.expr).list);
		    token_t *tok;
		    alist_new((yyval.expr).list,tok);
		    alist_init(tok->args);
		    tok->type=TOKEN_TYPE_FUNC;
		    tok->data=(yyvsp[(1) - (2)].lit);
		    free((yyvsp[(2) - (2)].lit));
		;}
    break;

  case 14:
#line 127 "cchr.y"
    { alist_init((yyval.expr).list); token_t *tok; alist_new((yyval.expr).list,tok); tok->data=(yyvsp[(1) - (1)].lit); tok->type=TOKEN_TYPE_LIT; alist_init(tok->args); ;}
    break;

  case 16:
#line 129 "cchr.y"
    { alist_init((yyval.expr).list); token_t *tok; alist_new((yyval.expr).list,tok); tok->data=(yyvsp[(1) - (1)].lit); tok->type=TOKEN_TYPE_LIT; alist_init(tok->args); ;}
    break;

  case 17:
#line 130 "cchr.y"
    { alist_init((yyval.expr).list); token_t *tok; alist_new((yyval.expr).list,tok); tok->data=(yyvsp[(1) - (1)].lit); tok->type=TOKEN_TYPE_LIT; alist_init(tok->args); ;}
    break;

  case 18:
#line 131 "cchr.y"
    { alist_init((yyval.expr).list); token_t *tok; alist_new((yyval.expr).list,tok); tok->data=(yyvsp[(1) - (3)].lit); tok->type=TOKEN_TYPE_LIT; alist_addall((yyval.expr).list,(yyvsp[(2) - (3)].expr).list); alist_new((yyval.expr).list,tok); tok->data=(yyvsp[(3) - (3)].lit); tok->type=TOKEN_TYPE_LIT; alist_free((yyvsp[(2) - (3)].expr).list); ;}
    break;

  case 19:
#line 132 "cchr.y"
    { 
   		    alist_init((yyval.expr).list);
		    token_t *tok;
		    alist_new((yyval.expr).list,tok);
		    tok->data=(yyvsp[(1) - (1)].lit);
		    tok->type=TOKEN_TYPE_SYMB;
		    alist_init(tok->args);

		  ;}
    break;

  case 20:
#line 141 "cchr.y"
    {
   		    alist_init((yyval.expr).list);
		    token_t *tok;
		    alist_new((yyval.expr).list,tok);
		    alist_init(tok->args);
		    tok->type=TOKEN_TYPE_FUNC;
		    tok->data=NULL;
		    free((yyvsp[(2) - (2)].lit));
		    free((yyvsp[(1) - (2)].lit));
	  ;}
    break;

  case 21:
#line 151 "cchr.y"
    { 
    		alist_init((yyval.expr).list);
		    (yyvsp[(2) - (3)].token).data=NULL;
		    alist_add((yyval.expr).list,(yyvsp[(2) - (3)].token));
		    free((yyvsp[(3) - (3)].lit));
		    free((yyvsp[(1) - (3)].lit));
		;}
    break;

  case 23:
#line 161 "cchr.y"
    { alist_init((yyval.expr).list); token_t *tok; alist_new((yyval.expr).list,tok); tok->data=(yyvsp[(1) - (1)].lit); tok->type=TOKEN_TYPE_LIT; ;}
    break;

  case 24:
#line 162 "cchr.y"
    { alist_init((yyval.expr).list); token_t *tok; alist_new((yyval.expr).list,tok); tok->data=(yyvsp[(1) - (1)].lit); tok->type=TOKEN_TYPE_SYMB; alist_new((yyval.expr).list,tok); tok->data=malloc(2); strcpy(tok->data,"@"); tok->type=TOKEN_TYPE_LIT;;}
    break;

  case 26:
#line 166 "cchr.y"
    { alist_init((yyval.expr).list); token_t *tok; alist_new((yyval.expr).list,tok); tok->data=(yyvsp[(1) - (1)].lit); tok->type=TOKEN_TYPE_LIT; ;}
    break;

  case 27:
#line 169 "cchr.y"
    { free((yyvsp[(1) - (1)].lit)); alist_init((yyval.elist).list); ;}
    break;

  case 28:
#line 170 "cchr.y"
    { alist_init((yyval.elist).list); alist_add((yyval.elist).list,(yyvsp[(1) - (1)].expr)); ;}
    break;

  case 29:
#line 171 "cchr.y"
    { (yyval.elist)=(yyvsp[(1) - (3)].elist); alist_add((yyval.elist).list,(yyvsp[(3) - (3)].expr)); free((yyvsp[(2) - (3)].lit)); ;}
    break;

  case 30:
#line 174 "cchr.y"
    { (yyval.lit)=malloc(strlen((yyvsp[(1) - (3)].lit))+strlen((yyvsp[(2) - (3)].lit))+strlen((yyvsp[(3) - (3)].lit))+1); strcpy((yyval.lit),(yyvsp[(1) - (3)].lit)); strcat((yyval.lit),(yyvsp[(2) - (3)].lit)); strcat((yyval.lit),(yyvsp[(3) - (3)].lit)); free((yyvsp[(1) - (3)].lit)); free((yyvsp[(2) - (3)].lit)); free((yyvsp[(3) - (3)].lit)); ;}
    break;

  case 31:
#line 177 "cchr.y"
    { (yyval.lit)=malloc(strlen((yyvsp[(1) - (3)].lit))+strlen((yyvsp[(2) - (3)].lit))+strlen((yyvsp[(3) - (3)].lit))+1); strcpy((yyval.lit),(yyvsp[(1) - (3)].lit)); strcat((yyval.lit),(yyvsp[(2) - (3)].lit)); strcat((yyval.lit),(yyvsp[(3) - (3)].lit)); free((yyvsp[(1) - (3)].lit)); free((yyvsp[(2) - (3)].lit)); free((yyvsp[(3) - (3)].lit)); ;}
    break;

  case 32:
#line 180 "cchr.y"
    { (yyval.lit)=malloc(1); (yyval.lit)[0]=0; ;}
    break;

  case 33:
#line 181 "cchr.y"
    { 
				(yyval.lit)=malloc(strlen((yyvsp[(1) - (2)].lit))+strlen((yyvsp[(2) - (2)].lit))+1);
				strcpy((yyval.lit),(yyvsp[(1) - (2)].lit));
				strcat((yyval.lit),(yyvsp[(2) - (2)].lit));
				free((yyvsp[(1) - (2)].lit));
				free((yyvsp[(2) - (2)].lit));
			  ;}
    break;

  case 34:
#line 190 "cchr.y"
    { (yyval.lit)=malloc(1); (yyval.lit)[0]=0; ;}
    break;

  case 35:
#line 191 "cchr.y"
    { 
				(yyval.lit)=malloc(strlen((yyvsp[(1) - (2)].lit))+strlen((yyvsp[(2) - (2)].lit))+1);
				strcpy((yyval.lit),(yyvsp[(1) - (2)].lit));
				strcat((yyval.lit),(yyvsp[(2) - (2)].lit));
				free((yyvsp[(1) - (2)].lit));
				free((yyvsp[(2) - (2)].lit));
			  ;}
    break;

  case 36:
#line 200 "cchr.y"
    { (yyval.token).type = TOKEN_TYPE_FUNC; alist_init((yyval.token).args); (yyval.token).data=NULL; alist_add((yyval.token).args,(yyvsp[(1) - (1)].expr)); ;}
    break;

  case 37:
#line 201 "cchr.y"
    { (yyval.token)=(yyvsp[(1) - (3)].token); alist_add((yyval.token).args,(yyvsp[(3) - (3)].expr)); free((yyvsp[(2) - (3)].lit)); ;}
    break;

  case 38:
#line 203 "cchr.y"
    { cchr_init(&(yyval.cchr)); alist_add((yyval.cchr).exts,(yyvsp[(1) - (1)].lit)); ;}
    break;

  case 39:
#line 204 "cchr.y"
    { (yyval.cchr)=(yyvsp[(1) - (3)].cchr); alist_add((yyval.cchr).exts,(yyvsp[(3) - (3)].lit)); free((yyvsp[(2) - (3)].lit)); ;}
    break;

  case 45:
#line 213 "cchr.y"
    { (yyval.lit)=(yyvsp[(1) - (1)].lit); ;}
    break;

  case 46:
#line 214 "cchr.y"
    { (yyval.lit)=NULL; ;}
    break;

  case 47:
#line 217 "cchr.y"
    { cchr_genrule(&(yyval.cchr),(yyvsp[(1) - (9)].lit),&(yyvsp[(2) - (9)].elist),&(yyvsp[(4) - (9)].elist),&(yyvsp[(6) - (9)].elist),&(yyvsp[(8) - (9)].elist)); free((yyvsp[(3) - (9)].lit)); free((yyvsp[(5) - (9)].lit)); free((yyvsp[(7) - (9)].lit)); free((yyvsp[(9) - (9)].lit)); ;}
    break;

  case 48:
#line 218 "cchr.y"
    { cchr_genrule(&(yyval.cchr),(yyvsp[(1) - (7)].lit),NULL,&(yyvsp[(2) - (7)].elist),&(yyvsp[(4) - (7)].elist),&(yyvsp[(6) - (7)].elist)); free((yyvsp[(3) - (7)].lit)); free((yyvsp[(5) - (7)].lit)); free((yyvsp[(7) - (7)].lit)); ;}
    break;

  case 49:
#line 219 "cchr.y"
    { cchr_genrule(&(yyval.cchr),(yyvsp[(1) - (7)].lit),&(yyvsp[(2) - (7)].elist),NULL,&(yyvsp[(4) - (7)].elist),&(yyvsp[(6) - (7)].elist)); free((yyvsp[(3) - (7)].lit)); free((yyvsp[(5) - (7)].lit)); free((yyvsp[(7) - (7)].lit)); ;}
    break;

  case 50:
#line 220 "cchr.y"
    { cchr_genrule(&(yyval.cchr),(yyvsp[(1) - (7)].lit),&(yyvsp[(2) - (7)].elist),&(yyvsp[(4) - (7)].elist),NULL,&(yyvsp[(6) - (7)].elist)); free((yyvsp[(3) - (7)].lit)); free((yyvsp[(5) - (7)].lit)); free((yyvsp[(7) - (7)].lit)); ;}
    break;

  case 51:
#line 221 "cchr.y"
    { cchr_genrule(&(yyval.cchr),(yyvsp[(1) - (5)].lit),NULL,&(yyvsp[(2) - (5)].elist),NULL,&(yyvsp[(4) - (5)].elist)); free((yyvsp[(3) - (5)].lit)); free((yyvsp[(5) - (5)].lit)); ;}
    break;

  case 52:
#line 222 "cchr.y"
    { cchr_genrule(&(yyval.cchr),(yyvsp[(1) - (5)].lit),&(yyvsp[(2) - (5)].elist),NULL,NULL,&(yyvsp[(4) - (5)].elist)); free((yyvsp[(3) - (5)].lit)); free((yyvsp[(5) - (5)].lit)); ;}
    break;

  case 53:
#line 226 "cchr.y"
    { (yyval.cchr)=(yyvsp[(2) - (3)].cchr); free((yyvsp[(1) - (3)].lit)); free((yyvsp[(3) - (3)].lit)); ;}
    break;

  case 54:
#line 227 "cchr.y"
    { (yyval.cchr)=(yyvsp[(2) - (3)].cchr); free((yyvsp[(1) - (3)].lit)); free((yyvsp[(3) - (3)].lit)); ;}
    break;

  case 55:
#line 228 "cchr.y"
    { cchr_init(&(yyval.cchr)); macro_t *nw; alist_new((yyval.cchr).macros,nw); nw->name=(yyvsp[(2) - (4)].constr); nw->def=(yyvsp[(3) - (4)].expr); free((yyvsp[(1) - (4)].lit)); free((yyvsp[(4) - (4)].lit)); ;}
    break;

  case 56:
#line 229 "cchr.y"
    { cchr_init(&(yyval.cchr)); logical_t *nw; alist_new((yyval.cchr).logicals,nw); nw->name=(yyvsp[(2) - (4)].lit); nw->cb=(yyvsp[(3) - (4)].lit); free((yyvsp[(1) - (4)].lit)); free((yyvsp[(4) - (4)].lit)); ;}
    break;

  case 58:
#line 234 "cchr.y"
    { cchr_init(&(yyval.cchr)); (yyvsp[(1) - (2)].constr).args=(yyvsp[(2) - (2)].constr).args; alist_add((yyval.cchr).constrs,(yyvsp[(1) - (2)].constr)); ;}
    break;

  case 59:
#line 235 "cchr.y"
    { (yyval.cchr)=(yyvsp[(1) - (4)].cchr); (yyvsp[(3) - (4)].constr).args=(yyvsp[(4) - (4)].constr).args; alist_add((yyval.cchr).constrs,(yyvsp[(3) - (4)].constr)); free((yyvsp[(2) - (4)].lit)); ;}
    break;

  case 60:
#line 238 "cchr.y"
    { alist_init((yyval.constr).args); alist_init((yyval.constr).list); (yyval.constr).name=NULL; ;}
    break;

  case 61:
#line 239 "cchr.y"
    { alist_add((yyvsp[(1) - (2)].constr).args,(yyvsp[(2) - (2)].expr)); (yyval.constr)=(yyvsp[(1) - (2)].constr); ;}
    break;

  case 62:
#line 242 "cchr.y"
    { (yyval.constr)=(yyvsp[(2) - (3)].constr); (yyval.constr).name=(yyvsp[(1) - (3)].lit); free((yyvsp[(3) - (3)].lit)); alist_init((yyval.constr).args); ;}
    break;

  case 63:
#line 245 "cchr.y"
    { (yyval.constr).name=NULL; alist_init((yyval.constr).list); ;}
    break;

  case 64:
#line 246 "cchr.y"
    { (yyval.constr) = (yyvsp[(1) - (1)].constr); ;}
    break;

  case 65:
#line 249 "cchr.y"
    { (yyval.constr).name=NULL; alist_init((yyval.constr).list); alist_add((yyval.constr).list,(yyvsp[(1) - (1)].lit)); ;}
    break;

  case 66:
#line 250 "cchr.y"
    { (yyval.constr)=(yyvsp[(1) - (3)].constr); alist_add((yyval.constr).list,(yyvsp[(3) - (3)].lit)); free((yyvsp[(2) - (3)].lit)); ;}
    break;

  case 67:
#line 253 "cchr.y"
    { (yyval.lit) = (yyvsp[(1) - (1)].lit); ;}
    break;

  case 68:
#line 254 "cchr.y"
    { (yyval.lit) = realloc((yyvsp[(1) - (2)].lit),strlen((yyvsp[(1) - (2)].lit))+strlen((yyvsp[(2) - (2)].lit))+2); strcat((yyval.lit)," "); strcat((yyval.lit),(yyvsp[(2) - (2)].lit)); free((yyvsp[(2) - (2)].lit)); ;}
    break;

  case 69:
#line 255 "cchr.y"
    { (yyval.lit) = realloc((yyvsp[(1) - (2)].lit),strlen((yyvsp[(1) - (2)].lit))+strlen((yyvsp[(2) - (2)].lit))+2); strcat((yyval.lit)," "); strcat((yyval.lit),(yyvsp[(2) - (2)].lit)); free((yyvsp[(2) - (2)].lit)); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2144 "intermediate/cchr.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
      yyerror (&yylloc, scanner, output, YY_("syntax error"));
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
	    yyerror (&yylloc, scanner, output, yymsg);
	  }
	else
	  {
	    yyerror (&yylloc, scanner, output, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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
		      yytoken, &yylval, &yylloc, scanner, output);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
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

  yyerror_range[0] = yylsp[1-yylen];
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, scanner, output);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, scanner, output, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc, scanner, output);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, scanner, output);
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


#line 258 "cchr.y"


void cchr_init(cchr_t *cchr) {
  alist_init(cchr->constrs);
  alist_init(cchr->rules);
  alist_init(cchr->exts);
  alist_init(cchr->macros);
  alist_init(cchr->logicals);
}

void cchr_merge(cchr_t *out,cchr_t *in) {
  alist_addall(out->constrs,in->constrs);
  alist_addall(out->rules,in->rules);
  alist_addall(out->exts,in->exts);
  alist_addall(out->macros,in->macros);
  alist_addall(out->logicals,in->logicals);
  alist_free(in->constrs);
  alist_free(in->rules);
  alist_free(in->exts);
  alist_free(in->macros);
  alist_free(in->logicals);
}

void cchr_genrule(cchr_t *cchr,char *name,exprlist_t *kept,exprlist_t *removed,exprlist_t *guard,exprlist_t *body) {
  cchr_init(cchr);
  rule_t *rule; alist_new(cchr->rules,rule);
  rule->name=name;
  if (kept) {
    rule->kept = *kept;
  } else {
    alist_init(rule->kept.list);
  }
  if (removed) {
    rule->removed = *removed;
  } else {
    alist_init(rule->removed.list);
  }
  if (body) {
    rule->body = *body;
  } else {
    alist_init(rule->body.list);
  }
  if (guard) {
    rule->guard= *guard;
  } else {
    alist_init(rule->guard.list);
  }
}

int static yyerror(YYLTYPE *loc,yyscan_t scanner,cchr_t *output,char *msg) {
  fprintf(stderr,"Parse error on line %i: %s\n",loc->last_line,msg);
  return 1;
}




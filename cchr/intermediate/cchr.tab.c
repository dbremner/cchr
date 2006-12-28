/* A Bison parser, made by GNU Bison 2.2.  */

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
#define YYBISON_VERSION "2.2"

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
     TOK_ERROR = 280,
     PRE_ENDALIST = 281,
     PRE_ELIST = 282,
     PRE_ETLIST = 283
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
#define TOK_ERROR 280
#define PRE_ENDALIST 281
#define PRE_ELIST 282
#define PRE_ETLIST 283




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

void dumpCHR(cchr_t *chr,int level);
int static yyerror(YYLTYPE *loc,yyscan_t scanner,cchr_t *output,int line,char *msg);
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
#line 47 "cchr.y"
{
  char *lit;
  expr_t expr;
  token_t token;
  constr_t constr;
  cchr_t cchr;
  exprlist_t elist;
}
/* Line 193 of yacc.c.  */
#line 199 "intermediate/cchr.tab.c"
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
#line 224 "intermediate/cchr.tab.c"

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
#define YYLAST   94

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  29
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNRULES -- Number of states.  */
#define YYNSTATES  91

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

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
      25,    26,    27,    28
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    12,    15,    16,    19,
      20,    23,    24,    28,    31,    33,    35,    37,    41,    43,
      46,    50,    52,    54,    56,    58,    60,    62,    64,    68,
      72,    73,    76,    78,    82,    84,    88,    90,    92,    94,
      96,    98,    99,   109,   117,   125,   133,   139,   145,   149,
     153,   155,   157,   161,   162,   165,   170,   171,   173,   175,
     179,   181
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      30,     0,    -1,    31,    -1,    31,     6,    -1,    -1,    31,
      47,    -1,    32,    36,    -1,    -1,    33,    37,    -1,    -1,
      34,    38,    -1,    -1,    16,    42,    15,    -1,    16,    15,
      -1,    44,    -1,    35,    -1,    40,    -1,     5,    34,     6,
      -1,    19,    -1,    14,    15,    -1,    14,    42,    15,    -1,
      36,    -1,    12,    -1,    17,    -1,    37,    -1,     7,    -1,
       4,    -1,    32,    -1,    39,     8,    32,    -1,    22,    41,
      24,    -1,    -1,    41,    23,    -1,    33,    -1,    42,     8,
      33,    -1,    19,    -1,    43,     8,    19,    -1,     8,    -1,
      18,    -1,    20,    -1,     9,    -1,    17,    -1,    -1,    45,
      39,    13,    39,    10,    39,    12,    39,     7,    -1,    45,
      39,    10,    39,    12,    39,     7,    -1,    45,    39,    11,
      39,    12,    39,     7,    -1,    45,    39,    13,    39,    10,
      39,     7,    -1,    45,    39,    10,    39,     7,    -1,    45,
      39,    11,    39,     7,    -1,     3,    48,     7,    -1,    21,
      43,     7,    -1,    46,    -1,    50,    -1,    48,     8,    50,
      -1,    -1,    49,    35,    -1,    16,    51,    15,    49,    -1,
      -1,    52,    -1,    53,    -1,    52,     8,    53,    -1,    19,
      -1,    53,    19,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    91,    91,    92,    97,    98,   101,   102,   105,   106,
     109,   110,   113,   119,   129,   130,   131,   132,   133,   142,
     152,   161,   162,   163,   166,   167,   170,   171,   172,   175,
     178,   179,   188,   189,   191,   192,   194,   195,   196,   197,
     200,   201,   204,   205,   206,   207,   208,   209,   213,   214,
     215,   219,   220,   223,   224,   227,   230,   231,   234,   235,
     238,   239
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
  "TOK_ERROR", "PRE_ENDALIST", "PRE_ELIST", "PRE_ETLIST", "$accept",
  "main", "input", "tokenlist", "etokenlist", "stokenlist", "functio",
  "token", "etoken", "stoken", "exprlist", "string", "stringparts",
  "arglist", "extlist", "literal", "rname", "rule", "stmt", "constrlist",
  "carglist", "constr", "typelist", "typelistc", "type", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    29,    30,    30,    31,    31,    32,    32,    33,    33,
      34,    34,    35,    35,    36,    36,    36,    36,    36,    36,
      36,    37,    37,    37,    38,    38,    39,    39,    39,    40,
      41,    41,    42,    42,    43,    43,    44,    44,    44,    44,
      45,    45,    46,    46,    46,    46,    46,    46,    47,    47,
      47,    48,    48,    49,    49,    50,    51,    51,    52,    52,
      53,    53
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     2,     0,     2,     0,
       2,     0,     3,     2,     1,     1,     1,     3,     1,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       0,     2,     1,     3,     1,     3,     1,     1,     1,     1,
       1,     0,     9,     7,     7,     7,     5,     5,     3,     3,
       1,     1,     3,     0,     2,     4,     0,     1,     1,     3,
       1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,    41,     1,     0,     3,    40,     0,     7,    50,
       5,    56,     0,    51,    34,     0,    26,    27,     0,    60,
       0,    57,    58,    48,     0,    49,     0,    11,    36,    39,
       9,     9,    37,    18,    38,    30,    15,     6,    16,    14,
       7,     7,     7,     7,    53,     0,    61,    52,    35,     0,
      19,    32,     0,    13,     0,     0,    28,     0,     0,     0,
      55,    59,    17,    25,    22,    23,    21,    24,    10,     8,
       9,    20,    12,    31,    29,    46,     7,    47,     7,     7,
      54,    33,     0,     0,     0,    43,    44,    45,     7,     0,
      42
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    17,    51,    49,    36,    66,    69,    68,
      18,    38,    55,    52,    15,    39,     8,     9,    10,    12,
      60,    13,    20,    21,    22
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -42
static const yytype_int8 yypact[] =
{
     -42,     8,     4,   -42,     7,   -42,   -42,    -5,    16,   -42,
     -42,    25,    66,   -42,   -42,    68,   -42,    50,    23,   -42,
      42,    41,    39,   -42,     7,   -42,    52,   -42,   -42,   -42,
      70,    71,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,
     -42,    16,    16,    16,   -42,    25,   -42,   -42,   -42,    10,
     -42,    34,    -3,   -42,    -2,    54,    50,    33,    53,     1,
      73,    39,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,
     -42,   -42,   -42,   -42,   -42,   -42,    16,   -42,    16,    16,
     -42,    34,    72,    74,    55,   -42,   -42,   -42,    16,    76,
     -42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -42,   -42,   -42,    47,    18,   -42,    30,   -14,    43,   -42,
     -41,   -42,   -42,    60,   -42,   -42,   -42,   -42,   -42,   -42,
     -42,    69,   -42,   -42,    49
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int8 yytable[] =
{
      57,    58,    59,    37,    -2,    70,    70,     4,     3,    40,
       5,    79,    71,    72,    14,    27,    62,    63,    28,    29,
      16,     6,    64,    11,    30,     7,    31,    65,    32,    33,
      34,    40,    35,    41,    42,    82,    43,    83,    84,    27,
      75,    40,    37,    29,    19,    76,    64,    89,    30,    45,
      31,    65,    32,    33,    34,    27,    35,    44,    46,    29,
      77,    40,    87,    40,    30,    78,    31,    88,    32,    33,
      34,    48,    35,    23,    24,    25,    26,    73,    74,    85,
      40,    86,    40,    90,    40,    50,    53,    56,    81,    31,
      80,    54,    67,    47,    61
};

static const yytype_uint8 yycheck[] =
{
      41,    42,    43,    17,     0,     8,     8,     3,     0,     8,
       6,    10,    15,    15,    19,     5,     6,     7,     8,     9,
       4,    17,    12,    16,    14,    21,    16,    17,    18,    19,
      20,     8,    22,    10,    11,    76,    13,    78,    79,     5,
       7,     8,    56,     9,    19,    12,    12,    88,    14,     8,
      16,    17,    18,    19,    20,     5,    22,    15,    19,     9,
       7,     8,     7,     8,    14,    12,    16,    12,    18,    19,
      20,    19,    22,     7,     8,     7,     8,    23,    24,     7,
       8,     7,     8,     7,     8,    15,    15,    40,    70,    16,
      60,    31,    49,    24,    45
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    30,    31,     0,     3,     6,    17,    21,    45,    46,
      47,    16,    48,    50,    19,    43,     4,    32,    39,    19,
      51,    52,    53,     7,     8,     7,     8,     5,     8,     9,
      14,    16,    18,    19,    20,    22,    35,    36,    40,    44,
       8,    10,    11,    13,    15,     8,    19,    50,    19,    34,
      15,    33,    42,    15,    42,    41,    32,    39,    39,    39,
      49,    53,     6,     7,    12,    17,    36,    37,    38,    37,
       8,    15,    15,    23,    24,     7,    12,     7,    12,    10,
      35,    33,    39,    39,    39,     7,     7,     7,    12,    39,
       7
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
      yyerror (&yylloc, scanner, output, base_line, YY_("syntax error: cannot back up")); \
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
		  Type, Value, Location, scanner, output, base_line); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, const YYSTYPE * const yyvaluep, const YYLTYPE * const yylocationp, yyscan_t scanner, cchr_t *output, int base_line)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, output, base_line)
    FILE *yyoutput;
    int yytype;
    const YYSTYPE * const yyvaluep;
    const YYLTYPE * const yylocationp;
    yyscan_t scanner;
    cchr_t *output;
    int base_line;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (scanner);
  YYUSE (output);
  YYUSE (base_line);
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
yy_symbol_print (FILE *yyoutput, int yytype, const YYSTYPE * const yyvaluep, const YYLTYPE * const yylocationp, yyscan_t scanner, cchr_t *output, int base_line)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, output, base_line)
    FILE *yyoutput;
    int yytype;
    const YYSTYPE * const yyvaluep;
    const YYLTYPE * const yylocationp;
    yyscan_t scanner;
    cchr_t *output;
    int base_line;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, output, base_line);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, yyscan_t scanner, cchr_t *output, int base_line)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, scanner, output, base_line)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    yyscan_t scanner;
    cchr_t *output;
    int base_line;
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
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , scanner, output, base_line);
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, scanner, output, base_line); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, yyscan_t scanner, cchr_t *output, int base_line)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, scanner, output, base_line)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    yyscan_t scanner;
    cchr_t *output;
    int base_line;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (scanner);
  YYUSE (output);
  YYUSE (base_line);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 3: /* "TOK_CONSTRAINT" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1230 "intermediate/cchr.tab.c"
	break;
      case 4: /* "TOK_TRUE" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1235 "intermediate/cchr.tab.c"
	break;
      case 5: /* "TOK_LCBRAC" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1240 "intermediate/cchr.tab.c"
	break;
      case 6: /* "TOK_RCBRAC" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1245 "intermediate/cchr.tab.c"
	break;
      case 7: /* "TOK_SEMI" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1250 "intermediate/cchr.tab.c"
	break;
      case 8: /* "TOK_COMMA" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1255 "intermediate/cchr.tab.c"
	break;
      case 9: /* "TOK_AT" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1260 "intermediate/cchr.tab.c"
	break;
      case 10: /* "TOK_SIMP" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1265 "intermediate/cchr.tab.c"
	break;
      case 11: /* "TOK_PROP" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1270 "intermediate/cchr.tab.c"
	break;
      case 12: /* "TOK_SPIPE" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1275 "intermediate/cchr.tab.c"
	break;
      case 13: /* "TOK_BSLASH" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1280 "intermediate/cchr.tab.c"
	break;
      case 14: /* "TOK_LRBRAC" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1285 "intermediate/cchr.tab.c"
	break;
      case 15: /* "TOK_RRBRAC" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1290 "intermediate/cchr.tab.c"
	break;
      case 16: /* "TOK_FUNC" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1295 "intermediate/cchr.tab.c"
	break;
      case 17: /* "TOK_SYMBAT" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1300 "intermediate/cchr.tab.c"
	break;
      case 18: /* "TOK_CONST" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1305 "intermediate/cchr.tab.c"
	break;
      case 19: /* "TOK_SYMB" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1310 "intermediate/cchr.tab.c"
	break;
      case 20: /* "TOK_OP" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1315 "intermediate/cchr.tab.c"
	break;
      case 21: /* "TOK_EXTERN" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1320 "intermediate/cchr.tab.c"
	break;
      case 22: /* "TOK_BSTRING" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1325 "intermediate/cchr.tab.c"
	break;
      case 23: /* "TOK_STRING" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1330 "intermediate/cchr.tab.c"
	break;
      case 24: /* "TOK_ESTRING" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1335 "intermediate/cchr.tab.c"
	break;
      case 31: /* "input" */
#line 75 "cchr.y"
	{ destruct_cchr_t(&(yyvaluep->cchr)); };
#line 1340 "intermediate/cchr.tab.c"
	break;
      case 32: /* "tokenlist" */
#line 69 "cchr.y"
	{ destruct_expr_t(&(yyvaluep->expr)); };
#line 1345 "intermediate/cchr.tab.c"
	break;
      case 33: /* "etokenlist" */
#line 69 "cchr.y"
	{ destruct_expr_t(&(yyvaluep->expr)); };
#line 1350 "intermediate/cchr.tab.c"
	break;
      case 35: /* "functio" */
#line 69 "cchr.y"
	{ destruct_expr_t(&(yyvaluep->expr)); };
#line 1355 "intermediate/cchr.tab.c"
	break;
      case 36: /* "token" */
#line 69 "cchr.y"
	{ destruct_expr_t(&(yyvaluep->expr)); };
#line 1360 "intermediate/cchr.tab.c"
	break;
      case 37: /* "etoken" */
#line 69 "cchr.y"
	{ destruct_expr_t(&(yyvaluep->expr)); };
#line 1365 "intermediate/cchr.tab.c"
	break;
      case 39: /* "exprlist" */
#line 78 "cchr.y"
	{ destruct_exprlist_t(&(yyvaluep->elist)); };
#line 1370 "intermediate/cchr.tab.c"
	break;
      case 42: /* "arglist" */
#line 72 "cchr.y"
	{ destruct_token_t(&(yyvaluep->token)); };
#line 1375 "intermediate/cchr.tab.c"
	break;
      case 43: /* "extlist" */
#line 75 "cchr.y"
	{ destruct_cchr_t(&(yyvaluep->cchr)); };
#line 1380 "intermediate/cchr.tab.c"
	break;
      case 44: /* "literal" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1385 "intermediate/cchr.tab.c"
	break;
      case 45: /* "rname" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1390 "intermediate/cchr.tab.c"
	break;
      case 46: /* "rule" */
#line 75 "cchr.y"
	{ destruct_cchr_t(&(yyvaluep->cchr)); };
#line 1395 "intermediate/cchr.tab.c"
	break;
      case 47: /* "stmt" */
#line 75 "cchr.y"
	{ destruct_cchr_t(&(yyvaluep->cchr)); };
#line 1400 "intermediate/cchr.tab.c"
	break;
      case 48: /* "constrlist" */
#line 75 "cchr.y"
	{ destruct_cchr_t(&(yyvaluep->cchr)); };
#line 1405 "intermediate/cchr.tab.c"
	break;
      case 49: /* "carglist" */
#line 66 "cchr.y"
	{ destruct_constr_t(&(yyvaluep->constr)); };
#line 1410 "intermediate/cchr.tab.c"
	break;
      case 50: /* "constr" */
#line 66 "cchr.y"
	{ destruct_constr_t(&(yyvaluep->constr)); };
#line 1415 "intermediate/cchr.tab.c"
	break;
      case 51: /* "typelist" */
#line 66 "cchr.y"
	{ destruct_constr_t(&(yyvaluep->constr)); };
#line 1420 "intermediate/cchr.tab.c"
	break;
      case 52: /* "typelistc" */
#line 66 "cchr.y"
	{ destruct_constr_t(&(yyvaluep->constr)); };
#line 1425 "intermediate/cchr.tab.c"
	break;
      case 53: /* "type" */
#line 63 "cchr.y"
	{ free((yyvaluep->lit)); };
#line 1430 "intermediate/cchr.tab.c"
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
int yyparse (yyscan_t scanner, cchr_t *output, int base_line);
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
yyparse (yyscan_t scanner, cchr_t *output, int base_line)
#else
int
yyparse (scanner, output, base_line)
    yyscan_t scanner;
    cchr_t *output;
    int base_line;
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
#line 91 "cchr.y"
    { *output=(yyvsp[(1) - (1)].cchr); ;}
    break;

  case 3:
#line 92 "cchr.y"
    { *output=(yyvsp[(1) - (2)].cchr); 
	   free((yyvsp[(2) - (2)].lit)); /* dumpCHR(output, 1); */ 
	   YYACCEPT; ;}
    break;

  case 4:
#line 97 "cchr.y"
    { cchr_init(&(yyval.cchr)); ;}
    break;

  case 5:
#line 98 "cchr.y"
    { (yyval.cchr)=(yyvsp[(1) - (2)].cchr); cchr_merge(&(yyval.cchr),&(yyvsp[(2) - (2)].cchr)); ;}
    break;

  case 6:
#line 101 "cchr.y"
    { (yyval.expr).list=(yyvsp[(1) - (2)].expr).list; alist_addall((yyval.expr).list,(yyvsp[(2) - (2)].expr).list); alist_free((yyvsp[(2) - (2)].expr).list); ;}
    break;

  case 7:
#line 102 "cchr.y"
    { alist_init((yyval.expr).list); ;}
    break;

  case 8:
#line 105 "cchr.y"
    { (yyval.expr).list=(yyvsp[(1) - (2)].expr).list; alist_addall((yyval.expr).list,(yyvsp[(2) - (2)].expr).list); alist_free((yyvsp[(2) - (2)].expr).list); ;}
    break;

  case 9:
#line 106 "cchr.y"
    { alist_init((yyval.expr).list); ;}
    break;

  case 10:
#line 109 "cchr.y"
    { (yyval.expr).list=(yyvsp[(1) - (2)].expr).list; alist_addall((yyval.expr).list,(yyvsp[(2) - (2)].expr).list); alist_free((yyvsp[(2) - (2)].expr).list); ;}
    break;

  case 11:
#line 110 "cchr.y"
    { alist_init((yyval.expr).list); ;}
    break;

  case 12:
#line 113 "cchr.y"
    { 
    		alist_init((yyval.expr).list);
		    (yyvsp[(2) - (3)].token).data=(yyvsp[(1) - (3)].lit);
		    alist_add((yyval.expr).list,(yyvsp[(2) - (3)].token));
		    free((yyvsp[(3) - (3)].lit));
		;}
    break;

  case 13:
#line 119 "cchr.y"
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
#line 129 "cchr.y"
    { alist_init((yyval.expr).list); token_t *tok; alist_new((yyval.expr).list,tok); tok->data=(yyvsp[(1) - (1)].lit); tok->type=TOKEN_TYPE_LIT; alist_init(tok->args); ;}
    break;

  case 16:
#line 131 "cchr.y"
    { alist_init((yyval.expr).list); token_t *tok; alist_new((yyval.expr).list,tok); tok->data=(yyvsp[(1) - (1)].lit); tok->type=TOKEN_TYPE_LIT; alist_init(tok->args); ;}
    break;

  case 17:
#line 132 "cchr.y"
    { alist_init((yyval.expr).list); token_t *tok; alist_new((yyval.expr).list,tok); tok->data=(yyvsp[(1) - (3)].lit); tok->type=TOKEN_TYPE_LIT; alist_addall((yyval.expr).list,(yyvsp[(2) - (3)].expr).list); alist_new((yyval.expr).list,tok); tok->data=(yyvsp[(3) - (3)].lit); tok->type=TOKEN_TYPE_LIT; alist_free((yyvsp[(2) - (3)].expr).list); ;}
    break;

  case 18:
#line 133 "cchr.y"
    { 
   		    alist_init((yyval.expr).list);
		    token_t *tok;
		    alist_new((yyval.expr).list,tok);
		    tok->data=(yyvsp[(1) - (1)].lit);
		    tok->type=TOKEN_TYPE_SYMB;
		    alist_init(tok->args);

		  ;}
    break;

  case 19:
#line 142 "cchr.y"
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

  case 20:
#line 152 "cchr.y"
    { 
    		alist_init((yyval.expr).list);
		    (yyvsp[(2) - (3)].token).data=NULL;
		    alist_add((yyval.expr).list,(yyvsp[(2) - (3)].token));
		    free((yyvsp[(3) - (3)].lit));
		    free((yyvsp[(1) - (3)].lit));
		;}
    break;

  case 22:
#line 162 "cchr.y"
    { alist_init((yyval.expr).list); token_t *tok; alist_new((yyval.expr).list,tok); tok->data=(yyvsp[(1) - (1)].lit); tok->type=TOKEN_TYPE_LIT; ;}
    break;

  case 23:
#line 163 "cchr.y"
    { alist_init((yyval.expr).list); token_t *tok; alist_new((yyval.expr).list,tok); tok->data=(yyvsp[(1) - (1)].lit); tok->type=TOKEN_TYPE_SYMB; alist_new((yyval.expr).list,tok); tok->data=malloc(2); strcpy(tok->data,"@"); tok->type=TOKEN_TYPE_LIT;;}
    break;

  case 25:
#line 167 "cchr.y"
    { alist_init((yyval.expr).list); token_t *tok; alist_new((yyval.expr).list,tok); tok->data=(yyvsp[(1) - (1)].lit); tok->type=TOKEN_TYPE_LIT; ;}
    break;

  case 26:
#line 170 "cchr.y"
    { free((yyvsp[(1) - (1)].lit)); alist_init((yyval.elist).list); ;}
    break;

  case 27:
#line 171 "cchr.y"
    { alist_init((yyval.elist).list); alist_add((yyval.elist).list,(yyvsp[(1) - (1)].expr)); ;}
    break;

  case 28:
#line 172 "cchr.y"
    { (yyval.elist)=(yyvsp[(1) - (3)].elist); alist_add((yyval.elist).list,(yyvsp[(3) - (3)].expr)); free((yyvsp[(2) - (3)].lit)); ;}
    break;

  case 29:
#line 175 "cchr.y"
    { (yyval.lit)=malloc(strlen((yyvsp[(1) - (3)].lit))+strlen((yyvsp[(2) - (3)].lit))+strlen((yyvsp[(3) - (3)].lit))+1); strcpy((yyval.lit),(yyvsp[(1) - (3)].lit)); strcat((yyval.lit),(yyvsp[(2) - (3)].lit)); strcat((yyval.lit),(yyvsp[(3) - (3)].lit)); free((yyvsp[(1) - (3)].lit)); free((yyvsp[(2) - (3)].lit)); free((yyvsp[(3) - (3)].lit)); ;}
    break;

  case 30:
#line 178 "cchr.y"
    { (yyval.lit)=malloc(1); (yyval.lit)[0]=0; ;}
    break;

  case 31:
#line 179 "cchr.y"
    { 
				(yyval.lit)=malloc(strlen((yyvsp[(1) - (2)].lit))+strlen((yyvsp[(2) - (2)].lit))+1);
				strcpy((yyval.lit),(yyvsp[(1) - (2)].lit));
				strcat((yyval.lit),(yyvsp[(2) - (2)].lit));
				free((yyvsp[(1) - (2)].lit));
				free((yyvsp[(2) - (2)].lit));
			  ;}
    break;

  case 32:
#line 188 "cchr.y"
    { (yyval.token).type = TOKEN_TYPE_FUNC; alist_init((yyval.token).args); (yyval.token).data=NULL; alist_add((yyval.token).args,(yyvsp[(1) - (1)].expr)); ;}
    break;

  case 33:
#line 189 "cchr.y"
    { (yyval.token)=(yyvsp[(1) - (3)].token); alist_add((yyval.token).args,(yyvsp[(3) - (3)].expr)); free((yyvsp[(2) - (3)].lit)); ;}
    break;

  case 34:
#line 191 "cchr.y"
    { cchr_init(&(yyval.cchr)); alist_add((yyval.cchr).exts,(yyvsp[(1) - (1)].lit)); ;}
    break;

  case 35:
#line 192 "cchr.y"
    { (yyval.cchr)=(yyvsp[(1) - (3)].cchr); alist_add((yyval.cchr).exts,(yyvsp[(3) - (3)].lit)); free((yyvsp[(2) - (3)].lit)); ;}
    break;

  case 40:
#line 200 "cchr.y"
    { (yyval.lit)=(yyvsp[(1) - (1)].lit); ;}
    break;

  case 41:
#line 201 "cchr.y"
    { (yyval.lit)=NULL; ;}
    break;

  case 42:
#line 204 "cchr.y"
    { cchr_genrule(&(yyval.cchr),(yyvsp[(1) - (9)].lit),&(yyvsp[(2) - (9)].elist),&(yyvsp[(4) - (9)].elist),&(yyvsp[(6) - (9)].elist),&(yyvsp[(8) - (9)].elist)); free((yyvsp[(3) - (9)].lit)); free((yyvsp[(5) - (9)].lit)); free((yyvsp[(7) - (9)].lit)); free((yyvsp[(9) - (9)].lit)); ;}
    break;

  case 43:
#line 205 "cchr.y"
    { cchr_genrule(&(yyval.cchr),(yyvsp[(1) - (7)].lit),NULL,&(yyvsp[(2) - (7)].elist),&(yyvsp[(4) - (7)].elist),&(yyvsp[(6) - (7)].elist)); free((yyvsp[(3) - (7)].lit)); free((yyvsp[(5) - (7)].lit)); free((yyvsp[(7) - (7)].lit)); ;}
    break;

  case 44:
#line 206 "cchr.y"
    { cchr_genrule(&(yyval.cchr),(yyvsp[(1) - (7)].lit),&(yyvsp[(2) - (7)].elist),NULL,&(yyvsp[(4) - (7)].elist),&(yyvsp[(6) - (7)].elist)); free((yyvsp[(3) - (7)].lit)); free((yyvsp[(5) - (7)].lit)); free((yyvsp[(7) - (7)].lit)); ;}
    break;

  case 45:
#line 207 "cchr.y"
    { cchr_genrule(&(yyval.cchr),(yyvsp[(1) - (7)].lit),&(yyvsp[(2) - (7)].elist),&(yyvsp[(4) - (7)].elist),NULL,&(yyvsp[(6) - (7)].elist)); free((yyvsp[(3) - (7)].lit)); free((yyvsp[(5) - (7)].lit)); free((yyvsp[(7) - (7)].lit)); ;}
    break;

  case 46:
#line 208 "cchr.y"
    { cchr_genrule(&(yyval.cchr),(yyvsp[(1) - (5)].lit),NULL,&(yyvsp[(2) - (5)].elist),NULL,&(yyvsp[(4) - (5)].elist)); free((yyvsp[(3) - (5)].lit)); free((yyvsp[(5) - (5)].lit)); ;}
    break;

  case 47:
#line 209 "cchr.y"
    { cchr_genrule(&(yyval.cchr),(yyvsp[(1) - (5)].lit),&(yyvsp[(2) - (5)].elist),NULL,NULL,&(yyvsp[(4) - (5)].elist)); free((yyvsp[(3) - (5)].lit)); free((yyvsp[(5) - (5)].lit)); ;}
    break;

  case 48:
#line 213 "cchr.y"
    { (yyval.cchr)=(yyvsp[(2) - (3)].cchr); free((yyvsp[(1) - (3)].lit)); free((yyvsp[(3) - (3)].lit)); ;}
    break;

  case 49:
#line 214 "cchr.y"
    { (yyval.cchr)=(yyvsp[(2) - (3)].cchr); free((yyvsp[(1) - (3)].lit)); free((yyvsp[(3) - (3)].lit)); ;}
    break;

  case 51:
#line 219 "cchr.y"
    { cchr_init(&(yyval.cchr)); alist_add((yyval.cchr).constrs,(yyvsp[(1) - (1)].constr)); ;}
    break;

  case 52:
#line 220 "cchr.y"
    { (yyval.cchr)=(yyvsp[(1) - (3)].cchr); alist_add((yyval.cchr).constrs,(yyvsp[(3) - (3)].constr)); free((yyvsp[(2) - (3)].lit)); ;}
    break;

  case 53:
#line 223 "cchr.y"
    { alist_init((yyval.constr).args); alist_init((yyval.constr).list); (yyval.constr).name=NULL; ;}
    break;

  case 54:
#line 224 "cchr.y"
    { alist_add((yyvsp[(1) - (2)].constr).args,(yyvsp[(2) - (2)].expr)); (yyval.constr)=(yyvsp[(1) - (2)].constr); ;}
    break;

  case 55:
#line 227 "cchr.y"
    { (yyval.constr)=(yyvsp[(2) - (4)].constr); (yyval.constr).name=(yyvsp[(1) - (4)].lit); free((yyvsp[(3) - (4)].lit)); (yyval.constr).args=(yyvsp[(4) - (4)].constr).args; ;}
    break;

  case 56:
#line 230 "cchr.y"
    { (yyval.constr).name=NULL; alist_init((yyval.constr).list); ;}
    break;

  case 57:
#line 231 "cchr.y"
    { (yyval.constr) = (yyvsp[(1) - (1)].constr); ;}
    break;

  case 58:
#line 234 "cchr.y"
    { (yyval.constr).name=NULL; alist_init((yyval.constr).list); alist_add((yyval.constr).list,(yyvsp[(1) - (1)].lit)); ;}
    break;

  case 59:
#line 235 "cchr.y"
    { (yyval.constr)=(yyvsp[(1) - (3)].constr); alist_add((yyval.constr).list,(yyvsp[(3) - (3)].lit)); free((yyvsp[(2) - (3)].lit)); ;}
    break;

  case 60:
#line 238 "cchr.y"
    { (yyval.lit) = (yyvsp[(1) - (1)].lit); ;}
    break;

  case 61:
#line 239 "cchr.y"
    { (yyval.lit) = realloc((yyvsp[(1) - (2)].lit),strlen((yyvsp[(1) - (2)].lit))+strlen((yyvsp[(2) - (2)].lit))+2); strcat((yyval.lit)," "); strcat((yyval.lit),(yyvsp[(2) - (2)].lit)); free((yyvsp[(2) - (2)].lit)); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2060 "intermediate/cchr.tab.c"
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
      yyerror (&yylloc, scanner, output, base_line, YY_("syntax error"));
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
	    yyerror (&yylloc, scanner, output, base_line, yymsg);
	  }
	else
	  {
	    yyerror (&yylloc, scanner, output, base_line, YY_("syntax error"));
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
		      yytoken, &yylval, &yylloc, scanner, output, base_line);
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
		  yystos[yystate], yyvsp, yylsp, scanner, output, base_line);
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
  yyerror (&yylloc, scanner, output, base_line, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc, scanner, output, base_line);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, scanner, output, base_line);
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
  return yyresult;
}


#line 242 "cchr.y"


void printIndent(int level) {
  fprintf(stderr,"%.*s",level*2,"                                                                                                  ");
}

void dumpConstr(constr_t *constr,int level) {
  printIndent(level); fprintf(stderr,"constr '%s' {\n",constr->name);
  level++;
  printIndent(level); fprintf(stderr,"nArgs=%i;\n",alist_len(constr->list));
  int j=0;
  while (j<alist_len(constr->list)) {
    printIndent(level); fprintf(stderr,"arg[%i]='%s'\n",j,alist_get(constr->list,j));
    j++;
  }
  level--;
  printIndent(level); fprintf(stderr,"}\n");
}

void dumpExpr(expr_t *expr);
void dumpExpr(expr_t *expr) {
  int j=0;
  while (j<alist_len(expr->list)) {
    if (j>0) fprintf(stderr," ");
    token_t *tok=alist_ptr(expr->list,j);
    if (tok->type == TOKEN_TYPE_LIT) fprintf(stderr,"%s",tok->data);
    if (tok->type == TOKEN_TYPE_SYMB) fprintf(stderr,"sym_%s",tok->data);
    if (tok->type == TOKEN_TYPE_FUNC) {
      fprintf(stderr,"func_%s[",tok->data);
      int l=0;
      while (l<alist_len(tok->args)) {
        if (l>0) fprintf(stderr,"|");
        dumpExpr(alist_ptr(tok->args,l));
        l++;
      }
      fprintf(stderr,"]");
    }
    j++;
  }
}

void dumpRule(rule_t *rule,int level) {
  printIndent(level); fprintf(stderr,"rule '%s' {\n",rule->name ? rule->name : "<anon>");
  level++;
  printIndent(level); fprintf(stderr,"nKept=%i;\n",alist_len(rule->kept.list));
  int j1=0;
  while (j1<alist_len(rule->kept.list)) {
    printIndent(level); fprintf(stderr,"kept[%i]='",j1); dumpExpr(alist_ptr(rule->kept.list,j1)); fprintf(stderr,"';\n");
    j1++;
  }
  printIndent(level); fprintf(stderr,"nRemoved=%i;\n",alist_len(rule->removed.list));
  int j2=0;
  while (j2<alist_len(rule->removed.list)) {
    printIndent(level); fprintf(stderr,"removed[%i]='",j2); dumpExpr(alist_ptr(rule->removed.list,j2)); fprintf(stderr,"';\n");
    j2++;
  }
  printIndent(level); fprintf(stderr,"nBody=%i;\n",alist_len(rule->body.list));
  int j3=0;
  while (j3<alist_len(rule->body.list)) {
    printIndent(level); fprintf(stderr,"body[%i]='",j3); dumpExpr(alist_ptr(rule->body.list,j3)); fprintf(stderr,"';\n");
    j3++;
  }
  printIndent(level); fprintf(stderr,"nGuard=%i;\n",alist_len(rule->guard.list));
  int j4=0;
  while (j4<alist_len(rule->guard.list)) {
    printIndent(level); fprintf(stderr,"guard[%i]='",j4); dumpExpr(alist_ptr(rule->guard.list,j4)); fprintf(stderr,"';\n");
    j4++;
  }
  level--;
  printIndent(level); fprintf(stderr,"}\n");
}

void dumpCHR(cchr_t *cchr,int level) {
  printIndent(level); fprintf(stderr,"cchr {\n");
  level++;
  printIndent(level); fprintf(stderr,"nConstraints=%i;\n",alist_len(cchr->constrs));
  int j=0;
  while (j<alist_len(cchr->constrs)) {
    dumpConstr(alist_ptr(cchr->constrs,j),level);
    j++;
  }
  printIndent(level); fprintf(stderr,"nRules=%i;\n",alist_len(cchr->rules));
  int k=0;
  while (k<alist_len(cchr->rules)) {
    dumpRule(alist_ptr(cchr->rules,k),level);
    k++;
  }
  printIndent(level); fprintf(stderr,"nExts=%i;\n",alist_len(cchr->exts));
  int l=0;
  while (l<alist_len(cchr->exts)) {
    printIndent(level); fprintf(stderr,"ext[%i]='%s'\n",l,alist_get(cchr->exts,l));
    l++;
  }
  level--;
  printIndent(level); fprintf(stderr,"}\n");
}

void cchr_init(cchr_t *cchr) {
  alist_init(cchr->constrs);
  alist_init(cchr->rules);
  alist_init(cchr->exts);
}

void cchr_merge(cchr_t *out,cchr_t *in) {
  alist_addall(out->constrs,in->constrs);
  alist_addall(out->rules,in->rules);
  alist_addall(out->exts,in->exts);
  alist_free(in->constrs);
  alist_free(in->rules);
  alist_free(in->exts);
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

int static yyerror(YYLTYPE *loc,yyscan_t scanner,cchr_t *output,int base_line,char *msg) {
  fprintf(stderr,"Parse error on line %i: %s\n",loc->last_line+base_line,msg);
  return 1;
}




/* A Bison parser, made by GNU Bison 1.875d.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

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
     TOK_HASH = 286,
     TOK_ERROR = 287,
     PRE_ENDALIST = 288,
     PRE_EC = 289,
     PRE_ELIST = 290,
     PRE_ETLIST = 291
   };
#endif
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
#define TOK_HASH 286
#define TOK_ERROR 287
#define PRE_ENDALIST 288
#define PRE_EC 289
#define PRE_ELIST 290
#define PRE_ETLIST 291




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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 45 "cchr.y"
typedef union YYSTYPE {
  char *lit;
  expr_t expr;
  token_t token;
  constr_t constr;
  cchr_t cchr;
  exprlist_t elist;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 194 "intermediate/cchr.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined (YYLTYPE) && ! defined (YYLTYPE_IS_DECLARED)
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


/* Line 214 of yacc.c.  */
#line 218 "intermediate/cchr.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYLTYPE_IS_TRIVIAL) && YYLTYPE_IS_TRIVIAL \
             && defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
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
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   141

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  27
/* YYNRULES -- Number of rules. */
#define YYNRULES  71
/* YYNRULES -- Number of states. */
#define YYNSTATES  111

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
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
      35,    36
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    12,    15,    16,    19,
      20,    23,    24,    28,    31,    33,    35,    37,    39,    43,
      45,    48,    52,    54,    56,    58,    60,    62,    64,    66,
      70,    74,    80,    84,    88,    89,    92,    93,    96,    98,
     102,   104,   108,   110,   112,   114,   116,   118,   120,   121,
     131,   139,   147,   155,   161,   167,   171,   175,   180,   185,
     187,   190,   195,   196,   199,   203,   204,   206,   208,   212,
     214,   217
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      38,     0,    -1,    39,    -1,    39,     6,    -1,    -1,    39,
      57,    -1,    40,    44,    -1,    -1,    41,    45,    -1,    -1,
      42,    46,    -1,    -1,    16,    52,    15,    -1,    16,    15,
      -1,    54,    -1,    43,    -1,    48,    -1,    49,    -1,     5,
      42,     6,    -1,    19,    -1,    14,    15,    -1,    14,    52,
      15,    -1,    44,    -1,    12,    -1,    17,    -1,    45,    -1,
       7,    -1,     4,    -1,    40,    -1,    40,    31,    19,    -1,
      47,     8,    40,    -1,    47,     8,    40,    31,    19,    -1,
      22,    50,    24,    -1,    27,    51,    29,    -1,    -1,    50,
      23,    -1,    -1,    51,    28,    -1,    41,    -1,    52,     8,
      41,    -1,    19,    -1,    53,     8,    19,    -1,     8,    -1,
      18,    -1,    20,    -1,     9,    -1,    26,    -1,    17,    -1,
      -1,    55,    47,    13,    47,    10,    47,    12,    47,     7,
      -1,    55,    47,    10,    47,    12,    47,     7,    -1,    55,
      47,    11,    47,    12,    47,     7,    -1,    55,    47,    13,
      47,    10,    47,     7,    -1,    55,    47,    10,    47,     7,
      -1,    55,    47,    11,    47,     7,    -1,     3,    58,     7,
      -1,    21,    53,     7,    -1,    25,    60,    41,     7,    -1,
      30,    63,    19,     7,    -1,    56,    -1,    60,    59,    -1,
      58,     8,    60,    59,    -1,    -1,    59,    43,    -1,    16,
      61,    15,    -1,    -1,    62,    -1,    63,    -1,    62,     8,
      63,    -1,    19,    -1,    63,    19,    -1,    63,    26,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    89,    89,    90,    95,    96,    99,   100,   103,   104,
     107,   108,   111,   118,   129,   130,   131,   132,   133,   134,
     143,   154,   164,   165,   166,   169,   170,   173,   174,   175,
     176,   177,   179,   182,   185,   186,   195,   196,   205,   206,
     208,   209,   211,   212,   213,   214,   215,   218,   219,   222,
     223,   224,   225,   226,   227,   231,   232,   233,   234,   235,
     239,   240,   243,   244,   247,   250,   251,   254,   255,   258,
     259,   260
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_CONSTRAINT", "TOK_TRUE",
  "TOK_LCBRAC", "TOK_RCBRAC", "TOK_SEMI", "TOK_COMMA", "TOK_AT",
  "TOK_SIMP", "TOK_PROP", "TOK_SPIPE", "TOK_BSLASH", "TOK_LRBRAC",
  "TOK_RRBRAC", "TOK_FUNC", "TOK_SYMBAT", "TOK_CONST", "TOK_SYMB",
  "TOK_OP", "TOK_EXTERN", "TOK_BSTRING", "TOK_STRING", "TOK_ESTRING",
  "TOK_MACRO", "TOK_ASTER", "TOK_BCHAR", "TOK_CHAR", "TOK_ECHAR",
  "TOK_LOGICAL", "TOK_HASH", "TOK_ERROR", "PRE_ENDALIST", "PRE_EC",
  "PRE_ELIST", "PRE_ETLIST", "$accept", "main", "input", "tokenlist",
  "etokenlist", "stokenlist", "functio", "token", "etoken", "stoken",
  "exprlist", "string", "char", "stringparts", "charparts", "arglist",
  "extlist", "literal", "rname", "rule", "stmt", "constrlist", "carglist",
  "constr", "typelist", "typelistc", "type", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    37,    38,    38,    39,    39,    40,    40,    41,    41,
      42,    42,    43,    43,    44,    44,    44,    44,    44,    44,
      44,    44,    45,    45,    45,    46,    46,    47,    47,    47,
      47,    47,    48,    49,    50,    50,    51,    51,    52,    52,
      53,    53,    54,    54,    54,    54,    54,    55,    55,    56,
      56,    56,    56,    56,    56,    57,    57,    57,    57,    57,
      58,    58,    59,    59,    60,    61,    61,    62,    62,    63,
      63,    63
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     2,     0,     2,     2,     0,     2,     0,
       2,     0,     3,     2,     1,     1,     1,     1,     3,     1,
       2,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     5,     3,     3,     0,     2,     0,     2,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     0,     9,
       7,     7,     7,     5,     5,     3,     3,     4,     4,     1,
       2,     4,     0,     2,     3,     0,     1,     1,     3,     1,
       2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       4,     0,    48,     1,     0,     3,    47,     0,     0,     0,
       7,    59,     5,    65,     0,    62,    40,     0,     9,    69,
       0,    27,    28,     0,     0,    66,    67,    55,     0,    60,
      56,     0,     0,    70,    71,    11,    42,    45,     9,     9,
      43,    19,    44,    34,    46,    36,     0,    15,     6,    16,
      17,    14,     7,     7,     7,     7,    64,     0,    70,    62,
      63,    41,    57,    23,    24,    22,     8,    58,     0,    20,
      38,     0,    13,     0,     0,     0,    29,    30,     0,     0,
       0,    68,    61,    18,    26,    25,    10,     9,    21,    12,
      35,    32,    37,    33,     0,    53,     7,    54,     7,     7,
      39,    31,     0,     0,     0,    50,    51,    52,     7,     0,
      49
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     1,     2,    22,    70,    68,    47,    65,    66,    86,
      23,    49,    50,    74,    75,    71,    17,    51,    10,    11,
      12,    14,    29,    15,    24,    25,    20
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -53
static const yysigned_char yypact[] =
{
     -53,     9,     7,   -53,    19,   -53,   -53,    39,    19,    56,
      75,   -53,   -53,    56,    44,   -53,   -53,    47,   -53,   -53,
      -8,   -53,     3,    32,    79,    88,     1,   -53,    19,    94,
     -53,    93,    97,   114,   -53,   -53,   -53,   -53,   105,   111,
     -53,   -53,   -53,   -53,   -53,   -53,   109,   -53,   -53,   -53,
     -53,   -53,   -53,    75,    75,    75,   -53,    56,   -53,   -53,
     -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,    81,   -53,
     113,    18,   -53,    23,    -9,    33,   -53,    54,    41,    59,
      31,     1,    94,   -53,   -53,   -53,   -53,   -53,   -53,   -53,
     -53,   -53,   -53,   -53,   115,   -53,    75,   -53,    75,    75,
     113,   -53,    57,    76,    70,   -53,   -53,   -53,    75,    84,
     -53
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -53,   -53,   -53,    85,   -18,   -53,   -25,   -17,    68,   -53,
     -52,   -53,   -53,   -53,   -53,    99,   -53,   -53,   -53,   -53,
     -53,   -53,    82,     8,   -53,   -53,    -7
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yysigned_char yytable[] =
{
      32,    78,    79,    80,    60,    48,    26,    -2,    35,     3,
       4,    33,    37,     5,    90,    91,    18,    38,    34,    39,
      58,    40,    41,    42,     6,    43,    87,    34,     7,    44,
      45,    87,     8,    88,    46,    13,    59,     9,    89,    52,
      52,    99,    53,    54,   102,    55,   103,   104,    95,    52,
      81,    27,    28,    96,    30,    31,   109,    60,    16,    35,
      48,    92,    93,    37,   105,    52,    97,    52,    38,   100,
      39,    98,    40,    41,    42,    19,    43,   107,    52,    21,
      44,    45,   108,   106,    52,    94,    35,    83,    84,    36,
      37,   110,    52,    63,    56,    38,    57,    39,    64,    40,
      41,    42,    35,    43,    62,    36,    37,    44,    45,    63,
      39,    38,    61,    39,    64,    40,    41,    42,    35,    43,
      69,    67,    37,    44,    45,    63,    72,    38,    76,    39,
      64,    40,    41,    42,   101,    43,    85,    77,    73,    44,
      45,    82
};

static const unsigned char yycheck[] =
{
      18,    53,    54,    55,    29,    22,    13,     0,     5,     0,
       3,    19,     9,     6,    23,    24,     8,    14,    26,    16,
      19,    18,    19,    20,    17,    22,     8,    26,    21,    26,
      27,     8,    25,    15,    31,    16,    28,    30,    15,     8,
       8,    10,    10,    11,    96,    13,    98,    99,     7,     8,
      57,     7,     8,    12,     7,     8,   108,    82,    19,     5,
      77,    28,    29,     9,     7,     8,     7,     8,    14,    87,
      16,    12,    18,    19,    20,    19,    22,     7,     8,     4,
      26,    27,    12,     7,     8,    31,     5,     6,     7,     8,
       9,     7,     8,    12,    15,    14,     8,    16,    17,    18,
      19,    20,     5,    22,     7,     8,     9,    26,    27,    12,
      16,    14,    19,    16,    17,    18,    19,    20,     5,    22,
      15,     7,     9,    26,    27,    12,    15,    14,    19,    16,
      17,    18,    19,    20,    19,    22,    68,    52,    39,    26,
      27,    59
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    38,    39,     0,     3,     6,    17,    21,    25,    30,
      55,    56,    57,    16,    58,    60,    19,    53,    60,    19,
      63,     4,    40,    47,    61,    62,    63,     7,     8,    59,
       7,     8,    41,    19,    26,     5,     8,     9,    14,    16,
      18,    19,    20,    22,    26,    27,    31,    43,    44,    48,
      49,    54,     8,    10,    11,    13,    15,     8,    19,    60,
      43,    19,     7,    12,    17,    44,    45,     7,    42,    15,
      41,    52,    15,    52,    50,    51,    19,    40,    47,    47,
      47,    63,    59,     6,     7,    45,    46,     8,    15,    15,
      23,    24,    28,    29,    31,     7,    12,     7,    12,    10,
      41,    19,    47,    47,    47,     7,     7,     7,    12,    47,
       7
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

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
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror (&yylloc, scanner, output, "syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
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
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value, Location);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;
  (void) yylocationp;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yytype, yyvaluep, yylocationp)
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;
  (void) yylocationp;

  switch (yytype)
    {
      case 3: /* TOK_CONSTRAINT */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 922 "intermediate/cchr.tab.c"
        break;
      case 4: /* TOK_TRUE */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 927 "intermediate/cchr.tab.c"
        break;
      case 5: /* TOK_LCBRAC */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 932 "intermediate/cchr.tab.c"
        break;
      case 6: /* TOK_RCBRAC */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 937 "intermediate/cchr.tab.c"
        break;
      case 7: /* TOK_SEMI */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 942 "intermediate/cchr.tab.c"
        break;
      case 8: /* TOK_COMMA */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 947 "intermediate/cchr.tab.c"
        break;
      case 9: /* TOK_AT */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 952 "intermediate/cchr.tab.c"
        break;
      case 10: /* TOK_SIMP */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 957 "intermediate/cchr.tab.c"
        break;
      case 11: /* TOK_PROP */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 962 "intermediate/cchr.tab.c"
        break;
      case 12: /* TOK_SPIPE */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 967 "intermediate/cchr.tab.c"
        break;
      case 13: /* TOK_BSLASH */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 972 "intermediate/cchr.tab.c"
        break;
      case 14: /* TOK_LRBRAC */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 977 "intermediate/cchr.tab.c"
        break;
      case 15: /* TOK_RRBRAC */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 982 "intermediate/cchr.tab.c"
        break;
      case 16: /* TOK_FUNC */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 987 "intermediate/cchr.tab.c"
        break;
      case 17: /* TOK_SYMBAT */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 992 "intermediate/cchr.tab.c"
        break;
      case 18: /* TOK_CONST */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 997 "intermediate/cchr.tab.c"
        break;
      case 19: /* TOK_SYMB */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 1002 "intermediate/cchr.tab.c"
        break;
      case 20: /* TOK_OP */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 1007 "intermediate/cchr.tab.c"
        break;
      case 21: /* TOK_EXTERN */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 1012 "intermediate/cchr.tab.c"
        break;
      case 22: /* TOK_BSTRING */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 1017 "intermediate/cchr.tab.c"
        break;
      case 23: /* TOK_STRING */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 1022 "intermediate/cchr.tab.c"
        break;
      case 24: /* TOK_ESTRING */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 1027 "intermediate/cchr.tab.c"
        break;
      case 26: /* TOK_ASTER */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 1032 "intermediate/cchr.tab.c"
        break;
      case 27: /* TOK_BCHAR */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 1037 "intermediate/cchr.tab.c"
        break;
      case 28: /* TOK_CHAR */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 1042 "intermediate/cchr.tab.c"
        break;
      case 29: /* TOK_ECHAR */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 1047 "intermediate/cchr.tab.c"
        break;
      case 30: /* TOK_LOGICAL */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 1052 "intermediate/cchr.tab.c"
        break;
      case 31: /* TOK_HASH */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 1057 "intermediate/cchr.tab.c"
        break;
      case 39: /* input */
#line 72 "cchr.y"
        { destruct_cchr_t(&yyvaluep->cchr); };
#line 1062 "intermediate/cchr.tab.c"
        break;
      case 40: /* tokenlist */
#line 66 "cchr.y"
        { destruct_expr_t(&yyvaluep->expr); };
#line 1067 "intermediate/cchr.tab.c"
        break;
      case 41: /* etokenlist */
#line 66 "cchr.y"
        { destruct_expr_t(&yyvaluep->expr); };
#line 1072 "intermediate/cchr.tab.c"
        break;
      case 42: /* stokenlist */
#line 66 "cchr.y"
        { destruct_expr_t(&yyvaluep->expr); };
#line 1077 "intermediate/cchr.tab.c"
        break;
      case 43: /* functio */
#line 66 "cchr.y"
        { destruct_expr_t(&yyvaluep->expr); };
#line 1082 "intermediate/cchr.tab.c"
        break;
      case 44: /* token */
#line 66 "cchr.y"
        { destruct_expr_t(&yyvaluep->expr); };
#line 1087 "intermediate/cchr.tab.c"
        break;
      case 45: /* etoken */
#line 66 "cchr.y"
        { destruct_expr_t(&yyvaluep->expr); };
#line 1092 "intermediate/cchr.tab.c"
        break;
      case 46: /* stoken */
#line 66 "cchr.y"
        { destruct_expr_t(&yyvaluep->expr); };
#line 1097 "intermediate/cchr.tab.c"
        break;
      case 47: /* exprlist */
#line 75 "cchr.y"
        { destruct_exprlist_t(&yyvaluep->elist); };
#line 1102 "intermediate/cchr.tab.c"
        break;
      case 52: /* arglist */
#line 69 "cchr.y"
        { destruct_token_t(&yyvaluep->token); };
#line 1107 "intermediate/cchr.tab.c"
        break;
      case 53: /* extlist */
#line 72 "cchr.y"
        { destruct_cchr_t(&yyvaluep->cchr); };
#line 1112 "intermediate/cchr.tab.c"
        break;
      case 54: /* literal */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 1117 "intermediate/cchr.tab.c"
        break;
      case 55: /* rname */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 1122 "intermediate/cchr.tab.c"
        break;
      case 56: /* rule */
#line 72 "cchr.y"
        { destruct_cchr_t(&yyvaluep->cchr); };
#line 1127 "intermediate/cchr.tab.c"
        break;
      case 57: /* stmt */
#line 72 "cchr.y"
        { destruct_cchr_t(&yyvaluep->cchr); };
#line 1132 "intermediate/cchr.tab.c"
        break;
      case 58: /* constrlist */
#line 72 "cchr.y"
        { destruct_cchr_t(&yyvaluep->cchr); };
#line 1137 "intermediate/cchr.tab.c"
        break;
      case 59: /* carglist */
#line 63 "cchr.y"
        { destruct_constr_t(&yyvaluep->constr); };
#line 1142 "intermediate/cchr.tab.c"
        break;
      case 60: /* constr */
#line 63 "cchr.y"
        { destruct_constr_t(&yyvaluep->constr); };
#line 1147 "intermediate/cchr.tab.c"
        break;
      case 61: /* typelist */
#line 63 "cchr.y"
        { destruct_constr_t(&yyvaluep->constr); };
#line 1152 "intermediate/cchr.tab.c"
        break;
      case 62: /* typelistc */
#line 63 "cchr.y"
        { destruct_constr_t(&yyvaluep->constr); };
#line 1157 "intermediate/cchr.tab.c"
        break;
      case 63: /* type */
#line 60 "cchr.y"
        { free(yyvaluep->lit); };
#line 1162 "intermediate/cchr.tab.c"
        break;

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse ( yyscan_t scanner ,  cchr_t *output );
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse ( yyscan_t scanner ,  cchr_t *output )
#else
int
yyparse (scanner, output)
     yyscan_t scanner ;
     cchr_t *output ;
#endif
#endif
{
  /* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  register short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  YYLTYPE *yylerrsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

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

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
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
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
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

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
  *++yylsp = yylloc;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, yylsp - yylen, yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 89 "cchr.y"
    { *output=yyvsp[0].cchr; ;}
    break;

  case 3:
#line 90 "cchr.y"
    { *output=yyvsp[-1].cchr; 
	   free(yyvsp[0].lit); /* dumpCHR(output, 1); */ 
	   YYACCEPT; ;}
    break;

  case 4:
#line 95 "cchr.y"
    { cchr_init(&yyval.cchr); ;}
    break;

  case 5:
#line 96 "cchr.y"
    { yyval.cchr=yyvsp[-1].cchr; cchr_merge(&yyval.cchr,&yyvsp[0].cchr); ;}
    break;

  case 6:
#line 99 "cchr.y"
    { yyval.expr.list=yyvsp[-1].expr.list; yyval.expr.occn=yyvsp[-1].expr.occn; alist_addall(yyval.expr.list,yyvsp[0].expr.list); alist_free(yyvsp[0].expr.list); ;}
    break;

  case 7:
#line 100 "cchr.y"
    { alist_init(yyval.expr.list); yyval.expr.occn=NULL; ;}
    break;

  case 8:
#line 103 "cchr.y"
    { yyval.expr.list=yyvsp[-1].expr.list; alist_addall(yyval.expr.list,yyvsp[0].expr.list); alist_free(yyvsp[0].expr.list); yyval.expr.occn=NULL; ;}
    break;

  case 9:
#line 104 "cchr.y"
    { alist_init(yyval.expr.list); yyval.expr.occn=NULL; ;}
    break;

  case 10:
#line 107 "cchr.y"
    { yyval.expr.list=yyvsp[-1].expr.list; alist_addall(yyval.expr.list,yyvsp[0].expr.list); alist_free(yyvsp[0].expr.list); yyval.expr.occn=NULL; ;}
    break;

  case 11:
#line 108 "cchr.y"
    { alist_init(yyval.expr.list); yyval.expr.occn=NULL; ;}
    break;

  case 12:
#line 111 "cchr.y"
    { 
    		alist_init(yyval.expr.list);
		    yyvsp[-1].token.data=yyvsp[-2].lit;
		    alist_add(yyval.expr.list,yyvsp[-1].token);
		    free(yyvsp[0].lit);
		    yyval.expr.occn=NULL;
		;}
    break;

  case 13:
#line 118 "cchr.y"
    { 
   		    alist_init(yyval.expr.list);
		    token_t *tok;
		    alist_new(yyval.expr.list,tok);
		    alist_init(tok->args);
		    tok->type=TOKEN_TYPE_FUNC;
		    tok->data=yyvsp[-1].lit;
		    free(yyvsp[0].lit);
		    yyval.expr.occn=NULL;
		;}
    break;

  case 14:
#line 129 "cchr.y"
    { alist_init(yyval.expr.list); token_t *tok; alist_new(yyval.expr.list,tok); tok->data=yyvsp[0].lit; tok->type=TOKEN_TYPE_LIT; alist_init(tok->args); yyval.expr.occn=NULL; ;}
    break;

  case 16:
#line 131 "cchr.y"
    { alist_init(yyval.expr.list); token_t *tok; alist_new(yyval.expr.list,tok); tok->data=yyvsp[0].lit; tok->type=TOKEN_TYPE_LIT; alist_init(tok->args); yyval.expr.occn=NULL; ;}
    break;

  case 17:
#line 132 "cchr.y"
    { alist_init(yyval.expr.list); token_t *tok; alist_new(yyval.expr.list,tok); tok->data=yyvsp[0].lit; tok->type=TOKEN_TYPE_LIT; alist_init(tok->args); yyval.expr.occn=NULL; ;}
    break;

  case 18:
#line 133 "cchr.y"
    { alist_init(yyval.expr.list); token_t *tok; alist_new(yyval.expr.list,tok); tok->data=yyvsp[-2].lit; tok->type=TOKEN_TYPE_LIT; alist_addall(yyval.expr.list,yyvsp[-1].expr.list); alist_new(yyval.expr.list,tok); tok->data=yyvsp[0].lit; tok->type=TOKEN_TYPE_LIT; alist_free(yyvsp[-1].expr.list); yyval.expr.occn=NULL; ;}
    break;

  case 19:
#line 134 "cchr.y"
    { 
   		    alist_init(yyval.expr.list);
		    token_t *tok;
		    alist_new(yyval.expr.list,tok);
		    tok->data=yyvsp[0].lit;
		    tok->type=TOKEN_TYPE_SYMB;
		    alist_init(tok->args);
		    yyval.expr.occn=NULL; 
		  ;}
    break;

  case 20:
#line 143 "cchr.y"
    {
   		    alist_init(yyval.expr.list);
		    token_t *tok;
		    alist_new(yyval.expr.list,tok);
		    alist_init(tok->args);
		    tok->type=TOKEN_TYPE_FUNC;
		    tok->data=NULL;
		    free(yyvsp[0].lit);
		    free(yyvsp[-1].lit);
		    yyval.expr.occn=NULL; 
	  ;}
    break;

  case 21:
#line 154 "cchr.y"
    { 
    		alist_init(yyval.expr.list);
		    yyvsp[-1].token.data=NULL;
		    alist_add(yyval.expr.list,yyvsp[-1].token);
		    free(yyvsp[0].lit);
		    free(yyvsp[-2].lit);
		    yyval.expr.occn=NULL; 
		;}
    break;

  case 23:
#line 165 "cchr.y"
    { alist_init(yyval.expr.list); token_t *tok; alist_new(yyval.expr.list,tok); tok->data=yyvsp[0].lit; tok->type=TOKEN_TYPE_LIT; yyval.expr.occn=NULL; ;}
    break;

  case 24:
#line 166 "cchr.y"
    { alist_init(yyval.expr.list); token_t *tok; alist_new(yyval.expr.list,tok); tok->data=yyvsp[0].lit; tok->type=TOKEN_TYPE_SYMB; alist_new(yyval.expr.list,tok); tok->data=malloc(2); strcpy(tok->data,"@"); tok->type=TOKEN_TYPE_LIT; yyval.expr.occn=NULL; ;}
    break;

  case 26:
#line 170 "cchr.y"
    { alist_init(yyval.expr.list); token_t *tok; alist_new(yyval.expr.list,tok); tok->data=yyvsp[0].lit; tok->type=TOKEN_TYPE_LIT; yyval.expr.occn=NULL; ;}
    break;

  case 27:
#line 173 "cchr.y"
    { free(yyvsp[0].lit); alist_init(yyval.elist.list); ;}
    break;

  case 28:
#line 174 "cchr.y"
    { yyvsp[0].expr.occn=NULL; alist_init(yyval.elist.list); alist_add(yyval.elist.list,yyvsp[0].expr); ;}
    break;

  case 29:
#line 175 "cchr.y"
    { yyvsp[-2].expr.occn=yyvsp[0].lit; alist_init(yyval.elist.list); alist_add(yyval.elist.list,yyvsp[-2].expr); free(yyvsp[-1].lit); ;}
    break;

  case 30:
#line 176 "cchr.y"
    { yyvsp[0].expr.occn=NULL; yyval.elist=yyvsp[-2].elist; alist_add(yyval.elist.list,yyvsp[0].expr); free(yyvsp[-1].lit); ;}
    break;

  case 31:
#line 177 "cchr.y"
    { yyvsp[-2].expr.occn=yyvsp[0].lit; yyval.elist=yyvsp[-4].elist; alist_add(yyval.elist.list,yyvsp[-2].expr); free(yyvsp[-3].lit); free(yyvsp[-1].lit); ;}
    break;

  case 32:
#line 179 "cchr.y"
    { yyval.lit=malloc(strlen(yyvsp[-2].lit)+strlen(yyvsp[-1].lit)+strlen(yyvsp[0].lit)+1); strcpy(yyval.lit,yyvsp[-2].lit); strcat(yyval.lit,yyvsp[-1].lit); strcat(yyval.lit,yyvsp[0].lit); free(yyvsp[-2].lit); free(yyvsp[-1].lit); free(yyvsp[0].lit); ;}
    break;

  case 33:
#line 182 "cchr.y"
    { yyval.lit=malloc(strlen(yyvsp[-2].lit)+strlen(yyvsp[-1].lit)+strlen(yyvsp[0].lit)+1); strcpy(yyval.lit,yyvsp[-2].lit); strcat(yyval.lit,yyvsp[-1].lit); strcat(yyval.lit,yyvsp[0].lit); free(yyvsp[-2].lit); free(yyvsp[-1].lit); free(yyvsp[0].lit); ;}
    break;

  case 34:
#line 185 "cchr.y"
    { yyval.lit=malloc(1); yyval.lit[0]=0; ;}
    break;

  case 35:
#line 186 "cchr.y"
    { 
				yyval.lit=malloc(strlen(yyvsp[-1].lit)+strlen(yyvsp[0].lit)+1);
				strcpy(yyval.lit,yyvsp[-1].lit);
				strcat(yyval.lit,yyvsp[0].lit);
				free(yyvsp[-1].lit);
				free(yyvsp[0].lit);
			  ;}
    break;

  case 36:
#line 195 "cchr.y"
    { yyval.lit=malloc(1); yyval.lit[0]=0; ;}
    break;

  case 37:
#line 196 "cchr.y"
    { 
				yyval.lit=malloc(strlen(yyvsp[-1].lit)+strlen(yyvsp[0].lit)+1);
				strcpy(yyval.lit,yyvsp[-1].lit);
				strcat(yyval.lit,yyvsp[0].lit);
				free(yyvsp[-1].lit);
				free(yyvsp[0].lit);
			  ;}
    break;

  case 38:
#line 205 "cchr.y"
    { yyval.token.type = TOKEN_TYPE_FUNC; alist_init(yyval.token.args); yyval.token.data=NULL; alist_add(yyval.token.args,yyvsp[0].expr); ;}
    break;

  case 39:
#line 206 "cchr.y"
    { yyval.token=yyvsp[-2].token; alist_add(yyval.token.args,yyvsp[0].expr); free(yyvsp[-1].lit); ;}
    break;

  case 40:
#line 208 "cchr.y"
    { cchr_init(&yyval.cchr); alist_add(yyval.cchr.exts,yyvsp[0].lit); ;}
    break;

  case 41:
#line 209 "cchr.y"
    { yyval.cchr=yyvsp[-2].cchr; alist_add(yyval.cchr.exts,yyvsp[0].lit); free(yyvsp[-1].lit); ;}
    break;

  case 47:
#line 218 "cchr.y"
    { yyval.lit=yyvsp[0].lit; ;}
    break;

  case 48:
#line 219 "cchr.y"
    { yyval.lit=NULL; ;}
    break;

  case 49:
#line 222 "cchr.y"
    { cchr_genrule(&yyval.cchr,yyvsp[-8].lit,&yyvsp[-7].elist,&yyvsp[-5].elist,&yyvsp[-3].elist,&yyvsp[-1].elist); free(yyvsp[-6].lit); free(yyvsp[-4].lit); free(yyvsp[-2].lit); free(yyvsp[0].lit); ;}
    break;

  case 50:
#line 223 "cchr.y"
    { cchr_genrule(&yyval.cchr,yyvsp[-6].lit,NULL,&yyvsp[-5].elist,&yyvsp[-3].elist,&yyvsp[-1].elist); free(yyvsp[-4].lit); free(yyvsp[-2].lit); free(yyvsp[0].lit); ;}
    break;

  case 51:
#line 224 "cchr.y"
    { cchr_genrule(&yyval.cchr,yyvsp[-6].lit,&yyvsp[-5].elist,NULL,&yyvsp[-3].elist,&yyvsp[-1].elist); free(yyvsp[-4].lit); free(yyvsp[-2].lit); free(yyvsp[0].lit); ;}
    break;

  case 52:
#line 225 "cchr.y"
    { cchr_genrule(&yyval.cchr,yyvsp[-6].lit,&yyvsp[-5].elist,&yyvsp[-3].elist,NULL,&yyvsp[-1].elist); free(yyvsp[-4].lit); free(yyvsp[-2].lit); free(yyvsp[0].lit); ;}
    break;

  case 53:
#line 226 "cchr.y"
    { cchr_genrule(&yyval.cchr,yyvsp[-4].lit,NULL,&yyvsp[-3].elist,NULL,&yyvsp[-1].elist); free(yyvsp[-2].lit); free(yyvsp[0].lit); ;}
    break;

  case 54:
#line 227 "cchr.y"
    { cchr_genrule(&yyval.cchr,yyvsp[-4].lit,&yyvsp[-3].elist,NULL,NULL,&yyvsp[-1].elist); free(yyvsp[-2].lit); free(yyvsp[0].lit); ;}
    break;

  case 55:
#line 231 "cchr.y"
    { yyval.cchr=yyvsp[-1].cchr; free(yyvsp[-2].lit); free(yyvsp[0].lit); ;}
    break;

  case 56:
#line 232 "cchr.y"
    { yyval.cchr=yyvsp[-1].cchr; free(yyvsp[-2].lit); free(yyvsp[0].lit); ;}
    break;

  case 57:
#line 233 "cchr.y"
    { cchr_init(&yyval.cchr); macro_t *nw; alist_new(yyval.cchr.macros,nw); nw->name=yyvsp[-2].constr; nw->def=yyvsp[-1].expr; free(yyvsp[-3].lit); free(yyvsp[0].lit); ;}
    break;

  case 58:
#line 234 "cchr.y"
    { cchr_init(&yyval.cchr); logical_t *nw; alist_new(yyval.cchr.logicals,nw); nw->name=yyvsp[-2].lit; nw->cb=yyvsp[-1].lit; free(yyvsp[-3].lit); free(yyvsp[0].lit); ;}
    break;

  case 60:
#line 239 "cchr.y"
    { cchr_init(&yyval.cchr); yyvsp[-1].constr.args=yyvsp[0].constr.args; alist_add(yyval.cchr.constrs,yyvsp[-1].constr); ;}
    break;

  case 61:
#line 240 "cchr.y"
    { yyval.cchr=yyvsp[-3].cchr; yyvsp[-1].constr.args=yyvsp[0].constr.args; alist_add(yyval.cchr.constrs,yyvsp[-1].constr); free(yyvsp[-2].lit); ;}
    break;

  case 62:
#line 243 "cchr.y"
    { alist_init(yyval.constr.args); alist_init(yyval.constr.list); yyval.constr.name=NULL; ;}
    break;

  case 63:
#line 244 "cchr.y"
    { alist_add(yyvsp[-1].constr.args,yyvsp[0].expr); yyval.constr=yyvsp[-1].constr; ;}
    break;

  case 64:
#line 247 "cchr.y"
    { yyval.constr=yyvsp[-1].constr; yyval.constr.name=yyvsp[-2].lit; free(yyvsp[0].lit); alist_init(yyval.constr.args); ;}
    break;

  case 65:
#line 250 "cchr.y"
    { yyval.constr.name=NULL; alist_init(yyval.constr.list); ;}
    break;

  case 66:
#line 251 "cchr.y"
    { yyval.constr = yyvsp[0].constr; ;}
    break;

  case 67:
#line 254 "cchr.y"
    { yyval.constr.name=NULL; alist_init(yyval.constr.list); alist_add(yyval.constr.list,yyvsp[0].lit); ;}
    break;

  case 68:
#line 255 "cchr.y"
    { yyval.constr=yyvsp[-2].constr; alist_add(yyval.constr.list,yyvsp[0].lit); free(yyvsp[-1].lit); ;}
    break;

  case 69:
#line 258 "cchr.y"
    { yyval.lit = yyvsp[0].lit; ;}
    break;

  case 70:
#line 259 "cchr.y"
    { yyval.lit = realloc(yyvsp[-1].lit,strlen(yyvsp[-1].lit)+strlen(yyvsp[0].lit)+2); strcat(yyval.lit," "); strcat(yyval.lit,yyvsp[0].lit); free(yyvsp[0].lit); ;}
    break;

  case 71:
#line 260 "cchr.y"
    { yyval.lit = realloc(yyvsp[-1].lit,strlen(yyvsp[-1].lit)+strlen(yyvsp[0].lit)+2); strcat(yyval.lit," "); strcat(yyval.lit,yyvsp[0].lit); free(yyvsp[0].lit); ;}
    break;


    }

/* Line 1010 of yacc.c.  */
#line 1836 "intermediate/cchr.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;
  yylsp -= yylen;

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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (&yylloc, scanner, output, yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror (&yylloc, scanner, output, "syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (&yylloc, scanner, output, "syntax error");
    }

  yylerrsp = yylsp;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {
		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp, yylsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	  *++yylerrsp = yylloc;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

  yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  yylerrsp = yylsp;
  *++yylerrsp = yyloc;
  yylsp -= yylen;
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
  YYLLOC_DEFAULT (yyloc, yylsp, yylerrsp - yylsp);
  *++yylsp = yyloc;

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
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror (&yylloc, scanner, output, "parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 263 "cchr.y"


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




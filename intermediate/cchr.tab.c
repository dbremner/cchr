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
     TOK_ERROR = 277,
     PRE_ENDALIST = 278,
     PRE_ELIST = 279,
     PRE_ETLIST = 280
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
#define TOK_ERROR 277
#define PRE_ENDALIST 278
#define PRE_ELIST 279
#define PRE_ETLIST 280




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

typedef void *yyscan_t;
#define YYLEX_PARAM scanner

void dumpCHR(cchr_t *chr,int level);
int static yyerror(YYLTYPE *loc,yyscan_t scanner,cchr_t *output,char *msg);
int yylex ( YYSTYPE * lvalp, YYLTYPE * llocp, yyscan_t scanner );

void cchr_init(cchr_t *cchr);
void cchr_merge(cchr_t *out,cchr_t *in);
void cchr_genrule(cchr_t *cchr,char *name,exprlist_t *kept,exprlist_t *removed,
                  expr_t *guard,exprlist_t *body);

#endif



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 39 "cchr.y"
typedef union YYSTYPE {
  char *lit;
  expr_t expr;
  token_t token;
  constr_t constr;
  cchr_t cchr;
  exprlist_t elist;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 168 "intermediate/cchr.tab.c"
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
#line 192 "intermediate/cchr.tab.c"

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
#define YYLAST   105

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  26
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  19
/* YYNRULES -- Number of rules. */
#define YYNRULES  47
/* YYNRULES -- Number of states. */
#define YYNSTATES  78

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   280

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
      25
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    12,    13,    16,    17,
      19,    23,    26,    28,    32,    34,    36,    38,    40,    42,
      46,    48,    52,    54,    58,    60,    62,    64,    66,    68,
      69,    79,    87,    95,   103,   109,   115,   119,   123,   125,
     127,   131,   135,   136,   138,   140,   144,   146
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      27,     0,    -1,    28,    -1,    -1,    28,    39,    -1,    29,
      31,    -1,    -1,    30,    32,    -1,    -1,    36,    -1,    16,
      34,    15,    -1,    16,    15,    -1,    19,    -1,    14,    30,
      15,    -1,    31,    -1,    12,    -1,    17,    -1,     4,    -1,
      29,    -1,    33,     8,    29,    -1,    30,    -1,    34,     8,
      30,    -1,    19,    -1,    35,     8,    19,    -1,     8,    -1,
      18,    -1,    20,    -1,     9,    -1,    17,    -1,    -1,    37,
      33,    13,    33,    10,    29,    12,    33,     7,    -1,    37,
      33,    10,    29,    12,    33,     7,    -1,    37,    33,    11,
      29,    12,    33,     7,    -1,    37,    33,    13,    33,    10,
      33,     7,    -1,    37,    33,    10,    33,     7,    -1,    37,
      33,    11,    33,     7,    -1,     3,    40,     7,    -1,    21,
      35,     7,    -1,    38,    -1,    41,    -1,    40,     8,    41,
      -1,    16,    42,    15,    -1,    -1,    43,    -1,    44,    -1,
      43,     8,    44,    -1,    19,    -1,    44,    19,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,    83,    83,    86,    87,    90,    91,    94,    95,    98,
     106,   112,   121,   130,   146,   147,   148,   151,   152,   153,
     155,   156,   158,   159,   161,   162,   163,   164,   167,   168,
     171,   172,   173,   174,   175,   176,   180,   181,   182,   186,
     187,   190,   192,   193,   196,   197,   200,   201
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
  "TOK_OP", "TOK_EXTERN", "TOK_ERROR", "PRE_ENDALIST", "PRE_ELIST",
  "PRE_ETLIST", "$accept", "main", "input", "tokenlist", "etokenlist",
  "token", "etoken", "exprlist", "arglist", "extlist", "literal", "rname",
  "rule", "stmt", "constrlist", "constr", "typelist", "typelistc", "type", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    26,    27,    28,    28,    29,    29,    30,    30,    31,
      31,    31,    31,    31,    32,    32,    32,    33,    33,    33,
      34,    34,    35,    35,    36,    36,    36,    36,    37,    37,
      38,    38,    38,    38,    38,    38,    39,    39,    39,    40,
      40,    41,    42,    42,    43,    43,    44,    44
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     0,     2,     2,     0,     2,     0,     1,
       3,     2,     1,     3,     1,     1,     1,     1,     1,     3,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     0,
       9,     7,     7,     7,     5,     5,     3,     3,     1,     1,
       3,     3,     0,     1,     1,     3,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       3,     0,    29,     1,     0,    28,     0,     6,    38,     4,
      42,     0,    39,    22,     0,    17,    18,     0,    46,     0,
      43,    44,    36,     0,    37,     0,    24,    27,     8,     8,
      25,    12,    26,     5,     9,     6,     6,     6,     6,    41,
       0,    47,    40,    23,     0,    11,    20,     0,    19,    18,
       0,    18,     0,     0,    45,    15,    13,    16,    14,     7,
       8,    10,     6,    34,     6,    35,     6,    21,     0,     0,
      18,     0,    31,    32,     6,    33,     0,    30
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     1,     2,    16,    44,    33,    59,    17,    47,    14,
      34,     7,     8,     9,    11,    12,    19,    20,    21
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -37
static const yysigned_char yypact[] =
{
     -37,    29,    10,   -37,    -8,   -37,    14,    36,   -37,   -37,
      33,    17,   -37,   -37,    42,   -37,    71,    84,   -37,    41,
      46,    45,   -37,    -8,   -37,    47,   -37,   -37,   -37,    53,
     -37,   -37,   -37,   -37,   -37,   -37,    36,    36,    36,   -37,
      33,   -37,   -37,   -37,    27,   -37,     3,    -1,    71,    39,
      54,    51,    66,     8,    45,   -37,   -37,   -37,   -37,   -37,
     -37,   -37,    36,   -37,    36,   -37,    36,     3,    91,    93,
      63,    95,   -37,   -37,    36,   -37,    97,   -37
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -37,   -37,   -37,   -32,   -23,   -35,   -37,   -36,   -37,   -37,
     -37,   -37,   -37,   -37,   -37,    55,   -37,   -37,    44
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yysigned_char yytable[] =
{
      50,    52,    53,    48,    49,    51,    46,    60,    10,    58,
      -2,    58,    27,     4,    61,    55,    35,    28,    66,    29,
      57,    30,    31,    32,    22,    23,    68,     5,    69,     3,
      71,     6,    58,    13,    70,    26,    27,    67,    76,    55,
      15,    28,    56,    29,    57,    30,    31,    32,    27,    24,
      25,    62,    18,    28,    40,    29,    39,    30,    31,    32,
      27,    63,    35,    64,    41,    28,    43,    29,    45,    30,
      31,    32,    27,    65,    35,    74,     0,    28,    42,    29,
      27,    30,    31,    32,    54,    28,     0,    29,     0,    30,
      31,    32,    35,     0,    36,    37,     0,    38,    72,    35,
      73,    35,    75,    35,    77,    35
};

static const yysigned_char yycheck[] =
{
      36,    37,    38,    35,    36,    37,    29,     8,    16,    44,
       0,    46,     9,     3,    15,    12,     8,    14,    10,    16,
      17,    18,    19,    20,     7,     8,    62,    17,    64,     0,
      66,    21,    67,    19,    66,     8,     9,    60,    74,    12,
       4,    14,    15,    16,    17,    18,    19,    20,     9,     7,
       8,    12,    19,    14,     8,    16,    15,    18,    19,    20,
       9,     7,     8,    12,    19,    14,    19,    16,    15,    18,
      19,    20,     9,     7,     8,    12,    -1,    14,    23,    16,
       9,    18,    19,    20,    40,    14,    -1,    16,    -1,    18,
      19,    20,     8,    -1,    10,    11,    -1,    13,     7,     8,
       7,     8,     7,     8,     7,     8
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    27,    28,     0,     3,    17,    21,    37,    38,    39,
      16,    40,    41,    19,    35,     4,    29,    33,    19,    42,
      43,    44,     7,     8,     7,     8,     8,     9,    14,    16,
      18,    19,    20,    31,    36,     8,    10,    11,    13,    15,
       8,    19,    41,    19,    30,    15,    30,    34,    29,    29,
      33,    29,    33,    33,    44,    12,    15,    17,    31,    32,
       8,    15,    12,     7,    12,     7,    10,    30,    33,    33,
      29,    33,     7,     7,    12,     7,    33,     7
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
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 849 "intermediate/cchr.tab.c"
        break;
      case 4: /* TOK_TRUE */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 854 "intermediate/cchr.tab.c"
        break;
      case 5: /* TOK_LCBRAC */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 859 "intermediate/cchr.tab.c"
        break;
      case 6: /* TOK_RCBRAC */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 864 "intermediate/cchr.tab.c"
        break;
      case 7: /* TOK_SEMI */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 869 "intermediate/cchr.tab.c"
        break;
      case 8: /* TOK_COMMA */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 874 "intermediate/cchr.tab.c"
        break;
      case 9: /* TOK_AT */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 879 "intermediate/cchr.tab.c"
        break;
      case 10: /* TOK_SIMP */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 884 "intermediate/cchr.tab.c"
        break;
      case 11: /* TOK_PROP */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 889 "intermediate/cchr.tab.c"
        break;
      case 12: /* TOK_SPIPE */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 894 "intermediate/cchr.tab.c"
        break;
      case 13: /* TOK_BSLASH */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 899 "intermediate/cchr.tab.c"
        break;
      case 14: /* TOK_LRBRAC */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 904 "intermediate/cchr.tab.c"
        break;
      case 15: /* TOK_RRBRAC */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 909 "intermediate/cchr.tab.c"
        break;
      case 16: /* TOK_FUNC */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 914 "intermediate/cchr.tab.c"
        break;
      case 17: /* TOK_SYMBAT */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 919 "intermediate/cchr.tab.c"
        break;
      case 18: /* TOK_CONST */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 924 "intermediate/cchr.tab.c"
        break;
      case 19: /* TOK_SYMB */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 929 "intermediate/cchr.tab.c"
        break;
      case 20: /* TOK_OP */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 934 "intermediate/cchr.tab.c"
        break;
      case 21: /* TOK_EXTERN */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 939 "intermediate/cchr.tab.c"
        break;
      case 28: /* input */
#line 67 "cchr.y"
        { destruct_cchr_t(&yyvaluep->cchr); };
#line 944 "intermediate/cchr.tab.c"
        break;
      case 29: /* tokenlist */
#line 61 "cchr.y"
        { destruct_expr_t(&yyvaluep->expr); };
#line 949 "intermediate/cchr.tab.c"
        break;
      case 30: /* etokenlist */
#line 61 "cchr.y"
        { destruct_expr_t(&yyvaluep->expr); };
#line 954 "intermediate/cchr.tab.c"
        break;
      case 31: /* token */
#line 61 "cchr.y"
        { destruct_expr_t(&yyvaluep->expr); };
#line 959 "intermediate/cchr.tab.c"
        break;
      case 32: /* etoken */
#line 61 "cchr.y"
        { destruct_expr_t(&yyvaluep->expr); };
#line 964 "intermediate/cchr.tab.c"
        break;
      case 33: /* exprlist */
#line 70 "cchr.y"
        { destruct_exprlist_t(&yyvaluep->elist); };
#line 969 "intermediate/cchr.tab.c"
        break;
      case 34: /* arglist */
#line 64 "cchr.y"
        { destruct_token_t(&yyvaluep->token); };
#line 974 "intermediate/cchr.tab.c"
        break;
      case 35: /* extlist */
#line 67 "cchr.y"
        { destruct_cchr_t(&yyvaluep->cchr); };
#line 979 "intermediate/cchr.tab.c"
        break;
      case 36: /* literal */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 984 "intermediate/cchr.tab.c"
        break;
      case 37: /* rname */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 989 "intermediate/cchr.tab.c"
        break;
      case 38: /* rule */
#line 67 "cchr.y"
        { destruct_cchr_t(&yyvaluep->cchr); };
#line 994 "intermediate/cchr.tab.c"
        break;
      case 39: /* stmt */
#line 67 "cchr.y"
        { destruct_cchr_t(&yyvaluep->cchr); };
#line 999 "intermediate/cchr.tab.c"
        break;
      case 40: /* constrlist */
#line 67 "cchr.y"
        { destruct_cchr_t(&yyvaluep->cchr); };
#line 1004 "intermediate/cchr.tab.c"
        break;
      case 41: /* constr */
#line 58 "cchr.y"
        { destruct_constr_t(&yyvaluep->constr); };
#line 1009 "intermediate/cchr.tab.c"
        break;
      case 42: /* typelist */
#line 58 "cchr.y"
        { destruct_constr_t(&yyvaluep->constr); };
#line 1014 "intermediate/cchr.tab.c"
        break;
      case 43: /* typelistc */
#line 58 "cchr.y"
        { destruct_constr_t(&yyvaluep->constr); };
#line 1019 "intermediate/cchr.tab.c"
        break;
      case 44: /* type */
#line 55 "cchr.y"
        { free(yyvaluep->lit); };
#line 1024 "intermediate/cchr.tab.c"
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
#line 83 "cchr.y"
    { *output=yyvsp[0].cchr; ;}
    break;

  case 3:
#line 86 "cchr.y"
    { cchr_init(&yyval.cchr); ;}
    break;

  case 4:
#line 87 "cchr.y"
    { yyval.cchr=yyvsp[-1].cchr; cchr_merge(&yyval.cchr,&yyvsp[0].cchr); ;}
    break;

  case 5:
#line 90 "cchr.y"
    { yyval.expr.list=yyvsp[-1].expr.list; alist_addall(yyval.expr.list,yyvsp[0].expr.list); alist_free(yyvsp[0].expr.list); ;}
    break;

  case 6:
#line 91 "cchr.y"
    { alist_init(yyval.expr.list); ;}
    break;

  case 7:
#line 94 "cchr.y"
    { yyval.expr.list=yyvsp[-1].expr.list; alist_addall(yyval.expr.list,yyvsp[0].expr.list); alist_free(yyvsp[0].expr.list); ;}
    break;

  case 8:
#line 95 "cchr.y"
    { alist_init(yyval.expr.list); ;}
    break;

  case 9:
#line 98 "cchr.y"
    { 
		    alist_init(yyval.expr.list);
		    token_t *tok;
		    alist_new(yyval.expr.list,tok);
		    tok->data=yyvsp[0].lit;
		    tok->type=TOKEN_TYPE_LIT;
		    alist_init(tok->args);
		;}
    break;

  case 10:
#line 106 "cchr.y"
    { 
    		    alist_init(yyval.expr.list);
		    yyvsp[-1].token.data=yyvsp[-2].lit;
		    alist_add(yyval.expr.list,yyvsp[-1].token);
		    free(yyvsp[0].lit);
		;}
    break;

  case 11:
#line 112 "cchr.y"
    { 
    		    alist_init(yyval.expr.list);
		    token_t *tok;
		    alist_new(yyval.expr.list,tok);
		    alist_init(tok->args);
		    tok->type=TOKEN_TYPE_FUNC;
		    tok->data=yyvsp[-1].lit;
		    free(yyvsp[0].lit);
		;}
    break;

  case 12:
#line 121 "cchr.y"
    { 
    		    alist_init(yyval.expr.list);
		    token_t *tok;
		    alist_new(yyval.expr.list,tok);
		    tok->data=yyvsp[0].lit;
		    tok->type=TOKEN_TYPE_SYMB;
		    alist_init(tok->args);

		  ;}
    break;

  case 13:
#line 130 "cchr.y"
    { 
    		    alist_init(yyval.expr.list);
		    token_t *tok;
		    alist_new(yyval.expr.list,tok);
		    tok->data=yyvsp[-2].lit;
		    tok->type=TOKEN_TYPE_LIT;
		    alist_init(tok->args);
		    alist_addall(yyval.expr.list,yyvsp[-1].expr.list);
		    alist_new(yyval.expr.list,tok);
		    tok->data=yyvsp[0].lit;
		    tok->type=TOKEN_TYPE_LIT;
		    alist_init(tok->args);
		    alist_free(yyvsp[-1].expr.list);
		;}
    break;

  case 15:
#line 147 "cchr.y"
    { alist_init(yyval.expr.list); token_t *tok; alist_new(yyval.expr.list,tok); tok->data=yyvsp[0].lit; tok->type=TOKEN_TYPE_LIT; ;}
    break;

  case 16:
#line 148 "cchr.y"
    { alist_init(yyval.expr.list); token_t *tok; alist_new(yyval.expr.list,tok); tok->data=yyvsp[0].lit; tok->type=TOKEN_TYPE_SYMB; alist_new(yyval.expr.list,tok); tok->data=malloc(2); strcpy(tok->data,"@"); tok->type=TOKEN_TYPE_LIT;;}
    break;

  case 17:
#line 151 "cchr.y"
    { free(yyvsp[0].lit); alist_init(yyval.elist.list); ;}
    break;

  case 18:
#line 152 "cchr.y"
    { alist_init(yyval.elist.list); alist_add(yyval.elist.list,yyvsp[0].expr); ;}
    break;

  case 19:
#line 153 "cchr.y"
    { yyval.elist=yyvsp[-2].elist; alist_add(yyval.elist.list,yyvsp[0].expr); free(yyvsp[-1].lit); ;}
    break;

  case 20:
#line 155 "cchr.y"
    { yyval.token.type = TOKEN_TYPE_FUNC; alist_init(yyval.token.args); yyval.token.data=NULL; alist_add(yyval.token.args,yyvsp[0].expr); ;}
    break;

  case 21:
#line 156 "cchr.y"
    { yyval.token=yyvsp[-2].token; alist_add(yyval.token.args,yyvsp[0].expr); free(yyvsp[-1].lit); ;}
    break;

  case 22:
#line 158 "cchr.y"
    { cchr_init(&yyval.cchr); alist_add(yyval.cchr.exts,yyvsp[0].lit); ;}
    break;

  case 23:
#line 159 "cchr.y"
    { yyval.cchr=yyvsp[-2].cchr; alist_add(yyval.cchr.exts,yyvsp[0].lit); free(yyvsp[-1].lit); ;}
    break;

  case 28:
#line 167 "cchr.y"
    { yyval.lit=yyvsp[0].lit; ;}
    break;

  case 29:
#line 168 "cchr.y"
    { yyval.lit=NULL; ;}
    break;

  case 30:
#line 171 "cchr.y"
    { cchr_genrule(&yyval.cchr,yyvsp[-8].lit,&yyvsp[-7].elist,&yyvsp[-5].elist,&yyvsp[-3].expr,&yyvsp[-1].elist); free(yyvsp[-6].lit); free(yyvsp[-4].lit); free(yyvsp[-2].lit); free(yyvsp[0].lit); ;}
    break;

  case 31:
#line 172 "cchr.y"
    { cchr_genrule(&yyval.cchr,yyvsp[-6].lit,NULL,&yyvsp[-5].elist,&yyvsp[-3].expr,&yyvsp[-1].elist); free(yyvsp[-4].lit); free(yyvsp[-2].lit); free(yyvsp[0].lit); ;}
    break;

  case 32:
#line 173 "cchr.y"
    { cchr_genrule(&yyval.cchr,yyvsp[-6].lit,&yyvsp[-5].elist,NULL,&yyvsp[-3].expr,&yyvsp[-1].elist); free(yyvsp[-4].lit); free(yyvsp[-2].lit); free(yyvsp[0].lit); ;}
    break;

  case 33:
#line 174 "cchr.y"
    { cchr_genrule(&yyval.cchr,yyvsp[-6].lit,&yyvsp[-5].elist,&yyvsp[-3].elist,NULL,&yyvsp[-1].elist); free(yyvsp[-4].lit); free(yyvsp[-2].lit); free(yyvsp[0].lit); ;}
    break;

  case 34:
#line 175 "cchr.y"
    { cchr_genrule(&yyval.cchr,yyvsp[-4].lit,NULL,&yyvsp[-3].elist,NULL,&yyvsp[-1].elist); free(yyvsp[-2].lit); free(yyvsp[0].lit); ;}
    break;

  case 35:
#line 176 "cchr.y"
    { cchr_genrule(&yyval.cchr,yyvsp[-4].lit,&yyvsp[-3].elist,NULL,NULL,&yyvsp[-1].elist); free(yyvsp[-2].lit); free(yyvsp[0].lit); ;}
    break;

  case 36:
#line 180 "cchr.y"
    { yyval.cchr=yyvsp[-1].cchr; free(yyvsp[-2].lit); free(yyvsp[0].lit); ;}
    break;

  case 37:
#line 181 "cchr.y"
    { yyval.cchr=yyvsp[-1].cchr; free(yyvsp[-2].lit); free(yyvsp[0].lit); ;}
    break;

  case 39:
#line 186 "cchr.y"
    { cchr_init(&yyval.cchr); alist_add(yyval.cchr.constrs,yyvsp[0].constr); ;}
    break;

  case 40:
#line 187 "cchr.y"
    { yyval.cchr=yyvsp[-2].cchr; alist_add(yyval.cchr.constrs,yyvsp[0].constr); free(yyvsp[-1].lit); ;}
    break;

  case 41:
#line 190 "cchr.y"
    { yyval.constr=yyvsp[-1].constr; yyval.constr.name=yyvsp[-2].lit; free(yyvsp[0].lit); ;}
    break;

  case 42:
#line 192 "cchr.y"
    { yyval.constr.name=NULL; alist_init(yyval.constr.list); ;}
    break;

  case 43:
#line 193 "cchr.y"
    { yyval.constr = yyvsp[0].constr; ;}
    break;

  case 44:
#line 196 "cchr.y"
    { yyval.constr.name=NULL; alist_init(yyval.constr.list); alist_add(yyval.constr.list,yyvsp[0].lit); ;}
    break;

  case 45:
#line 197 "cchr.y"
    { yyval.constr=yyvsp[-2].constr; alist_add(yyval.constr.list,yyvsp[0].lit); free(yyvsp[-1].lit); ;}
    break;

  case 46:
#line 200 "cchr.y"
    { yyval.lit = yyvsp[0].lit; ;}
    break;

  case 47:
#line 201 "cchr.y"
    { yyval.lit = realloc(yyvsp[-1].lit,strlen(yyvsp[-1].lit)+strlen(yyvsp[0].lit)+2); strcat(yyval.lit," "); strcat(yyval.lit,yyvsp[0].lit); free(yyvsp[0].lit); ;}
    break;


    }

/* Line 1010 of yacc.c.  */
#line 1580 "intermediate/cchr.tab.c"

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


#line 204 "cchr.y"


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
  printIndent(level); fprintf(stderr,"Guard='"); dumpExpr(&(rule->guard)); fprintf(stderr,"';\n");
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

void cchr_genrule(cchr_t *cchr,char *name,exprlist_t *kept,exprlist_t *removed,expr_t *guard,exprlist_t *body) {
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




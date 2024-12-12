/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "syntax.y"

#include "lex.yy.c"
#include "yystype.h"

void yyerror(char *msg);
void add_error(int lineno);
int error_flag = 0;
Node *tree_root=NULL;
int error_lineno[1024], cnt_errorb = 0;
int has_a_error = 0;

#line 83 "syntax.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "syntax.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_FLOAT = 3,                      /* FLOAT  */
  YYSYMBOL_INT = 4,                        /* INT  */
  YYSYMBOL_TYPE = 5,                       /* TYPE  */
  YYSYMBOL_STRUCT = 6,                     /* STRUCT  */
  YYSYMBOL_RETURN = 7,                     /* RETURN  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_WHILE = 10,                     /* WHILE  */
  YYSYMBOL_SEMI = 11,                      /* SEMI  */
  YYSYMBOL_COMMA = 12,                     /* COMMA  */
  YYSYMBOL_LC = 13,                        /* LC  */
  YYSYMBOL_RC = 14,                        /* RC  */
  YYSYMBOL_ID = 15,                        /* ID  */
  YYSYMBOL_ASSIGNOP = 16,                  /* ASSIGNOP  */
  YYSYMBOL_AND = 17,                       /* AND  */
  YYSYMBOL_OR = 18,                        /* OR  */
  YYSYMBOL_RELOP = 19,                     /* RELOP  */
  YYSYMBOL_PLUS = 20,                      /* PLUS  */
  YYSYMBOL_MINUS = 21,                     /* MINUS  */
  YYSYMBOL_DIV = 22,                       /* DIV  */
  YYSYMBOL_NOT = 23,                       /* NOT  */
  YYSYMBOL_STAR = 24,                      /* STAR  */
  YYSYMBOL_LP = 25,                        /* LP  */
  YYSYMBOL_RP = 26,                        /* RP  */
  YYSYMBOL_LB = 27,                        /* LB  */
  YYSYMBOL_RB = 28,                        /* RB  */
  YYSYMBOL_DOT = 29,                       /* DOT  */
  YYSYMBOL_LOWER_THAN_ELSE = 30,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_Program = 32,                   /* Program  */
  YYSYMBOL_ExtDefList = 33,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 34,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 35,                /* ExtDecList  */
  YYSYMBOL_Specifier = 36,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 37,           /* StructSpecifier  */
  YYSYMBOL_OptTag = 38,                    /* OptTag  */
  YYSYMBOL_Tag = 39,                       /* Tag  */
  YYSYMBOL_VarDec = 40,                    /* VarDec  */
  YYSYMBOL_FunDec = 41,                    /* FunDec  */
  YYSYMBOL_VarList = 42,                   /* VarList  */
  YYSYMBOL_ParamDec = 43,                  /* ParamDec  */
  YYSYMBOL_CompSt = 44,                    /* CompSt  */
  YYSYMBOL_StmtList = 45,                  /* StmtList  */
  YYSYMBOL_Stmt = 46,                      /* Stmt  */
  YYSYMBOL_DefList = 47,                   /* DefList  */
  YYSYMBOL_Def = 48,                       /* Def  */
  YYSYMBOL_DecList = 49,                   /* DecList  */
  YYSYMBOL_Dec = 50,                       /* Dec  */
  YYSYMBOL_Exp = 51,                       /* Exp  */
  YYSYMBOL_Args = 52                       /* Args  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   284

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  134

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    26,    26,    32,    36,    38,    42,    46,    50,    54,
      55,    57,    61,    66,    70,    75,    79,    84,    88,    90,
      95,    99,   103,   105,   109,   113,   115,   119,   124,   129,
     133,   135,   139,   141,   145,   149,   153,   158,   162,   166,
     167,   168,   169,   171,   173,   177,   179,   183,   185,   189,
     194,   198,   203,   207,   211,   215,   219,   223,   227,   231,
     235,   239,   243,   247,   251,   255,   259,   263,   267,   271,
     276,   280
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "FLOAT", "INT", "TYPE",
  "STRUCT", "RETURN", "IF", "ELSE", "WHILE", "SEMI", "COMMA", "LC", "RC",
  "ID", "ASSIGNOP", "AND", "OR", "RELOP", "PLUS", "MINUS", "DIV", "NOT",
  "STAR", "LP", "RP", "LB", "RB", "DOT", "LOWER_THAN_ELSE", "$accept",
  "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-42)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-33)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     278,    80,   -42,     4,    34,   -42,   278,    56,   -42,    39,
      10,   -42,    42,    46,   -42,   -42,   -42,    28,   -42,    64,
      86,    -5,    89,   -42,    63,    91,    10,    10,   -42,   -42,
     -42,    -3,   -42,    73,    99,   -42,   -42,    30,   -42,    52,
     100,   101,    62,   -42,   -42,   117,     3,    12,    90,   117,
     117,   117,   -42,   103,    91,   128,   -42,   108,   -42,    73,
      92,   111,    96,   -42,    98,   -42,   117,   -42,    73,   -42,
     -42,   142,   102,   117,   105,   117,   104,   248,   -15,   170,
     -42,   -42,   -42,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   118,   -42,   107,   -42,    10,   -42,   226,   -42,
     -42,    17,   184,    17,   198,   -42,   156,   109,   -42,   226,
     237,   237,   247,   248,   248,   -15,   -15,   212,   -42,   -42,
     127,    17,   -42,    17,   117,   -42,   -42,    17,   132,   -42,
     -42,   -42,    17,   -42
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    13,    18,     0,     2,     0,     0,    14,     0,
      45,    10,    19,     0,    16,     1,     3,     0,     6,    20,
       0,    11,     0,    30,     0,     0,    45,    45,     9,    25,
      22,     0,     5,     0,     0,     8,     7,     0,    20,    50,
       0,    48,     0,    69,    68,     0,     0,     0,    67,     0,
       0,     0,    34,     0,     0,     0,    44,     0,    24,     0,
       0,    27,     0,    12,     0,    47,     0,    46,     0,    39,
      40,     0,     0,     0,     0,     0,     0,    61,    62,     0,
      29,    31,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    15,    28,    23,     0,    21,    51,    49,
      35,     0,     0,     0,     0,    64,    71,     0,    60,    52,
      53,    54,    55,    56,    57,    59,    58,     0,    66,    26,
      42,     0,    41,     0,     0,    63,    65,     0,    36,    38,
      70,    43,     0,    37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -42,   -42,   131,   -42,   110,     0,   -42,   -42,   -42,    -7,
     -42,    55,   -42,     7,   113,   -41,    83,   -42,    88,   -42,
     -40,    41
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,    20,    24,     8,    13,    14,    21,
      22,    60,    61,    52,    53,    54,    25,    26,    40,    41,
      55,   107
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       7,    70,     2,     3,    72,    71,     7,    33,    11,    77,
      78,    79,    91,    74,    92,     2,     3,    39,    42,    12,
      43,    44,    34,    58,    45,    46,    98,    47,    73,    36,
      10,    59,    48,   102,    15,   104,   106,    75,    49,    28,
      50,    65,    51,   109,   110,   111,   112,   113,   114,   115,
     116,   117,    94,    23,    29,   -17,    30,    17,    30,    27,
     120,    39,   122,    42,    37,    43,    44,    18,    66,    45,
      46,    19,    47,    69,    62,    10,    23,    48,    38,    34,
     128,     9,   129,    49,   106,    50,   131,    51,    38,    31,
       9,   133,    42,    10,    43,    44,    59,    32,    45,    46,
      35,    47,    10,    64,    10,   -32,    48,    43,    44,    56,
      57,    67,    49,    68,    50,    76,    51,    80,    95,    48,
      43,    44,    93,    96,    30,    49,    97,    50,   101,    51,
     105,   103,    48,   118,    34,   125,   127,    16,    49,    82,
      50,   132,    51,    63,    83,    84,    85,    86,    87,    88,
      89,   119,    90,   100,     0,    91,    99,    92,    83,    84,
      85,    86,    87,    88,    89,   130,    90,    81,   124,    91,
       0,    92,    83,    84,    85,    86,    87,    88,    89,     0,
      90,     0,     0,    91,     0,    92,    83,    84,    85,    86,
      87,    88,    89,     0,    90,     0,   108,    91,     0,    92,
      83,    84,    85,    86,    87,    88,    89,     0,    90,     0,
     121,    91,     0,    92,    83,    84,    85,    86,    87,    88,
      89,     0,    90,     0,   123,    91,     0,    92,    83,    84,
      85,    86,    87,    88,    89,     0,    90,     0,     0,    91,
     126,    92,    83,    84,    85,    86,    87,    88,    89,     0,
      90,     0,     0,    91,     0,    92,    86,    87,    88,    89,
       0,    90,     0,     0,    91,     0,    92,    87,    88,    89,
      89,    90,    90,     0,    91,    91,    92,    92,    -4,     1,
       0,     0,     0,     2,     3
};

static const yytype_int16 yycheck[] =
{
       0,    42,     5,     6,     1,    45,     6,    12,     1,    49,
      50,    51,    27,     1,    29,     5,     6,    24,     1,    15,
       3,     4,    27,    26,     7,     8,    66,    10,    25,    22,
      13,    31,    15,    73,     0,    75,    76,    25,    21,    11,
      23,    11,    25,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    59,    14,    26,    13,    28,     1,    28,    13,
     101,    68,   103,     1,     1,     3,     4,    11,    16,     7,
       8,    15,    10,    11,     1,    13,    14,    15,    15,    27,
     121,     1,   123,    21,   124,    23,   127,    25,    15,    25,
       1,   132,     1,    13,     3,     4,    96,    11,     7,     8,
      11,    10,    13,     4,    13,    14,    15,     3,     4,    26,
      27,    11,    21,    12,    23,    25,    25,    14,    26,    15,
       3,     4,    14,    12,    28,    21,    28,    23,    26,    25,
      26,    26,    15,    15,    27,    26,     9,     6,    21,    11,
      23,     9,    25,    33,    16,    17,    18,    19,    20,    21,
      22,    96,    24,    11,    -1,    27,    68,    29,    16,    17,
      18,    19,    20,    21,    22,   124,    24,    54,    12,    27,
      -1,    29,    16,    17,    18,    19,    20,    21,    22,    -1,
      24,    -1,    -1,    27,    -1,    29,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    -1,    26,    27,    -1,    29,
      16,    17,    18,    19,    20,    21,    22,    -1,    24,    -1,
      26,    27,    -1,    29,    16,    17,    18,    19,    20,    21,
      22,    -1,    24,    -1,    26,    27,    -1,    29,    16,    17,
      18,    19,    20,    21,    22,    -1,    24,    -1,    -1,    27,
      28,    29,    16,    17,    18,    19,    20,    21,    22,    -1,
      24,    -1,    -1,    27,    -1,    29,    19,    20,    21,    22,
      -1,    24,    -1,    -1,    27,    -1,    29,    20,    21,    22,
      22,    24,    24,    -1,    27,    27,    29,    29,     0,     1,
      -1,    -1,    -1,     5,     6
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     5,     6,    32,    33,    34,    36,    37,     1,
      13,    44,    15,    38,    39,     0,    33,     1,    11,    15,
      35,    40,    41,    14,    36,    47,    48,    13,    11,    26,
      28,    25,    11,    12,    27,    11,    44,     1,    15,    40,
      49,    50,     1,     3,     4,     7,     8,    10,    15,    21,
      23,    25,    44,    45,    46,    51,    47,    47,    26,    36,
      42,    43,     1,    35,     4,    11,    16,    11,    12,    11,
      46,    51,     1,    25,     1,    25,    25,    51,    51,    51,
      14,    45,    11,    16,    17,    18,    19,    20,    21,    22,
      24,    27,    29,    14,    40,    26,    12,    28,    51,    49,
      11,    26,    51,    26,    51,    26,    51,    52,    26,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    15,    42,
      46,    26,    46,    26,    12,    26,    28,     9,    46,    46,
      52,    46,     9,    46
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    34,    34,
      34,    35,    35,    36,    36,    37,    37,    38,    38,    39,
      40,    40,    40,    41,    41,    41,    42,    42,    43,    44,
      44,    45,    45,    46,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    47,    47,    48,    48,    49,    49,
      50,    50,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      52,    52
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     3,     3,
       2,     1,     3,     1,     1,     5,     2,     1,     0,     1,
       1,     4,     2,     4,     3,     2,     3,     1,     2,     4,
       2,     2,     0,     2,     1,     3,     5,     7,     5,     2,
       2,     4,     4,     6,     2,     0,     3,     3,     1,     3,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     4,     3,     4,     3,     1,     1,     1,
       3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: ExtDefList  */
#line 26 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[0]};
                                                                BUILDTREE(Program, 1);
                                                                tree_root=yyval;
                                                            }
#line 1241 "syntax.tab.c"
    break;

  case 3: /* ExtDefList: ExtDef ExtDefList  */
#line 32 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(ExtDefList, 2);
                                                            }
#line 1250 "syntax.tab.c"
    break;

  case 4: /* ExtDefList: %empty  */
#line 36 "syntax.y"
                                                            {   yyval = NULL; }
#line 1256 "syntax.tab.c"
    break;

  case 5: /* ExtDef: Specifier ExtDecList SEMI  */
#line 38 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(ExtDef, 3);
                                                            }
#line 1265 "syntax.tab.c"
    break;

  case 6: /* ExtDef: Specifier SEMI  */
#line 42 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(ExtDef, 2);
                                                            }
#line 1274 "syntax.tab.c"
    break;

  case 7: /* ExtDef: Specifier FunDec CompSt  */
#line 46 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(ExtDef, 3);
                                                            }
#line 1283 "syntax.tab.c"
    break;

  case 8: /* ExtDef: Specifier FunDec SEMI  */
#line 50 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(ExtDef, 3);
                                                            }
#line 1292 "syntax.tab.c"
    break;

  case 9: /* ExtDef: Specifier error SEMI  */
#line 54 "syntax.y"
                                                            {}
#line 1298 "syntax.tab.c"
    break;

  case 10: /* ExtDef: error CompSt  */
#line 55 "syntax.y"
                                                            {}
#line 1304 "syntax.tab.c"
    break;

  case 11: /* ExtDecList: VarDec  */
#line 57 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[0]};
                                                                BUILDTREE(ExtDecList, 1);
                                                            }
#line 1313 "syntax.tab.c"
    break;

  case 12: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 61 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(ExtDecList, 3);
                                                            }
#line 1322 "syntax.tab.c"
    break;

  case 13: /* Specifier: TYPE  */
#line 66 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[0]};
                                                                BUILDTREE(Specifier, 1);
                                                            }
#line 1331 "syntax.tab.c"
    break;

  case 14: /* Specifier: StructSpecifier  */
#line 70 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[0]};
                                                                BUILDTREE(Specifier, 1);
                                                            }
#line 1340 "syntax.tab.c"
    break;

  case 15: /* StructSpecifier: STRUCT OptTag LC DefList RC  */
#line 75 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-4], &yyvsp[-3], &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(StructSpecifier, 5);
                                                            }
#line 1349 "syntax.tab.c"
    break;

  case 16: /* StructSpecifier: STRUCT Tag  */
#line 79 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(StructSpecifier, 2);
                                                            }
#line 1358 "syntax.tab.c"
    break;

  case 17: /* OptTag: ID  */
#line 84 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[0]};
                                                                BUILDTREE(OptTag, 1);
                                                            }
#line 1367 "syntax.tab.c"
    break;

  case 18: /* OptTag: %empty  */
#line 88 "syntax.y"
                                                            {   yyval = NULL; }
#line 1373 "syntax.tab.c"
    break;

  case 19: /* Tag: ID  */
#line 90 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[0]};
                                                                BUILDTREE(Tag, 1);
                                                            }
#line 1382 "syntax.tab.c"
    break;

  case 20: /* VarDec: ID  */
#line 95 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[0]};
                                                                BUILDTREE(VarDec, 1);
                                                            }
#line 1391 "syntax.tab.c"
    break;

  case 21: /* VarDec: VarDec LB INT RB  */
#line 99 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-3], &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(VarDec, 4);
                                                            }
#line 1400 "syntax.tab.c"
    break;

  case 22: /* VarDec: error RB  */
#line 103 "syntax.y"
                                                            {}
#line 1406 "syntax.tab.c"
    break;

  case 23: /* FunDec: ID LP VarList RP  */
#line 105 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-3], &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(FunDec, 4);
                                                            }
#line 1415 "syntax.tab.c"
    break;

  case 24: /* FunDec: ID LP RP  */
#line 109 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(FunDec, 3);
                                                            }
#line 1424 "syntax.tab.c"
    break;

  case 25: /* FunDec: error RP  */
#line 113 "syntax.y"
                                                            {}
#line 1430 "syntax.tab.c"
    break;

  case 26: /* VarList: ParamDec COMMA VarList  */
#line 115 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(VarList, 3);
                                                            }
#line 1439 "syntax.tab.c"
    break;

  case 27: /* VarList: ParamDec  */
#line 119 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[0]};
                                                                BUILDTREE(VarList, 1);
                                                            }
#line 1448 "syntax.tab.c"
    break;

  case 28: /* ParamDec: Specifier VarDec  */
#line 124 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(ParamDec, 2);
                                                            }
#line 1457 "syntax.tab.c"
    break;

  case 29: /* CompSt: LC DefList StmtList RC  */
#line 129 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-3], &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(CompSt, 4);
                                                            }
#line 1466 "syntax.tab.c"
    break;

  case 30: /* CompSt: error RC  */
#line 133 "syntax.y"
                                                            {}
#line 1472 "syntax.tab.c"
    break;

  case 31: /* StmtList: Stmt StmtList  */
#line 135 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(StmtList, 2);
                                                            }
#line 1481 "syntax.tab.c"
    break;

  case 32: /* StmtList: %empty  */
#line 139 "syntax.y"
                                                            {   yyval = NULL; }
#line 1487 "syntax.tab.c"
    break;

  case 33: /* Stmt: Exp SEMI  */
#line 141 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Stmt, 2);
                                                            }
#line 1496 "syntax.tab.c"
    break;

  case 34: /* Stmt: CompSt  */
#line 145 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[0]};
                                                                BUILDTREE(Stmt, 1);
                                                            }
#line 1505 "syntax.tab.c"
    break;

  case 35: /* Stmt: RETURN Exp SEMI  */
#line 149 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Stmt, 3);
                                                            }
#line 1514 "syntax.tab.c"
    break;

  case 36: /* Stmt: IF LP Exp RP Stmt  */
#line 154 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-4], &yyvsp[-3], &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Stmt, 5);
                                                            }
#line 1523 "syntax.tab.c"
    break;

  case 37: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 158 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-6], &yyvsp[-5], &yyvsp[-4], &yyvsp[-3], &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Stmt, 7);
                                                            }
#line 1532 "syntax.tab.c"
    break;

  case 38: /* Stmt: WHILE LP Exp RP Stmt  */
#line 162 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-4], &yyvsp[-3], &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Stmt, 5);
                                                            }
#line 1541 "syntax.tab.c"
    break;

  case 39: /* Stmt: error SEMI  */
#line 166 "syntax.y"
                                                            {}
#line 1547 "syntax.tab.c"
    break;

  case 40: /* Stmt: error Stmt  */
#line 167 "syntax.y"
                                                            {}
#line 1553 "syntax.tab.c"
    break;

  case 41: /* Stmt: WHILE error RP Stmt  */
#line 168 "syntax.y"
                                                            {}
#line 1559 "syntax.tab.c"
    break;

  case 42: /* Stmt: IF error RP Stmt  */
#line 170 "syntax.y"
                                                            {}
#line 1565 "syntax.tab.c"
    break;

  case 43: /* Stmt: IF error RP Stmt ELSE Stmt  */
#line 171 "syntax.y"
                                                            {}
#line 1571 "syntax.tab.c"
    break;

  case 44: /* DefList: Def DefList  */
#line 173 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(DefList, 2);
                                                            }
#line 1580 "syntax.tab.c"
    break;

  case 45: /* DefList: %empty  */
#line 177 "syntax.y"
                                                            {   yyval = NULL; }
#line 1586 "syntax.tab.c"
    break;

  case 46: /* Def: Specifier DecList SEMI  */
#line 179 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Def, 3);
                                                            }
#line 1595 "syntax.tab.c"
    break;

  case 47: /* Def: Specifier error SEMI  */
#line 183 "syntax.y"
                                                            {}
#line 1601 "syntax.tab.c"
    break;

  case 48: /* DecList: Dec  */
#line 185 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[0]};
                                                                BUILDTREE(DecList, 1);
                                                            }
#line 1610 "syntax.tab.c"
    break;

  case 49: /* DecList: Dec COMMA DecList  */
#line 189 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(DecList, 3);
                                                            }
#line 1619 "syntax.tab.c"
    break;

  case 50: /* Dec: VarDec  */
#line 194 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[0]};
                                                                BUILDTREE(Dec, 1);
                                                            }
#line 1628 "syntax.tab.c"
    break;

  case 51: /* Dec: VarDec ASSIGNOP Exp  */
#line 198 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Dec, 3);
                                                            }
#line 1637 "syntax.tab.c"
    break;

  case 52: /* Exp: Exp ASSIGNOP Exp  */
#line 203 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Exp, 3);
                                                            }
#line 1646 "syntax.tab.c"
    break;

  case 53: /* Exp: Exp AND Exp  */
#line 207 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Exp, 3);
                                                            }
#line 1655 "syntax.tab.c"
    break;

  case 54: /* Exp: Exp OR Exp  */
#line 211 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Exp, 3);
                                                            }
#line 1664 "syntax.tab.c"
    break;

  case 55: /* Exp: Exp RELOP Exp  */
#line 215 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Exp, 3);
                                                            }
#line 1673 "syntax.tab.c"
    break;

  case 56: /* Exp: Exp PLUS Exp  */
#line 219 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Exp, 3);
                                                            }
#line 1682 "syntax.tab.c"
    break;

  case 57: /* Exp: Exp MINUS Exp  */
#line 223 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Exp, 3);
                                                            }
#line 1691 "syntax.tab.c"
    break;

  case 58: /* Exp: Exp STAR Exp  */
#line 227 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Exp, 3);
                                                            }
#line 1700 "syntax.tab.c"
    break;

  case 59: /* Exp: Exp DIV Exp  */
#line 231 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Exp, 3);
                                                            }
#line 1709 "syntax.tab.c"
    break;

  case 60: /* Exp: LP Exp RP  */
#line 235 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Exp, 3);
                                                            }
#line 1718 "syntax.tab.c"
    break;

  case 61: /* Exp: MINUS Exp  */
#line 239 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Exp, 2);
                                                            }
#line 1727 "syntax.tab.c"
    break;

  case 62: /* Exp: NOT Exp  */
#line 243 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Exp, 2);
                                                            }
#line 1736 "syntax.tab.c"
    break;

  case 63: /* Exp: ID LP Args RP  */
#line 247 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-3], &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Exp, 4);
                                                            }
#line 1745 "syntax.tab.c"
    break;

  case 64: /* Exp: ID LP RP  */
#line 251 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Exp, 3);
                                                            }
#line 1754 "syntax.tab.c"
    break;

  case 65: /* Exp: Exp LB Exp RB  */
#line 255 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-3], &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Exp, 4);
                                                            }
#line 1763 "syntax.tab.c"
    break;

  case 66: /* Exp: Exp DOT ID  */
#line 259 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Exp, 3);
                                                            }
#line 1772 "syntax.tab.c"
    break;

  case 67: /* Exp: ID  */
#line 263 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[0]};
                                                                BUILDTREE(Exp, 1);
                                                            }
#line 1781 "syntax.tab.c"
    break;

  case 68: /* Exp: INT  */
#line 267 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[0]};
                                                                BUILDTREE(Exp, 1);
                                                            }
#line 1790 "syntax.tab.c"
    break;

  case 69: /* Exp: FLOAT  */
#line 271 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[0]};
                                                                BUILDTREE(Exp, 1);
                                                            }
#line 1799 "syntax.tab.c"
    break;

  case 70: /* Args: Exp COMMA Args  */
#line 276 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[-2], &yyvsp[-1], &yyvsp[0]};
                                                                BUILDTREE(Args, 3);
                                                            }
#line 1808 "syntax.tab.c"
    break;

  case 71: /* Args: Exp  */
#line 280 "syntax.y"
                                                            {
                                                                Node **args[8] = {&yyval, &yyvsp[0]};
                                                                BUILDTREE(Args, 1);
                                                            }
#line 1817 "syntax.tab.c"
    break;


#line 1821 "syntax.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 285 "syntax.y"

void yyerror(char *msg) {
    add_error(yylineno);
}
void add_error(int lineno) {
    if (cnt_errorb == 0 || error_lineno[cnt_errorb - 1] != lineno)
        error_lineno[cnt_errorb++] = lineno;
}

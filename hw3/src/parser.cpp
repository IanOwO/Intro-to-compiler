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
#line 1 "parser.y"

#include "AST/BinaryOperator.hpp"
#include "AST/CompoundStatement.hpp"
#include "AST/ConstantValue.hpp"
#include "AST/FunctionInvocation.hpp"
#include "AST/UnaryOperator.hpp"
#include "AST/VariableReference.hpp"
#include "AST/assignment.hpp"
#include "AST/ast.hpp"
#include "AST/decl.hpp"
#include "AST/expression.hpp"
#include "AST/for.hpp"
#include "AST/function.hpp"
#include "AST/if.hpp"
#include "AST/print.hpp"
#include "AST/program.hpp"
#include "AST/read.hpp"
#include "AST/return.hpp"
#include "AST/variable.hpp"
#include "AST/while.hpp"
#include "AST/AstDumper.hpp"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>


#define YYLTYPE yyltype

typedef struct YYLTYPE {
    uint32_t first_line;
    uint32_t first_column;
    uint32_t last_line;
    uint32_t last_column;
} yyltype;

extern int32_t line_num;    /* declared in scanner.l */
extern char current_line[]; /* declared in scanner.l */
extern FILE *yyin;          /* declared by lex */
extern char *yytext;        /* declared by lex */

static AstNode *root;

struct id_data{
    const char* const name;
    uint32_t line;
    uint32_t column;
};

extern "C" int yylex(void);
static void yyerror(const char *msg);
extern int yylex_destroy(void);

#line 127 "parser.cpp"

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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_COMMA = 3,                      /* COMMA  */
  YYSYMBOL_SEMICOLON = 4,                  /* SEMICOLON  */
  YYSYMBOL_COLON = 5,                      /* COLON  */
  YYSYMBOL_L_PARENTHESIS = 6,              /* L_PARENTHESIS  */
  YYSYMBOL_R_PARENTHESIS = 7,              /* R_PARENTHESIS  */
  YYSYMBOL_L_BRACKET = 8,                  /* L_BRACKET  */
  YYSYMBOL_R_BRACKET = 9,                  /* R_BRACKET  */
  YYSYMBOL_ASSIGN = 10,                    /* ASSIGN  */
  YYSYMBOL_OR = 11,                        /* OR  */
  YYSYMBOL_AND = 12,                       /* AND  */
  YYSYMBOL_NOT = 13,                       /* NOT  */
  YYSYMBOL_LESS = 14,                      /* LESS  */
  YYSYMBOL_LESS_OR_EQUAL = 15,             /* LESS_OR_EQUAL  */
  YYSYMBOL_EQUAL = 16,                     /* EQUAL  */
  YYSYMBOL_GREATER = 17,                   /* GREATER  */
  YYSYMBOL_GREATER_OR_EQUAL = 18,          /* GREATER_OR_EQUAL  */
  YYSYMBOL_NOT_EQUAL = 19,                 /* NOT_EQUAL  */
  YYSYMBOL_PLUS = 20,                      /* PLUS  */
  YYSYMBOL_MINUS = 21,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 22,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 23,                    /* DIVIDE  */
  YYSYMBOL_MOD = 24,                       /* MOD  */
  YYSYMBOL_UNARY_MINUS = 25,               /* UNARY_MINUS  */
  YYSYMBOL_ARRAY = 26,                     /* ARRAY  */
  YYSYMBOL_BOOLEAN = 27,                   /* BOOLEAN  */
  YYSYMBOL_INTEGER = 28,                   /* INTEGER  */
  YYSYMBOL_REAL = 29,                      /* REAL  */
  YYSYMBOL_STRING = 30,                    /* STRING  */
  YYSYMBOL_END = 31,                       /* END  */
  YYSYMBOL_BEGIN_ = 32,                    /* BEGIN_  */
  YYSYMBOL_DO = 33,                        /* DO  */
  YYSYMBOL_ELSE = 34,                      /* ELSE  */
  YYSYMBOL_FOR = 35,                       /* FOR  */
  YYSYMBOL_IF = 36,                        /* IF  */
  YYSYMBOL_THEN = 37,                      /* THEN  */
  YYSYMBOL_WHILE = 38,                     /* WHILE  */
  YYSYMBOL_DEF = 39,                       /* DEF  */
  YYSYMBOL_OF = 40,                        /* OF  */
  YYSYMBOL_TO = 41,                        /* TO  */
  YYSYMBOL_RETURN = 42,                    /* RETURN  */
  YYSYMBOL_VAR = 43,                       /* VAR  */
  YYSYMBOL_FALSE = 44,                     /* FALSE  */
  YYSYMBOL_TRUE = 45,                      /* TRUE  */
  YYSYMBOL_PRINT = 46,                     /* PRINT  */
  YYSYMBOL_READ = 47,                      /* READ  */
  YYSYMBOL_ID = 48,                        /* ID  */
  YYSYMBOL_INT_LITERAL = 49,               /* INT_LITERAL  */
  YYSYMBOL_REAL_LITERAL = 50,              /* REAL_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 51,            /* STRING_LITERAL  */
  YYSYMBOL_YYACCEPT = 52,                  /* $accept  */
  YYSYMBOL_Program = 53,                   /* Program  */
  YYSYMBOL_ProgramName = 54,               /* ProgramName  */
  YYSYMBOL_DeclarationList = 55,           /* DeclarationList  */
  YYSYMBOL_Declarations = 56,              /* Declarations  */
  YYSYMBOL_FunctionList = 57,              /* FunctionList  */
  YYSYMBOL_Functions = 58,                 /* Functions  */
  YYSYMBOL_Function = 59,                  /* Function  */
  YYSYMBOL_FunctionDeclaration = 60,       /* FunctionDeclaration  */
  YYSYMBOL_FunctionDefinition = 61,        /* FunctionDefinition  */
  YYSYMBOL_FunctionName = 62,              /* FunctionName  */
  YYSYMBOL_FormalArgList = 63,             /* FormalArgList  */
  YYSYMBOL_FormalArgs = 64,                /* FormalArgs  */
  YYSYMBOL_FormalArg = 65,                 /* FormalArg  */
  YYSYMBOL_IdList = 66,                    /* IdList  */
  YYSYMBOL_ReturnType = 67,                /* ReturnType  */
  YYSYMBOL_Declaration = 68,               /* Declaration  */
  YYSYMBOL_Type = 69,                      /* Type  */
  YYSYMBOL_ScalarType = 70,                /* ScalarType  */
  YYSYMBOL_ArrType = 71,                   /* ArrType  */
  YYSYMBOL_ArrDecl = 72,                   /* ArrDecl  */
  YYSYMBOL_LiteralConstant = 73,           /* LiteralConstant  */
  YYSYMBOL_NegOrNot = 74,                  /* NegOrNot  */
  YYSYMBOL_StringAndBoolean = 75,          /* StringAndBoolean  */
  YYSYMBOL_IntegerAndReal = 76,            /* IntegerAndReal  */
  YYSYMBOL_Statement = 77,                 /* Statement  */
  YYSYMBOL_CompoundStatement = 78,         /* CompoundStatement  */
  YYSYMBOL_Simple = 79,                    /* Simple  */
  YYSYMBOL_VariableReference = 80,         /* VariableReference  */
  YYSYMBOL_ArrRefList = 81,                /* ArrRefList  */
  YYSYMBOL_ArrRefs = 82,                   /* ArrRefs  */
  YYSYMBOL_Condition = 83,                 /* Condition  */
  YYSYMBOL_ElseOrNot = 84,                 /* ElseOrNot  */
  YYSYMBOL_While = 85,                     /* While  */
  YYSYMBOL_For = 86,                       /* For  */
  YYSYMBOL_Return = 87,                    /* Return  */
  YYSYMBOL_FunctionCall = 88,              /* FunctionCall  */
  YYSYMBOL_FunctionInvocation = 89,        /* FunctionInvocation  */
  YYSYMBOL_ExpressionList = 90,            /* ExpressionList  */
  YYSYMBOL_Expressions = 91,               /* Expressions  */
  YYSYMBOL_StatementList = 92,             /* StatementList  */
  YYSYMBOL_Statements = 93,                /* Statements  */
  YYSYMBOL_Expression = 94,                /* Expression  */
  YYSYMBOL_Epsilon = 95                    /* Epsilon  */
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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   321

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  187

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   306


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   196,   196,   208,   212,   216,   222,   227,   234,   238,
     244,   249,   256,   260,   266,   295,   327,   333,   337,   343,
     348,   355,   374,   382,   394,   398,   408,   429,   453,   457,
     463,   467,   471,   475,   481,   489,   497,   507,   516,   525,
     544,   548,   554,   559,   564,   571,   576,   587,   591,   595,
     599,   603,   607,   611,   617,   626,   630,   634,   640,   647,
     651,   657,   662,   669,   678,   683,   689,   697,   729,   735,
     741,   748,   752,   758,   763,   770,   774,   780,   785,   792,
     796,   801,   806,   811,   816,   821,   826,   831,   836,   841,
     846,   851,   856,   861,   866,   871,   876,   893,   897,   905
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
  "\"end of file\"", "error", "\"invalid token\"", "COMMA", "SEMICOLON",
  "COLON", "L_PARENTHESIS", "R_PARENTHESIS", "L_BRACKET", "R_BRACKET",
  "ASSIGN", "OR", "AND", "NOT", "LESS", "LESS_OR_EQUAL", "EQUAL",
  "GREATER", "GREATER_OR_EQUAL", "NOT_EQUAL", "PLUS", "MINUS", "MULTIPLY",
  "DIVIDE", "MOD", "UNARY_MINUS", "ARRAY", "BOOLEAN", "INTEGER", "REAL",
  "STRING", "END", "BEGIN_", "DO", "ELSE", "FOR", "IF", "THEN", "WHILE",
  "DEF", "OF", "TO", "RETURN", "VAR", "FALSE", "TRUE", "PRINT", "READ",
  "ID", "INT_LITERAL", "REAL_LITERAL", "STRING_LITERAL", "$accept",
  "Program", "ProgramName", "DeclarationList", "Declarations",
  "FunctionList", "Functions", "Function", "FunctionDeclaration",
  "FunctionDefinition", "FunctionName", "FormalArgList", "FormalArgs",
  "FormalArg", "IdList", "ReturnType", "Declaration", "Type", "ScalarType",
  "ArrType", "ArrDecl", "LiteralConstant", "NegOrNot", "StringAndBoolean",
  "IntegerAndReal", "Statement", "CompoundStatement", "Simple",
  "VariableReference", "ArrRefList", "ArrRefs", "Condition", "ElseOrNot",
  "While", "For", "Return", "FunctionCall", "FunctionInvocation",
  "ExpressionList", "Expressions", "StatementList", "Statements",
  "Expression", "Epsilon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-60)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -15,   -60,    35,    33,   -60,    -5,    -9,    -7,    -5,   -60,
     -60,   -60,    10,   -60,    16,    -7,   -60,   -60,   -60,    52,
     -60,   -60,    11,    59,    -5,    45,   -60,    -9,   -60,   -60,
      28,   -60,   -60,   -60,   -60,   -60,   -60,   -60,    74,   -60,
     -60,    27,    75,   -30,   -60,   -60,    70,   -60,    76,    77,
     -60,    13,   -60,    42,   -60,    41,   -60,   -60,   -60,   -60,
      43,     1,     1,     1,     1,    44,    24,   -60,   -60,   -60,
      84,   -60,   -60,   -60,   -60,   -60,    92,    67,    70,   -60,
      94,    -9,   122,   -60,    60,    91,     1,     1,     1,   -60,
     -60,   -60,   -60,   -60,   -60,   110,   155,   178,   199,   101,
     107,     1,     1,   -60,   105,   -60,     1,   -60,   -60,   -60,
      -4,     4,   -60,   -60,   -60,   -60,    65,   238,   121,   -60,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,    16,    16,   -60,   -60,   -60,   108,   120,
     284,   -60,   254,     1,   220,   -60,   -60,   115,   112,   -60,
     297,   121,   139,   139,   139,   139,   139,   139,   -13,   -13,
     -60,   -60,   -60,   130,   123,   -60,     1,   -60,   270,   -60,
     -60,   106,    16,   125,   -60,   132,   284,   -60,   147,   -60,
     145,   -60,    16,   -60,   152,   151,   -60
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     3,     0,     0,     1,    99,     0,    99,     5,     6,
       4,    22,     0,    16,     0,     9,    10,    12,    13,     0,
       8,     7,     0,    99,    99,     0,    11,    99,    23,    41,
       0,    33,    30,    31,    32,    44,    43,    42,     0,    28,
      29,     0,     0,     0,    39,    40,    99,     2,     0,    18,
      19,     0,    17,     0,    26,     0,    34,    27,    37,    38,
       0,     0,     0,     0,     0,     0,    99,    77,    47,    48,
       0,    49,    50,    51,    52,    53,     0,     0,    76,    75,
      99,     0,     0,    35,     0,     0,     0,     0,     0,    45,
      46,    96,    95,    97,    98,     0,     0,     0,     0,    99,
       0,    99,     0,    58,    60,    59,     0,    69,    54,    78,
       0,     0,    25,    20,    21,    36,     0,     0,    92,    80,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    68,    56,    57,     0,    72,
      73,    71,     0,     0,     0,    24,    14,     0,     0,    79,
      94,    93,    86,    87,    90,    88,    89,    91,    84,    85,
      81,    82,    83,    99,     0,    70,     0,    61,     0,    55,
      15,     0,     0,     0,    65,     0,    74,    62,     0,    64,
       0,    66,     0,    63,     0,     0,    67
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -60,   -60,   -60,   161,   -60,   -60,   -60,   171,   -60,   -60,
     -60,   -60,   -60,   124,   181,   -60,   183,   126,   -35,   -60,
     -60,   -60,   -60,   184,   -60,   128,   -14,   -60,   -34,   -60,
     -60,   -60,   -60,   -60,   -60,   -60,   -60,   -44,   -60,   -60,
     -60,   -60,   -59,    -6
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     7,     8,    14,    15,    16,    17,    18,
      19,    48,    49,    50,    51,   111,     9,    38,    39,    40,
      41,    42,    43,    91,    92,    67,    68,    69,    93,   103,
     104,    71,   173,    72,    73,    74,    75,    94,   138,   139,
      77,    78,    95,    10
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      25,    20,    76,    96,    97,    98,    56,    86,   146,   130,
     131,   132,    70,    22,    87,    23,    22,    45,    82,    58,
      59,    52,    88,    31,    32,    33,    34,   117,   118,   119,
     101,   100,   102,     1,    76,     4,    24,     5,     6,    11,
      79,    13,   140,   142,    70,    35,    36,   144,    24,    66,
      89,    90,    37,    55,    31,    32,    33,    34,    27,    28,
     105,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   112,   145,    47,    53,    54,    57,
      29,    81,    83,    80,   168,    30,    31,    32,    33,    34,
      84,    85,    99,   105,   106,   141,   107,   147,   108,   110,
     115,   116,    24,    35,    36,    60,    61,   176,    62,   102,
      37,   137,    63,   143,   148,   165,    64,    65,    66,   163,
     164,   120,   121,   166,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   170,   133,    30,    31,
      32,    33,    34,   171,   175,   178,   180,   174,   179,   128,
     129,   130,   131,   132,   172,   181,   120,   121,   184,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     182,   183,   135,   185,   186,    46,    26,    12,   134,   120,
     121,    21,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   136,     0,   113,   109,    44,   114,     0,
     120,   121,     0,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   169,     0,     0,     0,     0,     0,
       0,   120,   121,     0,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   149,     0,     0,     0,   120,
     121,     0,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   167,     0,   120,   121,     0,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   177,
       0,   120,   121,     0,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   120,   121,     0,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   121,
       0,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132
};

static const yytype_int16 yycheck[] =
{
      14,     7,    46,    62,    63,    64,    41,     6,     4,    22,
      23,    24,    46,     3,    13,     5,     3,    23,     5,    49,
      50,    27,    21,    27,    28,    29,    30,    86,    87,    88,
       6,    65,     8,    48,    78,     0,    32,     4,    43,    48,
      46,    48,   101,   102,    78,    44,    45,   106,    32,    48,
      49,    50,    51,    26,    27,    28,    29,    30,     6,    48,
      66,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,    80,   110,    31,    49,     4,     4,
      21,     4,    40,     7,   143,    26,    27,    28,    29,    30,
      49,    48,    48,    99,    10,   101,     4,   111,    31,     5,
      40,    10,    32,    44,    45,    35,    36,   166,    38,     8,
      51,     4,    42,     8,    49,     7,    46,    47,    48,   133,
     134,    11,    12,     3,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    31,    37,    26,    27,
      28,    29,    30,    41,    31,    49,    31,   163,   172,    20,
      21,    22,    23,    24,    34,    33,    11,    12,   182,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      33,    36,     4,    31,    33,    24,    15,     6,    33,    11,
      12,     8,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     4,    -1,    81,    78,    23,    82,    -1,
      11,    12,    -1,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     4,    -1,    -1,    -1,    -1,    -1,
      -1,    11,    12,    -1,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,     7,    -1,    -1,    -1,    11,
      12,    -1,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     9,    -1,    11,    12,    -1,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,     9,
      -1,    11,    12,    -1,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    11,    12,    -1,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    12,
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    48,    53,    54,     0,     4,    43,    55,    56,    68,
      95,    48,    66,    48,    57,    58,    59,    60,    61,    62,
      95,    68,     3,     5,    32,    78,    59,     6,    48,    21,
      26,    27,    28,    29,    30,    44,    45,    51,    69,    70,
      71,    72,    73,    74,    75,    95,    55,    31,    63,    64,
      65,    66,    95,    49,     4,    26,    70,     4,    49,    50,
      35,    36,    38,    42,    46,    47,    48,    77,    78,    79,
      80,    83,    85,    86,    87,    88,    89,    92,    93,    95,
       7,     4,     5,    40,    49,    48,     6,    13,    21,    49,
      50,    75,    76,    80,    89,    94,    94,    94,    94,    48,
      80,     6,     8,    81,    82,    95,    10,     4,    31,    77,
       5,    67,    95,    65,    69,    40,    10,    94,    94,    94,
      11,    12,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    37,    33,     4,     4,     4,    90,    91,
      94,    95,    94,     8,    94,    70,     4,    78,    49,     7,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    78,    78,     7,     3,     9,    94,     4,
      31,    41,    34,    84,    95,    31,    94,     9,    49,    78,
      31,    33,    33,    36,    78,    31,    33
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    54,    55,    55,    56,    56,    57,    57,
      58,    58,    59,    59,    60,    61,    62,    63,    63,    64,
      64,    65,    66,    66,    67,    67,    68,    68,    69,    69,
      70,    70,    70,    70,    71,    72,    72,    73,    73,    73,
      74,    74,    75,    75,    75,    76,    76,    77,    77,    77,
      77,    77,    77,    77,    78,    79,    79,    79,    80,    81,
      81,    82,    82,    83,    84,    84,    85,    86,    87,    88,
      89,    90,    90,    91,    91,    92,    92,    93,    93,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    95
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     6,     1,     1,     1,     1,     2,     1,     1,
       1,     2,     1,     1,     6,     7,     1,     1,     1,     1,
       3,     3,     1,     3,     2,     1,     5,     5,     1,     1,
       1,     1,     1,     1,     2,     3,     4,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     4,     3,     3,     2,     1,
       1,     3,     4,     7,     2,     1,     6,    10,     3,     2,
       4,     1,     1,     1,     3,     1,     1,     1,     2,     3,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     3,     3,     1,     1,     1,     1,     0
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: ProgramName SEMICOLON DeclarationList FunctionList CompoundStatement END  */
#line 200 "parser.y"
        {
        root = new ProgramNode((yylsp[-5]).first_line, (yylsp[-5]).first_column,
                               (yyvsp[-5].identifier), (yyvsp[-3].node_list_ptr), (yyvsp[-2].node_list_ptr), (yyvsp[-1].compound_stmt_ptr));
        free((yyvsp[-5].identifier));
    }
#line 1489 "parser.cpp"
    break;

  case 4: /* DeclarationList: Epsilon  */
#line 212 "parser.y"
            {
        (yyval.node_list_ptr) = nullptr;
    }
#line 1497 "parser.cpp"
    break;

  case 5: /* DeclarationList: Declarations  */
#line 216 "parser.y"
                 {
        (yyval.node_list_ptr) = (yyvsp[0].node_list_ptr);
    }
#line 1505 "parser.cpp"
    break;

  case 6: /* Declarations: Declaration  */
#line 222 "parser.y"
                {
        (yyval.node_list_ptr) = new std::vector<AstNode*>;
        (yyval.node_list_ptr)->push_back((yyvsp[0].decl_ptr));
    }
#line 1514 "parser.cpp"
    break;

  case 7: /* Declarations: Declarations Declaration  */
#line 227 "parser.y"
                             {
        (yyval.node_list_ptr) = (yyvsp[-1].node_list_ptr);
        (yyval.node_list_ptr)->push_back((yyvsp[0].decl_ptr));
    }
#line 1523 "parser.cpp"
    break;

  case 8: /* FunctionList: Epsilon  */
#line 234 "parser.y"
            {
        (yyval.node_list_ptr) = nullptr;
    }
#line 1531 "parser.cpp"
    break;

  case 9: /* FunctionList: Functions  */
#line 238 "parser.y"
              {
        (yyval.node_list_ptr) = (yyvsp[0].node_list_ptr);
    }
#line 1539 "parser.cpp"
    break;

  case 10: /* Functions: Function  */
#line 244 "parser.y"
             {
        (yyval.node_list_ptr) = new std::vector<AstNode*>;
        (yyval.node_list_ptr)->push_back((yyvsp[0].func_ptr));
    }
#line 1548 "parser.cpp"
    break;

  case 11: /* Functions: Functions Function  */
#line 249 "parser.y"
                       {
        (yyval.node_list_ptr) = (yyvsp[-1].node_list_ptr);
        (yyval.node_list_ptr)->push_back((yyvsp[0].func_ptr));
    }
#line 1557 "parser.cpp"
    break;

  case 12: /* Function: FunctionDeclaration  */
#line 256 "parser.y"
                        {
        (yyval.func_ptr) = (yyvsp[0].func_ptr);
    }
#line 1565 "parser.cpp"
    break;

  case 13: /* Function: FunctionDefinition  */
#line 260 "parser.y"
                       {
        (yyval.func_ptr) = (yyvsp[0].func_ptr);
    }
#line 1573 "parser.cpp"
    break;

  case 14: /* FunctionDeclaration: FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType SEMICOLON  */
#line 266 "parser.y"
                                                                                {
        std::vector<AstNode*> *ast_node = new std::vector<AstNode*>;
        std::string arg_list;
        
        arg_list = (yyvsp[-1].identifier);
        arg_list += " (";
        if ((yyvsp[-3].decl_list_ptr) != nullptr) {
            for (unsigned int i = 0;i < ((yyvsp[-3].decl_list_ptr))->size();i++){
                // variable node pushback
                ast_node->push_back(new DeclNode(((yyvsp[-3].decl_list_ptr))->at(i)->getLocation().line, ((yyvsp[-3].decl_list_ptr))->at(i)->getLocation().col, 
                                                ((yyvsp[-3].decl_list_ptr))->at(i)->var_body, ((yyvsp[-3].decl_list_ptr))->at(i)->id_body, ((yyvsp[-3].decl_list_ptr))->at(i)->type_body));
                // type & parameter add
                if (i > 0) {
                    arg_list += ", ";
                }
                for (unsigned int j = 0;j < ((yyvsp[-3].decl_list_ptr))->at(i)->id_body->size();j++){
                    if (j > 0) {
                        arg_list += ", ";
                    }
                    arg_list += (yyvsp[-3].decl_list_ptr)->at(i)->type_body;
                }
            }
        }
        arg_list += ')';
        (yyval.func_ptr) = new FunctionNode((yylsp[-5]).first_line, (yylsp[-5]).first_column, (yyvsp[-5].identifier), arg_list, nullptr, ast_node);
    }
#line 1604 "parser.cpp"
    break;

  case 15: /* FunctionDefinition: FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType CompoundStatement END  */
#line 297 "parser.y"
        {
        std::vector<AstNode*> *ast_node = new std::vector<AstNode*>;
        std::string arg_list;
        // printf("name:%s,type:%s\n",$1,$5);
        arg_list = (yyvsp[-2].identifier);
        arg_list += " (";
        if ((yyvsp[-4].decl_list_ptr) != nullptr) {
            for (unsigned int i = 0;i < ((yyvsp[-4].decl_list_ptr))->size();i++){
                // variable node pushback
                ast_node->push_back(new DeclNode(((yyvsp[-4].decl_list_ptr))->at(i)->getLocation().line, ((yyvsp[-4].decl_list_ptr))->at(i)->getLocation().col, 
                                                ((yyvsp[-4].decl_list_ptr))->at(i)->var_body, ((yyvsp[-4].decl_list_ptr))->at(i)->id_body, ((yyvsp[-4].decl_list_ptr))->at(i)->type_body));
                // type & parameter add
                if (i > 0) {
                    arg_list += ", ";
                }
                for (unsigned int j = 0;j < ((yyvsp[-4].decl_list_ptr))->at(i)->id_body->size();j++){
                    if (j > 0) {
                        arg_list += ", ";
                    }
                    arg_list += (yyvsp[-4].decl_list_ptr)->at(i)->type_body;
                }
            }         
        }
        arg_list += ')';
        // printf("result:%s\n",arg_list.c_str());
        (yyval.func_ptr) = new FunctionNode((yylsp[-6]).first_line, (yylsp[-6]).first_column, (yyvsp[-6].identifier), arg_list, (yyvsp[-1].compound_stmt_ptr), ast_node);
    }
#line 1636 "parser.cpp"
    break;

  case 16: /* FunctionName: ID  */
#line 327 "parser.y"
       {
        (yyval.identifier) = (yyvsp[0].identifier);
    }
#line 1644 "parser.cpp"
    break;

  case 17: /* FormalArgList: Epsilon  */
#line 333 "parser.y"
            {
        (yyval.decl_list_ptr) = nullptr;
    }
#line 1652 "parser.cpp"
    break;

  case 18: /* FormalArgList: FormalArgs  */
#line 337 "parser.y"
               {
        (yyval.decl_list_ptr) = (yyvsp[0].decl_list_ptr);
    }
#line 1660 "parser.cpp"
    break;

  case 19: /* FormalArgs: FormalArg  */
#line 343 "parser.y"
              {
        (yyval.decl_list_ptr) = new std::vector<DeclNode*>;
        (yyval.decl_list_ptr)->push_back((yyvsp[0].decl_ptr));
    }
#line 1669 "parser.cpp"
    break;

  case 20: /* FormalArgs: FormalArgs SEMICOLON FormalArg  */
#line 348 "parser.y"
                                   {
        (yyval.decl_list_ptr) = (yyvsp[-2].decl_list_ptr);
        (yyval.decl_list_ptr)->push_back((yyvsp[0].decl_ptr));
    }
#line 1678 "parser.cpp"
    break;

  case 21: /* FormalArg: IdList COLON Type  */
#line 355 "parser.y"
                      {
        std::vector<AstNode*> *id_node = new std::vector<AstNode*>;
        std::vector<std::string> *id_string = new std::vector<std::string>;
        std::string var_type_string = (yyvsp[0].identifier);
        if ((yyvsp[-2].id_list_ptr) != nullptr) {
            for (auto &var_node : *((yyvsp[-2].id_list_ptr))) {
                id_node->push_back(new VariableNode(var_node.line, var_node.column, var_node.name, var_type_string, nullptr));
                id_string->push_back(var_node.name);
            }
        }
        else {
            id_node = nullptr;
        }

        (yyval.decl_ptr) = new DeclNode((yylsp[-2]).first_line, (yylsp[-2]).first_column, id_node, id_string, var_type_string);
    }
#line 1699 "parser.cpp"
    break;

  case 22: /* IdList: ID  */
#line 374 "parser.y"
       {
        // printf("parser to ID\n");
        (yyval.id_list_ptr) = new std::vector<struct id_data>;
        struct id_data cur_var = {(yyvsp[0].identifier), (yylsp[0]).first_line, (yylsp[0]).first_column};
        (yyval.id_list_ptr)->push_back(cur_var);
        // printf("idnew:%s\n",$1);
    }
#line 1711 "parser.cpp"
    break;

  case 23: /* IdList: IdList COMMA ID  */
#line 382 "parser.y"
                    {
        // printf("parser to ID_list\n");
        (yyval.id_list_ptr) = (yyvsp[-2].id_list_ptr);
        // printf("in id list:%s, %u\n",$1->at(0)->name,$1->at(0)->column);
        struct id_data cur_var_new = {(yyvsp[0].identifier), (yylsp[0]).first_line, (yylsp[0]).first_column};
        (yyval.id_list_ptr)->push_back(cur_var_new);
        // printf("in id list:%s, %u\n",$$->at(1)->name,$$->at(1)->column);
        // printf("idadd:%s\n",$3);
    }
#line 1725 "parser.cpp"
    break;

  case 24: /* ReturnType: COLON ScalarType  */
#line 394 "parser.y"
                     {
        (yyval.identifier) = (yyvsp[0].identifier);
    }
#line 1733 "parser.cpp"
    break;

  case 25: /* ReturnType: Epsilon  */
#line 398 "parser.y"
            {
        (yyval.identifier) = (char*)"void";
    }
#line 1741 "parser.cpp"
    break;

  case 26: /* Declaration: VAR IdList COLON Type SEMICOLON  */
#line 408 "parser.y"
                                    {
        // for (unsigned int i = 0;i < $2->size();i++){
        //     printf("id list struct:%u,%u,%s\n",$2->at(i).line,$2->at(i).column,$2->at(i).name);
        // }

        std::vector<AstNode*> *id_node = new std::vector<AstNode*>;
        std::vector<std::string> *id_string = new std::vector<std::string>;
        std::string var_type_string = (yyvsp[-1].identifier);
        if ((yyvsp[-3].id_list_ptr) != nullptr) {
            for (auto &var_node : *((yyvsp[-3].id_list_ptr))) {
                id_node->push_back(new VariableNode(var_node.line, var_node.column, var_node.name, var_type_string, nullptr));
                id_string->push_back(var_node.name);
            }
        }
        else {
            id_node = nullptr;
        }

        (yyval.decl_ptr) = new DeclNode((yylsp[-4]).first_line, (yylsp[-4]).first_column, id_node, id_string, var_type_string);
    }
#line 1766 "parser.cpp"
    break;

  case 27: /* Declaration: VAR IdList COLON LiteralConstant SEMICOLON  */
#line 429 "parser.y"
                                               {
        // for (unsigned int i = 0;i < $2->size();i++){
        //     printf("id list struct:%u,%u,%s\n",$2->at(i).line,$2->at(i).column,$2->at(i).name);
        // }

        std::vector<AstNode*> *id_const_node = new std::vector<AstNode*>;
        std::vector<std::string> *id_string = new std::vector<std::string>;
        
        std::string var_type_string = (yyvsp[-1].const_val_ptr)->getdatatype((yyvsp[-1].const_val_ptr)->type_data);
        if ((yyvsp[-3].id_list_ptr) != nullptr) {
            for (auto &id_list : *(yyvsp[-3].id_list_ptr)) {
                id_const_node->push_back(new VariableNode(id_list.line, id_list.column, id_list.name, var_type_string, (yyvsp[-1].const_val_ptr)));
                id_string->push_back(id_list.name);
            }
        }
        else {
            id_const_node = nullptr;
        }
        
        (yyval.decl_ptr) = new DeclNode((yylsp[-4]).first_line, (yylsp[-4]).first_column, id_const_node, id_string, var_type_string);
    }
#line 1792 "parser.cpp"
    break;

  case 28: /* Type: ScalarType  */
#line 453 "parser.y"
               {
        (yyval.identifier) = (yyvsp[0].identifier);
    }
#line 1800 "parser.cpp"
    break;

  case 29: /* Type: ArrType  */
#line 457 "parser.y"
            {
        (yyval.identifier) = (yyvsp[0].identifier);
    }
#line 1808 "parser.cpp"
    break;

  case 30: /* ScalarType: INTEGER  */
#line 463 "parser.y"
            {
        (yyval.identifier) = (char*)"integer";
    }
#line 1816 "parser.cpp"
    break;

  case 31: /* ScalarType: REAL  */
#line 467 "parser.y"
         {
        (yyval.identifier) = (char*)"real";
    }
#line 1824 "parser.cpp"
    break;

  case 32: /* ScalarType: STRING  */
#line 471 "parser.y"
           {
        (yyval.identifier) = (char*)"string";
    }
#line 1832 "parser.cpp"
    break;

  case 33: /* ScalarType: BOOLEAN  */
#line 475 "parser.y"
            {
        (yyval.identifier) = (char*)"boolean";
    }
#line 1840 "parser.cpp"
    break;

  case 34: /* ArrType: ArrDecl ScalarType  */
#line 481 "parser.y"
                       {
        std::string str = (yyvsp[0].identifier);
        str += (yyvsp[-1].identifier);
        (yyval.identifier) = (char*)str.c_str();
    }
#line 1850 "parser.cpp"
    break;

  case 35: /* ArrDecl: ARRAY INT_LITERAL OF  */
#line 489 "parser.y"
                         {
        std::string str = " [";
        str += std::to_string((yyvsp[-1].int_lit));
        str += ']';
        //printf("string:%s,int:%d",std::to_string(INT_LITERAL),);
        (yyval.identifier) = (char*)str.c_str();
    }
#line 1862 "parser.cpp"
    break;

  case 36: /* ArrDecl: ArrDecl ARRAY INT_LITERAL OF  */
#line 497 "parser.y"
                                 {
        std::string str = (yyvsp[-3].identifier);
        str += '[';
        str += std::to_string((yyvsp[-1].int_lit));
        str += ']';
        (yyval.identifier) = (char*)str.c_str();
    }
#line 1874 "parser.cpp"
    break;

  case 37: /* LiteralConstant: NegOrNot INT_LITERAL  */
#line 507 "parser.y"
                         {
        // std::string str = $1;
        // str += std::to_string(INT_LITERAL);
        // $$ = (char*)str.c_str();
        struct literal_data ld = {INT, (yyvsp[-1].int_lit) * (yyvsp[0].int_lit), 0.0, nullptr};
        if ((yyvsp[-1].int_lit) == 1) (yyval.const_val_ptr) = new ConstantValueNode((yylsp[0]).first_line, (yylsp[0]).first_column, ld);
        else (yyval.const_val_ptr) = new ConstantValueNode((yylsp[-1]).first_line, (yylsp[-1]).first_column, ld);
    }
#line 1887 "parser.cpp"
    break;

  case 38: /* LiteralConstant: NegOrNot REAL_LITERAL  */
#line 516 "parser.y"
                          {
        // std::string str = $1;
        // str += std::to_string(INT_LITERAL);
        // $$ = (char*)str.c_str();
        struct literal_data ld = {FLOAT, 0, (yyvsp[-1].int_lit) * (yyvsp[0].real_lit), nullptr};
        if ((yyvsp[-1].int_lit) == 1) (yyval.const_val_ptr) = new ConstantValueNode((yylsp[0]).first_line, (yylsp[0]).first_column, ld);
        else (yyval.const_val_ptr) = new ConstantValueNode((yylsp[-1]).first_line, (yylsp[-1]).first_column, ld);
    }
#line 1900 "parser.cpp"
    break;

  case 39: /* LiteralConstant: StringAndBoolean  */
#line 525 "parser.y"
                     {
        if (((yyvsp[0].id_data_ptr))->line == 1) {
            struct literal_data ld = {STRING_, 0, 0.0, ((yyvsp[0].id_data_ptr))->name};
            (yyval.const_val_ptr) = new ConstantValueNode((yylsp[0]).first_line, (yylsp[0]).first_column, ld);
        }
        else {
            if (((yyvsp[0].id_data_ptr))->column == 1){
                struct literal_data ld = {TRUE_, 0, 0.0, ((yyvsp[0].id_data_ptr))->name};
                (yyval.const_val_ptr) = new ConstantValueNode((yylsp[0]).first_line, (yylsp[0]).first_column, ld);
            }
            else {
                struct literal_data ld = {FALSE_, 0, 0.0, ((yyvsp[0].id_data_ptr))->name};
                (yyval.const_val_ptr) = new ConstantValueNode((yylsp[0]).first_line, (yylsp[0]).first_column, ld);
            }
        }
    }
#line 1921 "parser.cpp"
    break;

  case 40: /* NegOrNot: Epsilon  */
#line 544 "parser.y"
            {
        (yyval.int_lit) = 1;
    }
#line 1929 "parser.cpp"
    break;

  case 41: /* NegOrNot: MINUS  */
#line 548 "parser.y"
                            {
        (yyval.int_lit) = -1;
    }
#line 1937 "parser.cpp"
    break;

  case 42: /* StringAndBoolean: STRING_LITERAL  */
#line 554 "parser.y"
                   {
        struct id_data id_ = {(yyvsp[0].identifier),1,0};
        (yyval.id_data_ptr) = &id_;
    }
#line 1946 "parser.cpp"
    break;

  case 43: /* StringAndBoolean: TRUE  */
#line 559 "parser.y"
         {
        struct id_data id_ = {"true",0,1};
        (yyval.id_data_ptr) = &id_;
    }
#line 1955 "parser.cpp"
    break;

  case 44: /* StringAndBoolean: FALSE  */
#line 564 "parser.y"
          {
        struct id_data id_ = {"false",0,0};
        (yyval.id_data_ptr) = &id_;
    }
#line 1964 "parser.cpp"
    break;

  case 45: /* IntegerAndReal: INT_LITERAL  */
#line 571 "parser.y"
                {
        struct literal_data ld = {INT, (yyvsp[0].int_lit), 0.0, nullptr};
        (yyval.literal_data_ptr) = &ld;
    }
#line 1973 "parser.cpp"
    break;

  case 46: /* IntegerAndReal: REAL_LITERAL  */
#line 576 "parser.y"
                 {
        struct literal_data ld = {FLOAT, 0, (yyvsp[0].real_lit), nullptr};
        (yyval.literal_data_ptr) = &ld;
    }
#line 1982 "parser.cpp"
    break;

  case 47: /* Statement: CompoundStatement  */
#line 587 "parser.y"
                      {
        (yyval.node) = (yyvsp[0].compound_stmt_ptr);
    }
#line 1990 "parser.cpp"
    break;

  case 48: /* Statement: Simple  */
#line 591 "parser.y"
           {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1998 "parser.cpp"
    break;

  case 49: /* Statement: Condition  */
#line 595 "parser.y"
              {
        (yyval.node) = (yyvsp[0].if_ptr);
    }
#line 2006 "parser.cpp"
    break;

  case 50: /* Statement: While  */
#line 599 "parser.y"
          {
        (yyval.node) = (yyvsp[0].while_ptr);
    }
#line 2014 "parser.cpp"
    break;

  case 51: /* Statement: For  */
#line 603 "parser.y"
        {
        (yyval.node) = (yyvsp[0].for_ptr);
    }
#line 2022 "parser.cpp"
    break;

  case 52: /* Statement: Return  */
#line 607 "parser.y"
           {
        (yyval.node) = (yyvsp[0].return_ptr);
    }
#line 2030 "parser.cpp"
    break;

  case 53: /* Statement: FunctionCall  */
#line 611 "parser.y"
                 {
        (yyval.node) = (yyvsp[0].exp_ptr);
    }
#line 2038 "parser.cpp"
    break;

  case 54: /* CompoundStatement: BEGIN_ DeclarationList StatementList END  */
#line 620 "parser.y"
        {
        (yyval.compound_stmt_ptr) = new CompoundStatementNode((yylsp[-3]).first_line, (yylsp[-3]).first_column, (yyvsp[-2].node_list_ptr), (yyvsp[-1].node_list_ptr));
    }
#line 2046 "parser.cpp"
    break;

  case 55: /* Simple: VariableReference ASSIGN Expression SEMICOLON  */
#line 626 "parser.y"
                                                  {
        (yyval.node) = new AssignmentNode((yylsp[-2]).first_line, (yylsp[-2]).first_column, (AstNode*)(yyvsp[-3].var_ref_ptr), (AstNode*)(yyvsp[-1].exp_ptr));
    }
#line 2054 "parser.cpp"
    break;

  case 56: /* Simple: PRINT Expression SEMICOLON  */
#line 630 "parser.y"
                               {
        (yyval.node) = new PrintNode((yylsp[-2]).first_line, (yylsp[-2]).first_column, (AstNode*)(yyvsp[-1].exp_ptr));
    }
#line 2062 "parser.cpp"
    break;

  case 57: /* Simple: READ VariableReference SEMICOLON  */
#line 634 "parser.y"
                                     {
        (yyval.node) = new ReadNode((yylsp[-2]).first_line, (yylsp[-2]).first_column, (AstNode*)(yyvsp[-1].var_ref_ptr));
    }
#line 2070 "parser.cpp"
    break;

  case 58: /* VariableReference: ID ArrRefList  */
#line 640 "parser.y"
                  {
        std::string var_name = (yyvsp[-1].identifier);
        (yyval.var_ref_ptr) = new VariableReferenceNode((yylsp[-1]).first_line, (yylsp[-1]).first_column, var_name, (yyvsp[0].exp_list_ptr));
    }
#line 2079 "parser.cpp"
    break;

  case 59: /* ArrRefList: Epsilon  */
#line 647 "parser.y"
            {
        (yyval.exp_list_ptr) = nullptr;
    }
#line 2087 "parser.cpp"
    break;

  case 60: /* ArrRefList: ArrRefs  */
#line 651 "parser.y"
            {
        (yyval.exp_list_ptr) = (yyvsp[0].exp_list_ptr);
    }
#line 2095 "parser.cpp"
    break;

  case 61: /* ArrRefs: L_BRACKET Expression R_BRACKET  */
#line 657 "parser.y"
                                   {
        (yyval.exp_list_ptr) = new std::vector<ExpressionNode*>;
        (yyval.exp_list_ptr)->push_back((yyvsp[-1].exp_ptr));
    }
#line 2104 "parser.cpp"
    break;

  case 62: /* ArrRefs: ArrRefs L_BRACKET Expression R_BRACKET  */
#line 662 "parser.y"
                                           {
        (yyval.exp_list_ptr) = (yyvsp[-3].exp_list_ptr);
        (yyval.exp_list_ptr)->push_back((yyvsp[-1].exp_ptr));
    }
#line 2113 "parser.cpp"
    break;

  case 63: /* Condition: IF Expression THEN CompoundStatement ElseOrNot END IF  */
#line 672 "parser.y"
           {
        (yyval.if_ptr) = new IfNode((yylsp[-6]).first_line, (yylsp[-6]).first_column, (AstNode*)(yyvsp[-5].exp_ptr), (yyvsp[-3].compound_stmt_ptr), (yyvsp[-2].compound_stmt_ptr));
    }
#line 2121 "parser.cpp"
    break;

  case 64: /* ElseOrNot: ELSE CompoundStatement  */
#line 679 "parser.y"
                      {
        (yyval.compound_stmt_ptr) = (yyvsp[0].compound_stmt_ptr);
    }
#line 2129 "parser.cpp"
    break;

  case 65: /* ElseOrNot: Epsilon  */
#line 683 "parser.y"
            {
        (yyval.compound_stmt_ptr) = nullptr;
    }
#line 2137 "parser.cpp"
    break;

  case 66: /* While: WHILE Expression DO CompoundStatement END DO  */
#line 691 "parser.y"
           {
        (yyval.while_ptr) = new WhileNode((yylsp[-5]).first_line, (yylsp[-5]).first_column, (AstNode*)(yyvsp[-4].exp_ptr), (yyvsp[-2].compound_stmt_ptr));
    }
#line 2145 "parser.cpp"
    break;

  case 67: /* For: FOR ID ASSIGN INT_LITERAL TO INT_LITERAL DO CompoundStatement END DO  */
#line 699 "parser.y"
           {
        // DeclNode part
        std::vector<AstNode*> *id_node = new std::vector<AstNode*>;
        std::vector<std::string> *id_string = new std::vector<std::string>;
        std::string var_name_string = (yyvsp[-8].identifier);
        std::string var_type_string = "integer";
        if ((yyvsp[-8].identifier) != nullptr) {
            id_node->push_back(new VariableNode((yylsp[-8]).first_line, (yylsp[-8]).first_column, (yyvsp[-8].identifier), var_type_string, nullptr));
            id_string->push_back(var_name_string);
        }
        else {
            id_node = nullptr;
        }
        DeclNode* decl_node_ptr = new DeclNode((yylsp[-8]).first_line, (yylsp[-8]).first_column, id_node, id_string, var_type_string);

        // AssignmentNode part
        VariableReferenceNode* var_ref_node_ptr = new VariableReferenceNode((yylsp[-8]).first_line, (yylsp[-8]).first_column, var_name_string, nullptr);
        struct literal_data ld_one = {INT, (yyvsp[-6].int_lit), 0.0, nullptr};
        ConstantValueNode* const_val_node_1 = new ConstantValueNode((yylsp[-6]).first_line, (yylsp[-6]).first_column, ld_one);
        AssignmentNode* assign_node_ptr = new AssignmentNode((yylsp[-7]).first_line, (yylsp[-7]).first_column, (AstNode*)var_ref_node_ptr, (AstNode*)const_val_node_1);

        // ConstantValueNode part
        struct literal_data ld_two = {INT, (yyvsp[-4].int_lit), 0.0, nullptr};
        ConstantValueNode* const_val_node_2 = new ConstantValueNode((yylsp[-4]).first_line, (yylsp[-4]).first_column, ld_two);

        (yyval.for_ptr) = new ForNode((yylsp[-9]).first_line, (yylsp[-9]).first_column, decl_node_ptr, assign_node_ptr, const_val_node_2, (yyvsp[-2].compound_stmt_ptr));
    }
#line 2177 "parser.cpp"
    break;

  case 68: /* Return: RETURN Expression SEMICOLON  */
#line 729 "parser.y"
                                {
        (yyval.return_ptr) = new ReturnNode((yylsp[-2]).first_line, (yylsp[-2]).first_column, (yyvsp[-1].exp_ptr));
    }
#line 2185 "parser.cpp"
    break;

  case 69: /* FunctionCall: FunctionInvocation SEMICOLON  */
#line 735 "parser.y"
                                 {
        (yyval.exp_ptr) = (yyvsp[-1].exp_ptr);
    }
#line 2193 "parser.cpp"
    break;

  case 70: /* FunctionInvocation: ID L_PARENTHESIS ExpressionList R_PARENTHESIS  */
#line 741 "parser.y"
                                                  {
        std::string tmp_name = (yyvsp[-3].identifier);
        (yyval.exp_ptr) = new FunctionInvocationNode((yylsp[-3]).first_line, (yylsp[-3]).first_column, tmp_name, (yyvsp[-1].exp_list_ptr));
    }
#line 2202 "parser.cpp"
    break;

  case 71: /* ExpressionList: Epsilon  */
#line 748 "parser.y"
            {
        (yyval.exp_list_ptr) = nullptr;
    }
#line 2210 "parser.cpp"
    break;

  case 72: /* ExpressionList: Expressions  */
#line 752 "parser.y"
                {
        (yyval.exp_list_ptr) = (yyvsp[0].exp_list_ptr);
    }
#line 2218 "parser.cpp"
    break;

  case 73: /* Expressions: Expression  */
#line 758 "parser.y"
               {
        (yyval.exp_list_ptr) = new std::vector<ExpressionNode*>;
        (yyval.exp_list_ptr)->push_back((yyvsp[0].exp_ptr));
    }
#line 2227 "parser.cpp"
    break;

  case 74: /* Expressions: Expressions COMMA Expression  */
#line 763 "parser.y"
                                 {
        (yyval.exp_list_ptr) = (yyvsp[-2].exp_list_ptr);
        (yyval.exp_list_ptr)->push_back((yyvsp[0].exp_ptr));    
    }
#line 2236 "parser.cpp"
    break;

  case 75: /* StatementList: Epsilon  */
#line 770 "parser.y"
            {
        (yyval.node_list_ptr) = nullptr;
    }
#line 2244 "parser.cpp"
    break;

  case 76: /* StatementList: Statements  */
#line 774 "parser.y"
               {
        (yyval.node_list_ptr) = (yyvsp[0].node_list_ptr);
    }
#line 2252 "parser.cpp"
    break;

  case 77: /* Statements: Statement  */
#line 780 "parser.y"
              {
        (yyval.node_list_ptr) = new std::vector<AstNode*>;
        (yyval.node_list_ptr)->push_back((yyvsp[0].node));
    }
#line 2261 "parser.cpp"
    break;

  case 78: /* Statements: Statements Statement  */
#line 785 "parser.y"
                         {
        (yyval.node_list_ptr) = (yyvsp[-1].node_list_ptr);
        (yyval.node_list_ptr)->push_back((yyvsp[0].node));    
    }
#line 2270 "parser.cpp"
    break;

  case 79: /* Expression: L_PARENTHESIS Expression R_PARENTHESIS  */
#line 792 "parser.y"
                                           {
        (yyval.exp_ptr) = (yyvsp[-1].exp_ptr);
    }
#line 2278 "parser.cpp"
    break;

  case 80: /* Expression: MINUS Expression  */
#line 796 "parser.y"
                                       {
        std::string op = "neg";
        (yyval.exp_ptr) = new UnaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column, op, (yyvsp[0].exp_ptr));
    }
#line 2287 "parser.cpp"
    break;

  case 81: /* Expression: Expression MULTIPLY Expression  */
#line 801 "parser.y"
                                   {
        std::string op = "*";
        (yyval.exp_ptr) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column, op, (yyvsp[-2].exp_ptr), (yyvsp[0].exp_ptr));
    }
#line 2296 "parser.cpp"
    break;

  case 82: /* Expression: Expression DIVIDE Expression  */
#line 806 "parser.y"
                                 {
        std::string op = "/";
        (yyval.exp_ptr) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column, op, (yyvsp[-2].exp_ptr), (yyvsp[0].exp_ptr));
    }
#line 2305 "parser.cpp"
    break;

  case 83: /* Expression: Expression MOD Expression  */
#line 811 "parser.y"
                              {
        std::string op = "mod";
        (yyval.exp_ptr) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column, op, (yyvsp[-2].exp_ptr), (yyvsp[0].exp_ptr));
    }
#line 2314 "parser.cpp"
    break;

  case 84: /* Expression: Expression PLUS Expression  */
#line 816 "parser.y"
                               {
        std::string op = "+";
        (yyval.exp_ptr) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column, op, (yyvsp[-2].exp_ptr), (yyvsp[0].exp_ptr));
    }
#line 2323 "parser.cpp"
    break;

  case 85: /* Expression: Expression MINUS Expression  */
#line 821 "parser.y"
                                {
        std::string op = "-";
        (yyval.exp_ptr) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column, op, (yyvsp[-2].exp_ptr), (yyvsp[0].exp_ptr));
    }
#line 2332 "parser.cpp"
    break;

  case 86: /* Expression: Expression LESS Expression  */
#line 826 "parser.y"
                               {
        std::string op = "<";
        (yyval.exp_ptr) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column, op, (yyvsp[-2].exp_ptr), (yyvsp[0].exp_ptr));
    }
#line 2341 "parser.cpp"
    break;

  case 87: /* Expression: Expression LESS_OR_EQUAL Expression  */
#line 831 "parser.y"
                                        {
        std::string op = "<=";
        (yyval.exp_ptr) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column, op, (yyvsp[-2].exp_ptr), (yyvsp[0].exp_ptr));
    }
#line 2350 "parser.cpp"
    break;

  case 88: /* Expression: Expression GREATER Expression  */
#line 836 "parser.y"
                                  {
        std::string op = ">";
        (yyval.exp_ptr) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column, op, (yyvsp[-2].exp_ptr), (yyvsp[0].exp_ptr));
    }
#line 2359 "parser.cpp"
    break;

  case 89: /* Expression: Expression GREATER_OR_EQUAL Expression  */
#line 841 "parser.y"
                                           {
        std::string op = ">=";
        (yyval.exp_ptr) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column, op, (yyvsp[-2].exp_ptr), (yyvsp[0].exp_ptr));
    }
#line 2368 "parser.cpp"
    break;

  case 90: /* Expression: Expression EQUAL Expression  */
#line 846 "parser.y"
                                {
        std::string op = "=";
        (yyval.exp_ptr) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column, op, (yyvsp[-2].exp_ptr), (yyvsp[0].exp_ptr));
    }
#line 2377 "parser.cpp"
    break;

  case 91: /* Expression: Expression NOT_EQUAL Expression  */
#line 851 "parser.y"
                                    {
        std::string op = "<>";
        (yyval.exp_ptr) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column, op, (yyvsp[-2].exp_ptr), (yyvsp[0].exp_ptr));
    }
#line 2386 "parser.cpp"
    break;

  case 92: /* Expression: NOT Expression  */
#line 856 "parser.y"
                   {
        std::string op = "not";
        (yyval.exp_ptr) = new UnaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column, op, (yyvsp[0].exp_ptr));
    }
#line 2395 "parser.cpp"
    break;

  case 93: /* Expression: Expression AND Expression  */
#line 861 "parser.y"
                              {
        std::string op = "and";
        (yyval.exp_ptr) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column, op, (yyvsp[-2].exp_ptr), (yyvsp[0].exp_ptr));
    }
#line 2404 "parser.cpp"
    break;

  case 94: /* Expression: Expression OR Expression  */
#line 866 "parser.y"
                             {
        std::string op = "or";
        (yyval.exp_ptr) = new BinaryOperatorNode((yylsp[-1]).first_line, (yylsp[-1]).first_column, op, (yyvsp[-2].exp_ptr), (yyvsp[0].exp_ptr));
    }
#line 2413 "parser.cpp"
    break;

  case 95: /* Expression: IntegerAndReal  */
#line 871 "parser.y"
                   {
        // struct literal_data ld = {INT, $1 * $2, 0.0, nullptr};
        (yyval.exp_ptr) = new ConstantValueNode((yylsp[0]).first_line, (yylsp[0]).first_column, *((yyvsp[0].literal_data_ptr)));
    }
#line 2422 "parser.cpp"
    break;

  case 96: /* Expression: StringAndBoolean  */
#line 876 "parser.y"
                     {
        if (((yyvsp[0].id_data_ptr))->line == 1) {
            struct literal_data ld = {STRING_, 0, 0.0, ((yyvsp[0].id_data_ptr))->name};
            (yyval.exp_ptr) = new ConstantValueNode((yylsp[0]).first_line, (yylsp[0]).first_column, ld);
        }
        else {
            if (((yyvsp[0].id_data_ptr))->column == 1){
                struct literal_data ld = {TRUE_, 0, 0.0, ((yyvsp[0].id_data_ptr))->name};
                (yyval.exp_ptr) = new ConstantValueNode((yylsp[0]).first_line, (yylsp[0]).first_column, ld);
            }
            else {
                struct literal_data ld = {FALSE_, 0, 0.0, ((yyvsp[0].id_data_ptr))->name};
                (yyval.exp_ptr) = new ConstantValueNode((yylsp[0]).first_line, (yylsp[0]).first_column, ld);
            }
        }
    }
#line 2443 "parser.cpp"
    break;

  case 97: /* Expression: VariableReference  */
#line 893 "parser.y"
                      {
        (yyval.exp_ptr) = (yyvsp[0].var_ref_ptr);
    }
#line 2451 "parser.cpp"
    break;

  case 98: /* Expression: FunctionInvocation  */
#line 897 "parser.y"
                       {
        (yyval.exp_ptr) = (yyvsp[0].exp_ptr);
    }
#line 2459 "parser.cpp"
    break;


#line 2463 "parser.cpp"

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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 908 "parser.y"


void yyerror(const char *msg) {
    fprintf(stderr,
            "\n"
            "|-----------------------------------------------------------------"
            "---------\n"
            "| Error found in Line #%d: %s\n"
            "|\n"
            "| Unmatched token: %s\n"
            "|-----------------------------------------------------------------"
            "---------\n",
            line_num, current_line, yytext);
    exit(-1);
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename> [--dump-ast]\n", argv[0]);
        exit(-1);
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        perror("fopen() failed");
        exit(-1);
    }

    yyparse();

    if (argc >= 3 && strcmp(argv[2], "--dump-ast") == 0) {
        AstDumper ast_dumper;
        root->accept(ast_dumper);
    }

    printf("\n"
           "|--------------------------------|\n"
           "|  There is no syntactic error!  |\n"
           "|--------------------------------|\n");

    delete root;
    fclose(yyin);
    yylex_destroy();
    return 0;
}

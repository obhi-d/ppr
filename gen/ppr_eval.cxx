// A Bison parser, made by GNU Bison 3.7.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.


// Take the name prefix into account.
#define yylex   ppr_lex



#include "ppr_eval.hxx"


// Unqualified %code blocks.

#include "ppr_transform.hpp"
YY_DECL;



#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if PPR_DEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !PPR_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !PPR_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace ppr {

  /// Build a parser object.
  parser_impl::parser_impl (ppr::live_eval& ctx_yyarg)
#if PPR_DEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      ctx (ctx_yyarg)
  {}

  parser_impl::~parser_impl ()
  {}

  parser_impl::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  parser_impl::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser_impl::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser_impl::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser_impl::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser_impl::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser_impl::symbol_kind_type
  parser_impl::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser_impl::stack_symbol_type::stack_symbol_type ()
  {}

  parser_impl::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_BOOL: // BOOL
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_ternary: // ternary
      case symbol_kind::S_or: // or
      case symbol_kind::S_and: // and
      case symbol_kind::S_bwor: // bwor
      case symbol_kind::S_bwxor: // bwxor
      case symbol_kind::S_bwand: // bwand
      case symbol_kind::S_equality: // equality
      case symbol_kind::S_comparison: // comparison
      case symbol_kind::S_bwshift: // bwshift
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_primary: // primary
        value.YY_MOVE_OR_COPY< ppr::eval_type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.YY_MOVE_OR_COPY< std::int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UINT: // UINT
        value.YY_MOVE_OR_COPY< std::uint64_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser_impl::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_BOOL: // BOOL
        value.move< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_ternary: // ternary
      case symbol_kind::S_or: // or
      case symbol_kind::S_and: // and
      case symbol_kind::S_bwor: // bwor
      case symbol_kind::S_bwxor: // bwxor
      case symbol_kind::S_bwand: // bwand
      case symbol_kind::S_equality: // equality
      case symbol_kind::S_comparison: // comparison
      case symbol_kind::S_bwshift: // bwshift
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_primary: // primary
        value.move< ppr::eval_type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.move< std::int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UINT: // UINT
        value.move< std::uint64_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser_impl::stack_symbol_type&
  parser_impl::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_BOOL: // BOOL
        value.copy< bool > (that.value);
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_ternary: // ternary
      case symbol_kind::S_or: // or
      case symbol_kind::S_and: // and
      case symbol_kind::S_bwor: // bwor
      case symbol_kind::S_bwxor: // bwxor
      case symbol_kind::S_bwand: // bwand
      case symbol_kind::S_equality: // equality
      case symbol_kind::S_comparison: // comparison
      case symbol_kind::S_bwshift: // bwshift
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_primary: // primary
        value.copy< ppr::eval_type > (that.value);
        break;

      case symbol_kind::S_INT: // INT
        value.copy< std::int64_t > (that.value);
        break;

      case symbol_kind::S_UINT: // UINT
        value.copy< std::uint64_t > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser_impl::stack_symbol_type&
  parser_impl::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_BOOL: // BOOL
        value.move< bool > (that.value);
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_ternary: // ternary
      case symbol_kind::S_or: // or
      case symbol_kind::S_and: // and
      case symbol_kind::S_bwor: // bwor
      case symbol_kind::S_bwxor: // bwxor
      case symbol_kind::S_bwand: // bwand
      case symbol_kind::S_equality: // equality
      case symbol_kind::S_comparison: // comparison
      case symbol_kind::S_bwshift: // bwshift
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_primary: // primary
        value.move< ppr::eval_type > (that.value);
        break;

      case symbol_kind::S_INT: // INT
        value.move< std::int64_t > (that.value);
        break;

      case symbol_kind::S_UINT: // UINT
        value.move< std::uint64_t > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser_impl::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if PPR_DEBUG
  template <typename Base>
  void
  parser_impl::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YYUSE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser_impl::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser_impl::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser_impl::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if PPR_DEBUG
  std::ostream&
  parser_impl::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser_impl::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser_impl::debug_level_type
  parser_impl::debug_level () const
  {
    return yydebug_;
  }

  void
  parser_impl::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PPR_DEBUG

  parser_impl::state_type
  parser_impl::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser_impl::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser_impl::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser_impl::operator() ()
  {
    return parse ();
  }

  int
  parser_impl::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
{  
}



    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (ctx));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_BOOL: // BOOL
        yylhs.value.emplace< bool > ();
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_ternary: // ternary
      case symbol_kind::S_or: // or
      case symbol_kind::S_and: // and
      case symbol_kind::S_bwor: // bwor
      case symbol_kind::S_bwxor: // bwxor
      case symbol_kind::S_bwand: // bwand
      case symbol_kind::S_equality: // equality
      case symbol_kind::S_comparison: // comparison
      case symbol_kind::S_bwshift: // bwshift
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_primary: // primary
        yylhs.value.emplace< ppr::eval_type > ();
        break;

      case symbol_kind::S_INT: // INT
        yylhs.value.emplace< std::int64_t > ();
        break;

      case symbol_kind::S_UINT: // UINT
        yylhs.value.emplace< std::uint64_t > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 3: // line: expression "end of file"
                         { ctx.set_result(yystack_[1].value.as < ppr::eval_type > ()); }
    break;

  case 4: // expression: ternary
                     { yylhs.value.as < ppr::eval_type > () = yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 5: // ternary: or
             { yylhs.value.as < ppr::eval_type > () = yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 6: // ternary: expression "?" ternary ":" ternary
                                                                        { yylhs.value.as < ppr::eval_type > () = yystack_[4].value.as < ppr::eval_type > () ? yystack_[2].value.as < ppr::eval_type > () : yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 7: // or: and
              { yylhs.value.as < ppr::eval_type > () = yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 8: // or: or "||" and
                                            { yylhs.value.as < ppr::eval_type > () = yystack_[2].value.as < ppr::eval_type > () || yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 9: // and: bwor
               { yylhs.value.as < ppr::eval_type > () = yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 10: // and: and "&&" bwor
                                               { yylhs.value.as < ppr::eval_type > () = yystack_[2].value.as < ppr::eval_type > () && yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 11: // bwor: bwxor
                { yylhs.value.as < ppr::eval_type > () = yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 12: // bwor: bwor "|" bwxor
                                                   { yylhs.value.as < ppr::eval_type > () = yystack_[2].value.as < ppr::eval_type > () | yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 13: // bwxor: bwand
                { yylhs.value.as < ppr::eval_type > () = yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 14: // bwxor: bwxor "^" bwand
                                                     { yylhs.value.as < ppr::eval_type > () = yystack_[2].value.as < ppr::eval_type > () ^ yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 15: // bwand: equality
                   { yylhs.value.as < ppr::eval_type > () = yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 16: // bwand: bwand "&" equality
                                                        { yylhs.value.as < ppr::eval_type > () = yystack_[2].value.as < ppr::eval_type > () & yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 17: // equality: comparison
                      { yylhs.value.as < ppr::eval_type > () = yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 18: // equality: equality "!=" comparison
                                                               { yylhs.value.as < ppr::eval_type > () = (yystack_[2].value.as < ppr::eval_type > () != yystack_[0].value.as < ppr::eval_type > ()); }
    break;

  case 19: // equality: equality "==" comparison
                                                              { yylhs.value.as < ppr::eval_type > () = (yystack_[2].value.as < ppr::eval_type > () == yystack_[0].value.as < ppr::eval_type > ()); }
    break;

  case 20: // comparison: bwshift
                     { yylhs.value.as < ppr::eval_type > () = yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 21: // comparison: comparison ">" bwshift
                                        { yylhs.value.as < ppr::eval_type > () = yystack_[2].value.as < ppr::eval_type > () > yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 22: // comparison: comparison ">=" bwshift
                                                                        { yylhs.value.as < ppr::eval_type > () = yystack_[2].value.as < ppr::eval_type > () >= yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 23: // comparison: comparison "<" bwshift
                                                                   { yylhs.value.as < ppr::eval_type > () = yystack_[2].value.as < ppr::eval_type > () < yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 24: // comparison: comparison "<=" bwshift
                                                                     { yylhs.value.as < ppr::eval_type > () = yystack_[2].value.as < ppr::eval_type > () <= yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 25: // bwshift: term
               { yylhs.value.as < ppr::eval_type > () = yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 26: // bwshift: bwshift "<<" term
                                                      { yylhs.value.as < ppr::eval_type > () = yystack_[2].value.as < ppr::eval_type > () << yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 27: // bwshift: bwshift ">>" term
                                                      { yylhs.value.as < ppr::eval_type > () = yystack_[2].value.as < ppr::eval_type > () >> yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 28: // term: factor
              { yylhs.value.as < ppr::eval_type > () = yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 29: // term: term "+" factor
                                          { yylhs.value.as < ppr::eval_type > () = yystack_[2].value.as < ppr::eval_type > () + yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 30: // term: term "-" factor
                                            { yylhs.value.as < ppr::eval_type > () = yystack_[2].value.as < ppr::eval_type > () + yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 31: // factor: unary
               { yylhs.value.as < ppr::eval_type > () = yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 32: // factor: factor "*" unary
                                           { yylhs.value.as < ppr::eval_type > () = yystack_[2].value.as < ppr::eval_type > () * yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 33: // factor: factor "/" unary
                                           { yylhs.value.as < ppr::eval_type > () = yystack_[2].value.as < ppr::eval_type > () / yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 34: // factor: factor "%" unary
                                               { yylhs.value.as < ppr::eval_type > () = yystack_[2].value.as < ppr::eval_type > () % yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 35: // unary: "-" unary
                    { yylhs.value.as < ppr::eval_type > () = -yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 36: // unary: "!" unary
                                          { yylhs.value.as < ppr::eval_type > () = !yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 37: // unary: "~" unary
                                             { yylhs.value.as < ppr::eval_type > () = ~yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 38: // unary: primary
                          { yylhs.value.as < ppr::eval_type > () = yystack_[0].value.as < ppr::eval_type > (); }
    break;

  case 39: // primary: INT
              { yylhs.value.as < ppr::eval_type > () = ppr::eval_type{yystack_[0].value.as < std::int64_t > ()}; }
    break;

  case 40: // primary: UINT
                               { yylhs.value.as < ppr::eval_type > () = ppr::eval_type{yystack_[0].value.as < std::uint64_t > ()}; }
    break;

  case 41: // primary: BOOL
                               { yylhs.value.as < ppr::eval_type > () = ppr::eval_type{yystack_[0].value.as < bool > ()}; }
    break;

  case 42: // primary: "nil"
                              { yylhs.value.as < ppr::eval_type > () = ppr::eval_type{}; }
    break;

  case 43: // primary: "(" expression ")"
                                                   { yylhs.value.as < ppr::eval_type > () = yystack_[1].value.as < ppr::eval_type > (); }
    break;



            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
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


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser_impl::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser_impl::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
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
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser_impl::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser_impl::context.
  parser_impl::context::context (const parser_impl& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser_impl::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }



  int
  parser_impl::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser_impl::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser_impl::yypact_ninf_ = -29;

  const signed char parser_impl::yytable_ninf_ = -5;

  const signed char
  parser_impl::yypact_[] =
  {
       4,   -29,     0,     0,     0,     0,   -29,   -29,   -29,   -29,
      10,     6,   -29,    -8,    -5,    31,     8,    42,   -17,     3,
      28,    46,    34,   -29,   -29,   -29,   -29,   -29,    35,   -29,
     -29,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -29,     9,    40,    -5,    31,     8,    42,   -17,     3,     3,
      28,    28,    28,    28,    46,    46,    34,    34,   -29,   -29,
     -29,     0,    44
  };

  const signed char
  parser_impl::yydefact_[] =
  {
       0,     2,     0,     0,     0,     0,    42,    40,    39,    41,
       0,     0,     4,     5,     7,     9,    11,    13,    15,    17,
      20,    25,    28,    31,    38,    35,    36,    37,     0,     1,
       3,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      43,     0,     4,     8,    10,    12,    14,    16,    19,    18,
      23,    21,    24,    22,    26,    27,    29,    30,    32,    33,
      34,     0,     6
  };

  const signed char
  parser_impl::yypgoto_[] =
  {
     -29,   -29,    17,   -28,   -29,    32,    30,    33,    36,    29,
      18,    -3,    14,    15,    -2,   -29
  };

  const signed char
  parser_impl::yydefgoto_[] =
  {
      -1,    10,    51,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24
  };

  const signed char
  parser_impl::yytable_[] =
  {
      25,    26,    27,    52,     1,     2,    30,    37,    38,     2,
      29,     3,    39,    40,     4,     3,     5,    11,     4,    32,
       5,    33,    28,    35,    31,    41,    42,    31,     6,     7,
       8,     9,     6,     7,     8,     9,    60,    61,    62,    63,
      47,    48,    49,    72,    34,    68,    69,    70,    43,    44,
      45,    46,    50,    31,    36,    58,    59,    64,    65,    71,
      66,    67,    -4,    54,    53,    57,     0,    55,     0,     0,
       0,    56
  };

  const signed char
  parser_impl::yycheck_[] =
  {
       2,     3,     4,    31,     0,     5,     0,    24,    25,     5,
       0,    11,     9,    10,    14,    11,    16,     0,    14,    27,
      16,    26,     5,    15,    18,    22,    23,    18,    28,    29,
      30,    31,    28,    29,    30,    31,    39,    40,    41,    42,
       6,     7,     8,    71,    13,    47,    48,    49,    20,    21,
       4,     5,    17,    18,    12,    37,    38,    43,    44,    19,
      45,    46,    18,    33,    32,    36,    -1,    34,    -1,    -1,
      -1,    35
  };

  const signed char
  parser_impl::yystos_[] =
  {
       0,     0,     5,    11,    14,    16,    28,    29,    30,    31,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    46,    46,    46,    34,     0,
       0,    18,    27,    26,    13,    15,    12,    24,    25,     9,
      10,    22,    23,    20,    21,     4,     5,     6,     7,     8,
      17,    34,    35,    37,    38,    39,    40,    41,    42,    42,
      43,    43,    43,    43,    44,    44,    45,    45,    46,    46,
      46,    19,    35
  };

  const signed char
  parser_impl::yyr1_[] =
  {
       0,    32,    33,    33,    34,    35,    35,    36,    36,    37,
      37,    38,    38,    39,    39,    40,    40,    41,    41,    41,
      42,    42,    42,    42,    42,    43,    43,    43,    44,    44,
      44,    45,    45,    45,    45,    46,    46,    46,    46,    47,
      47,    47,    47,    47
  };

  const signed char
  parser_impl::yyr2_[] =
  {
       0,     2,     1,     2,     1,     1,     5,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     2,     2,     2,     1,     1,
       1,     1,     1,     3
  };


#if PPR_DEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser_impl::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"defined\"", "\"+\"",
  "\"-\"", "\"*\"", "\"/\"", "\"%\"", "\"<\"", "\">\"", "\"!\"", "\"&\"",
  "\"|\"", "\"~\"", "\"^\"", "\"(\"", "\")\"", "\"?\"", "\":\"", "\"<<\"",
  "\">>\"", "\"<=\"", "\">=\"", "\"==\"", "\"!=\"", "\"&&\"", "\"||\"",
  "\"nil\"", "UINT", "INT", "BOOL", "$accept", "line", "expression",
  "ternary", "or", "and", "bwor", "bwxor", "bwand", "equality",
  "comparison", "bwshift", "term", "factor", "unary", "primary", YY_NULLPTR
  };
#endif


#if PPR_DEBUG
  const unsigned char
  parser_impl::yyrline_[] =
  {
       0,    89,    89,    90,    92,    94,    95,    97,    98,   100,
     101,   103,   104,   106,   107,   109,   110,   112,   113,   114,
     116,   117,   118,   119,   120,   122,   123,   124,   126,   127,
     128,   130,   131,   132,   133,   135,   136,   137,   138,   140,
     141,   142,   143,   144
  };

  void
  parser_impl::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser_impl::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // PPR_DEBUG


} // ppr



namespace ppr {

	
void parser_impl::error(location_type const& l,
												std::string const & e) 
{
  ctx.push_error(e, " bison ", l.begin);
}

ppr::eval_type transform::eval(ppr::live_eval& eval) 
{
	parser_impl parser(eval);
	//parser.set_debug_level(flags_ & ppr::impl::debug);
	
	parser.parse();
	return eval.result;
}

}


ppr::parser_impl::symbol_type ppr_lex(ppr::live_eval& ctx)
{
	using namespace ppr;
	if(! (ctx.error_bit() || ctx.has_result()) )
	{
		auto const& tnp = ctx.get();
		auto const& tok = tnp.first;
		auto const pos = tnp.second;
		switch(tok.type)
		{
		case token_type::ty_eof:
			return ppr::parser_impl::make_END(pos);
		case token_type::ty_true:
			return ppr::parser_impl::make_BOOL(true, pos);
		case token_type::ty_false:
			return ppr::parser_impl::make_BOOL(false, pos);
		case token_type::ty_integer:
		{
			auto s = ctx.value(tok);
			if (s[0] == '-')
			{
				std::int64_t value;
				std::from_chars(s.data(), s.data() + s.length(), value);
				return ppr::parser_impl::make_INT(value, pos);
			}
			else
			{
				std::uint64_t value;
				std::from_chars(s.data(), s.data() + s.length(), value);
				return ppr::parser_impl::make_UINT(value, pos);
			}
		}
		case token_type::ty_hex_integer:
		{
			auto s = ctx.value(tok);
			
			std::uint64_t value;
			std::from_chars(s.data(), s.data() + s.length(), value, 16);
			return ppr::parser_impl::make_UINT(value, pos);
		}
		case token_type::ty_oct_integer:
		{
			auto s = ctx.value(tok);
			
			std::uint64_t value;
			std::from_chars(s.data() + 1, s.data() + s.length(), value, 8);
			return ppr::parser_impl::make_UINT(value, pos);
		}
		case token_type::ty_real_number:
		{
			ctx.push_error("float in preprocessor", ctx.value(tok), pos);
			return ppr::parser_impl::make_END(pos);
		}			
		case token_type::ty_bracket:
			if (tok.op == '(')
				return ppr::parser_impl::make_LPAREN(pos);
			else
				return ppr::parser_impl::make_RPAREN(pos);
		case token_type::ty_operator:
			switch(tok.op)
			{
			case      '+':
				return ppr::parser_impl::make_ADD(pos);
			case      '-':
				return ppr::parser_impl::make_MINUS(pos);
			case      '*':
				return ppr::parser_impl::make_MUL(pos);
			case      '/':
				return ppr::parser_impl::make_DIV(pos);
			case      '<':
				return ppr::parser_impl::make_LESS(pos);
			case	  '>':
				return ppr::parser_impl::make_GREATER(pos);
			case       '!':
				return ppr::parser_impl::make_NOT(pos);
			case    '&':
				return ppr::parser_impl::make_BW_AND(pos);
			case     '|':
				return ppr::parser_impl::make_BW_OR(pos);
			case    '~':
				return ppr::parser_impl::make_BW_NOT(pos);
			case    '^':
				return ppr::parser_impl::make_BW_XOR(pos);
			case    '(':
				return ppr::parser_impl::make_LPAREN(pos);
			case    ')':
				return ppr::parser_impl::make_RPAREN(pos);
			case      '?':
				return ppr::parser_impl::make_COND(pos);
			case     ':':
				return ppr::parser_impl::make_COLON(pos);
			default:
				// error
				return ppr::parser_impl::make_END(pos);
			}
		case token_type::ty_operator2:
			switch(tok.op2)
			{
			case operator2_type::op_lshift:
					return ppr::parser_impl::make_LSHIFT(pos);
			case operator2_type::op_rshift:
					return ppr::parser_impl::make_RSHIFT(pos);
			case operator2_type::op_lequal:
					return ppr::parser_impl::make_LESSEQ(pos);
			case operator2_type::op_gequal:
					return ppr::parser_impl::make_GREATEREQ(pos);
			case operator2_type::op_equals:
					return ppr::parser_impl::make_EQUALS(pos);
			case operator2_type::op_nequals:
					return ppr::parser_impl::make_NEQUALS(pos);
			case operator2_type::op_and:
					return ppr::parser_impl::make_AND(pos);
			case operator2_type::op_or:
					return ppr::parser_impl::make_OR(pos);
			default: // error
				  return ppr::parser_impl::make_END(pos);
			}
		default:
			return ppr::parser_impl::make_NIL(pos);
		}
		
	}
	return ppr::parser_impl::make_END({});
}

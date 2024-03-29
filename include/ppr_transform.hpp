

#pragma once

#include "ppr_common.hpp"
#include "ppr_eval_type.hpp"
#include "ppr_sink.hpp"
#include "ppr_tokenizer.hpp"
#include <list>
#include <tuple>

namespace ppr
{

struct live_eval;
class PPR_API transform
{
public:
  using token_cache        = ppr::vector<token, 8>;
  using rtoken_cache       = ppr::vector<rtoken, 8>;
  using param_substitution = ppr::vector<token_cache, 4>;

  friend class sink;
  friend struct live_eval;

  transform() : last_sink(nullptr) {}
  transform(sink& s) : last_sink(&s) {}

  void preprocess(std::string_view sources);

  bool          eval_bool(std::string_view sources);
  std::uint64_t eval_uint(std::string_view sources);

  void set_transform_code(bool tc)
  {
    transform_code = tc;
  }

  void set_ignore_disabled(bool ig)
  {
    ignore_disabled = ig;
  }

  void push_error(std::string_view s, token const& t);
  void push_error(std::string_view s, std::string_view t, loc const& l);

  bool error_bit() const
  {
    return err_bit;
  }

  sink* exchange(sink* newsink)
  {
    sink* save = last_sink;
    last_sink  = newsink;
    return save;
  }

private:
  void token_paste(rtoken& rt, token const& t);
  void token_paste(rtoken& rt, rtoken const& t);

  struct rtoken_generator;

  inline token_type type(token const& t) const
  {
    return (t.type == token_type::ty_rtoken ? t.value.rt->type : t.type);
  }

  inline bool istype(token const& t, token_type tt) const
  {
    return tt == (t.type == token_type::ty_rtoken ? t.value.rt->type : t.type);
  }

  inline bool hasop(token const& t, char op) const
  {
    return op == (t.type == token_type::ty_rtoken ? t.value.rt->op_type() : t.op_type());
  }

  rtoken from(token const&);

  inline std::string_view value(rtoken const& t) const
  {
    return t.svalue();
  }

  inline std::string_view token_string_range(token const& t) const
  {
    return content_value(t.value.td.start - t.value.td.whitespaces, t.value.td.length + t.value.td.whitespaces);
  }

  inline std::string_view value(token const& t) const
  {
    switch (t.type)
    {
    case token_type::ty_rtoken:
      return t.value.rt->svalue();
    case token_type::ty_raw:
      return *t.value.raw;
    default:
      return content_value(t.value.td.start, t.value.td.length);
    }
  }

  static inline bool is_token_paste(rtoken const& t)
  {
    return t.type == ppr::token_type::ty_operator2 && t.op2 == operator2_type::op_tokpaste;
  }

  bool is_not_defined(std::string_view name) const
  {
    return !is_defined(name);
  }

  bool is_defined(std::string_view name) const
  {
    return (macros.find(name) != macros.end());
  }

  static inline token get(tokenizer& tk)
  {
    return tk.get();
  }

  inline void post(token t)
  {
    t.was_disabled = section_disabled;
    last_sink->filter(t, *this);
  }

  inline void post_const(token const& t)
  {
    last_sink->filter(t, *this);
  }

  inline std::string_view content_value(std::int32_t start, std::int32_t length) const
  {
    return std::string_view{content.data() + start, static_cast<std::size_t>(length)};
  }

  inline auto wspace_content_pair(token const& t) const
  {
    using spair = std::pair<std::string_view, std::string_view>;
    switch (t.type)
    {
    case token_type::ty_rtoken:
      return spair{t.value.rt->sspace(), t.value.rt->svalue()};
    case token_type::ty_raw:
      return spair{std::string_view{}, *t.value.raw};
    default:
      return spair{content_value(t.value.td.start - t.value.td.whitespaces, t.value.td.whitespaces),
                   content_value(t.value.td.start, t.value.td.length)};
    }
  }

  struct macro
  {
    using rtoken = ppr::rtoken;
    ppr::vector<std::string, 4> params;
    rtoken_cache                content;
    bool                        is_function = false;
  };

  using macromap = std::unordered_map<std::string, macro, ppr::str_hash, ppr::str_equal_test>;

  void        read_macro_fn(token start, tokenizer&, macro&);
  void        read_macro_def(token start, tokenizer&, macro&);
  std::string read_define(tokenizer&, macro&);

  class token_stream;

  eval_type eval(ppr::live_eval& tk);

  token                   undefine(tokenizer&);
  std::tuple<token, bool> is_defined(token_stream& tk);

  void expand_macro_call(transform& tf, macromap::iterator it, token_stream& tcache);

  enum class resolve_state
  {
    rsset,
    rsjoin,
    rsresolve
  };

  void resolve_identifier(token start, std::string_view sv, token_stream&);
  void resolve_tokens(token_stream&, bool single = false);

  void do_substitutions(param_substitution const& subs, rtoken_cache const& input, rtoken_cache& output);

  // temporaries
  // token_cache      cache;
  std::string_view content;

  sink* last_sink;

  macromap     macros;
  std::int32_t disable_depth    = 0;
  std::int32_t if_depth         = 0;
  bool         transform_code   = false;
  bool         ignore_disabled  = true;
  bool         err_bit          = false;
  bool         section_disabled = false;
};

struct live_eval : public sink
{
  enum class finish_state : std::uint8_t
  {
    none,
    end_of_seq,
    result_available
  };

  transform&                             tr;
  transform::token_stream&               ts;
  std::uint32_t                          i = 0;
  ppr::vector<std::pair<rtoken, loc>, 2> saved;
  std::pair<rtoken, loc> empty;
  sink&                  chain;

#ifndef PPR_DISABLE_RECORD
  std::string record;
  bool        record_content = false;
#endif

  eval_type    result   = {};
  finish_state finished = finish_state::none;

  live_eval(transform& r, transform::token_stream& s, sink& cchain) : tr(r), ts(s), chain(cchain) {}

  void reset()
  {
    result   = false;
    finished = finish_state::none;
    saved.clear();
#ifndef PPR_DISABLE_RECORD
    record.clear();
#endif
    i = 0;
  }
  auto const& get()
  {
    while (true)
    {      
      if (i >= static_cast<std::uint32_t>(saved.size()))
      {
        i = 0;
        saved.clear();
        tr.resolve_tokens(ts, true);
        if (saved.empty())
          break;
      }
      if (i < static_cast<std::uint32_t>(saved.size()))
      {
        auto& ret = saved[i++];
        return ret;
      }
    }

    return empty;
  }

  std::string_view value(rtoken const& t)
  {
    return t.svalue();
  }

  bool error_bit() const
  {
    return tr.err_bit;
  }

  void set_result(eval_type val)
  {
    result   = val;
    finished = finish_state::result_available;
  }

  bool has_result() const
  {
    return finished == finish_state::result_available;
  }

  void handle(token const& t, symvalue const& data) override
  {
#ifndef PPR_DISABLE_RECORD
    if (record_content)
    {
      record += data.first;
      record += data.second;
    }
#endif

    if (t.was_disabled)
      return;

    if (finished != finish_state::none)
      return;
    if (t.type == ppr::token_type::ty_eof)
    {
      finished = finish_state::end_of_seq;
      return;
    }
    auto ty = tr.from(t);
    if (ty.type == ppr::token_type::ty_eof)
    {
      finished = finish_state::end_of_seq;
      return;
    }
    if (ty.type != token_type::ty_newline)
      saved.emplace_back(std::move(ty), (t.type != token_type::ty_rtoken) ? t.value.td.pos : loc{});
    else
      finished = finish_state::end_of_seq;
  }
  void push_error(std::string_view err, std::string_view tok, loc pos)
  {
    chain.error(err, tok, ppr::token(), pos);
  }
  void error(std::string_view, std::string_view, ppr::token, ppr::loc) override {}
};
} // namespace ppr

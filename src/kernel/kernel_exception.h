/*
Copyright (c) 2013 Microsoft Corporation. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.

Author: Leonardo de Moura
*/
#pragma once
#include "kernel/environment.h"
#include "kernel/ext_exception.h"

namespace lean {
class environment;
/** \brief Base class for all kernel exceptions. */
class kernel_exception : public ext_exception {
protected:
    environment m_env;
public:
    kernel_exception(environment const & env):m_env(env) {}
    kernel_exception(environment const & env, char const * msg):ext_exception(msg), m_env(env) {}
    kernel_exception(environment const & env, sstream const & strm):ext_exception(strm), m_env(env) {}
    environment const & get_environment() const { return m_env; }
    virtual format pp(formatter const & fmt) const override;
    virtual throwable * clone() const override { return new kernel_exception(m_env, m_msg.c_str()); }
    virtual void rethrow() const override { throw *this; }
};

[[ noreturn ]] void throw_kernel_exception(environment const & env, char const * msg, optional<expr> const & m = none_expr());
[[ noreturn ]] void throw_kernel_exception(environment const & env, sstream const & strm, optional<expr> const & m = none_expr());
[[ noreturn ]] void throw_kernel_exception(environment const & env, char const * msg, expr const & m);
[[ noreturn ]] void throw_kernel_exception(environment const & env, sstream const & strm, expr const & m);
[[ noreturn ]] void throw_kernel_exception(environment const & env, char const * msg, optional<expr> const & m, pp_fn const & fn);
[[ noreturn ]] void throw_kernel_exception(environment const & env, optional<expr> const & m, pp_fn const & fn);
[[ noreturn ]] void throw_kernel_exception(environment const & env, char const * msg, expr const & m, pp_fn const & fn);
[[ noreturn ]] void throw_kernel_exception(environment const & env, expr const & m, pp_fn const & fn);
[[ noreturn ]] void throw_unknown_declaration(environment const & env, name const & n);
[[ noreturn ]] void throw_already_declared(environment const & env, name const & n);
}

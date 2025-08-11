//
// Copyright (c) 2025 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#ifndef BOOST_RTS_PSL_SERVICE_HPP
#define BOOST_RTS_PSL_SERVICE_HPP

#include <boost/rts/context_fwd.hpp>
#include <boost/rts/detail/config.hpp>
#include <boost/rts/psl/ctx_fwd.hpp>
#include <boost/rts/psl/error.hpp>
#include <boost/rts/service.hpp>

#include <ctime>
#include <stdio.h>

namespace boost {
namespace rts {
namespace psl {

/** Provides the psl API
*/
struct BOOST_SYMBOL_VISIBLE
service
    : public rts::service
{
    virtual void free(ctx *psl) = 0;
    virtual void free_string(char *str) = 0;
    virtual ctx * load_file(const char *fname) = 0;
    virtual ctx * load_fp(FILE *fp) = 0;
    virtual const ctx * builtin() = 0;
    virtual ctx * latest(const char *fname) = 0;
    virtual int is_public_suffix(const ctx *psl, const char *domain) = 0;
    virtual int is_public_suffix2(const ctx *psl, const char *domain, int type) = 0;
    virtual int is_cookie_domain_acceptable(const ctx *psl, const char *hostname, const char *cookie_domain) = 0;
    virtual const char * unregistrable_domain(const ctx *psl, const char *domain) = 0;
    virtual const char * registrable_domain(const ctx *psl, const char *domain) = 0;
    virtual error str_to_utf8lower(const char *str, const char *encoding, const char *locale, char **lower) = 0;
    virtual int suffix_count(const ctx *psl) = 0;
    virtual int suffix_exception_count(const ctx *psl) = 0;
    virtual int suffix_wildcard_count(const ctx *psl) = 0;
    virtual time_t builtin_file_time() = 0;
    virtual const char * builtin_sha1sum() = 0;
    virtual const char * builtin_filename() = 0;
    virtual const char * dist_filename() = 0;
    virtual const char * get_version() = 0;
    virtual int check_version_number(int version) = 0;
    virtual int builtin_outdated() = 0;
};

BOOST_RTS_DECL
service&
install_service(context& ctx);

} // psl
} // rts
} // boost

#endif

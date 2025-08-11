//
// Copyright (c) 2025 Mohammad Nejati
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#include <boost/rts/context.hpp>
#include <boost/rts/psl/service.hpp>
#include <boost/rts/psl/version_error.hpp>

#include <libpsl.h>

namespace boost {
namespace rts {
namespace psl {

class service_impl
    : public service
{
public:
    using key_type = service;

    explicit
    service_impl(
        rts::context&) noexcept
    {
    }

    ~service_impl()
    {
    }

    void free(ctx *psl) override
    {
        psl_free(reinterpret_cast<psl_ctx_t*>(psl));
    }

    void free_string(char *str) override
    {
        psl_free_string(str);
    }

    ctx * load_file(const char *fname) override
    {
        return reinterpret_cast<ctx*>(psl_load_file(fname));
    }

    ctx * load_fp(FILE *fp) override
    {
        return reinterpret_cast<ctx*>(psl_load_fp(fp));
    }

    const ctx * builtin() override
    {
        return reinterpret_cast<const ctx*>(psl_builtin());
    }

    ctx * latest(const char *fname) override
    {
#if PSL_VERSION_NUMBER >= 0x001000
        return reinterpret_cast<ctx*>(psl_latest(fname));
#else
        BOOST_THROW_EXCEPTION(version_error{});
        (void)fname;
#endif
    }

    int is_public_suffix(const ctx *psl, const char *domain) override
    {
        return psl_is_public_suffix(reinterpret_cast<const psl_ctx_t*>(psl), domain);
    }

    int is_public_suffix2(const ctx *psl, const char *domain, int type) override
    {
        return psl_is_public_suffix2(reinterpret_cast<const psl_ctx_t*>(psl), domain, type);
    }

    int is_cookie_domain_acceptable(const ctx *psl, const char *hostname, const char *cookie_domain) override
    {
        return psl_is_cookie_domain_acceptable(reinterpret_cast<const psl_ctx_t*>(psl), hostname, cookie_domain);
    }

    const char * unregistrable_domain(const ctx *psl, const char *domain) override
    {
        return psl_unregistrable_domain(reinterpret_cast<const psl_ctx_t*>(psl), domain);
    }

    const char * registrable_domain(const ctx *psl, const char *domain) override
    {
        return psl_registrable_domain(reinterpret_cast<const psl_ctx_t*>(psl), domain);
    }

    error str_to_utf8lower(const char *str, const char *encoding, const char *locale, char **lower) override
    {
        return static_cast<error>(psl_str_to_utf8lower(str, encoding, locale, lower));
    }

    int suffix_count(const ctx *psl) override
    {
        return psl_suffix_count(reinterpret_cast<const psl_ctx_t*>(psl));
    }

    int suffix_exception_count(const ctx *psl) override
    {
        return psl_suffix_exception_count(reinterpret_cast<const psl_ctx_t*>(psl));
    }

    int suffix_wildcard_count(const ctx *psl) override
    {
        return psl_suffix_wildcard_count(reinterpret_cast<const psl_ctx_t*>(psl));
    }

    time_t builtin_file_time() override
    {
        return psl_builtin_file_time();
    }

    const char * builtin_sha1sum() override
    {
        return psl_builtin_sha1sum();
    }

    const char * builtin_filename() override
    {
        return psl_builtin_filename();
    }

    const char * dist_filename() override
    {
        return psl_dist_filename();
    }

    const char * get_version() override
    {
        return psl_get_version();
    }

    int check_version_number(int version) override
    {
#if PSL_VERSION_NUMBER >= 0x000B00
        return psl_check_version_number(version);
#else
        BOOST_THROW_EXCEPTION(version_error{});
        (void)version;
#endif
    }

    int builtin_outdated() override
    {
        return psl_builtin_outdated();
    }
};

service&
install_service(context& ctx)
{
    return ctx.make_service<service_impl>();
}

} // psl
} // rts
} // boost

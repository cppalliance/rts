//
// Copyright (c) 2023 Christian Mazakas
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#include <boost/rts/context.hpp>

#include <boost/config.hpp>

#include "test_helpers.hpp"

namespace boost {
namespace rts {

struct virtual_service :
#ifdef BOOST_NO_RTTI
    service
#else
    virtual service
#endif
{
  int *px_ = nullptr;

  virtual_service(context &) : px_(new int{42}) {}
  ~virtual_service() override { delete px_; }
  int get_value() const { return *px_; }
};

struct virtual_service_test {
  // want to ensure that our service architecture works with virtual inheritance
  void run() {
    context ctx;
    ctx.make_service<virtual_service>();

    auto const psvc = ctx.find_service<virtual_service>();
    BOOST_TEST_EQ(psvc->get_value(), 42);
  }
};

TEST_SUITE(virtual_service_test, "boost.rts.virtual_service");

} // namespace rts
} // namespace boost

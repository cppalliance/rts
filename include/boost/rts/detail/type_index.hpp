//
// Copyright (c) 2023 Christian Mazakas
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/rts
//

#ifndef BOOST_RTS_DETAIL_TYPE_INDEX_HPP
#define BOOST_RTS_DETAIL_TYPE_INDEX_HPP

#include <boost/config.hpp>
#include <boost/container_hash/hash.hpp>
#include <boost/core/typeinfo.hpp>
#include <boost/throw_exception.hpp>

namespace boost {
namespace rts {
namespace detail {

struct type_index_impl
{
private:
  boost::core::typeinfo const *pdata_ = nullptr;

  std::size_t
  get_raw_name_length() const noexcept
  {
    // Boost.TypeIndex has a dramatically more sophisticated implementation here
    // see if this eventually turns out to matter and if it does, essentially
    // just do more copy-paste
    return std::strlen(raw_name());
  }

  bool
  equal(type_index_impl const &rhs) const noexcept
  {
    return raw_name() == rhs.raw_name() ||
           !std::strcmp(raw_name(), rhs.raw_name());
  }

public:
  type_index_impl(
      boost::core::typeinfo const &type_info) noexcept
      : pdata_(&type_info) {}

  type_index_impl(type_index_impl const &) = default;
  type_index_impl& operator=(
      type_index_impl const &) = default;

  ~type_index_impl() = default;

  template <class T>
  static
  type_index_impl
  type_id() noexcept
  {
      return type_index_impl(BOOST_CORE_TYPEID(T));
  }

  char const*
  raw_name() const noexcept
  {
      return pdata_->name();
  }

  std::size_t
  hash_code() const noexcept
  {
      return boost::hash_range(
        raw_name(), raw_name() + get_raw_name_length());
  }

  bool
  operator==(type_index_impl const &rhs) const noexcept
  {
      return equal(rhs);
  }

  bool
  operator!=(type_index_impl const &rhs) const noexcept
  {
      return !equal(rhs);
  }
};

// like std::type_index,
// but without requiring RTTI
using type_index = type_index_impl;

template <class T>
type_index
get_type_index() noexcept
{
  return type_index_impl::type_id<T>();
}

struct type_index_hasher
{
  std::size_t
  operator()(type_index const &tid) const noexcept
  {
    return tid.hash_code();
  }
};

template <class U, class T>
U
downcast(T *p)
{
#ifdef BOOST_NO_RTTI
  return static_cast<U>(p);
#else
  auto q = dynamic_cast<U>(p);
  if(! q )
    BOOST_THROW_EXCEPTION(std::bad_cast());
  return q;
#endif
}

template <class U, class T>
U
downcast(T &p)
{
#ifdef BOOST_NO_RTTI
  return static_cast<U>(p);
#else
  return dynamic_cast<U>(p);
#endif
}

} // namespace detail
} // namespace rts
} // namespace boost

#endif

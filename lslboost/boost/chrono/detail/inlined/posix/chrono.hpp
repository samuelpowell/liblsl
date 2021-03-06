//  posix/chrono.cpp  --------------------------------------------------------------//

//  Copyright Beman Dawes 2008
//  Copyright Vicente J. Botet Escriba 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//----------------------------------------------------------------------------//
//                                POSIX                                     //
//----------------------------------------------------------------------------//

#include <time.h>  // for clock_gettime
#include <boost/assert.hpp>

namespace lslboost
{
namespace chrono
{

  system_clock::time_point system_clock::now() BOOST_NOEXCEPT
  {
    timespec ts;
    if ( ::clock_gettime( CLOCK_REALTIME, &ts ) )
    {
      BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
    }

    return time_point(duration(
      static_cast<system_clock::rep>( ts.tv_sec ) * 1000000000 + ts.tv_nsec));
  }

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
  system_clock::time_point system_clock::now(system::error_code & ec)
  {
    timespec ts;
    if ( ::clock_gettime( CLOCK_REALTIME, &ts ) )
    {
        if (::lslboost::chrono::is_throws(ec))
        {
            lslboost::throw_exception(
                    system::system_error(
                            errno,
                            ::lslboost::system::system_category(),
                            "chrono::system_clock" ));
        }
        else
        {
            ec.assign( errno, ::lslboost::system::system_category() );
            return time_point();
        }
    }

    if (!::lslboost::chrono::is_throws(ec))
    {
        ec.clear();
    }
    return time_point(duration(
      static_cast<system_clock::rep>( ts.tv_sec ) * 1000000000 + ts.tv_nsec));
  }
#endif

  std::time_t system_clock::to_time_t(const system_clock::time_point& t) BOOST_NOEXCEPT
  {
      return static_cast<std::time_t>( t.time_since_epoch().count() / 1000000000 );
  }

  system_clock::time_point system_clock::from_time_t(std::time_t t) BOOST_NOEXCEPT
  {
      return time_point(duration(static_cast<system_clock::rep>(t) * 1000000000));
  }

#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY

  steady_clock::time_point steady_clock::now() BOOST_NOEXCEPT
  {
    timespec ts;
    if ( ::clock_gettime( CLOCK_MONOTONIC, &ts ) )
    {
      BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
    }

    return time_point(duration(
      static_cast<steady_clock::rep>( ts.tv_sec ) * 1000000000 + ts.tv_nsec));
  }

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
  steady_clock::time_point steady_clock::now(system::error_code & ec)
  {
    timespec ts;
    if ( ::clock_gettime( CLOCK_MONOTONIC, &ts ) )
    {
        if (::lslboost::chrono::is_throws(ec))
        {
            lslboost::throw_exception(
                    system::system_error(
                            errno,
                            ::lslboost::system::system_category(),
                            "chrono::steady_clock" ));
        }
        else
        {
            ec.assign( errno, ::lslboost::system::system_category() );
            return time_point();
        }
    }

    if (!::lslboost::chrono::is_throws(ec))
    {
        ec.clear();
    }
    return time_point(duration(
      static_cast<steady_clock::rep>( ts.tv_sec ) * 1000000000 + ts.tv_nsec));
  }
#endif
#endif

}  // namespace chrono
}  // namespace lslboost



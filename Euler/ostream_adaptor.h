#pragma once

#include <ostream>
#include <boost/range/algorithm/copy.hpp>

namespace euler {
namespace detail {

template< typename Elem >
struct to_ostream_adaptor { std::ostream& o; Elem* s; };

template< typename Range, typename Elem >
inline void operator|( Range&& r, const to_ostream_adaptor< Elem >& o )
{
	typedef typename std::decay< Range >::type range_t;
	boost::copy( r, std::ostream_iterator< typename range_t::value_type >( o.o, o.s ) );
}

}

template< typename Elem >
auto to_ostream( std::ostream& o, Elem* s )
{
	return detail::to_ostream_adaptor< Elem >{ o, s };
}

}
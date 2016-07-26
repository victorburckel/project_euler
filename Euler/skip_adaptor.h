#pragma once

#include <boost/range/iterator_range.hpp>
#include <vector>

namespace euler {
namespace detail {

struct skip_adaptor
{
	size_t n;
};

template< typename Range >
inline auto operator|( const Range& r, const skip_adaptor& s )
{
	return boost::make_iterator_range( std::next( r.begin(), s.n ), r.end() );
}

}

detail::skip_adaptor skip( size_t n )
{
	return detail::skip_adaptor{ n };
}

}
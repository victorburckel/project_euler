#pragma once

#include "vector_adaptor.h"
#include <algorithm>

namespace euler {
namespace detail {

template< typename Less >
struct sorted_adaptor
{
	Less less;
};

template< typename Range, typename Less >
inline auto operator|( const Range& r, const sorted_adaptor< Less >& s )
{
	auto v = r | to_vector;
	std::sort( v.begin(), v.end(), s.less );
	return v;
}

}

namespace {

template< typename Less >
auto sorted( Less less )
{
	return detail::sorted_adaptor< Less >{ less };
}

auto sorted()
{
	return sorted( []( auto&& l, auto&& r ) { return l < r; } );
}

}

}
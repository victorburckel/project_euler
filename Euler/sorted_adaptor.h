#pragma once

#include "vector_adaptor.h"
#include <algorithm>

namespace euler {
namespace detail {

struct sorted_adaptor {};

template< typename Range >
inline auto operator|( const Range& r, const sorted_adaptor& )
{
	auto v = r | to_vector;
	std::sort( v.begin(), v.end() );
	return v;
}

}

namespace {

const auto sorted = detail::sorted_adaptor();

}

}
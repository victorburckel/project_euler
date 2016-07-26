#pragma once

#include <vector>

namespace euler {
namespace detail {

struct to_vector_adaptor {};

template< typename Range >
inline auto operator|( const Range& r, const to_vector_adaptor& )
{
	return std::vector< typename Range::value_type >( r.begin(), r.end() );
}

}

namespace {

const auto to_vector = detail::to_vector_adaptor();

}

}
#pragma once

#include <vector>

namespace euler {
namespace detail {

struct to_vector_adaptor {};

template< typename Range >
inline auto operator|( const Range& r, const to_vector_adaptor& )
{
	using namespace std;
	typedef typename std::decay< decltype( *begin( r ) ) >::type value_type;
	return std::vector< typename value_type >( begin( r ), end( r ) );
}

}

namespace {

const auto to_vector = detail::to_vector_adaptor();

}

}
#pragma once

#include "vector_adaptor.h"
#include <boost/coroutine/asymmetric_coroutine.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/algorithm/permutation.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <vector>

namespace euler {

template< typename T >
using coro_t = boost::coroutines::asymmetric_coroutine< std::vector< T > >;

template< typename T >
inline void combinations_generator( typename coro_t< T >::push_type& sink, const std::vector< T >& digits, size_t n )
{
	std::vector< bool > v( digits.size() );
	std::fill( v.end() - n, v.end(), true );
	do
	{
		sink( boost::combine( v, digits )
			| boost::adaptors::filtered( []( const auto& e ) { return boost::get< 0 >( e ); } )
			| boost::adaptors::transformed( []( const auto& e ) { return boost::get< 1 >( e ); } )
			| euler::to_vector );
	} while( boost::next_permutation( v ) );
}

template< typename T >
inline void arragements_generator( typename coro_t< T >::push_type& sink, std::vector< T > digits )
{
	std::sort( digits.begin(), digits.end() );
	do
	{
		sink( digits );
	} while( boost::next_permutation( digits ) );
}

template< typename T >
inline void arragements_generator( typename coro_t< T >::push_type& sink, const std::vector< T >& digits, size_t n )
{
	using pull_type = typename coro_t< T >::pull_type;
	using push_type = typename coro_t< T >::push_type;

	pull_type combinations( [ &digits, n ]( push_type& sink ) {
		combinations_generator( sink, digits, n );
	} );

	for( const auto& combination : combinations )
	{
		pull_type arrangements( [ &combination ]( push_type& sink ) {
			arragements_generator( sink, combination );
		} );

		for( const auto& arrangement : arrangements )
			sink( arrangement );
	}
}

}

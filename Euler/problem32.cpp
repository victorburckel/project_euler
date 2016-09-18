#include "euler.h"
#include "level2.h"
#include "combinations.h"
#include <set>

size_t euler::problem32()
{
	// multiplicand * multiplier = product

	// multiplicand: n digits ( min value 10 ^ ( n - 1 ) )
	// multiplier: p digits ( min value 10 ^ ( p - 1 ) )
	// product: 9 - n - p digits => p < 9 - n

	// 10 ^ ( n - 1 ) <= multiplicand < 10 ^ n
	// 10 ^ ( p - 1 ) <= multiplier < 10 ^ p

	// min value for product = multiplicand * multiplier is 10 ^ ( n - 1 + p - 1 ) => n + p - 1 digits
	// 9 - n - p >= n + p - 1 => 2p <= 10 - 2n => p <= 5 - n

	// max value for product = multiplicand * multiplier is 10 ^ ( n + p ) => n + p + 1 digits
	// 9 - n - p < n + p + 1 => 2p >= 8 - 2n => p > 4 - n

	// p = 5 - n

	coro_t< int >::pull_type arragements( []( coro_t< int >::push_type& sink ) {
		arragements_generator( sink, boost::irange( 1, 10 ) | to_vector );
	} );

	auto compute_value_impl = []( const auto& range ) {
		int power = 0;
		return boost::accumulate( range, 0, [ &power ]( int total, int digit ) { return total + static_cast< int >( std::pow( 10, power++ ) ) * digit; } );
	};

	auto compute_value = [ &compute_value_impl ]( const auto& range, int begin, int end ) {
		return compute_value_impl( boost::make_iterator_range( std::next( range.begin(), begin ), std::next( range.begin(), end ) ) );
	};

	std::set< int > result;
	for( const auto& arragement : arragements )
	{
		for( const auto n : { 1, 2 } )
		{
			const auto p = 5 - n;
			const auto multiplicant = compute_value( arragement, 0, n );
			const auto multiplier = compute_value( arragement, n, n + p );
			const auto product = compute_value( arragement, n + p, 9 );
			if( multiplicant * multiplier == product )
				result.insert( product );
		}
	}

	return boost::accumulate( result, 0 );
}
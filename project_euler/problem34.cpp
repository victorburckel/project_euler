#include "euler.h"
#include "level2.h"
#include "combinations.h"
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <set>

namespace {

const int factorials[] = {
	1,
	1,
	2,
	6,
	24,
	120,
	720,
	5040,
	40320,
	362880
};

int compute( const std::vector< int >& digits )
{
	int power = 0;
	return boost::accumulate( digits | boost::adaptors::reversed, 0, [ &power ]( int total, int digit ) { return total + static_cast< int >( std::pow( 10, power++ ) ) * digit; } );
}

bool isDigitFactorial( const std::vector< int >& digits )
{
	auto firstIt = boost::find_if( digits, []( int digit ) { return digit != 0; } );
	return boost::accumulate( boost::make_iterator_range( firstIt, digits.end() ), 0_u, []( const size_t total, int digit ) { return total + factorials[ digit ]; } ) == compute( digits );
}

}

size_t euler::problem34()
{
	assert( isDigitFactorial( { 1,4,5 } ) );

	// Let p be a number with n digit
	// Sum factorial digits < n * 9!
	// p > 10 ^ ( n - 1 )

	// 10 ^ ( n - 1 ) > n * 9!
	// True if n >= 7

	const auto result = coro_t< int >::pull_type( []( coro_t< int >::push_type& sink ) { number_generator( sink, boost::irange( 0, 10 ) | to_vector, 7 ); } )
		| boost::adaptors::filtered( isDigitFactorial )
		| boost::adaptors::transformed( compute )
		| to_vector;

	std::set< size_t > sorted( result.begin(), result.end() );
	assert( sorted.erase( 1 ) );
	assert( sorted.erase( 2 ) );

	return boost::accumulate( sorted, 0_u );
}
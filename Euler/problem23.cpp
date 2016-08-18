#include "euler.h"
#include "level1.h"
#include "divisors.h"
#include <boost/unordered_set.hpp>

size_t euler::problem23()
{
	const auto is_abundant = []( size_t n ) {
		return euler::getSumOfProperDivisorsAlt( n ) > n;
	};

	const auto abundants = boost::irange( 12_u, 28123_u ) | boost::adaptors::filtered( is_abundant ) | to_vector;
	assert( abundants[ 0 ] == 12_u );

	const auto is_sum_of_two_abundants = [ &abundants, abundants_checker = boost::unordered_set< size_t >( abundants.begin(), abundants.end() ) ]( size_t n ) {
		for( auto it = abundants.begin(); it != abundants.end() && *it < n; ++it )
			if( abundants_checker.find( n - *it ) != abundants_checker.end() )
				return true;

		return false;
	};
	
	const auto result = boost::irange( 1_u, 28123_u ) | boost::adaptors::filtered( [ is_sum_of_two_abundants ]( size_t n ) { return !is_sum_of_two_abundants( n ); } ) | to_vector;
	return boost::accumulate( result, 0_u );
}
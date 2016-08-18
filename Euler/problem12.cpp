#include "euler.h"
#include "level1.h"
#include "primes.h"

#include <boost/range/algorithm/upper_bound.hpp>
#include <boost/range/algorithm/find_if.hpp>

size_t euler::problem12()
{
	const auto init = { 2_u, 3_u };
	std::vector< size_t > primes( init );

	generate_primes( [ &primes ]( auto prime ) { primes.push_back( prime ); }, 1e6_u, init );

	const auto nbDivisors = 500_u;
	const auto minimalValue = boost::accumulate( boost::make_iterator_range( primes.begin(), std::next( primes.begin(), nbDivisors ) ), 0_u );
	
	const auto getNbDivisors = [ &primes ]( size_t number ) {
		const auto limit = static_cast< size_t >( std::ceil( sqrt( number ) ) );
		const auto end = boost::upper_bound( primes, limit );

		const auto result = boost::accumulate( boost::make_iterator_range( primes.begin(), end ), 1_u, [ &number ]( size_t total, size_t prime ) {
			auto power = 0_u;
			while( number % prime == 0 )
			{
				number /= prime;
				power++;
			}
			return total * ( power + 1 );
		} );

		return number != 1_u ? result * 2_u : result;
	};

	assert( getNbDivisors( 3 ) == 2 );
	assert( getNbDivisors( 6 ) == 4 );
	assert( getNbDivisors( 10 ) == 4 );
	assert( getNbDivisors( 15 ) == 4 );
	assert( getNbDivisors( 21 ) == 4 );
	assert( getNbDivisors( 28 ) == 6 );

	// n( n + 1 ) / 2 >= minmalValue
	// ~ n > sqrt( 2 * minimalValue )
	auto n = static_cast< size_t >( std::floor( std::sqrt( 2 * minimalValue ) ) );
	for( auto sum = n * ( n + 1 ) / 2;; sum += ++n )
	{
		const auto temp = getNbDivisors( sum );
		if( temp >= nbDivisors )
			return sum;
	}
}
#include "euler.h"
#include "level2.h"
#include "primes.h"
#include <boost/range/algorithm/lower_bound.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <set>

namespace {

size_t get_quadratic_expr_length( int a, int b, const std::set< int >& tester )
{
	int n = 0;
	for( ; tester.find( n * n + a * n + b ) != tester.end(); ++n );
	return n;
}

}

int euler::problem27()
{
	std::vector< int > primes{ 1, 2, 3 };
	generate_primes( [ &primes ]( size_t prime ) { primes.push_back( static_cast< int >( prime ) ); }, 3e6_u, { 2, 3 } );

	// n² + an + b prime
	
	// with n = 0 => b prime
	// |b| <= 1000
	const auto primes1000 = boost::make_iterator_range( primes.begin(), boost::lower_bound( primes, 1000 ) );

	// with n = 1
	// 1 + a + b prime => a = prime - b - 1
	// |a| < 1000 => -1000 < prime - b - 1 < 1000
	// 1 <= b <= 997 
	// => left condition always true
	// => right condition true iif prime < 1000 + b + 1
	// maximum prime < 1098
	const auto primes2000 = boost::make_iterator_range( primes.begin(), boost::lower_bound( primes, 1000 ) );

	
	size_t max_length = 0;
	int result = 0;

	std::set< int > tester( primes.begin(), primes.end() );
	assert( get_quadratic_expr_length( 1, 41, tester ) == 40 );
	for( auto b : primes1000 | boost::adaptors::reversed )
	{
		for( auto a : boost::make_iterator_range( primes2000.begin(), boost::lower_bound( primes2000, b + 1001 ) ) )
		{
			a = a - b - 1;
			const auto length = get_quadratic_expr_length( a, b, tester );
			if( length > max_length )
			{
				max_length = length;
				result = a * b;
			}
		}

		// as b | b² + ab + b, maximum length is b
		if( max_length > b )
			break;
	}
	
	return result;
}
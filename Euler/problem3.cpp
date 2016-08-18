#include "euler.h"
#include "level1.h"
#include "primes.h"

size_t euler::problem3()
{
	const auto tester = 600851475143;
	size_t result;
	generate_primes( [ tester, &result ]( auto&& prime ) { if( tester % prime == 0 ) result = prime;  }, static_cast< size_t >( std::sqrt( tester ) ), std::vector< size_t >{ 2, 3 } );

	return result;
}
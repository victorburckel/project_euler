#include "primes.h"

size_t problem7()
{
	size_t count = 2_u;
	size_t result = 3_u;
	generate_primes( [ & ]( auto prime ) { if( ++count == 10001 ) result = prime; }, 1e9_u, { 2, 3 } );
	return result;
}
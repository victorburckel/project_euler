#include "euler.h"
#include "level2.h"
#include <iostream>

size_t euler::problem28()
{
	std::vector< size_t > s{ 3, 8, 8, 8 };

	const auto sum = []( size_t n ) {
		size_t c = 3;
		size_t m = 2;
		size_t result = 0;;
		for( auto i : boost::irange( 0_u, n / 2 ) )
		{
			( void ) i;
			result += c * 4 + m * 6;
			c += m * 4 + 2;
			m += 2;
		}

		return result + 1;
	};


	assert( sum( 5 ) == 101 );
	return sum( 1001 );
}
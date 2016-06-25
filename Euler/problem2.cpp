#include "problems.h"
#include <array>

size_t euler::problem2()
{
	std::array< size_t, 3 > fibo = { 1, 2, 3 };

	size_t result = 0;
	while( fibo[ 1 ] < 4000000 )
	{
		result += fibo[ 1 ];
		fibo[ 0 ] = fibo[ 1 ] + fibo[ 2 ];
		fibo[ 1 ] = fibo[ 0 ] + fibo[ 2 ];
		fibo[ 2 ] = fibo[ 0 ] + fibo[ 1 ];
	}

	return result;
}
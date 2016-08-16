#include "euler.h"
#include "divisors.h"

size_t euler::problem21()
{
	assert( getSumOfProperDivisorsAlt( 220_u ) == 284_u );
	assert( getSumOfProperDivisorsAlt( 284_u ) == 220_u );
	
	std::vector< size_t > sums = boost::irange( 2_u, 10000_u ) | boost::adaptors::transformed( &getSumOfProperDivisorsAlt ) | to_vector;

	auto result = 0_u;
	const auto size = sums.size();
	auto index = 0_u;
	for( auto sum : sums )
	{
		const auto current = index + 2_u;
		if( sum != current && sum < size && sum > 1 && sums[ sum - 2_u ] == current )
			result += current;
		++index;
	}

	return result;
}
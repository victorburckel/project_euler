#include "euler.h"
#include "sorted_adaptor.h"
#include <boost/range/adaptor/uniqued.hpp>
#include <boost/range/algorithm/max_element.hpp>

namespace {

size_t reduce_impl( size_t n, size_t d )
{
	while( n % d == 0 )
		n /= d;
	return n;
}

size_t reduce( size_t n )
{
	return reduce_impl( reduce_impl( n, 2 ), 5 );
}

size_t cycle_length( size_t d )
{
	if( d == 1 )
		return 0;

	size_t result = 1;

	size_t n = 10;
	while( n != 1 )
	{
		while( d > n )
		{
			++result;
			n *= 10;
		}
		n = n % d;
	}

	return result;
}

}

size_t euler::problem26()
{
	assert( cycle_length( 3 ) == 1 );
	assert( cycle_length( 9 ) == 1 );
	assert( cycle_length( 7 ) == 6 );

	return *boost::max_element(
		boost::irange( 3_u, 1001_u ) |
		boost::adaptors::transformed( &reduce ) |
		sorted |
		boost::adaptors::uniqued |
		boost::adaptors::transformed( &cycle_length ) ).base().base();
}
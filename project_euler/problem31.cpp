#include "euler.h"
#include "level2.h"

namespace {

size_t count( const boost::iterator_range< std::vector< unsigned >::const_iterator >& range, unsigned n )
{
	if( range.size() == 1 )
	{
		assert( n % range.back() == 0 );
		return 1;
	}

	return boost::accumulate( boost::irange( 0u, n / range.back() + 1u ), 0_u, [ &range, n ]( size_t result, unsigned p ) {
		return result + count( boost::make_iterator_range( range.begin(), range.end() - 1 ), n - p * range.back() );
	} );
}

}

size_t euler::problem31()
{
	std::vector< unsigned > coins{ 1, 2, 5, 10, 20, 50, 100, 200 };
	return count( coins, 200 );
}
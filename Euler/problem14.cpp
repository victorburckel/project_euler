#include "problems.h"
#include "literals.h"
#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/irange.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <assert.h>

namespace {

size_t next_collactz_seq_element( size_t n )
{
	return n % 2_u == 0_u ? n / 2_u : 3_u * n + 1_u;
}

size_t collatz_seq_size( size_t n )
{
	size_t s = 1_u;  
	for( ; n != 1_u; n = next_collactz_seq_element( n ), ++s );
	return s;
}

}

size_t euler::problem14()
{
	assert( collatz_seq_size( 13 ) == 10 );

	return *boost::max_element( boost::irange( 1_u, 1e6_u ) | boost::adaptors::transformed( collatz_seq_size ) ).base();
}
#include "euler.h"
#include "level1.h"

size_t euler::problem1()
{
	return boost::accumulate( boost::irange( 3_u, 1000_u, 3 ), 0_u ) + boost::accumulate( boost::irange( 5_u, 1000_u, 5 ), 0_u ) - boost::accumulate( boost::irange( 15_u, 1000_u, 15 ), 0_u );
}
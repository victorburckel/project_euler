#include "problems.h"
#include "literals.h"
#include <boost/range/numeric.hpp>
#include <boost/range/irange.hpp>

size_t euler::problem1()
{
	return boost::accumulate( boost::irange( 3_u, 1000_u, 3 ), 0_u ) + boost::accumulate( boost::irange( 5_u, 1000_u, 5 ), 0_u ) - boost::accumulate( boost::irange( 15_u, 1000_u, 15 ), 0_u );
}
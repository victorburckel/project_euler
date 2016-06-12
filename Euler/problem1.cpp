#include <boost/range/numeric.hpp>
#include <boost/range/irange.hpp>

int problem1()
{
	return boost::accumulate( boost::irange( 3, 1000, 3 ), 0 ) + boost::accumulate( boost::irange( 5, 1000, 5 ), 0 ) - boost::accumulate( boost::irange( 15, 1000, 15 ), 0 );
}
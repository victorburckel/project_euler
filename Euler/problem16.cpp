#include "problems.h"
#include "literals.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/range/numeric.hpp>
#include <boost/lexical_cast.hpp>

namespace {

size_t sum_power_digits( unsigned p )
{
	using boost::multiprecision::checked_int1024_t;
	return boost::accumulate( boost::multiprecision::pow( checked_int1024_t( 2 ), p ).str(), 0_u, []( size_t total, char s ) { return total + boost::lexical_cast< size_t >( s ); } );
}

}

size_t euler::problem16()
{
	assert( sum_power_digits( 15u ) == 26 );
	return sum_power_digits( 1000u );
}
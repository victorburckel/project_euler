#include "euler.h"
#include "level1.h"
#include <boost/multiprecision/cpp_int.hpp>

size_t euler::problem20()
{
	boost::multiprecision::cpp_int factorial = 1;
	for( unsigned i = 1; i <= 100; ++i )
		factorial *= i;

	return boost::accumulate( factorial.str(), 0_u, []( size_t total, char s ) { return total + boost::lexical_cast< size_t >( s ); } );
}
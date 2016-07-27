#include "problems.h"
#include "literals.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/range/numeric.hpp>
#include <boost/lexical_cast.hpp>

size_t euler::problem20()
{
	boost::multiprecision::cpp_int factorial = 1;
	for( unsigned i = 1; i <= 100; ++i )
		factorial *= i;

	return boost::accumulate( factorial.str(), 0_u, []( size_t total, char s ) { return total + boost::lexical_cast< size_t >( s ); } );
}
#include "euler.h"
#include <boost/range/adaptor/reversed.hpp>

namespace {

size_t get_nth_permutation( size_t numDigits, size_t n )
{
	auto factorial = 1_u;
	auto factorials = boost::irange( 1_u, numDigits ) | boost::adaptors::transformed( [ &factorial ]( size_t i ) { return factorial *= i; } ) | euler::to_vector | boost::adaptors::reversed | euler::to_vector;
	
	std::vector< char > digits( numDigits );
	char digit = 0;
	std::generate( digits.begin(), digits.end(), [ &digit ]() { return '0' + digit++; } );

	std::string result;
	result.resize( numDigits );
	for( auto i : boost::irange( 0_u, numDigits - 1_u ) )
	{
		auto it = std::next( digits.begin(), n / factorials[ i ] );
		result[ i ] = *it;
		digits.erase( it );

		n = n % factorials[ i ];
	}
	result.back() = digits.front();

	return boost::lexical_cast< size_t >( result );
}

}

size_t euler::problem24()
{
	assert( get_nth_permutation( 3, 0 ) == 12 );
	assert( get_nth_permutation( 3, 1 ) == 21 );
	assert( get_nth_permutation( 3, 2 ) == 102 );
	assert( get_nth_permutation( 3, 3 ) == 120 );
	assert( get_nth_permutation( 3, 4 ) == 201 );
	assert( get_nth_permutation( 3, 5 ) == 210 );
	
	return get_nth_permutation( 10, 1000000 - 1 );
}
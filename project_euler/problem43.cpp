#include "euler.h"
#include "level2.h"
#include "combinations.h"
#include <boost/range/adaptor/reversed.hpp>

namespace {

bool test_divisibility_impl( const std::vector< int >& n, size_t hundreds, size_t tens, size_t units, int divisor )
{
	const auto value = n[ hundreds ] * 100 + n[ tens ] * 10 + n[ units ];
	return value % divisor == 0;
}

bool test_divisibility( const std::vector< int >& n )
{
	return
		test_divisibility_impl( n, 1, 2, 3, 2 ) &&
		test_divisibility_impl( n, 2, 3, 4, 3 ) &&
		test_divisibility_impl( n, 3, 4, 5, 5 ) &&
		test_divisibility_impl( n, 4, 5, 6, 7 ) &&
		test_divisibility_impl( n, 5, 6, 7, 11 ) &&
		test_divisibility_impl( n, 6, 7, 8, 13 ) &&
		test_divisibility_impl( n, 7, 8, 9, 17 );
}

}

size_t euler::problem43()
{
	assert( test_divisibility( { 1, 4, 0, 6, 3, 5, 7, 2, 8, 9 } ) );

	using namespace std::string_literals;

	coro_t< int >::pull_type source( []( coro_t< int >::push_type& sink ) {
		arragements_generator( sink, boost::irange( 0, 10 ) | to_vector );
	} );

	using namespace boost::adaptors;

	const auto to_number = []( const std::vector< int >& n ) {
		int pow = 0;
		return boost::accumulate( n | reversed, 0_u, [ &pow ]( size_t total, int n ) { return total + n * std::pow( 10, pow++ ); } );
	};

	const auto test = source | filtered( &test_divisibility ) | to_vector;
	return boost::accumulate( test | transformed( to_number ), 0_u, std::plus< size_t >() );
}
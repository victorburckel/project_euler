#include "euler.h"
#include "level2.h"
#include "primes.h"
#include <boost/coroutine/asymmetric_coroutine.hpp>
#include <boost/range/algorithm/adjacent_find.hpp>

namespace {

bool is_pandigital( size_t n )
{
	auto str = std::to_string( n );
	std::sort( str.begin(), str.end() );

	return str[ 0 ] == '1' && boost::adjacent_find( str, []( char l, char r ) { return r - l != 1; } ) == str.end();
}

}

size_t euler::problem41()
{
	typedef boost::coroutines::asymmetric_coroutine< size_t > coro_t;

	const auto limit = 987654321_u;

	coro_t::pull_type source( [ limit ]( coro_t::push_type& sink ) {
		generate_primes( sink, limit, { 2, 3 } );
	} );

	using namespace boost::adaptors;
	const auto pandigitalPrimes = source | filtered( [ limit ]( size_t n ) { return n < limit; } ) | filtered( []( size_t n ) { return is_pandigital( n ); } ) | to_vector;

	return pandigitalPrimes.back();
}
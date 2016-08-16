#include "euler.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/unordered_map.hpp>
#include <boost/range/algorithm/lower_bound.hpp>

using namespace boost::multiprecision;

namespace {

cpp_int fibo( size_t n, boost::unordered_map< size_t, cpp_int >& cache )
{
	const auto it = cache.insert( std::make_pair( n, cpp_int( 0 ) ) );
	if( it.second )
		it.first->second = pow( fibo( n / 2 + 1, cache ), 2 ) - ( n % 2 == 0 ? 1 : -1 ) * pow( fibo( ( n - 1 ) / 2, cache ), 2 );
	return it.first->second;
}

}

size_t euler::problem25()
{
	boost::unordered_map< size_t, cpp_int > cache = { { 0, 0 }, { 1, 1 }, { 2, 1 } };
	assert( fibo( 256, cache ).str() == "141693817714056513234709965875411919657707794958199867" );
	return *boost::lower_bound( boost::irange( 1_u, 10000_u ), 1000_u, [ &cache ]( size_t n, size_t digits ) { return fibo( n, cache ).str().size() < digits; } );
}
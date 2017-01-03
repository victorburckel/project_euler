#include "euler.h"
#include "level2.h"
#include "primes.h"
#include <boost/unordered_set.hpp>
#include <boost/coroutine/asymmetric_coroutine.hpp>
#include <boost/range/algorithm/find.hpp>

namespace {

bool is_truncatable_prime( const std::string& prime, const boost::unordered_set< size_t >& truncatablePrimes )
{
	return truncatablePrimes.find( boost::lexical_cast< size_t >( prime ) ) != truncatablePrimes.end();
}

std::pair< bool, bool > is_truncatable_prime( size_t prime, const boost::unordered_set< size_t >& lrTruncatablePrimes, const boost::unordered_set< size_t >& rlTruncatablePrimes )
{
	const auto str = std::to_string( prime );
	return std::make_pair( is_truncatable_prime( str.substr( 1 ), lrTruncatablePrimes ), is_truncatable_prime( str.substr( 0, str.size() - 1 ), rlTruncatablePrimes ) );
}

}

size_t euler::problem37()
{
	const auto total = 11_u;
	std::vector< size_t > result;
	result.reserve( total );

	boost::unordered_set< size_t > lrTruncatablePrimes = { 2, 3, 5, 7 };
	auto rlTruncatablePrimes = lrTruncatablePrimes;

	typedef boost::coroutines::asymmetric_coroutine< size_t > coro_t;

	coro_t::pull_type source( []( coro_t::push_type& sink ) { generate_primes( sink, 1e6_u, { 2, 3, 5, 7 } ); } );

	for( auto prime : source )
	{
		const auto t = is_truncatable_prime( prime, lrTruncatablePrimes, rlTruncatablePrimes );
		if( t.first )
			lrTruncatablePrimes.insert( prime );

		if( t.second )
			rlTruncatablePrimes.insert( prime );

		if( t.first && t.second )
			result.push_back( prime );

		if( result.size() == total )
			break;
	}

	assert( result.size() == total );
	assert( boost::find( result, 3797 ) != result.end() );

	return boost::accumulate( result, 0_u );
}
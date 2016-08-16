#include "euler.h"
#include "primes.h"
#include <boost/coroutine/asymmetric_coroutine.hpp>

size_t euler::problem10()
{
	std::vector< size_t > primes = { 2u, 3u };

	typedef boost::coroutines::asymmetric_coroutine< size_t > coro_t;
	const auto limit = 2 * 1e6_u;

	coro_t::pull_type source( [ &primes, limit ]( coro_t::push_type& sink ) {
		generate_primes( sink, limit, primes );
	} );


	return boost::accumulate( source | boost::adaptors::filtered( std::bind( std::less< size_t >(), std::placeholders::_1, limit ) ), boost::accumulate( primes, 0_u ) );
}
#pragma once

#include <boost/math/common_factor_rt.hpp>
#include <boost/range/irange.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/algorithm/cxx11/none_of.hpp>
#include <boost/dynamic_bitset.hpp>
#include <vector>
#include <numeric>

inline size_t operator "" _u( unsigned long long int v ) { return static_cast< size_t >( v ); }
inline size_t operator "" _u( long double v ) { return static_cast< size_t >( v ); }

struct Factors
{
	size_t divisor;
	std::vector< size_t > remainders;
};

inline Factors resolve( const std::vector< size_t >& primes )
{
	assert( !primes.empty() );

	Factors result = { boost::accumulate( primes, 1_u, std::multiplies< size_t >() ) };

	struct Filter
	{
		Filter( const std::vector< size_t >& primes ) : primes( primes )
		{ /* no-op */
		}

		bool operator()( size_t i ) const
		{
			return boost::algorithm::none_of( primes, [ i ]( size_t prime ) { return i % prime == 0; } );
		}

		const std::vector< size_t >& primes;
	};
	boost::copy( boost::irange( 1_u, result.divisor ) | boost::adaptors::filtered( Filter( primes ) ), std::back_inserter( result.remainders ) );
	return result;
}

template< typename F >
inline void generate_primes( F&& sink, size_t n, const std::vector< size_t >& primes )
{
	assert( primes.back() <= n );

	const auto factors = resolve( primes );
	const auto nbRemainders = factors.remainders.size();

	const auto subSize = ( n + factors.divisor - 1 ) / factors.divisor;
	std::vector< boost::dynamic_bitset<> > result( nbRemainders, boost::dynamic_bitset<>( subSize ).flip() );
	std::vector< size_t > offsets( factors.divisor );


	for( size_t primeRemainderIndex = 1, primeQuotient = 0; primeQuotient != boost::dynamic_bitset<>::npos; )
	{
		const auto primeRemainder = factors.remainders[ primeRemainderIndex ];
		const auto prime = factors.divisor * primeQuotient + primeRemainder;
		sink( prime );

		for( size_t i = 0; i < nbRemainders; ++i )
		{
			const auto multiple = factors.remainders[ i ] * prime;
			const auto multipleRemainder = multiple % factors.divisor;
			const auto multipleQuotient = multiple / factors.divisor;

			offsets[ multipleRemainder ] = multipleQuotient - primeQuotient;
		}

		for( size_t i = 0; i < nbRemainders; ++i )
		{
			auto& tab = result[ i ];
			const auto offset = offsets[ factors.remainders[ i ] ];

			// multiple = i * prime = b * q + r => ( i + b ) * prime = b * ( q + prime ) + r
			for( size_t subIndex = primeQuotient + offset; subIndex < subSize; subIndex += prime )
				tab.reset( subIndex );
		}

		size_t nextPrimeRemainderIndex = boost::dynamic_bitset<>::npos;
		size_t nextPrimeQuotient = boost::dynamic_bitset<>::npos;
		for( size_t i = 0; i <= primeRemainderIndex; ++i )
		{
			auto tabQuotient = result[ i ].find_next( primeQuotient );
			if( tabQuotient < nextPrimeQuotient )
			{
				nextPrimeQuotient = tabQuotient;
				nextPrimeRemainderIndex = i;
			}
		}
		if( primeQuotient )
		{
			for( size_t i = primeRemainderIndex + 1; i < nbRemainders; ++i )
			{
				auto tabQuotient = result[ i ].find_next( primeQuotient - 1 );
				if( tabQuotient < nextPrimeQuotient )
				{
					nextPrimeQuotient = tabQuotient;
					nextPrimeRemainderIndex = i;
				}
			}
		}
		else
		{
			for( size_t i = primeRemainderIndex + 1; i < nbRemainders; ++i )
			{
				auto tabQuotient = result[ i ].find_first();
				if( tabQuotient < nextPrimeQuotient )
				{
					nextPrimeQuotient = tabQuotient;
					nextPrimeRemainderIndex = i;
				}
			}
		}

		primeRemainderIndex = nextPrimeRemainderIndex;
		primeQuotient = nextPrimeQuotient;
	}
}
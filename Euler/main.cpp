#include "chunk_iterator.h"
#include "cross_product_iterator.h"
#include <boost/algorithm/cxx11/all_of.hpp>
#include <boost/algorithm/cxx11/none_of.hpp>
#include <boost/range/irange.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/algorithm/mismatch.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/coroutine/asymmetric_coroutine.hpp>
#include <boost/math/common_factor_rt.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/timer/timer.hpp>
#include <iostream>
#include <array>
#include <vector>

size_t operator "" _u( unsigned long long int v ) { return static_cast< size_t >( v ); }

void problem1()
{
	const auto result = boost::accumulate( boost::irange( 3, 1000, 3 ), 0  ) + boost::accumulate( boost::irange( 5, 1000, 5 ), 0 ) - boost::accumulate( boost::irange( 15, 1000, 15 ), 0 );
	std::cout << "problem1: " << result << std::endl;
}

void problem2()
{
	std::array< size_t, 3 > fibo = { 1, 2, 3 };

	size_t result = 0;
	while( fibo[ 1 ] < 4000000 )
	{
		result += fibo[ 1 ];
		fibo[ 0 ] = fibo[ 1 ] + fibo[ 2 ];
		fibo[ 1 ] = fibo[ 0 ] + fibo[ 2 ];
		fibo[ 2 ] = fibo[ 0 ] + fibo[ 1 ];
	}

	std::cout << "problem2: " << result << std::endl;
}

namespace v1 {

// Parameters for a x + b
struct Parameters
{
	size_t a;
	size_t b;

	size_t operator()( size_t x ) const { return a * x + b; }
};

// Solve a x + b = a' y + b' with x and y integral numbers
Parameters resolve( const Parameters& l, const Parameters& r )
{
	typedef boost::coroutines::asymmetric_coroutine< size_t > coro_t;
	coro_t::pull_type source( []( coro_t::push_type& sink ) {
		for( size_t i = 0;; ++i )
			sink( i );
	} );

	// Search for a solution
	// a * x0 + b = a' * y0 + b' => a * x0 + b - b' % a' == 0
	const auto x0 = *std::find_if( boost::begin( source ), boost::end( source ), [ &l, &r ]( size_t x ) {
		return ( l( x ) - r.b ) % r.a == 0;
	} );
	// const auto y0 = ( l( x0 ) - r.b ) / r.a;
	// assert( l( x0 ) == l( y0 ) );

	// Now
	// a x + b = a'x + b'
	// a x0 + b = a' x0 + b'
	// => a( x - x0 ) = a'( y -y0 )
	const auto gcd = boost::math::gcd_evaluator< size_t >()( l.a, r.a );

	// As a / gcd and a' / gcd are relatively prime numbers
	// x - x0 = k * a' / gcd
	// y - y0 = k' * a / gcd
	// a ( k * a' / gcd ) = a' ( k' * a / gcd )
	// k = k'
	// x = x0 + k * a'
	// a * ( x0 + k * a' / gcd ) + b
	return Parameters{ l.a * r.a / gcd, l.b + l.a * x0 };
}

std::vector< Parameters > resolve( const std::vector< Parameters >& l, const std::vector< Parameters >& r )
{
	std::vector< Parameters > result;
	result.reserve( l.size() * r.size() );

	for( const auto& le : l )
		for( const auto& re : r )
			result.push_back( resolve( le, re ) );

	return result;
}

template< typename Range >
auto to_vector( Range&& range )
{
	return std::vector< typename Range::value_type >( range.begin(), range.end() );
}

std::vector< Parameters > init( size_t a )
{
	return to_vector( boost::irange( 1_u, a ) | boost::adaptors::transformed( [ a ]( size_t b ) { return Parameters{ a, b }; } ) );
}

std::vector< Parameters > resolve( const std::vector< size_t >& primes )
{
	assert( !primes.empty() );
	auto result = std::accumulate( std::next( primes.begin() ), primes.end(), init( primes[ 0 ] ), []( const auto& result, size_t i ) { return resolve( result, init( i ) ); } );
	
	std::sort( result.begin(), result.end(), []( const Parameters& l, const Parameters& r ) { return l.b < r.b; } );
	return result;
}

void generate_primes( size_t n, const std::vector< size_t >& primes )
{
	assert( primes.back() <= n );

	const auto factors = resolve( primes );
	const auto mainFactor = boost::accumulate( primes, 1_u, std::multiplies< size_t >() );
	const auto nbFactors = factors.size();
	assert( boost::algorithm::all_of( factors, [ mainFactor ]( const Parameters& e ) { return e.a == mainFactor && e.b < mainFactor; } ) );

	boost::timer::auto_cpu_timer t;
	std::vector< bool > result;

	const auto size = static_cast< size_t >( ( n / mainFactor + ( n % mainFactor ? 1 : 0 ) ) * nbFactors );
	std::cout << size << std::endl;
	result.resize( size );

	const auto get_value = [ &factors, nbFactors, begin = result.begin() ]( std::vector< bool >::iterator it ) {
		const auto index = std::distance( begin, it );

		// Skip first as it is always mainFactor + 1 and would compute 1
		return factors[ ( index + 1 ) % nbFactors ]( ( index + 1 ) / nbFactors );
	};

	const auto mark = [ &get_value ]( std::vector< bool >::iterator begin, std::vector< bool >::iterator end, size_t prime ) {
		for( auto it = std::find( std::next( begin ), end, false ); it != end; it = std::find( std::next( it ), end, false ) )
			*it = get_value( it ) % prime == 0;
	};

	for( size_t prime : primes )
		mark( result.begin(), result.end(), prime );

	// First one is necessary prime
	for( auto primeIt = result.begin(), end = result.end(); primeIt != end; primeIt = std::find( std::next( primeIt ), end, false ) )
	{
		const auto primeValue = get_value( primeIt );
		mark( primeIt, end, primeValue );
	}
}

}

struct Factors
{
	size_t divisor;
	std::vector< size_t > remainders;
};

Factors resolve( const std::vector< size_t >& primes )
{
	assert( !primes.empty() );

	Factors result = { boost::accumulate( primes, 1_u, std::multiplies< size_t >() ) };

	struct Filter
	{
		Filter( const std::vector< size_t >& primes ) : primes( primes )
		{ /* no-op */ }

		bool operator()( size_t i ) const
		{
			return boost::algorithm::none_of( primes, [ i ]( size_t prime ) { return i % prime == 0; } );
		}

		const std::vector< size_t >& primes;
	};
	boost::copy( boost::irange( 1_u, result.divisor ) | boost::adaptors::filtered( Filter( primes ) ), std::back_inserter( result.remainders ) );
	return result;
}

typedef boost::coroutines::asymmetric_coroutine< size_t > coro_t;

template< typename F >
void generate_primes( F&& sink, size_t n, const std::vector< size_t >& primes )
{
	assert( primes.back() <= n );

	const auto factors = resolve( primes );
	const auto nbRemainders = factors.remainders.size();

	boost::timer::auto_cpu_timer t;

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

void problem3()
{
	const std::vector< size_t > test_result = {
		2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
		31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
		73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
		127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
		179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
		233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
		283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
		353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
		419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
		467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
		547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
		607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
		661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
		739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
		811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
		877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
		947, 953, 967, 971, 977, 983, 991, 997
	};


	const auto it = std::next( test_result.begin(), 2 );

	// Check
	{
		coro_t::pull_type source( [ &test_result, it ]( coro_t::push_type& sink ) {
			generate_primes( sink, static_cast< size_t >( 1e3 ), std::vector< size_t >( test_result.begin(), it ) );
		} );

		std::cout << std::boolalpha << std::equal( it, test_result.end(), boost::begin( source ) ) << std::endl;
	}

	// Perf
	generate_primes( []( auto&& ) {}, static_cast< size_t >( 1e9 ), std::vector< size_t >( test_result.begin(), it ) );

	// Problem3
	const auto tester = 600851475143;
	size_t result;
	generate_primes( [ tester, &result ]( auto&& prime ) { if( tester % prime == 0 ) result = prime;  }, static_cast< size_t >( std::sqrt( tester ) ), std::vector< size_t >( test_result.begin(), it ) );
	std::cout << "problem3: " << result << std::endl;
}

template< class T >
constexpr T pow( const T & x, std::size_t n )
{
	return n > 0 ? x * pow( x, n - 1 ) : 1;
}

void problem4()
{
	struct multiply { auto operator()( std::tuple< int&, int& > element ) const { return std::get< 0 >( element ) * std::get< 1 >( element ); } };
	struct is_palindrome { bool operator()( int i ) const { auto s = std::to_string( i ); return std::equal( s.begin(), s.end(), s.rbegin() ); } };

	const auto result = *boost::max_element(
		cross_product( boost::irange( 100, 1000 ), boost::irange( 100, 1000 ) )
		| boost::adaptors::transformed( multiply() )
		| boost::adaptors::filtered( is_palindrome() ) 
	);

	std::cout << "problem4: " << result << std::endl;
}

void main()
{
	//problem1();
	//problem2();
	//problem3();
	problem4();
}
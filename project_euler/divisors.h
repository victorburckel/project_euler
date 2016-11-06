#pragma once

#include <vector>

namespace euler {

struct prime_factor
{
	unsigned prime;
	unsigned factor;

	bool operator<( const prime_factor& other ) const;
	bool operator==( const prime_factor& other ) const;
};

std::vector< prime_factor > getPrimeFactors( size_t n );
std::vector< size_t > getDivisors( size_t n );
std::vector< size_t > getProperDivisors( size_t n );
size_t getSumOfProperDivisors( size_t n );
size_t getSumOfProperDivisorsAlt( size_t n );

}

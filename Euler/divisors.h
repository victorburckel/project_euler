#pragma once

#include <vector>

namespace euler {

std::vector< size_t > getDivisors( size_t n );
std::vector< size_t > getProperDivisors( size_t n );
size_t getSumOfProperDivisors( size_t n );
size_t getSumOfProperDivisorsAlt( size_t n );

}

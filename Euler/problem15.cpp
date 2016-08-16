#include "euler.h"
#include <boost/math/special_functions/factorials.hpp>

namespace {

size_t cnp( unsigned n, unsigned p )
{
	return static_cast< size_t >( boost::math::factorial< double >( n ) / ( boost::math::factorial< double >( n - p ) * boost::math::factorial< double >( p ) ) );
}

}

size_t euler::problem15()
{
	return cnp( 40u, 20u );
}
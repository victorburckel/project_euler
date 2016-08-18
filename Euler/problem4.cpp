#include "euler.h"
#include "level1.h"
#include "cross_product_iterator.h"
#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/algorithm/mismatch.hpp>
#include <string>

size_t euler::problem4()
{
	struct multiply { auto operator()( std::tuple< size_t&, size_t& > element ) const { return std::get< 0 >( element ) * std::get< 1 >( element ); } };
	struct is_palindrome { bool operator()( size_t i ) const { auto s = std::to_string( i ); return std::equal( s.begin(), s.end(), s.rbegin() ); } };

	const auto result = *boost::max_element(
		cross_product( boost::irange( 100_u, 1000_u ), boost::irange( 100_u, 1000_u ) )
		| boost::adaptors::transformed( multiply() )
		| boost::adaptors::filtered( is_palindrome() )
	);

	return result;
}
#include "cross_product_iterator.h"
#include <boost/range/irange.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/algorithm/mismatch.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <string>

int problem4()
{
	struct multiply { auto operator()( std::tuple< int&, int& > element ) const { return std::get< 0 >( element ) * std::get< 1 >( element ); } };
	struct is_palindrome { bool operator()( int i ) const { auto s = std::to_string( i ); return std::equal( s.begin(), s.end(), s.rbegin() ); } };

	const auto result = *boost::max_element(
		cross_product( boost::irange( 100, 1000 ), boost::irange( 100, 1000 ) )
		| boost::adaptors::transformed( multiply() )
		| boost::adaptors::filtered( is_palindrome() )
	);

	return result;
}
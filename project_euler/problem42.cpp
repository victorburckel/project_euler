#include "euler.h"
#include "level2.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/algorithm/count_if.hpp>
#include <boost/unordered_set.hpp>
#include <fstream>

size_t euler::problem42()
{
	std::ifstream ifs( "p042_words.txt" );
	assert( ifs.is_open() );

	std::string content;
	std::getline( ifs, content );

	std::vector< std::string > words;
	boost::split( words, content, boost::is_any_of( "\"," ), boost::algorithm::token_compress_on );

	const auto maxLen = boost::max_element( words, []( const std::string& l, const std::string& r ) { return l.size() < r.size(); } )->size();
	const auto limit = maxLen * 26;

	boost::unordered_set< int > triangleNumbers;
	for( auto current = 1, step = 2; current < limit; current+= step++ )
		triangleNumbers.insert( current );
	assert( triangleNumbers.find( 55 ) != triangleNumbers.end() );

	const auto is_triangle_word = [ &triangleNumbers ]( const std::string& word ) { return triangleNumbers.find( boost::accumulate( word, 0, []( int total, char c ) { return total + c - 'A' + 1; } ) ) != triangleNumbers.end(); };
	assert( is_triangle_word( "SKY" ) );
	return boost::count_if( words, is_triangle_word );
}
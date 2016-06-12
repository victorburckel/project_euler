#pragma once

#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <tuple>

template< typename It1, typename It2 >
class cross_product_iterator : public boost::iterator_facade< cross_product_iterator< It1, It2 >, std::tuple< typename It1::value_type&, typename It2::value_type& >, boost::forward_traversal_tag, std::tuple< typename It1::value_type&, typename It2::value_type& > >
{
public:
	cross_product_iterator()
	{ /* no-op */ }

	cross_product_iterator( It1 it1, It2 it2, It2 begin2, It2 end2 )
		: _it1( it1 )
		, _it2( it2 )
		, _begin2( begin2 )
		, _end2( end2 )
	{ /* no-op */ }

	cross_product_iterator( It1 it1, It2 it2 )
		: _it1( it1 )
		, _it2( it2 )
	{ /* no-op */ }

private:
	friend class boost::iterator_core_access;

	bool equal( const cross_product_iterator< It1, It2 >& other ) const
	{
		return
			_it1 == other._it1 &&
			_it2 == other._it2;
	}

	void increment()
	{
		if( ++_it2 == _end2 )
		{
			++_it1;
			_it2 = _begin2;
		}
	}

	std::tuple< typename It1::value_type&, typename It2::value_type& > dereference() const
	{
		return std::forward_as_tuple( *_it1, *_it2 );
	}

	It1 _it1;
	It2 _it2;
	It2 _begin2;
	It2 _end2;
};

template< typename It1, typename It2 >
auto make_cross_product_iterator( It1 it1, It2 it2, It2 begin2, It2 end2 )
{
	return cross_product_iterator< It1, It2 >( it1, it2, begin2, end2 );
}

template< typename It1, typename It2 >
auto make_cross_product_iterator( It1 it1, It2 it2 )
{
	return cross_product_iterator< It1, It2 >( it1, it2 );
}


template< typename Seq1, typename Seq2 >
auto cross_product( Seq1&& seq1, Seq2&& seq2 )
{
	return boost::make_iterator_range(
		make_cross_product_iterator( seq1.begin(), seq2.begin(), seq2.begin(), seq2.end() ),
		make_cross_product_iterator( seq1.end(), seq2.begin() )
	);
}
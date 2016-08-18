#pragma once
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>

namespace euler {

#define PROBLEM( z, n, data ) size_t BOOST_PP_CAT( problem, BOOST_PP_ADD( n, 1 ) ) ();
BOOST_PP_REPEAT( 200, PROBLEM, ~ )
#undef PROBLEM

}
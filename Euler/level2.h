#pragma once
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>

namespace euler {

size_t problem26();
int problem27();
#define PROBLEM( z, n, data ) size_t BOOST_PP_CAT( problem, BOOST_PP_ADD( n, 28 ) ) ();
BOOST_PP_REPEAT( 23, PROBLEM, ~)
#undef PROBLEM

}
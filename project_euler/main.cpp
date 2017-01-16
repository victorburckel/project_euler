#include "level1.h"
#include "level2.h"
#include <iostream>

void main()
{
#define PROBLEM( i ) std::cout << "problem" #i ": " << euler::problem ## i() << std::endl;
	PROBLEM( 40 );
#undef PROBLEM
}
#include "problems.h"
#include <iostream>

void problem5()
{

}

void main()
{
#define PROBLEM( i ) std::cout << "problem" #i ": " << euler::problem ## i() << std::endl;
	PROBLEM( 19 );
#undef PROBLEM
}
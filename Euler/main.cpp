#include "problems.h"
#include <iostream>

void problem5()
{

}

void main()
{
#define PROBLEM( i ) std::cout << "problem" #i ": " << problem ## i() << std::endl;
	PROBLEM( 1 );
	PROBLEM( 2 );
	PROBLEM( 3 );
	PROBLEM( 4 );
#undef PROBLEM
}
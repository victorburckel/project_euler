#include "level1.h"
#include "level2.h"
#include <iostream>

void problem5()
{

}

void main()
{
#define PROBLEM( i ) std::cout << "problem" #i ": " << euler::problem ## i() << std::endl;
	PROBLEM( 27 );
#undef PROBLEM
}
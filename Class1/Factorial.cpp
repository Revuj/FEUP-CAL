/*
 * Factorial.cpp
 */

#include "Factorial.h"

//Space Complexity: O(n)
//Time Complexity: O(n)
int factorialRecurs(int n)
{
    if(n > 1)
        return n * factorialRecurs(n - 1);
    else
        return 1;
}

//Space Complexity: O(1)
//Time Complexity: O(n)
int factorialDinam(int n)
{
	int factorial(1);

	while (n != 1) {
		factorial *= n;
		n--;
	}
	return factorial;
}

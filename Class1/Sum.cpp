/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>
#include <algorithm>
#include <sstream>
#include <string>

string minSum(int* sequence, int size, int k) {

	int res = 0;
	int index = 0;

	for (int i = 0; i < k; i++) {
		res += sequence[i];
	}

	int sumK = res;

	for (int i = k; i < size; i++) {
		sumK += sequence[i] - sequence[i - k];
		if (sumK < res) {
			res = sumK;
			index = i - k + 1;
		}
	}

	ostringstream out;

	out << res << "," << index << ";";
	return out.str();
}


string calcSum(int* sequence, int size)
{
	ostringstream out;

	for (int i =1; i <= size; i++) {
		out << minSum(sequence, size, i);
	}

	cout << out.str() << endl;
	return out.str();
}


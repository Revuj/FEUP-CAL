/*
 * Change.cpp
 */

#include "Change.h"
#include <iostream>
#include <sstream>
#include <iomanip>

string calcChange(int m, int numCoins, int *coinValues)
{
	if (m  == 0)
		return "";

	int lastCoin[m + 1] = {0};
	int minCoins[m + 1] = {0};

	for (int i = 0; i < numCoins; i++) {
		for (int k = coinValues[i]; k <= m; k++) {
			if (1 + minCoins[k - coinValues[i]] < minCoins[k] || i == 0) {
				minCoins[k] = 1 + minCoins[k - coinValues[i]];
				lastCoin[k] = coinValues[i];
			}
		}
	}

	if (lastCoin[m] == 0)
		return "-";

	ostringstream out;

	for (int i = m; i > 0; i -= lastCoin[i]) {
		out << lastCoin[i] << ";";
	}

	cout << out.str() << endl;

	return out.str();
}



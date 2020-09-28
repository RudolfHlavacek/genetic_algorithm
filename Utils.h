#ifndef UTILS_H
#define UTILS_H

#include <set>

// returns 0 - 0.999
double randomDouble();

// returns true with a probability
bool randomProbability(double probability);

double precision(int low, int high, int numberOfBits);

std::set<int> randomDistinctNumbers(int upperLimit, int howManyNumbers);

#endif // UTILS_H

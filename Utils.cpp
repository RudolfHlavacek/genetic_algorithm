#include "Utils.h"
#include <cstdlib>
#include <stdexcept>
#include <set>
#include <math.h>

double randomDouble()
{
    return double(rand() % 1000) / 1000; // 0 - 0.999
}

//bool b = randomProbability(0.7) --> 70% true, 30% false
bool randomProbability(double probability)
{
    if (probability < 0 || probability > 1)
    {
        throw std::runtime_error("Probability should be between 0 and 1");
    }
    double r = randomDouble();
    if (r < probability)
    {
        return true;
    }
    else
    {
        return false;
    }
}

double precision(int low, int high, int numberOfBits)
{
    double prec = (double)(high - low) / (double)(pow(2, numberOfBits) - 1);
    return prec;
}

// randomDistinctNumbers(7, 3);
// returns 3 numbers 0-6
std::set<int> randomDistinctNumbers(int upperLimit, int howManyNumbers)
{
    std::set<int> numbers;
    while (numbers.size() < howManyNumbers)
    {
        numbers.insert(rand() % upperLimit);
    }
    return numbers;
}













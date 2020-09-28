#include <iostream>
#include "GeneticAlgorithm.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    const int populationSize = 100;
    const int generations = 10;
    const int bits = 8;
    const int low = 0;
    const int high = 4;
    const int tournamentGroupSize = 3;
    const double crossoverProbability = 0.7;
    const double mutationProbability = 0.01;

    GeneticAlgorithm ga(populationSize, generations,
                        tournamentGroupSize, crossoverProbability,
                        mutationProbability);
    Solution bestSolution = ga.run(bits, low, high);

    std::cout << "Best solution = " << bestSolution.toString() << std::endl;

    return 0;
}

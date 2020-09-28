#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include "Solution.h"

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(int populationSize,
                     int generations,
                     int tournamentGroupSize,
                     double crossoverProbability,
                     double mutationProbability);
    virtual ~GeneticAlgorithm();
    Solution run(int numberOfBits, int low, int high);
private:
    Solution tournamentWinner(std::vector<Solution> const &currentGeneration);
    std::vector<Solution> tournamentCrossover(std::vector<Solution> const &currentGeneration);
private:
    int m_populationSize;
    int m_generations;
    int m_tournamentGroupSize;
    double m_crossoverProbability;
    double m_mutationProbability;
};

#endif // GENETIC_ALGORITHM_H

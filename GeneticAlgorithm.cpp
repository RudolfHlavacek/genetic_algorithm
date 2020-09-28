#include "GeneticAlgorithm.h"
#include "Utils.h"
#include <iostream>
#include <ctime>
#include <set>

GeneticAlgorithm::GeneticAlgorithm(int populationSize, int generations,
                                   int tournamentGroupSize,
                                   double crossoverProbability,
                                   double mutationProbability) :
    m_populationSize(populationSize),
    m_generations(generations),
    m_tournamentGroupSize(tournamentGroupSize),
    m_crossoverProbability(crossoverProbability),
    m_mutationProbability(mutationProbability)
{
    //ctor
}

GeneticAlgorithm::~GeneticAlgorithm()
{
    //dtor
}

Solution GeneticAlgorithm::run(int numberOfBits, int low, int high)
{
    Solution best(numberOfBits, low, high);
    srand(time(NULL));
    // 1st generation
    std::vector<Solution> currentGeneration;

    for (int i = 0; i < m_populationSize; i++)
    {
        currentGeneration.push_back(Solution(numberOfBits, low, high));
    }

    std::cout << "First generation" << std::endl;
    for (Solution s: currentGeneration)
    {
        std::cout << s.toString() << std::endl;
    }

    for (int i = 0; i < m_generations; i++)
    {
        std::vector<Solution> crossedSolutions = tournamentCrossover(currentGeneration);
        std::cout << "Crossed generation" << std::endl;
        for (Solution s: crossedSolutions)
        {
//            std::cout << s.toString() << std::endl;
            s.mutate(m_mutationProbability);
        }

        currentGeneration = crossedSolutions;
    }

    double maxFitness = currentGeneration[0].fitness();
    best = currentGeneration[0];
    for(int i = 0; i < m_populationSize; i++)
    {
        double fitness = currentGeneration[i].fitness();
        if(fitness > maxFitness)
        {
            maxFitness = fitness;;
            best = currentGeneration[i];
        }
    }

    return best;
}

Solution GeneticAlgorithm::tournamentWinner(std::vector<Solution> const &currentGeneration)
{
    std::vector<Solution> candidates;

    std::set<int> randomNumbers = randomDistinctNumbers(m_populationSize, m_tournamentGroupSize);
    for (int rn: randomNumbers)
    {
        candidates.push_back(currentGeneration[rn]);
    }

    Solution bestCandidate = candidates[0];
    double maxFitness = candidates[0].fitness();
    for (Solution s: candidates)
    {
        double fitness = s.fitness();
        if (fitness > maxFitness)
        {
            maxFitness = fitness;
            bestCandidate = s;
        }
    }

    return bestCandidate;
}

std::vector<Solution> GeneticAlgorithm::tournamentCrossover(std::vector<Solution> const &currentGeneration)
{
    std::vector<Solution> newSolutions;
    while (newSolutions.size() < m_populationSize)
    {
        Solution winner1 = tournamentWinner(currentGeneration);
        Solution winner2 = tournamentWinner(currentGeneration);
        std::cout << "Crossing the winners: " << winner1.toString() << " & " << winner2.toString() << std::endl;

        // perform single point crossover
        std::vector<Solution> children = winner1.singlePointCrossover(winner2, m_crossoverProbability);
        newSolutions.push_back(children[0]);
        newSolutions.push_back(children[1]);

        std::cout << "Children            : " << winner1.toString() << " & " << winner2.toString() << std::endl;
    }
    return newSolutions;
}

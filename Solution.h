#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <string>

class Solution
{
public:
    Solution(int numberOfBits, int low, int high);
    Solution(int numberOfBits, int low, int high, std::vector<int> bits);
    std::vector<Solution> singlePointCrossover(Solution other, double crossoverProbability);
    virtual ~Solution();
    std::string toString() const;
    double fitness() const;
    void mutate(double mutationProbability);
private:
    int m_numberOfBits;
    int m_low;
    int m_high;
    std::vector<int> m_bits; // chromosomes
private:
    double bitsToDouble() const;
};

#endif // SOLUTION_H

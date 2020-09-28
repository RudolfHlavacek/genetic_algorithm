#include "Solution.h"
#include <sstream>
#include "Utils.h"
#include <math.h>
#include <iostream>

Solution::Solution(int numberOfBits, int low, int high) :
    m_numberOfBits(numberOfBits), m_low(low), m_high(high)
{
    m_bits.reserve(m_numberOfBits); // avoid reallocating (optional)
    for (int i = 0; i < m_numberOfBits; i++)
    {
        m_bits.push_back(rand() % 2); // 0 - 1
    }
}

Solution::Solution(int numberOfBits, int low, int high, std::vector<int> bits) :
    m_numberOfBits(numberOfBits),
    m_low(low),
    m_high(high),
    m_bits(bits)
{

}

Solution::~Solution()
{
    //dtor
}

std::string Solution::toString() const
{
    std::ostringstream stream;
    stream << "[";
    for (int bit : m_bits)
    {
        stream << bit << " ";
    }
    stream << "] double = " << bitsToDouble() << " fitness = " << fitness();

    return stream.str();
}

double Solution::bitsToDouble() const
{
    double prec = precision(m_low, m_high, m_numberOfBits);
    int dec = 0;
    for (int i = 0; i < m_numberOfBits; i++)
    {
        dec += pow(2, i) * m_bits[i];
    }
    return dec*prec + m_low;
}

// f(x) = x + 2 * sin(x)
// in interval from 0 (low) to 4 (high)
double Solution::fitness() const
{
    double x = bitsToDouble();
    return x + 3 * sin(x);
}

std::vector<Solution> Solution::singlePointCrossover(Solution other,
                                                     double crossoverProbability)
{
    bool cross = randomProbability(crossoverProbability);
    std::cout << "Cross? " << cross << std::endl;
    if(cross)
    {
        int crossPoint = rand() % m_numberOfBits;
        std::cout << "cross point: " << crossPoint << std::endl;

        std::vector<Solution> children;

        std::vector<int> bits1;
        std::vector<int> bits2;

        std::copy(this->m_bits.begin(), this->m_bits.begin() + crossPoint, std::back_inserter(bits1));
        std::copy(other.m_bits.begin() + crossPoint, other.m_bits.end(), std::back_inserter(bits1));

        std::copy(other.m_bits.begin(), other.m_bits.begin() + crossPoint, std::back_inserter(bits2));
        std::copy(this->m_bits.begin() + crossPoint, this->m_bits.end(), std::back_inserter(bits2));

        Solution child1(m_numberOfBits, m_low, m_high, bits1);
        Solution child2(m_numberOfBits, m_low, m_high, bits2);
        std::cout << child1.toString() << std::endl;
        std::cout << child2.toString() << std::endl;

        return { child1, child2 };
    }
    else
    {
        return { *this, other };
    }
}

void Solution::mutate(double mutationProbability)
{
//    std::cout << "\nBefore mutation: " << this->toString() << std::endl;
    for (int i = 0; i < m_numberOfBits; i++)
    {
        bool mutateBool = randomProbability(mutationProbability);
        if (mutateBool)
        {
            m_bits[i] = 1 - m_bits[i]; // flips a bit
//            std::cout << "[Mutated]" << std::endl;
        }
    }

//    std::cout << "After mutation:  " << this->toString() << std::endl;
}





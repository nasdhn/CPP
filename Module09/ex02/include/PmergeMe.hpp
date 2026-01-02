#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <limits.h>
#include <exception>
#include <algorithm>
#include <sstream>
#include <ctime>

class PmergeMe {

public :
        PmergeMe();
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        std::deque<int> getTabDeque();
        std::vector<int> getTabVect();

        void parseInput(int ac, char **av);
        void vectSort();
        void dequSort();

    private :
        std::deque<int> _tabDeque;
        std::vector<int> _tabVect;

        bool isNumber(std::string &input);
        void sort2Nbr(int &a, int &b);

        unsigned int Jacobsthal(unsigned int n);
        std::vector<int> generateJacobsthalSequence(size_t n);

        // vect
        bool vectIsSorted(std::vector<int> &vTab);
        int binaryInsertion(int &value, std::vector<int> &vTab);
        std::vector<int> sortVectRecursive(std::vector<int> &currentTab);

        // deque
        bool dequeIsSorted(std::deque<int> &vTab); 
        int binaryInsertionD(int &value, std::deque<int> &dTab);
        std::deque<int>  sortDequeRecursive(std::deque<int> &currentTab);
};

#endif
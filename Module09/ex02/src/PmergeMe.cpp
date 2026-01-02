#include "../include/PmergeMe.hpp"

PmergeMe::PmergeMe()
{

}

PmergeMe::PmergeMe(const PmergeMe& other)
{
    _tabDeque = other._tabDeque;
    _tabVect = other._tabVect;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        _tabDeque = other._tabDeque;
        _tabVect = other._tabVect;
    }
    return (*this);
}

PmergeMe::~PmergeMe()
{

}

std::deque<int> PmergeMe::getTabDeque()
{
    return _tabDeque;
}
        
std::vector<int> PmergeMe::getTabVect()
{
    return _tabVect;
}

bool PmergeMe::isNumber(std::string &input)
{
    std::string max = "2147483647";
    if (input.empty())
        return false;

    for (unsigned int i = 0; i < input.length(); ++i)
    {
        if (!isdigit(input[i]))
            return false;
    }
    if (input.length() > 10)
        return false;
    if (input.length() == 10)
    {
        for (int idx = 0; idx < 10; idx++)
        {
            if (input[idx] > max[idx])
                return false;
            else if (input[idx] < max[idx])
                break ;
        }
    }
    return true;
}

void PmergeMe::parseInput(int ac, char **av)
{
    for (int i = 1; i < ac; i++)
    {
        std::string arg = av[i];

        if (isNumber(arg) == false)
        {
            std::cerr << "Error: Invalid number => " << arg << std::endl;
            exit(1);
        }
        std::istringstream iss(arg);

        long value;
        iss >> value;

        if (value < 0 || value > INT_MAX)
        {
            std::cerr << "Error: Bad range => " << arg << std::endl;
            exit(1);
        }

        _tabDeque.push_back(static_cast<int>(value));
        _tabVect.push_back(static_cast<int>(value));
    }
    std::cout << "Before: ";
    for (unsigned int i = 0; i < _tabVect.size(); i++)
        std::cout << _tabVect[i] << " ";
}

void PmergeMe::sort2Nbr(int &a, int &b)
{
    int tmp;
    if (a > b)
    {
        tmp = a;
        a = b;
        b = tmp;
    }
}

unsigned int PmergeMe::Jacobsthal(unsigned int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    return (Jacobsthal(n - 1) + 2 * Jacobsthal(n - 2));
}

std::vector<int> PmergeMe::generateJacobsthalSequence(size_t n)
{
    std::vector<int> jacobSeq;
    if (n == 0)
        return jacobSeq;

    jacobSeq.push_back(0);

    size_t jacobIndex = 3;
    size_t lastValue = 1;

    while (true)
    {
        size_t nextValue = Jacobsthal(jacobIndex);
        size_t limit;
        
        if (nextValue > n)
            limit = n;
        else
            limit = nextValue;

        for (size_t i = limit; i > lastValue; i--)
        {
            jacobSeq.push_back(i - 1);
        }

        if (nextValue >= n)
            break;
        
        lastValue = nextValue;
        jacobIndex++;
    }
    return jacobSeq;
}

bool PmergeMe::vectIsSorted(std::vector<int> &vTab)
{
    for (unsigned int i = 0; i < vTab.size() - 1; i++)
    {
        if (vTab[i] > vTab[i + 1])
            return false;
    }
    return true;
}

int PmergeMe::binaryInsertion(int &value, std::vector<int> &vTab)
{
    int left = 0;
    int right = vTab.size();
    int mid;

    while (left < right)
    {
        mid = (left + right) / 2;

        if (vTab[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

std::vector<int> PmergeMe::sortVectRecursive(std::vector<int> &currentTab)
{
    if (currentTab.size() <= 1)
        return currentTab;

    std::vector<int> lead;
    std::vector<int> insert;
    int impair = 0;
    bool oldnbr = false;

    if (currentTab.size() % 2 != 0)
    {   
        impair = currentTab.back();
        oldnbr = true;
        currentTab.pop_back();
    }

    for (unsigned int i = 0; i < currentTab.size(); i = i + 2)
    {
        if (currentTab[i] > currentTab[i + 1])
        {   
            lead.push_back(currentTab[i]);
            insert.push_back(currentTab[i + 1]);
        }
        else
        {               
            lead.push_back(currentTab[i + 1]);
            insert.push_back(currentTab[i]);
        }
    }

    lead = sortVectRecursive(lead);

    std::vector<int> jacobIndices = generateJacobsthalSequence(insert.size());

    for (unsigned int i = 0; i < jacobIndices.size(); i++)
    {
        int idx = jacobIndices[i];
        int val = insert[idx];
        
        int pos = binaryInsertion(val, lead);
        lead.insert(lead.begin() + pos, val);
    }

    if (oldnbr)
    {   
        int pos = binaryInsertion(impair, lead);
        lead.insert(lead.begin() + pos, impair);
    }

    return lead;
}

void PmergeMe::vectSort()
{
    int start = clock();

    _tabVect = sortVectRecursive(_tabVect);

    int stop = clock() - start;

    // Affichage résultat
    std::cout << std::endl << "After: ";
    for (unsigned int i = 0; i < _tabVect.size(); i++)
        std::cout << _tabVect[i] << " ";

    if (vectIsSorted(_tabVect) == false)
    {
        std::cout << "Error: Problem with the sort" << std::endl;
        return ;
    }

    double duration = (double)stop * 1000.0 / CLOCKS_PER_SEC;
    std::cout << std::endl << "Time to process a range of  " << _tabVect.size() 
              << " elements with std::vector<int> : " << duration << " ms" << std::endl;
}

bool PmergeMe::dequeIsSorted(std::deque<int> &vTab)
{
    for (unsigned int i = 0; i < vTab.size() - 1; i++)
    {
        if (vTab[i] > vTab[i + 1])
            return false;
    }
    return true;
}

int PmergeMe::binaryInsertionD(int &value, std::deque<int> &dTab)
{
    int left = 0;
    int right = dTab.size();
    int mid;

    while (left < right)
    {
        mid = (left + right) / 2;

        if (dTab[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

std::deque<int> PmergeMe::sortDequeRecursive(std::deque<int> &currentTab)
{
    if (currentTab.size() <= 1)
        return currentTab;

    std::deque<int> lead;
    std::deque<int> insert;
    int impair = 0;
    bool oldnbr = false;

    if (currentTab.size() % 2 != 0)
    {   
        impair = currentTab.back();
        oldnbr = true;
        currentTab.pop_back();
    }

    for (unsigned int i = 0; i < currentTab.size(); i = i + 2)
    {
        if (currentTab[i] > currentTab[i + 1])
        {   
            lead.push_back(currentTab[i]);
            insert.push_back(currentTab[i + 1]);
        }
        else
        {               
            lead.push_back(currentTab[i + 1]);
            insert.push_back(currentTab[i]);
        }
    }

    lead = sortDequeRecursive(lead);

    std::vector<int> jacobIndices = generateJacobsthalSequence(insert.size());

    for (unsigned int i = 0; i < jacobIndices.size(); i++)
    {
        int idx = jacobIndices[i];
        int val = insert[idx];
        
        int pos = binaryInsertionD(val, lead);
        lead.insert(lead.begin() + pos, val);
    }

    if (oldnbr)
    {   
        int pos = binaryInsertionD(impair, lead);
        lead.insert(lead.begin() + pos, impair);
    }

    return lead;
}

void PmergeMe::dequSort()
{
    int start = clock();

    _tabDeque = sortDequeRecursive(_tabDeque);

    int stop = clock() - start;

    if (dequeIsSorted(_tabDeque) == false)
    {
        std::cout << "Error: Problem with the sort" << std::endl;
        return ;
    }    
    double duration = (double)stop * 1000.0 / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of  " << _tabDeque.size() 
              << " elements with std::deque<int> : " << duration << " ms" << std::endl;
}
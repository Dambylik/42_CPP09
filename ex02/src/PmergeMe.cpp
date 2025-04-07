// PmergeMe.cpp (Refactored for C++98)

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(PmergeMe const &src) : _vector(src._vector), _deque(src._deque) {}
PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(PmergeMe const &other)
{
    if (this != &other)
    {
        this->_vector = other._vector;
        this->_deque = other._deque;
    }
    return *this;
}

void PmergeMe::checkInput(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string input = argv[i];
        for (size_t j = 0; j < input.length(); ++j)
        {
            if (!isdigit(input[j]))
                throw WrongInputException();
        }
        double val = atof(argv[i]);
        if (val < 0 || val > INT_MAX)
            throw WrongInputException();
    }
}

void PmergeMe::fillVector(int argc, char **argv)
{
    std::cout << "DEBUG: Filling vector with values:"; 
    for (int i = 1; i < argc; ++i) {
        int val = atoi(argv[i]);
        std::cout << " " << val; 
        _vector.push_back(val);
    }
    std::cout << std::endl;
}


void PmergeMe::fillDeque(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i)
        _deque.push_back(atoi(argv[i]));
}

void PmergeMe::printBefore(void)
{
    std::cout << "\nBefore: ";
    for (size_t i = 0; i < _vector.size(); ++i)
        std::cout << _vector[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::printAfter(void)
{
   
    std::cout << "\nAfter: ";
    for (size_t i = 0; i < _vector.size(); ++i)
        std::cout << _vector[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::printTime(int containerType, double time)
{
    std::string container = (containerType == VECTOR) ? "vector" : "deque";
    std::cout << "\nTime to process elements with std::" << container
              << " : " << std::fixed << std::setprecision(4)
              << time << "ms." << std::endl;
}

void PmergeMe::setVector(vector_t vector)
{
    _vector = vector;
}

void PmergeMe::setDeque(deque_t deque)
{
    _deque = deque;
}

const vector_t &PmergeMe::getVector(void) const { return _vector; }
const deque_t &PmergeMe::getDeque(void) const { return _deque; }

vector_t PmergeMe::mergeInsertionSortVector(vector_t input)
{
    std::cout << "DEBUG: mergeInsertionSortVector called with input size = " << input.size() << std::endl; // ←
    vector_t sorted;
    for (size_t i = 0; i < input.size(); ++i)
        binaryInsertVector(sorted, input[i]);
    std::cout << "DEBUG: Sorted size = " << sorted.size() << std::endl;
    return sorted;
}



void PmergeMe::binaryInsertVector(vector_t sorted, int value)
{
    if (sorted.empty())
    {
        sorted.push_back(value);
        return;
    }

    size_t low = 0, high = sorted.size();
    while (low < high)
    {
        size_t mid = (low + high) / 2;
        if (value < sorted[mid])
            high = mid;
        else
            low = mid + 1;
    }
    sorted.insert(sorted.begin() + low, value);
}



deque_t PmergeMe::mergeInsertionSortDeque(deque_t input)
{
    deque_t sorted;
    for (size_t i = 0; i < input.size(); ++i)
        binaryInsertDeque(sorted, input[i]);
    return sorted;
}

void PmergeMe::binaryInsertDeque(deque_t sorted, int value)
{
    size_t low = 0, high = sorted.size();
    while (low < high)
    {
        size_t mid = (low + high) / 2;
        if (value < sorted[mid])
            high = mid;
        else
            low = mid + 1;
    }
    sorted.insert(sorted.begin() + low, value);
}

double getTime(void)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1)
        throw ErrorTimeException();
    return (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0);
}

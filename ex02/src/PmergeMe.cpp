/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:52:29 by okapshai          #+#    #+#             */
/*   Updated: 2025/04/07 17:33:32 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(PmergeMe const &src) : _vector(src._vector), _deque(src._deque) {}
PmergeMe::~PmergeMe() {}

PmergeMe & PmergeMe::operator=( PmergeMe const & other ) {

    this->_deque = other._deque;
    this->_vector = other._vector;
    return (*this);
}

void PmergeMe::setDeque( deque_t deque ) { this->_deque = deque; }

void PmergeMe::setVector( vector_t vector ) { this->_vector = vector; }

deque_t const &	PmergeMe::getDeque( void ) const { return (this->_deque); }

vector_t const & PmergeMe::getVector( void ) const { return (this->_vector); }


// -------------------------------------------------------------------- Methods


void PmergeMe::checkInput( int argc, char **argv ) {

	for (int i = 1; i < argc; i++) {

		std::string input = argv[i];
		for (int j = 0; j < (int)input.size(); j++) {
			if (isdigit(input[j]) == 0)
				throw(WrongInputException());
		}

		double dbl = atof(argv[i]); // Converts to double (atof) and ensures it's in range (0 <= num <= INT_MAX).
		if (dbl < 0 || dbl > __INT_MAX__)
			throw(WrongInputException());
	}
}

void PmergeMe::fillDeque(int argc, char **argv) {

	for (int i = 1; i < argc; i++)
		this->_deque.push_back(atoi(argv[i]));
}

void PmergeMe::fillVector(int argc, char **argv) {

	for (int i = 1; i < argc; i++)
		this->_vector.push_back(atoi(argv[i]));
}

void PmergeMe::printBefore(void) {

	std::cout << "\n" << "Before: ";

	for (int i = 0; i < (int)this->_vector.size(); i++)
		std::cout << this->_vector[i] << " ";

	std::cout << std::endl;
}

void PmergeMe::printAfter(void) {

	std::cout << "\n" << "After: ";

	for (int i = 0; i < (int)this->_vector.size(); i++)
		std::cout << this->_vector[i] << " ";

	std::cout << std::endl;
}

// Divide: Splits the array into two halves (cutAndSort()).
deque_t	PmergeMe::cutAndSort(deque_t deque) {

    //Initialization of two empty deque_t objects, dequeOne and dequeTwo:
    //These are used to hold the two halves of the original deque.
	deque_t	dequeOne;
	deque_t	dequeTwo;

    //Base Case Check: If the size of the input deque is less than 2,
    //the function returns the deque as is, because a deque of size 0 or 1 is already "sorted."
	if (deque.size() < 2)
		return (deque);

    //The first loop iterates from the start of the deque up to (but not including)
    //the halfway point, pushing each element into dequeOne.
	for (int i = 0; i < (int)(deque.size() / 2); i++)
		dequeOne.push_back(deque[i]);

    //The second loop starts from the halfway point to the end of the deque, pushing each element into dequeTwo.
	for (int i = (int)(deque.size() / 2); i < (int)deque.size(); i++)
		dequeTwo.push_back(deque[i]);

    //Recursive Calls: Both dequeOne and dequeTwo are then passed to recursive calls of cutAndSort,
    //which continues to split and sort each half until the base case is reached.
	dequeOne = cutAndSort(dequeOne);
	dequeTwo = cutAndSort(dequeTwo);

    //Merging: Once the base case is reached for all recursive calls,
    //the mergeSort function is used to merge dequeOne and dequeTwo back together in a sorted manner.
    //This step is crucial and where the actual sorting happens.
    //Each level of recursion will merge its two halves in a sorted order,
    //building up to the final, sorted deque.

    //Return Statement: The function returns the result of the mergeSort call,
    //which should be the sorted version of the original input deque.
	return (mergeSort(dequeOne,dequeTwo));
}

vector_t PmergeMe::cutAndSort(vector_t vector)
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

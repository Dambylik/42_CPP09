/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:52:29 by okapshai          #+#    #+#             */
/*   Updated: 2025/03/28 12:57:32 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe( PmergeMe const & src ) : _deque(src._deque), _vector(src._vector) {}

PmergeMe::~PmergeMe() {}

PmergeMe& PmergeMe::operator=( PmergeMe const & other ) {

    this->_deque = other._deque;
    this->_vector = other._vector;
    return (*this);
}

// -------------------------------------------------------------------- Methods

void PmergeMe::checkInput( int argc, char **argv ) {

	for (int i = 1; i < argc; i++) {

		std::string input = argv[i];

		for (int j = 0; j < (int)input.size(); j++) {
			if (isdigit(input[j]) == 0)
				throw(WrongInputException());
		}

		double dbl = atof(argv[i]);
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
	vector_t vectorOne;
	vector_t vectorTwo;

	if (vector.size() < 2)
		return (vector);

	for (int i = 0; i < (int)(vector.size() / 2); i++)
		vectorOne.push_back(vector[i]);

	for (int i = (int)(vector.size() / 2); i < (int)vector.size(); i++)
		vectorTwo.push_back(vector[i]);

	vectorOne = cutAndSort(vectorOne);
	vectorTwo = cutAndSort(vectorTwo);

	return (mergeSort(vectorOne,vectorTwo));
}

deque_t	PmergeMe::mergeSort(deque_t dequeOne, deque_t dequeTwo) {

    //Initialization of dequeThree: This is an empty deque_t object that will eventually
    //contain the sorted elements from both dequeOne and dequeTwo.
	deque_t	dequeThree;

    //The function enters a while loop that continues as long as
    //both dequeOne and dequeTwo are not empty. Within this loop,
    //it compares the front elements of both deques.
	while (dequeOne.empty() != true && dequeTwo.empty() != true) {

        //If the front element of dequeOne is less than the front element of dequeTwo,
        //that element is moved from dequeOne to dequeThree, and then removed from dequeOne.
		if (dequeOne[0] < dequeTwo[0]) {
			dequeThree.push_back(dequeOne[0]);
			dequeOne.erase(dequeOne.begin());
		}

        //If the front element of dequeTwo is less than or equal
        //to the front element of dequeOne, that element is moved
        //from dequeTwo to dequeThree, and then removed from dequeTwo.
		else {
			dequeThree.push_back(dequeTwo[0]);
			dequeTwo.erase(dequeTwo.begin());
		}
	}
	
    //Two additional while loops ensure that any remaining elements
    //in dequeOne or dequeTwo are moved to dequeThree.
    //This is necessary because, after the first while loop,
    //at least one of the deques will be empty, but the other might still have elements
    //that are already sorted and just need to be appended to dequeThree.
	while (dequeOne.empty() != true) {
		dequeThree.push_back(dequeOne[0]);
		dequeOne.erase(dequeOne.begin());
	}

	while (dequeTwo.empty() != true) {
			dequeThree.push_back(dequeTwo[0]);
			dequeTwo.erase(dequeTwo.begin());
	}

    // Returning the Merged dequeThree: Once both dequeOne and dequeTwo are completely
    // empty, the function returns dequeThree, which now contains all elements
    // from the original two deques in a sorted order.
	return (dequeThree);
}

vector_t PmergeMe::mergeSort(vector_t vectorOne, vector_t vectorTwo) {

	vector_t vectorThree;

	while (vectorOne.empty() != true && vectorTwo.empty() != true) {

		if (vectorOne[0] < vectorTwo[0]) {
			vectorThree.push_back(vectorOne[0]);
			vectorOne.erase(vectorOne.begin());
		}

		else {
			vectorThree.push_back(vectorTwo[0]);
			vectorTwo.erase(vectorTwo.begin());
		}
	}
	
	while (vectorOne.empty() != true) {
		vectorThree.push_back(vectorOne[0]);
		vectorOne.erase(vectorOne.begin());
	}

	while (vectorTwo.empty() != true) {
        vectorThree.push_back(vectorTwo[0]);
        vectorTwo.erase(vectorTwo.begin());
	}

	return (vectorThree);
}

double getTime(void) {

	struct timeval	tv;
	double milisecondes;
	double secondes;
	double time;

    // fill the 'tv' struct with the current time
	if (gettimeofday(&tv, NULL) == -1)
		throw(ErrorTimeException());

    // calculate milisecondes / tv_usec = nb of microseconds since Epoch
	milisecondes = (double)tv.tv_usec / 1000;

    // calculate secondes / tv_sec = nb of seconds since Epoch
	secondes = (double)tv.tv_sec * 0.001;

    // combining seconds && milisecondes
	time = secondes + milisecondes;

	return (time);
}

void PmergeMe::printTime(int containerType, double time) {

	std::string container = "deque";

	if (containerType == VECTOR)
		container = "vector";

    std::cout << "\n";
	std::cout << "Time to process elements with std::" << container << " : " << std::fixed << std::setprecision(4) << time << "ms.\n";
}


// -------------------------------------------------------------------- Setters
void PmergeMe::setDeque(deque_t deque) {
	this->_deque = deque;
}

void PmergeMe::setVector(vector_t vector) {
	this->_vector = vector;
}

// -------------------------------------------------------------------- Getters
deque_t const&	PmergeMe::getDeque(void) const {
	return (this->_deque);
}

vector_t const& PmergeMe::getVector(void) const {
	return (this->_vector);
}
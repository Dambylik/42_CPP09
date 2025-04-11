/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olly <olly@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:01:28 by olly              #+#    #+#             */
/*   Updated: 2025/04/11 14:41:31 by olly             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe( PmergeMe const & other ) : _vector(other._vector), _deque(other._deque) {}

PmergeMe & PmergeMe::operator=( PmergeMe const & other ) {
    if (this != &other)
    {
        this->_vector = other._vector;
        this->_deque = other._deque;
    }
    return (*this);
}

void PmergeMe::setVector( vector_t vector ) { _vector = vector;}
void PmergeMe::setDeque( deque_t deque ) { _deque = deque;}
const vector_t & PmergeMe::getVector( void ) const { return _vector; }
const deque_t & PmergeMe::getDeque( void ) const { return _deque; }

PmergeMe::~PmergeMe() {}

//-------------------------------------------------------------------Methods

void PmergeMe::checkInput( int argc, char **argv ) {
    for (int i = 1; i < argc; ++i) {
        std::string input = argv[i];
        for (size_t j = 0; j < input.length(); ++j){
            if (!isdigit(input[j]))
                throw WrongInputException();
        }
        double val = atof(argv[i]);
        if (val < 0 || val > INT_MAX)
            throw WrongInputException();
    }
}

void PmergeMe::fillVector( int argc, char **argv ) {
    for (int i = 1; i < argc; ++i)
        _vector.push_back(atoi(argv[i]));
}

void PmergeMe::fillDeque( int argc, char **argv ) {
    for (int i = 1; i < argc; ++i)
        _deque.push_back(atoi(argv[i]));
}

void PmergeMe::printBefore( void ) {
    std::cout << FYEL("\nBefore: ");
    for (size_t i = 0; i < _vector.size(); ++i)
        std::cout << _vector[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::printAfter( void ) {
    std::cout << FYEL("\nAfter: ");
    for (size_t i = 0; i < _vector.size(); ++i)
        std::cout << _vector[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::printTime( int containerType, double time ) {
    std::string container = (containerType == VECTOR) ? "vector" : "deque";
    std::cout << FYEL("\nTime to process elements with std::") << FYEL(container)
              << " : " << std::fixed << std::setprecision(4)
              << time << "ms." << std::endl;
}

vector_t PmergeMe::mergeInsertionSortVector(vector_t input) {
    if (input.size() <= 1)
        return input;
        
    // Handle odd size input case
    int straggler = -1;
    if (input.size() % 2 != 0) {
        straggler = input.back();
        input.pop_back();
    }
    
    // Step 1: Create pairs and sort them
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < input.size(); i += 2) {
        if (input[i] > input[i + 1])
            pairs.push_back(std::make_pair(input[i], input[i + 1]));
        else
            pairs.push_back(std::make_pair(input[i + 1], input[i]));
    }
    
    // Step 2: Extract the larger elements
    vector_t largerElements;
    for (size_t i = 0; i < pairs.size(); ++i)
        largerElements.push_back(pairs[i].first);
    
    // Step 3: Recursively sort the larger elements
    largerElements = mergeInsertionSortVector(largerElements);
    
    // Step 4: Create the sorted main chain with large elements
    vector_t result;
    for (size_t i = 0; i < largerElements.size(); ++i)
        result.push_back(largerElements[i]);
        
    // Step 5: Insert smaller elements using binary insertion
    for (size_t i = 0; i < pairs.size(); ++i) {
        // Find the index of the larger element in the result
        size_t idx = 0;
        while (idx < result.size() && result[idx] != pairs[i].first)
            idx++;
            
        // Insert the smaller element using binary insertion
        if (idx < result.size()) {
            // Binary insert the smaller element
            size_t insertPos = 0;
            size_t low = 0;
            size_t high = result.size();
            
            // Find insertion point
            while (low < high) {
                size_t mid = (low + high) / 2;
                if (pairs[i].second < result[mid])
                    high = mid;
                else
                    low = mid + 1;
            }
            insertPos = low;
            
            // Insert at the found position
            result.insert(result.begin() + insertPos, pairs[i].second);
        }
    }
    
    // Insert the straggler if it exists
    if (straggler != -1) {
        // Find insertion position
        size_t low = 0;
        size_t high = result.size();
        while (low < high) {
            size_t mid = (low + high) / 2;
            if (straggler < result[mid])
                high = mid;
            else
                low = mid + 1;
        }
        result.insert(result.begin() + low, straggler);
    }
        
    return result;
}

void PmergeMe::binaryInsertVector(vector_t &sorted, int value) {
    size_t low = 0;
    size_t high = sorted.size();
    while (low < high) {
        size_t mid = (low + high) / 2;
        if (value < sorted[mid])
            high = mid;
        else
            low = mid + 1;
    }
    sorted.insert(sorted.begin() + low, value);
}

deque_t PmergeMe::mergeInsertionSortDeque(deque_t input) {
    if (input.size() <= 1)
        return input;
        
    // Handle odd size input case
    int straggler = -1;
    if (input.size() % 2 != 0) {
        straggler = input.back();
        input.pop_back();
    }
    
    // Step 1: Create pairs and sort them
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < input.size(); i += 2) {
        if (input[i] > input[i + 1])
            pairs.push_back(std::make_pair(input[i], input[i + 1]));
        else
            pairs.push_back(std::make_pair(input[i + 1], input[i]));
    }
    
    // Step 2: Extract the larger elements
    deque_t largerElements;
    for (size_t i = 0; i < pairs.size(); ++i)
        largerElements.push_back(pairs[i].first);
    
    // Step 3: Recursively sort the larger elements
    largerElements = mergeInsertionSortDeque(largerElements);
    
    // Step 4: Create the sorted main chain with large elements
    deque_t result;
    for (size_t i = 0; i < largerElements.size(); ++i)
        result.push_back(largerElements[i]);
        
    // Step 5: Insert smaller elements using binary insertion
    for (size_t i = 0; i < pairs.size(); ++i) {
        // Find the index of the larger element in the result
        size_t idx = 0;
        while (idx < result.size() && result[idx] != pairs[i].first)
            idx++;
            
        // Insert the smaller element using binary insertion
        if (idx < result.size()) {
            // Binary insert the smaller element
            size_t insertPos = 0;
            size_t low = 0;
            size_t high = result.size();
            
            // Find insertion point
            while (low < high) {
                size_t mid = (low + high) / 2;
                if (pairs[i].second < result[mid])
                    high = mid;
                else
                    low = mid + 1;
            }
            insertPos = low;
            
            // Insert at the found position
            result.insert(result.begin() + insertPos, pairs[i].second);
        }
    }
    
    // Insert the straggler if it exists
    if (straggler != -1) {
        // Find insertion position
        size_t low = 0;
        size_t high = result.size();
        while (low < high) {
            size_t mid = (low + high) / 2;
            if (straggler < result[mid])
                high = mid;
            else
                low = mid + 1;
        }
        result.insert(result.begin() + low, straggler);
    }
        
    return result;
}

void PmergeMe::binaryInsertDeque(deque_t &sorted, int value) {
    size_t low = 0;
    size_t high = sorted.size();
    while (low < high) {
        size_t mid = (low + high) / 2;
        if (value < sorted[mid])
            high = mid;
        else
            low = mid + 1;
    }
    sorted.insert(sorted.begin() + low, value);
}

double getTime(void) {
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1)
        throw ErrorTimeException();
    return (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0);
}

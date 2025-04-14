/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:39:50 by olly              #+#    #+#             */
/*   Updated: 2025/04/14 11:59:38 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "Usage: ./PmergeMe <sequence of positive integers>" << std::endl;
        return (1);
    }

    PmergeMe sorter;

    try {
        sorter.checkInput(argc, argv);
        sorter.fillVector(argc, argv);
        sorter.fillDeque(argc, argv);
        sorter.printBefore();
        double start = getTime();
        
        vector_t sortedVec = sorter.mergeInsertionSortVector(sorter.getVector());
        sorter.setVector(sortedVec);
        sorter.printAfter();
        sorter.printTime(VECTOR, getTime() - start);

        start = getTime();
        deque_t sortedDeque = sorter.mergeInsertionSortDeque(sorter.getDeque());
        sorter.setDeque(sortedDeque);
        sorter.printTime(DEQUE, getTime() - start);
        return (0);
    }
    catch (std::exception & e) {
        std::cerr << FRED(e.what()) << std::endl;  
    }
    return (1);    
}

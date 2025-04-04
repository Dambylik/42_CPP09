/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:52:59 by okapshai          #+#    #+#             */
/*   Updated: 2025/04/03 16:52:15 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "PmergeMe.hpp"

// Your program implements the Merge-Insertion Sort (Ford-Johnson Algorithm) using 
// both std::vector and std::deque containers. It takes a sequence of positive integers 
// as input, sorts them using merge-insertion sort, and measures the sorting time for each container.

int	main(int argc, char **argv)
{
	if (argc < 2) {
		std::cerr << FRED("Error: Usage is ./PmergeMe <numbers>") << std::endl;
		return (1);
	}

	PmergeMe PME;
	
	try {
		
		PME.checkInput(argc, argv);
		
		double startTime = getTime();
		PME.fillVector(argc, argv);
		PME.printBefore(); // Prints the sequence before sorting.
		PME.setVector(PME.cutAndSort(PME.getVector())); // Sorts using cutAndSort() and sets the sorted vector.
		PME.printAfter(); // Prints the sorted sequence.
		PME.printTime(VECTOR, getTime() - startTime); // Calculates and prints sorting time.
	
		startTime = getTime(); // Repeats the sorting process for deque.
		PME.fillDeque(argc, argv);
		PME.setDeque(PME.cutAndSort(PME.getDeque()));
		PME.printTime(DEQUE, getTime() - startTime);
	}
	catch(const std::exception& e) {
		std::cerr << FRED("Error: ") << FRED(e.what()) << '\n';
	}
	return (0);
}
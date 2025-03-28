/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:52:59 by okapshai          #+#    #+#             */
/*   Updated: 2025/03/28 12:59:38 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	if (argc < 2) {
		std::cerr << FRED("Error: Usage is ./PmergeMe <numbers>") << std::endl;
		return (1);
	}

	try {
		PmergeMe PME;
		PME.checkInput(argc, argv);
		
		double startTime = getTime();
		PME.fillVector(argc, argv);
		PME.printBefore();
		PME.setVector(PME.cutAndSort(PME.getVector()));
		PME.printAfter();
		PME.printTime(VECTOR, getTime() - startTime);
	
		startTime = getTime();
		PME.fillDeque(argc, argv);
		PME.setDeque(PME.cutAndSort(PME.getDeque()));
		PME.printTime(DEQUE, getTime() - startTime);
	}
	catch(const std::exception& e) {
		std::cerr << FRED("Error: ") << FRED(e.what()) << '\n';
	}
	return (0);
}
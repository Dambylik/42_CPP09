/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olly <olly@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:51:02 by okapshai          #+#    #+#             */
/*   Updated: 2025/04/11 12:53:23 by olly             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "Colors.hpp"
# include "Exceptions.hpp"
# include <cstdlib>
# include <deque>
# include <iomanip>
# include <iostream>
# include <limits.h>
# include <string>
# include <sys/time.h>
# include <vector>
# define DEQUE 0
# define VECTOR 1

typedef std::vector<int> 	vector_t;
typedef std::deque<int> 	deque_t;

class PmergeMe {
	
	public:
	
		PmergeMe();
		PmergeMe( PmergeMe const & other );
		PmergeMe & operator=( PmergeMe const & other );
		~PmergeMe();

		void 				checkInput( int argc, char **argv );
		void 				fillDeque( int argc, char **argv) ;
		void 				fillVector( int argc, char **argv );
		void 				printBefore( void );
		void 				printAfter( void );
		void 				printTime( int containerType, double time );

		void 				setVector( vector_t vector );
		void 				setDeque( deque_t deque );
		vector_t const &	getVector( void ) const;
		deque_t const &		getDeque( void ) const;

		vector_t 			mergeInsertionSortVector( vector_t input );
		void 				binaryInsertVector( vector_t & sorted, int value );

		deque_t 			mergeInsertionSortDeque( deque_t input );
		void 				binaryInsertDeque( deque_t & sorted, int value );

	private:
	
		vector_t 			_vector;
		deque_t 			_deque;
};

double getTime(void);
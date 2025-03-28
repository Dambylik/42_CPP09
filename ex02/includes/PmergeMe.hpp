/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:51:02 by okapshai          #+#    #+#             */
/*   Updated: 2025/03/28 17:47:31 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Colors.hpp"
#include "Exceptions.hpp"
# include <cstdlib>
# include <deque>
# include <iomanip>
# include <iostream>
# include <limits.h>
# include <string>
# include <sys/time.h>
# include <vector>

#define SUCCESS 0
#define ERROR 1
#define DEQUE 0
#define VECTOR 1
//Two containers: _vector (vector) and _deque (deque).
typedef std::vector<int> vector_t;
typedef std::deque<int> deque_t;

class PmergeMe
{
	public:

		PmergeMe();
		PmergeMe( PmergeMe const & src );
		PmergeMe &			operator=( PmergeMe const & other );
		~PmergeMe();

		deque_t const 		&getDeque( void ) const;
		void				setDeque( deque_t deque );

		vector_t const 		&getVector( void ) const;
		void				setVector( vector_t vector );

		void				checkInput( int argc, char **argv );
		void				fillDeque( int argc, char **argv );
		void				fillVector( int argc, char **argv );
		void				printBefore( void );
		void				printAfter( void );

		void				printTime( int containerType, double time );

		vector_t			cutAndSort( vector_t vector );
		vector_t			mergeSort( vector_t vectorOne, vector_t vectorTwo );

		deque_t				cutAndSort( deque_t deque );
		deque_t				mergeSort( deque_t dequeOne, deque_t dequeTwo );

	private:

		deque_t				_deque;
		vector_t			_vector;
};

double	getTime(void);
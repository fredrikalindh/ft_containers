/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skybt <skybt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:31:12 by skybt             #+#    #+#             */
/*   Updated: 2020/08/08 12:37:33 by skybt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"
#define RESET "\x1B[0m"
#define BOLD "\x1B[1m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"
int main()
{
	std::cout << GREEN << ":: Vector ::" << RESET << std::endl;
	test_vector();
	std::cout << GREEN << ":: List ::" << RESET << std::endl;
	test_list();
	std::cout << GREEN << ":: Stack ::" << RESET << std::endl;
	test_stack();
	std::cout << GREEN << ":: Queue ::" << RESET << std::endl;
	test_queue();
	std::cout << GREEN << ":: Map ::" << RESET << std::endl;
	test_map();
	std::cout << GREEN << ":: Set ::" << RESET << std::endl;
	test_set();
	std::cout << GREEN << ":: MultiMap ::" << RESET << std::endl;
	test_multimap();
	std::cout << GREEN << ":: MultiSet ::" << RESET << std::endl;
	test_multiset();
	std::cout << GREEN << ":: Deque ::" << RESET << std::endl;
	test_deque();
	std::cout << GREEN << ":: Everything is ok! ::" << RESET << std::endl;
	return 0;
}

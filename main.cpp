/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:32:38 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/19 14:10:31 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Server.hpp"

int main(int ac, char **av) {

	if (ac != 3) {
		std::cout << "`error`: usage: ./ircserv [port] [password]" << std::endl;
		return (EXIT_FAILURE);
	}
	
	try {
		Server serv(av[1], av[2]);
		
	} catch(std::exception &err) {
		std::cout << err.what() << std::endl;
	}
}
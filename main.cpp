/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:32:38 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/21 00:55:19 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Server.hpp"

static bool is_run = true;

static inline void	singleton_ctrl_c(int sig) { (void)sig; is_run = false; }

int main(int ac, char **av) {

	if (ac != 3) {
		std::cout << "`error`: usage: ./ircserv [port] [password]" << std::endl;
		return (EXIT_FAILURE);
	}

	try {
		signal(SIGINT, singleton_ctrl_c);
		Server serv(av[1], av[2]);
		serv.server_initialisation();

		while (is_run) {
			serv.run();
		}
		
	} catch(std::exception &err) {
		std::cout << err.what() << std::endl;
	}
}
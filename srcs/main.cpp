/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:32:38 by jucheval          #+#    #+#             */
/*   Updated: 2023/11/10 01:02:49 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "utils.hpp"

static bool __is_running__ = true;
static inline void	singleton_ctrl_c(int sig)
{ (void)sig; __is_running__ = false; }

int main(int ac, char **av) {
	if (ac == 3) {
		try {
			signal(SIGINT, singleton_ctrl_c);
			Server serv(av[1], av[2]);
			serv.server_initialisation();

			
			logger(INFO, "Listening ...");
			while (__is_running__)
				serv.run();
			
		} catch(std::exception &err) {
			std::cerr
				<< err.what()
				<< std::endl;

			return (EXIT_FAILURE);
		}

		return (EXIT_SUCCESS);
	}

	std::cerr
		<< "`error`: usage: ./ircserv [port] [password]"
		<< std::endl;

	return (EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:51:08 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/21 21:24:45 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./Server.hpp"

#include <iostream>
#include <vector>
#include <stdint.h>
#include <netinet/in.h>
#include <sstream>

class Server;

class User {
	
	private:
		int32_t						_fd;
		Server						*_server;
		struct sockaddr_in			_address;
		std::vector<std::string>	_commands;

	public:
		User(int32_t fd, struct sockaddr_in addr, Server *serv);
		~User();

		void	receive_client_input(void);
		void	exec_client_commands(void);

		int32_t	get_fd(void);

		std::vector<std::string>	split_space(std::string cmd);


		void	DEBUG_PRINT_CMD_VEC(void);
		void	DEBUG_PRINT_CMD_SPLIT_VEC(std::vector<std::string> cmd);

};

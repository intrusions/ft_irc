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

		int32_t						get_fd(void);
		std::vector<std::string>	*fetch_commands(void);
};

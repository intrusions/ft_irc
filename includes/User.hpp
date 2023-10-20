/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:51:08 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/20 17:36:19 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./Server.hpp"
#include <stdint.h>
#include <netinet/in.h>

class Server;

class User {
	
	private:
		int32_t				_fd;
		Server				*_server;
		struct sockaddr_in	_address;

	public:
		User(int32_t fd, struct sockaddr_in addr, Server *serv);
		~User();
};

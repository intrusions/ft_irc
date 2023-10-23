/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:51:08 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/23 21:57:32 by xel              ###   ########.fr       */
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
		
		std::string					_prefix;
		std::string					_nickname;
		std::string					_username;
		std::string					_hostname;

		bool						_pass_is_valid;


	public:
		User(int32_t fd, struct sockaddr_in addr, Server *serv);
		~User();

		std::vector<std::string>	*fetch_commands(void);
		
		
		int32_t			get_fd(void);
		int32_t			get_pass_is_valid(void);
		std::string		get_prefix(void);
		std::string		get_nickname(void);

		void			set_pass_is_valid(bool n);
		void			set_nickname(std::string n);


};

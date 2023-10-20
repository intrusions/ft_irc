/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:05 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/20 17:36:15 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./User.hpp"
#include <iostream>
#include <stdint.h>
#include <exception>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <vector>
#include <map>
#include <netinet/in.h>
#include <poll.h>
#include <cstring>

class User;

class Server {
	
	private:
		uint16_t    			_port;
		std::string 			_password;
		int32_t					_sockfd;
		struct sockaddr_in		_addr;
		std::vector<pollfd>		_fds;
		std::map<int, User *>	_users;
		

		uint16_t    _check_port(char *port);
		std::string _check_password(char *password);
		void		_accept_user(void);


	public:
		Server(char *port, char *pass);
		~Server();

		void	server_initialisation(void);
		void	run(void);
		
		
		class SocketInitialisationFailed : public std::exception {
			public :
			   virtual const char *what() const throw() {
					return ("error: `socket()` function failed");
				} 
		};
		class SetSockOptFailed : public std::exception {
			public :
			   virtual const char *what() const throw() {
					return ("error: `setsockopt()` function failed");
				} 
		};
		class BindFailed : public std::exception {
			public :
			   virtual const char *what() const throw() {
					return ("error: `bind()` function failed");
				} 
		};
		class ListenFailed : public std::exception {
			public :
			   virtual const char *what() const throw() {
					return ("error: `listen()` function failed");
				} 
		};
};
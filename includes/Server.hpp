/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:05 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/28 00:27:38 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./User.hpp"
#include "./reply.hpp"

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
#include <unistd.h>
#include <signal.h>

class User;

class Server {
	
	private:
		uint16_t    			_port;
		std::string 			_password;
		std::string 			_networkname;
		std::string 			_servername;
		std::string				_start_time;
		std::string				_version;
		int32_t					_sockfd;
		struct sockaddr_in		_addr;
		std::vector<pollfd>		_fds;
		std::map<int, User *>	_users;


		uint16_t    _check_port(char *port);
		std::string _check_password(char *password);

		void		_accept_user(void);
		void		_delete_user(int32_t fd);

		void		_receive_client_input(User *user);
		void		_exec_client_commands(User *user);

		void		_command_pass(std::vector<std::string> cmd, int32_t fd);
		void		_command_nick(std::vector<std::string> cmd, int32_t fd);
		void		_command_user(std::string cmd, int32_t fd);
		void		_command_ping(uint32_t fd);

		void		_send_reply(int32_t fd, int32_t err, std::vector<std::string> err_param);


	public:
		Server(char *port, char *pass);
		~Server();

		void	server_initialisation(void);
		void	run(void);

		std::string 	get_networkname(void);
		std::string 	get_servername(void);
		std::string 	get_start_time(void);


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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:05 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/19 16:19:13 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdint.h>
#include <exception>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <vector>
#include <netinet/in.h>
#include <poll.h>
#include <cstring>

class Server {
	
	private:
		uint16_t    		_port;
		std::string 		_password;
		int32_t				_sockfd;
		struct sockaddr_in	_addr;
		std::vector<pollfd> _fds;
		

		uint16_t    _check_port(char *port);
		std::string _check_password(char *password);



	public:
		Server(char *port, char *pass);
		~Server();

		void	server_initialisation(void);
		
		
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
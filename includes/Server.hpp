/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:05 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/19 14:10:28 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdint.h>
#include <exception>
#include <cstdlib>

class Server {
	
	private:
		uint16_t    _port;
		std::string _password;

		uint16_t    _check_port(char *port);
		std::string _check_password(char *password);


	public:
		Server(char *port, char *pass);
		~Server();

		class InvalidPort : public std::exception {
			
			public :
			   virtual const char *what() const throw() {
					return ("`error`: invalid port");
				} 
		};

		class InvalidPassword : public std::exception {
			
			public :
			   virtual const char *what() const throw() {
					return ("`error`: invalid password");
				} 
		};
};
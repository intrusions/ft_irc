/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:13 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/19 14:11:35 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

/* constructor/destructor */
Server::Server(char *port, char *password) {
	
	_port = _check_port(port);
	_password = _check_password(password);
}

Server::~Server() {}

/* main argument's parsing */
uint16_t    Server::_check_port(char *port) {
	
	uint16_t	nPort = atoi(port);

	for (uint8_t i = 0; port[i]; i++) {
		if (!isdigit(port[i]))
			throw Server::InvalidPort();
	}

	if (nPort < 1024 || nPort > 49551)
		throw Server::InvalidPort();
	
	return (nPort);
}

std::string Server::_check_password(char *password) {
	
	std::string nPass(password);

	if (nPass.size() < 6)
		throw Server::InvalidPassword();
	
	return (nPass);
}
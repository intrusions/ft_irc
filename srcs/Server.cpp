/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:13 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/20 17:54:03 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/User.hpp"


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
			throw std::invalid_argument("`error`: invalid port");
	}

	if (nPort < 1024 || nPort > 49551)
		throw std::invalid_argument("`error`: invalid port");
	
	return (nPort);
}

std::string Server::_check_password(char *password) {
	
	std::string nPass(password);

	if (nPass.size() < 6)
		throw std::invalid_argument("`error`: invalid password");
	
	return (nPass);
}

/* server initialisation */
/* ce code initialise un socket, configure certaines options,
lie le socket à une adresse et un port,
le met en ecoute pour les connexions entrantes,
et l'ajoute a une liste de sockets surveilles par poll pour les
evenements d'entree et de fermeture */
void		Server::server_initialisation() {

	int32_t	optsock = 1;
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (_sockfd == -1)
		throw Server::SocketInitialisationFailed();
	
	if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &optsock, sizeof(int32_t)) < 0)
		throw Server::SetSockOptFailed();

	memset(&_addr, 0, sizeof(_addr));

	_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(_port);

	if (bind(_sockfd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
		throw Server::BindFailed();

	if (listen(_sockfd, SOMAXCONN) == -1)
		throw Server::ListenFailed();

	_fds.push_back(pollfd());
	_fds.back().fd = _sockfd;
	_fds.back().events = (POLLIN | POLLHUP);
}

void	Server::run() {
	
	if (poll(&_fds.front(), _fds.size(), -1) == -1)
		return ;		

	if (_fds.front().revents == POLLIN) {
		std::cout << "User connected" << std::endl;
		_accept_user();
	} else {
		// std::cout << "Ici"  << std::endl;
	}
}

void	Server::_accept_user() {
	
	struct sockaddr_in	addr;
	memset(&addr, 0, sizeof(addr));
	
	socklen_t sock_len = sizeof(addr);
	int32_t fd = accept(_sockfd, (struct sockaddr *)&addr, &sock_len);

	if (fd == -1) {
		std::cout << "error: `accept()` function failed" << std::endl;
		return ;
	}

	_users[fd] = new User(fd, addr, this);

	_fds.push_back(pollfd());
	_fds.back().fd = fd;
	_fds.back().events = (POLLIN | POLLRDHUP);
}

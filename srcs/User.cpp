/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:52:09 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/20 22:21:50 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"

/* constructor/destructor */
User::User(int32_t fd, struct sockaddr_in addr, Server *serv)
	: _fd(fd)
	, _server(serv)
	, _address(addr) {}

User::~User() {}


/* `User` function */
void	User::receive_response() {
	
	char		buff[512] = {};
	int64_t		bytes_read;

	bytes_read = recv(_fd, &buff, sizeof(buff), 0);
	
	if (bytes_read == -1) {
		return ;
	} else if (bytes_read == 512) {
		buff[510] = '\n';
		buff[510] = '\0';
	}

	std::cout << buff << std::endl;
}


/* accessor */
int32_t	User::get_fd(void) { return (_fd); }
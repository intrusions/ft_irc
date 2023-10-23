/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:52:09 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/21 22:37:48 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"

/* constructor/destructor */
User::User(int32_t fd, struct sockaddr_in addr, Server *serv)
	: _fd(fd)
	, _server(serv)
	, _address(addr) {}

User::~User() {}


/* accessor */
int32_t						User::get_fd() { return (_fd); }

/* fetch arg */
std::vector<std::string>	*User::fetch_commands() { return (&_commands); }

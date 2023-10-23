/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:52:09 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/23 21:56:39 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"

/* constructor/destructor */
User::User(int32_t fd, struct sockaddr_in addr, Server *serv)
	: _fd(fd)
	, _server(serv)
	, _address(addr)
	, _prefix("GUEST")
	, _nickname("GUEST")
	, _username ("GUEST")
	, _hostname ("GUEST")
	, _pass_is_valid(0) {}

User::~User() {}


/* accessor */
int32_t			User::get_fd() { return (_fd); }
int32_t			User::get_pass_is_valid() { return (_pass_is_valid); }
std::string		User::get_prefix() { return (_prefix); }
std::string		User::get_nickname() { return (_prefix); }

void			User::set_pass_is_valid(bool n) { _pass_is_valid = n; }
void			User::set_nickname(std::string n) { _nickname = n; }

/* fetch arg */
std::vector<std::string>	*User::fetch_commands() { return (&_commands); }

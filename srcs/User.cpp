/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:52:09 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/24 03:38:07 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"

/* constructor/destructor */
User::User(int32_t fd, struct sockaddr_in addr, Server *serv)
	: _fd(fd)
	, _server(serv)
	, _address(addr)
	, _nickname("GUEST")
	, _username ("GUEST")
	, _realname ("GUEST")
	, _hostname ("GUEST")
	, _pass_is_valid(0) { set_prefix(); }

User::~User() {}


/* accessor */
int32_t			User::get_fd() { return (_fd); }
std::string		User::get_prefix() { return (_prefix); }
std::string		User::get_nickname() { return (_nickname); }
std::string		User::get_username() { return (_username); }
std::string		User::get_realname() { return (_realname); }
std::string		User::get_hostname() { return (_hostname); }
int32_t			User::get_pass_is_valid() { return (_pass_is_valid); }

void 			User::set_prefix() { _prefix = ":" + _nickname + "!" + _username + "@" + _hostname; }
void			User::set_nickname(std::string n) { _nickname = n; }
void			User::set_username(std::string n) { _username = n; }
void			User::set_realname(std::string n) { _realname = n; }
void			User::set_hostname(std::string n) { _hostname = n; }
void			User::set_pass_is_valid(bool n) { _pass_is_valid = n; }

/* fetch */
std::vector<std::string>	*User::fetch_commands() { return (&_commands); }

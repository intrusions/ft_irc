/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:52:09 by jucheval          #+#    #+#             */
/*   Updated: 2023/11/10 17:46:24 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

/* constructor/destructor */
User::User(int32_t fd)
    : _fd(fd)
    , _nickname(DEFAULT_INFO_VALUE)
    , _username(DEFAULT_INFO_VALUE)
    , _realname(DEFAULT_INFO_VALUE)
    , _hostname(DEFAULT_INFO_VALUE)
    , _pass_is_valid(0) { set_prefix(); }

User::~User() {}


/* accessors */
int32_t         User::get_fd() const            { return (_fd); }
std::string     User::get_prefix() const        { return (_prefix); }
std::string     User::get_nickname() const      { return (_nickname); }
std::string     User::get_username() const      { return (_username); }
std::string     User::get_realname() const      { return (_realname); }
std::string     User::get_hostname() const      { return (_hostname); }
int32_t         User::get_pass_is_valid() const { return (_pass_is_valid); }

void            User::set_prefix()                       { _prefix = ":" + _nickname + "!" + _username + "@" + _hostname; }
void            User::set_nickname(const std::string &n) { _nickname = n; }
void            User::set_username(const std::string &n) { _username = n; }
void            User::set_realname(const std::string &n) { _realname = n; }
void            User::set_hostname(const std::string &n) { _hostname = n; }
void            User::set_pass_is_valid(const bool n)    { _pass_is_valid = n; }

/* fetch */
std::vector<std::string>    *User::fetch_commands()	{ return (&_commands); }

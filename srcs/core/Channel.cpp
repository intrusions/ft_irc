/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:03:06 by jucheval          #+#    #+#             */
/*   Updated: 2023/11/10 17:13:11 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

/* constructor/destructor */
Channel::Channel(std::string name, int32_t fd)
    : _name(name)
    , _password("") { _fds.push_back(fd); }

Channel::Channel(std::string name, int32_t fd, std::string password)
    : _name(name)
    , _password(password) { _fds.push_back(fd); }

Channel::~Channel() {}

/* accessors */
std::string             Channel::get_name(void) { return (_name); }
std::string             Channel::get_password(void) { return (_password); }

std::vector<int32_t>    *Channel::fetch_fds(void) { return (&_fds); }
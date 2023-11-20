/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:03:06 by jucheval          #+#    #+#             */
/*   Updated: 2023/11/20 18:14:01 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Channel.hpp"

/* constructor/destructor */
Channel::Channel(std::string name, int32_t fd)
    : _name(name)
    , _topic("The topic has not been set")
    , _password("") { _fds.push_back(fd); _operator_fds.push_back(fd); }

Channel::Channel(std::string name, int32_t fd, std::string password)
    : _name(name)
    , _topic("The topic has not been set")
    , _password(password) { _fds.push_back(fd); _operator_fds.push_back(fd); }

Channel::~Channel() {}

/* accessors */
std::string             Channel::get_name(void) const       { return (_name); }
std::string             Channel::get_password(void) const   { return (_password); }
std::string             Channel::get_topic(void) const      { return (_topic); }


std::vector<int32_t>	*Channel::fetch_fds(void)           { return (&_fds); }
std::vector<int32_t>	*Channel::fetch_banned_fds(void)    { return (&_banned_fds); }
std::vector<int32_t>	*Channel::fetch_operator_fds(void)  { return (&_operator_fds); }

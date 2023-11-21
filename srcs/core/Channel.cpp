/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:03:06 by jucheval          #+#    #+#             */
/*   Updated: 2023/11/21 11:44:16 by xel              ###   ########.fr       */
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
uint64_t	            Channel::get_mflags(void)           { return (_mflags); }
bool                    Channel::get_is_invite_only(void)   { return (_is_invite_only); }

void                    Channel::set_mflags(uint64_t flags) { _mflags = flags; }
void                    Channel::set_is_invite_only(bool w) { _is_invite_only = w; }

std::vector<int32_t>	*Channel::fetch_fds(void)           { return (&_fds); }
std::vector<int32_t>	*Channel::fetch_banned_fds(void)    { return (&_banned_fds); }
std::vector<int32_t>	*Channel::fetch_operator_fds(void)  { return (&_operator_fds); }
std::vector<int32_t>	*Channel::fetch_invite_fds(void)    { return (&_invite_fds); }

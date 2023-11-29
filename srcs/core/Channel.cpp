/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:03:06 by jucheval          #+#    #+#             */
/*   Updated: 2023/11/27 19:36:13 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "utils.hpp"

/* constructor/destructor */
Channel::Channel(std::string name, int32_t fd)
    : _name(name)
    , _topic("The topic has not been set")
    , _password("") { _fds.push_back(fd); }

Channel::Channel(std::string name, int32_t fd, std::string password)
    : _name(name)
    , _topic("The topic has not been set")
    , _password(password) { _fds.push_back(fd); }

Channel::~Channel() {}

/* accessors */
std::string             Channel::get_name(void) const { return (_name); }
std::string             Channel::get_password(void) const { return (_password); }
std::string             Channel::get_topic(void) const { return (_topic); }

bool    Channel::find_fds(const int32_t fd) {

    vec_foreach(int32_t, _fds, it) {
        if (*it == fd)
            return (true);
    }
    return (false);
}

std::vector<int32_t>	*Channel::fetch_fds(void) { return (&_fds); }

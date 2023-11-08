/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:03:06 by jucheval          #+#    #+#             */
/*   Updated: 2023/11/08 23:51:45 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

/* constructor/destructor */
Channel::Channel(std::string name, int32_t fd)
	: _name(name) { _fds.push_back(fd); }

Channel::~Channel() {}

/* accessor */
std::string				Channel::get_name(void) { return (_name); }
std::vector<int32_t>	*Channel::fetch_fds(void) { return (&_fds); }
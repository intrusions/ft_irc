/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_ping.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 00:23:26 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/28 00:27:48 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"
#include "utils.hpp"

void    Server::_command_ping(uint32_t fd) {
	
	std::string res = "PONG " + _users[fd]->get_prefix() + "\r\n";
	
	if (send(_users[fd]->get_fd(), res.c_str(), res.size(), 0) == -1)
		return ;
}

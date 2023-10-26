/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_nick.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:36:53 by xel               #+#    #+#             */
/*   Updated: 2023/10/26 05:14:29 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"
#include "../../includes/User.hpp"
#include "../../includes/utils.hpp"

void	Server::_command_nick(std::vector<std::string> cmd, int32_t fd) {

	std::vector<std::string>	err_param;

	if (cmd.size() != 2) {
		_send_reply(fd, 431, err_param);
		return ;
	}

	if (isdigit(cmd[1][0]) || cmd[1][0] == '#' || cmd[1][0] == ':' || cmd[1].length() > 31) {
		err_param.push_back(cmd[1]);
		_send_reply(fd, 432, err_param);
		return ;
	}

	for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); it++) {
		
		if (it->second->get_nickname() == cmd[1]) {
			err_param.push_back(cmd[1]);
			_send_reply(fd, 433, err_param);
			return ;
		}
	}

	if (!_users[fd]->get_pass_is_valid()) {
		logs("logs(client need to set a password before entering a /NICK)", 3);
		return ;
	}

	_users[fd]->set_nickname(cmd[1]);
	_users[fd]->set_prefix();
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_user.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:36:53 by xel               #+#    #+#             */
/*   Updated: 2023/10/24 03:36:42 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"
#include "../../includes/User.hpp"
#include "../../includes/utils.hpp"

void	Server::_command_user(std::string cmd, int32_t fd) {

	std::vector<std::string>	err_param;
	std::vector<std::string>	cmd_splited;
	std::string					realname;
	std::string					username;
	std::string					hostname;
    uint32_t 					pos = 0;
	

	if (_users[fd]->get_nickname() == "GUEST") {
		std::cout << "nickname is guest" << std::endl;
		return ;
	}

	if ((pos = cmd.find(":")) && pos == std::string::npos) {
		_send_reply(fd, 461, err_param);
		return ;
	} else {
		realname = cmd.substr(pos + 1, cmd.length());
		cmd.erase(pos - 1, cmd.length());
	}

	cmd_splited = split_space(cmd);

	if (cmd_splited.size() != 4) {
		_send_reply(fd, 461, err_param);
		return ;
	} else {
		username = cmd_splited[1];
		hostname = cmd_splited[3];
	}

	// check if realname is valid

	for (std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); it++) {

		if (it->second->get_username() == username) {
			_send_reply(fd, 462, err_param);
			return ;
		}
	}

    _users[fd]->set_username(username);
    _users[fd]->set_realname(realname);
    _users[fd]->set_hostname(hostname);
    _users[fd]->set_prefix();
    
	_send_reply(fd, 001, err_param);
	_send_reply(fd, 002, err_param);
	_send_reply(fd, 003, err_param);
	_send_reply(fd, 004, err_param);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_user.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:36:53 by xel               #+#    #+#             */
/*   Updated: 2023/10/26 17:57:59 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"
#include "../../includes/User.hpp"
#include "../../includes/utils.hpp"

static bool	is_valid_realname(std::string realname) {
	(void)realname;
	return (true);
}

void	Server::_command_user(std::string cmd, int32_t fd) {

	std::vector<std::string>	err_param;
	std::vector<std::string>	cmd_splited;
	std::string					realname;
	std::string					username;
	std::string					hostname;
    uint64_t 					pos = 0;


	if ((pos = cmd.find(":")) && pos == std::string::npos) {
		err_param.push_back("/USER");
		_send_reply(fd, 461, err_param);
		return ;
	} else {
		realname = cmd.substr(pos + 1, cmd.length());
		cmd.erase(pos - 1, cmd.length());
	}

	cmd_splited = split_space(cmd);

	if (cmd_splited.size() != 4) {
		err_param.push_back("/USER");
		_send_reply(fd, 461, err_param);
		return ;
	} else {
		username = cmd_splited[1];
		hostname = cmd_splited[3];
	}

	if (!is_valid_realname(realname)) {
		err_param.push_back("/USER");
		_send_reply(fd, 461, err_param);
		return ;
	}

	for (std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); it++) {

		if (it->second->get_username() == username) {
			_send_reply(fd, 462, err_param);
			return ;
		}
	}

	if (_users[fd]->get_nickname() == "GUEST") {
		logs("logs(client need to set a nickname before entering a /USER)", 3);
		return ;
	}

    _users[fd]->set_username(username);
    _users[fd]->set_realname(realname);
    _users[fd]->set_hostname(hostname);
    _users[fd]->set_prefix();
    
	_send_reply(fd, 001, err_param);
	_send_reply(fd, 002, err_param);
	_send_reply(fd, 003, err_param);
	_send_reply(fd, 004, err_param);

	logs("logs(client connected)", 2);
}
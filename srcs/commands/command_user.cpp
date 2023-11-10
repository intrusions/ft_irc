/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_user.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:36:53 by xel               #+#    #+#             */
/*   Updated: 2023/11/10 18:00:28 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"
#include "utils.hpp"

/* todo */
static bool	is_valid_realname(std::string realname) {
    (void)realname;
    return (true);
}

void	Server::_command_user(std::string cmd, int32_t fd) {

    std::vector<std::string>    err_param;
    std::vector<std::string>    cmd_splited;
    std::string                 realname;
    std::string                 username;
    std::string                 hostname;
    uint64_t                    pos = 0;


    if ((pos = cmd.find(":")) && pos == std::string::npos) {
        err_param.push_back("/USER");
        _send_reply(fd, 461, err_param);
        return ;
    } else {
        realname = cmd.substr(pos + 1, cmd.length());
        cmd.erase(pos - 1, cmd.length());
    }

    cmd_splited = split(cmd, ' ');

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

    /**
     * Let this function commented if you work on local with multiple irssi client.
     */
    // for (std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); it++) {

    // 	if (it->second->get_username() == username) {
    // 		_send_reply(fd, 462, err_param);
    // 		return ;
    // 	}
    // }

    if (_users[fd]->get_nickname() == DEFAULT_INFO_VALUE) {
        logger(WARNING, "Client need to set a nickname before entering a `/USER`");
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

    logger(INFO, "Client connected");
}

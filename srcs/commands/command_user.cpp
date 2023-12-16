/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_user.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:36:53 by xel               #+#    #+#             */
/*   Updated: 2023/12/16 03:15:57 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Server.hpp"
#include "User.hpp"
#include "utils.hpp"

void	Server::_command_user(std::string cmd, int32_t fd) {

    std::vector<std::string>    reply_arg;
    std::vector<std::string>    cmd_splited;
    std::string                 realname;
    std::string                 username;
    std::string                 hostname;
    uint64_t                    pos = 0;


    if ((pos = cmd.find(":")) && pos == std::string::npos) {
        reply_arg.push_back("/USER");
        _send_reply(fd, 461, reply_arg);
        return ;
    } else {
        realname = cmd.substr(pos + 1, cmd.length());
        cmd.erase(pos - 1, cmd.length());
    }

    cmd_splited = split(cmd, ' ');

    if (cmd_splited.size() != 4) {
        reply_arg.push_back("/USER");
        _send_reply(fd, 461, reply_arg);
        return ;
    } else {
        username = cmd_splited[1];
        hostname = cmd_splited[3];
    }

    
    // Let this function commented if you work on local with multiple irssi client.
    // for (std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); it++) {

    // 	if (it->second->get_username() == username) {
    // 		_send_reply(fd, 462, reply_arg);
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
    
    _send_reply(fd, 1, reply_arg);
    _send_reply(fd, 2, reply_arg);
    _send_reply(fd, 3, reply_arg);
    _send_reply(fd, 4, reply_arg);

    logger(INFO, "Client connected");
}

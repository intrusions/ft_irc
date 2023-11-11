/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_nick.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:36:53 by xel               #+#    #+#             */
/*   Updated: 2023/11/11 18:33:14 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"
#include "utils.hpp"

// static bool is_nickname_valid(const std::string &nickname) {
//     if (nickname.empty()
// 		|| nickname[0] == '$'
// 		|| nickname[0] == ':') {
//         return (false);
//     }

//     const std::string forbiddenChars = " *,?!@";
//     const std::string channelTypePrefixes = "#&+!";

//     if (nickname.find_first_of(forbiddenChars) != std::string::npos
// 		|| channelTypePrefixes.find(nickname[0]) != std::string::npos
// 		|| nickname.find('.') != std::string::npos) {
//         return (false);
//     }

//     return (true);
// }

void	Server::_command_nick(std::vector<std::string> cmd, int32_t fd) {

    std::vector<std::string>    reply_arg;

    if (cmd.size() != 2) {
        _send_reply(fd, 431, reply_arg);
        return ;
    }

    if (isdigit(cmd[1][0]) || cmd[1][0] == '#' || cmd[1][0] == ':' || cmd[1].length() > 31) {
        reply_arg.push_back(cmd[1]);
        _send_reply(fd, 432, reply_arg);
        return ;
    }

    for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); it++) {
        
        if (it->second->get_nickname() == cmd[1]) {
            reply_arg.push_back(cmd[1]);
            _send_reply(fd, 433, reply_arg);
            return ;
        }
    }

    if (!_users[fd]->get_pass_is_valid()) {
        logger(WARNING, "Client need to set a password before entering a `/NICK`");
        return ;
    }

    if ((_users[fd]->get_nickname() != DEFAULT_INFO_VALUE) && (_users[fd]->get_username() != DEFAULT_INFO_VALUE)) {
        
        reply_arg.push_back(_users[fd]->get_prefix());
        reply_arg.push_back(cmd[1]);
        for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); it++) {
            _send_reply(it->second->get_fd(), 1001, reply_arg);
        }	
    }

    _users[fd]->set_nickname(cmd[1]);
    _users[fd]->set_prefix();
}

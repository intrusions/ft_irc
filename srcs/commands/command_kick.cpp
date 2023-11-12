/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_kick.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 06:33:56 by xel               #+#    #+#             */
/*   Updated: 2023/11/12 07:59:51 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "utils.hpp"

// todo
// 482

void	Server::_command_kick(std::vector<std::string> cmd, int32_t fd) {
    
    std::vector<std::string>            reply_arg;
    std::vector<Channel *>::iterator    channel = _channel.end();
    bool                                ope_are_in = false;
    int32_t                             client_to_kick = 0;

    if (cmd.size() < 3) {
        reply_arg.push_back(cmd[0]);
        _send_reply(fd, 461, reply_arg);
        return ;
    }

    for (std::vector<Channel *>::iterator it = _channel.begin(); it != _channel.end(); it++) {
        if ((*it)->get_name() == cmd[1]) {
            channel = it;
            break ;
        }
    }
    if (channel == _channel.end()) {
        reply_arg.push_back(cmd[1]);
        _send_reply(fd, 403, reply_arg);
        return ;
    }

    for (std::vector<int32_t>::iterator it = (*channel)->fetch_fds()->begin(); it != (*channel)->fetch_fds()->end(); it++) {
        if (_users[*it]->get_nickname() == cmd[2]) {
            client_to_kick = *it;
        }
    }
    if (!client_to_kick) {
        reply_arg.push_back(cmd[2]);
        reply_arg.push_back(cmd[1]);
        _send_reply(fd, 441, reply_arg);
        return ;
    }

    for (std::vector<int32_t>::iterator it = (*channel)->fetch_fds()->begin(); it != (*channel)->fetch_fds()->end(); it++) {
        if (*it == fd) {
            ope_are_in = true;
        }
    }
    if (!ope_are_in) {
        reply_arg.push_back(cmd[1]);
        _send_reply(fd, 442, reply_arg);
    } else {
        uint8_t i = 0;
        for (std::vector<int32_t>::iterator it = (*channel)->fetch_fds()->begin(); it != (*channel)->fetch_fds()->end(); it++) {
            if (*it == client_to_kick) {
                (*channel)->fetch_fds()->erase((*channel)->fetch_fds()->begin() + i);
            }
            i++;
        }
    }
    DEBUG_PRINT_ALL_CHANNEL(_channel);
}
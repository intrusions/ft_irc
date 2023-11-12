/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_kick.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 06:33:56 by xel               #+#    #+#             */
/*   Updated: 2023/11/12 11:57:19 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "utils.hpp"

// todo (when mode is coded)
// 482 - "<client> <channel> :You're not channel operator"

std::vector<Channel *>::iterator    channel_is_existing(std::vector<Channel *> &c_list, std::string &c_name) {
    
    for (std::vector<Channel *>::iterator it = c_list.begin(); it != c_list.end(); it++) {
        if ((*it)->get_name() == c_name) {
            return (it);
        }
    }
    return (c_list.end());
}

int32_t    user_is_in_channel(std::map<int, User *> &users, Channel *channel, std::string &nickname) {
    
    for (std::vector<int32_t>::iterator it = channel->fetch_fds()->begin(); it != channel->fetch_fds()->end(); it++) {
        if (users[*it]->get_nickname() == nickname) {
            return (*it);
        }
    }
    return (0);
}

bool    operator_is_in_channel(Channel *channel, int32_t fd) {

    for (std::vector<int32_t>::iterator it = channel->fetch_fds()->begin(); it != channel->fetch_fds()->end(); it++) {
        if (*it == fd) {
            return (true);
        }
    }
    return (false);
}

void	Server::_command_kick(std::vector<std::string> cmd, int32_t fd) {
    
    std::vector<std::string>            reply_arg;
    std::vector<Channel *>::iterator    channel_it;
    int32_t                             user_to_kick;

    if (cmd.size() < 3) {
        reply_arg.push_back(cmd[0]);
        _send_reply(fd, 461, reply_arg);
        return ;
    }

    if ((channel_it = channel_is_existing(_channel, cmd[1])) == _channel.end()) {
        logger(INFO, "This channel does not exist");

        reply_arg.push_back(cmd[1]);
        _send_reply(fd, 403, reply_arg);
        return ;  
    }
    
    if ((user_to_kick = user_is_in_channel(_users, *channel_it, cmd[2])) == 0) {
        logger(INFO, "The client who should be kicked, is not in this channel");

        reply_arg.push_back(cmd[2]);
        reply_arg.push_back(cmd[1]);
        _send_reply(fd, 441, reply_arg);
        return ;
    }

    if (user_to_kick == fd) {
        logger(INFO, "A client can't be kick himself");
        return ;
    }

    if (operator_is_in_channel(*channel_it, fd) == 0) {
        logger(INFO, "The client who would like kick, is not in this channel");

        reply_arg.push_back(cmd[1]);
        _send_reply(fd, 442, reply_arg);
        return ;
    } else {
        uint8_t i = 0;
        for (std::vector<int32_t>::iterator it = (*channel_it)->fetch_fds()->begin(); it != (*channel_it)->fetch_fds()->end(); it++) {
            if (*it == user_to_kick) {
                logger(INFO, "Client is successfully kicked");

                (*channel_it)->fetch_fds()->erase((*channel_it)->fetch_fds()->begin() + i);
                DEBUG_PRINT_ALL_CHANNEL(_channel);
                return ;
            }
            i++;
        }
    }
}
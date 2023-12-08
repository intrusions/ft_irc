/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_kick.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 06:33:56 by xel               #+#    #+#             */
/*   Updated: 2023/12/08 06:29:19 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "utils.hpp"

// todo
// if a channel is invite-only, and operator invite a client, it join it, and be kicked by operator
// ADD a remove of it old invitation

void	Server::_command_kick(std::vector<std::string> cmd, int32_t fd) {
    
    std::vector<std::string>     reply_arg;
    Channel                     *channel;
    int32_t                      user_to_kick;

    if (cmd.size() < 3) {
        logger(WARNING, "No channel name or nickname are given");
        
        reply_arg.push_back(cmd[0]);
        _send_reply(fd, 461, reply_arg);
        return ;
    }

    if ((channel = channel_is_existing(_channel, cmd[1])) == NULL) {
        logger(WARNING, "This channel does not exist");

        reply_arg.push_back(cmd[1]);
        _send_reply(fd, 403, reply_arg);
        return ;  
    }
    
    if ((user_to_kick = nickname_is_in_channel(_users, channel, cmd[2])) == 0) {
        logger(WARNING, "The client who should be kicked, is not in this channel");

        reply_arg.push_back(cmd[2]);
        reply_arg.push_back(cmd[1]);
        _send_reply(fd, 441, reply_arg);
        return ;
    }

    if (user_to_kick == fd) {
        logger(WARNING, "A client can't be kick himself");
        
        return ;
    }

    if (!find_fds_in_vec(channel->fetch_fds(), fd)) {
        logger(WARNING, "The client who would like kick, is not in this channel");

        reply_arg.push_back(cmd[1]);
        _send_reply(fd, 442, reply_arg);
        return ;
    }
    
    
    if (!find_fds_in_vec(channel->fetch_operator_fds(), fd)) {
        logger(WARNING, "The client who would like kick, is not operator on this channel");

        reply_arg.push_back(cmd[1]);
        _send_reply(fd, 482, reply_arg);
        return ;
    }
    
    
    reply_arg.push_back(_users[fd]->get_prefix());
    reply_arg.push_back(cmd[0]);
    reply_arg.push_back(cmd[1]);
    reply_arg.push_back(cmd[2]);

    for (std::vector<int32_t>::iterator it = channel->fetch_fds()->begin(); it != channel->fetch_fds()->end(); ) {
        
        _send_reply(*it, 1002, reply_arg);
        
        if (*it == user_to_kick) {
            logger(INFO, "Client is successfully kicked");

            it = channel->fetch_fds()->erase(it);
        } else {
            it++;
        }
    }
    DEBUG_PRINT_ALL_CHANNEL(_channel);
}

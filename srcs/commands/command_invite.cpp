/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_invite.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:07:20 by xel               #+#    #+#             */
/*   Updated: 2023/11/24 11:51:04 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "utils.hpp"

void	Server::_command_invite(std::vector<std::string> cmd, int32_t fd) {

    std::vector<std::string>    reply_arg;
    Channel                     *channel = NULL;
    int32_t                     to_invite_fd;

    if (cmd.size() < 3) {
        logger(WARNING, "No channel name or nickname given");

        return ;
    }

    if ((channel = channel_is_existing(_channel, cmd[2])) == NULL) {
        logger(WARNING, "Channel not existing on this server");
        
        reply_arg.push_back(cmd[2]);
        _send_reply(fd, 403, reply_arg);
        return ;
    }

    if (!find_fds_in_vec(channel->fetch_fds(), fd)) {
        logger(WARNING, "Client who want to invite, are not in the channel");
        
        reply_arg.push_back(cmd[2]);
        _send_reply(fd, 442, reply_arg);
        return ;
    }

    if (channel->get_is_invite_only()) {
        
        if (!find_fds_in_vec(channel->fetch_operator_fds(), fd)) {
            logger(WARNING, "Channel is Invite-Only, and the client who want invite are not channel operator");
            
            reply_arg.push_back(cmd[2]);
            _send_reply(fd, 482, reply_arg);
            return ;
        }
    }

    if ((nickname_is_in_channel(_users, channel, cmd[1]))) {
        logger(WARNING, "Client are already in the channel");
        
        reply_arg.push_back(cmd[1]);
        reply_arg.push_back(cmd[2]);
        _send_reply(fd, 443, reply_arg);
        return ;
    }

    if ((to_invite_fd = search_fd_by_nickname(_users, cmd[1])) != 0) {
        logger(WARNING, "Invitation to the channel sended");
        
        channel->fetch_invite_fds()->push_back(to_invite_fd);
        reply_arg.push_back(cmd[1]);
        reply_arg.push_back(cmd[2]);
        _send_reply(fd, 341, reply_arg);
        _send_reply(to_invite_fd, 341, reply_arg);
    }
}

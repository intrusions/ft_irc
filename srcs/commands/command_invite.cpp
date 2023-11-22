/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_invite.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:07:20 by xel               #+#    #+#             */
/*   Updated: 2023/11/22 09:12:16 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "utils.hpp"

static int32_t    user_is_in_channel(std::map<int, User *> &users, Channel *channel, std::string &nickname) {
    
    for (std::vector<int32_t>::iterator it = channel->fetch_fds()->begin(); it != channel->fetch_fds()->end(); it++) {
        if (users[*it]->get_nickname() == nickname) {
            return (*it);
        }
    }
    return (0);
}

static int32_t    search_fd_by_nickname(std::map<int, User *> &users, std::string &nickname) {
    
    for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++) {
        if ((*it).second->get_nickname() == nickname) {
            return ((*it).second->get_fd());
        }
    }
    return (0);
}

void	Server::_command_invite(std::vector<std::string> cmd, int32_t fd) {

    std::vector<std::string>    reply_arg;
    Channel                     *channel = NULL;
    bool                        user_want_to_invite_found = false;
    int32_t                     to_invite_fd;

    if (cmd.size() < 3) {
        logger(WARNING, "No channel name or nickname given");

        return ;
    }

    for (std::vector<Channel *>::iterator it = _channel.begin(); it != _channel.end(); it++) {
        
        if ((*it)->get_name() == cmd[2]) {
            channel = *it;
            break;
        }
    }
    if (channel == NULL) {
        logger(WARNING, "Channel not existing on this server");
        
        reply_arg.push_back(cmd[2]);
        _send_reply(fd, 403, reply_arg);
        return ;
    }
    
    for (std::vector<int32_t>::iterator it = channel->fetch_fds()->begin(); it != channel->fetch_fds()->end(); it++) {
    
        if ((*it) == fd) {
            user_want_to_invite_found = true;
            break ;
        }
    }
    if (user_want_to_invite_found == false) {
        logger(WARNING, "Client who want to invite, are not in the channel");
        
        reply_arg.push_back(cmd[2]);
        _send_reply(fd, 442, reply_arg);
        return ;
    }

    if (channel->get_is_invite_only()) {
        
        if (find_fds_in_vec(channel->fetch_operator_fds(), fd) == false) {
            logger(WARNING, "Channel is Invite-Only, and the client who want invite are not channel operator");
            
            reply_arg.push_back(cmd[2]);
            _send_reply(fd, 482, reply_arg);
            return ;
        }
    }

    if ((user_is_in_channel(_users, channel, cmd[1]))) {
        logger(WARNING, "Client are already in the channel");
        
        reply_arg.push_back(cmd[1]);
        reply_arg.push_back(cmd[2]);
        _send_reply(fd, 443, reply_arg);
        return ;
    }

    if ((to_invite_fd = search_fd_by_nickname(_users, cmd[1])) != false) {
        logger(WARNING, "Invitation to the channel sended");
        
        channel->fetch_invite_fds()->push_back(to_invite_fd);
        reply_arg.push_back(cmd[1]);
        reply_arg.push_back(cmd[2]);
        _send_reply(fd, 341, reply_arg);
        _send_reply(to_invite_fd, 341, reply_arg);
    }
}

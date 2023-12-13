/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_topic.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:53:49 by xel               #+#    #+#             */
/*   Updated: 2023/12/13 20:07:22 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"
#include "utils.hpp"

void    Server::_send_ntopic_to_channel(Channel *channel, std::string cname, int32_t sender_fd, std::vector<std::string> &reply_arg) {
    
    reply_arg.push_back(_users[sender_fd]->get_prefix());
    reply_arg.push_back(cname);
    reply_arg.push_back(channel->get_topic());

    for (std::vector<int32_t>::iterator it = channel->fetch_fds()->begin(); it != channel->fetch_fds()->end(); it++) {
        _send_reply(*it, 332, reply_arg);
    }
}

void	Server::_command_topic(std::string cmd, int32_t fd) {

    std::vector<std::string>    reply_arg;
    std::vector<std::string>    cmd_splited;
    Channel                     *channel;
    uint64_t                    pos = 0;
    std::string                 ntopic;

    if ((pos = cmd.find(":")) && pos != std::string::npos) {
        ntopic = cmd.substr(pos, cmd.length());
        cmd.erase(pos - 1, cmd.length());
    }

    cmd_splited = split(cmd, ' ');

    if (cmd_splited.size() < 2) {
        logger(WARNING, "Missing channel");
        return ;
    }

    if ((channel = channel_is_existing(_channel, cmd_splited[1])) == NULL) {
        logger(WARNING, "Channel is not in the server");

        reply_arg.push_back(cmd_splited[1]);
        _send_reply(fd, 403, reply_arg);
		return;
	}

    if (!find_fds_in_vec(channel->fetch_fds(), fd)) {
        logger(WARNING, "Client are not in this channel");
        
        reply_arg.push_back(cmd_splited[1]);
        _send_reply(fd, 442, reply_arg);
        return;
	}

    if (!ntopic.size()) {
        logger(INFO, "Actual topic sensed to the client");
        
        reply_arg.push_back(_users[fd]->get_prefix());
        reply_arg.push_back(cmd_splited[1]);
        reply_arg.push_back(channel->get_topic());
        _send_reply(fd, 332, reply_arg);

    } else {
        
        if (((channel->get_mflags() & CHANNEL_MODE_TOPIC_MANAGE) && (find_fds_in_vec(channel->fetch_operator_fds(), fd)))
            || (channel->get_mflags() & CHANNEL_MODE_TOPIC_MANAGE) == 0) {
            
            if (ntopic.size() == 1 && ntopic[0] == ':') {
                logger(INFO, "Channel topic cleaned");

                channel->set_topic("No topic is set");
                _send_ntopic_to_channel(channel, cmd_splited[1], fd, reply_arg);

            } else if (ntopic[0] == ':') {
                logger(INFO, "New channel topic set");
                
                channel->set_topic(&ntopic[1]);
                _send_ntopic_to_channel(channel, cmd_splited[1], fd, reply_arg);
            }
            
        } else {
            logger(WARNING, "Channel mode +t is set, and client are not a channel operator");

            reply_arg.push_back(cmd_splited[1]);
            _send_reply(fd, 482, reply_arg);
        }
    }
}

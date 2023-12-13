/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_part.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:36:53 by xel               #+#    #+#             */
/*   Updated: 2023/12/13 22:22:11 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "utils.hpp"


void    Server::_send_part_message_by_channel_name(std::string &c_name, std::string &message, int32_t fd) {

    std::vector<std::string>    reply_arg;
    Channel                     *channel;

    if ((channel = channel_is_existing(_channel, c_name)) == NULL) {
        logger(WARNING, "Channel deos not exist, can't `/PART`");

        reply_arg.push_back(c_name);
        _send_reply(fd, 403, reply_arg);
        return ;
    }

    if (!find_fds_in_vec(channel->fetch_fds(), fd)) {
        logger(WARNING, "Client who want leave channel, are not in");
        
        reply_arg.push_back(c_name);
        _send_reply(fd, 442, reply_arg);
        return ;
    }
    
    reply_arg.push_back(_users[fd]->get_prefix());
    reply_arg.push_back("PART");
    reply_arg.push_back(c_name);
    reply_arg.push_back(message);
    
    for (std::vector<int32_t>::iterator it = channel->fetch_fds()->begin(); it != channel->fetch_fds()->end(); it++) {
        _send_reply(*it, 1002, reply_arg);
    }
    logger(INFO, "Part message sended to channel");

    for (std::vector<int32_t>::iterator it = channel->fetch_fds()->begin(); it != channel->fetch_fds()->end(); it++) {
        
        if (fd == *it) {
            logger(INFO, "Client deleted in _fds of Channel");

            channel->fetch_fds()->erase(it);
            break ;
        }
    }

    for (std::vector<int32_t>::iterator it = channel->fetch_operator_fds()->begin(); it != channel->fetch_operator_fds()->end(); it++) {
        
        if (fd == *it) {
            logger(INFO, "Client deleted in _fds_operator of Channel");

            channel->fetch_operator_fds()->erase(it);
            break ;
        }
    }

    for (std::vector<Channel *>::iterator it = _channel.begin(); it != _channel.end(); it++) {

        if ((*it)->get_name() == c_name) {

            if ((*it)->fetch_fds()->empty()) {
                logger(INFO, "Channel member is empty, deleting ...");
                
                _channel.erase(it);
                break;
            }
        }
    }
    
    DEBUG_PRINT_ALL_CHANNEL(_channel);
}

void    Server::_command_part(std::string cmd, int32_t fd) {

    std::vector<std::string>    reply_arg;
    std::vector<std::string>    cmd_splited;
    std::vector<std::string>    channel_list;
    std::string                 message;
    uint64_t                    pos = 0;

    if ((pos = cmd.find(":")) && pos == std::string::npos) {
        message = "";
    } else {
        message = cmd.substr(pos + 1, cmd.length());
        cmd.erase(pos - 1, cmd.length());
    }

    cmd_splited = split(cmd, ' ');

    if (cmd_splited.size() != 2) {
        reply_arg.push_back("/PART");
        _send_reply(fd, 411, reply_arg);
        return ;
    } else {
        channel_list = split(cmd_splited[1], ',');
    }

    for (std::vector<std::string>::iterator it = channel_list.begin(); it != channel_list.end(); it++) {
        _send_part_message_by_channel_name(*it, message, fd);
    }
}

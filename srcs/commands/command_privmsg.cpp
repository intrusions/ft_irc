/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_privmsg.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:32:24 by jucheval          #+#    #+#             */
/*   Updated: 2023/11/20 12:44:28 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Server.hpp"
#include "User.hpp"
#include "utils.hpp"

void    Server::_send_message_by_channel_name(std::string &c_name, std::string &message, int32_t fd) {

    std::vector<std::string>    reply_arg;
    Channel                     *channel = NULL;
    bool                        sender_are_in = false;

    for (std::vector<Channel *>::iterator it = _channel.begin(); it != _channel.end(); it++) {

        if (c_name == (*it)->get_name()) {
            channel = *it;
            break ;
        }
    }
    if (!channel) {
        logger(WARNING, "Channel deos not exist, can't `/PRIVMSG`");

        reply_arg.push_back(c_name);
        _send_reply(fd, 403, reply_arg);
        return ;
    }


    for (std::vector<int32_t>::iterator it = channel->fetch_fds()->begin(); it != channel->fetch_fds()->end(); it++) {
        
        if (*it == fd) {
            sender_are_in = true;
            break;
        }
    }
    if (sender_are_in == false) {
        logger(WARNING, "Client who want send message, are not in channel");
        
        reply_arg.push_back(c_name);
        _send_reply(fd, 404, reply_arg);
        return ;
    }

    for (std::vector<int32_t>::iterator it = channel->fetch_banned_fds()->begin(); it != channel->fetch_banned_fds()->end(); it++) {
    
        if (*it == fd) {
            logger(INFO, "Can't send message, client banned from channel");
            
            reply_arg.push_back(c_name);
            _send_reply(fd, 404, reply_arg);
            return ;
        }
    }

    for (std::vector<int32_t>::iterator it = channel->fetch_fds()->begin(); it != channel->fetch_fds()->end(); it++) {
        
        if (*it != fd) {
            logger(INFO, "Message sended to channel");
            
            reply_arg.push_back(_users[fd]->get_prefix());
            reply_arg.push_back("PRIVMSG");
            reply_arg.push_back(c_name);
            reply_arg.push_back(message);
            _send_reply(*it, 1002, reply_arg);
        }
    }
}

void    Server::_send_message_by_nickname(std::string &nickname, std::string &message, int32_t fd) {

    std::vector<std::string>    reply_arg;
    int32_t                     fd_to_send = 0;

    for (std::map<int32_t, User*>::iterator it = _users.begin(); it != _users.end(); it++) {
    
        if ((*it).second->get_nickname() == nickname) {
            fd_to_send = (*it).second->get_fd();
            break ;
        }
    }

    if (fd_to_send == false) {
        logger(WARNING, "Can't send message, client are not in server");

        reply_arg.push_back(nickname);
        _send_reply(fd, 401, reply_arg);
        return ;
    }

    if (fd != fd_to_send) {
        logger(INFO, "Message sended to client");

        reply_arg.push_back(_users[fd]->get_nickname());
        reply_arg.push_back("PRIVMSG");
        reply_arg.push_back(nickname);
        reply_arg.push_back(message);
        _send_reply(fd_to_send, 1002, reply_arg);
    }
}


void    Server::_command_privmsg(std::string cmd, int32_t fd) {

    std::vector<std::string>    reply_arg;
    std::vector<std::string>    cmd_splited;
    std::vector<std::string>    user_list;
    std::string                 message;
    uint64_t                    pos = 0;

    if ((pos = cmd.find(":")) && pos == std::string::npos) {
        _send_reply(fd, 412, reply_arg);
        return ;
    } else {
        message = cmd.substr(pos + 1, cmd.length());
        cmd.erase(pos - 1, cmd.length());
    }

    cmd_splited = split(cmd, ' ');

    if (cmd_splited.size() != 2) {
        reply_arg.push_back("/PRIVMSG");
        _send_reply(fd, 411, reply_arg);
        return ;
    } else {
        user_list = split(cmd_splited[1], ',');
    }

    for (std::vector<std::string>::iterator it = user_list.begin(); it != user_list.end(); it++) {

        if ((*it)[0] == '#') {
            _send_message_by_channel_name(*it, message, fd);
        } else {
            _send_message_by_nickname(*it, message, fd);
        }
    }

}

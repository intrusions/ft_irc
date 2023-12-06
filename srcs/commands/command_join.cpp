/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_join.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:36:53 by xel               #+#    #+#             */
/*   Updated: 2023/12/06 15:42:46 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "utils.hpp"


//todo
// if a user is invited in a channel with a password
// we actually dont check if his pass is valid
// we adding in automatically if he try to join


// 353 when joining existing channel

/**
 * Irrsi put automatically a `#` at the beginning of the string.
 */
static bool  channel_name_is_valid(std::string c_name) {
    
    return ((c_name[0] == '#'));
}

void    Server::_send_welcome_message(int32_t fd_sender, Channel *channel, std::string cmd, std::string cname) {
    
    std::vector<std::string>    reply_arg;

    reply_arg.push_back(_users[fd_sender]->get_prefix());
    reply_arg.push_back(cmd);
    reply_arg.push_back(cname);
    reply_arg.push_back(cname);
    
    for (std::vector<int32_t>::iterator it = channel->fetch_fds()->begin(); it != channel->fetch_fds()->end(); it++) {
        _send_reply(*it, 1002, reply_arg);
    }
}

void	Server::_command_join(std::vector<std::string> cmd, int32_t fd) {

    std::vector<std::string>    reply_arg;
    std::vector<std::string>    channel_list;
    std::vector<std::string>    password_list;
    bool                        found;

    if (cmd.size() <= 1) {
        reply_arg.push_back(cmd[0]);
        _send_reply(fd, 461, reply_arg);
        return ;
    }

    if (_users[fd]->get_pass_is_valid() == 0) {
        
        _send_reply(fd, 451, reply_arg);
        return ;
    }

    channel_list = split(cmd[1], ',');
    
    if (cmd.size() >= 3)
        password_list = split(cmd[2], ',');

    for (std::vector<std::string>::iterator it = channel_list.begin(); it != channel_list.end(); it++) {
        found = false;
        reply_arg.clear();

        for (std::vector<Channel *>::iterator it2 = _channel.begin(); it2 != _channel.end(); it2++) {
            
            if (*it == (*it2)->get_name()) {
                found = true;
                
                if (find_fds_in_vec((*it2)->fetch_fds(), fd)) {
                    logger(INFO, "Client are already in this channel");
                
                    break ;
                }
                
                if ((*it2)->get_is_invite_only() == false) {
                    
                    if ((*it2)->get_password() != "") {

                        if (password_list.size() && (*it2)->get_password() == password_list[0]) {

                            if ((int32_t)((*it2)->fetch_fds()->size() + 1) <= (*it2)->get_limits()) {
                                logger(INFO, "Channel is already exist, valid password, joining channel...");
                                
                                reply_arg.push_back(_users[fd]->get_prefix());
                                reply_arg.push_back((*it2)->get_name());
                                reply_arg.push_back((*it2)->get_topic());
                                (*it2)->fetch_fds()->push_back(fd);
                                
                                _send_welcome_message(fd, *it2, "JOIN", *it);
                                _send_reply(fd, 332, reply_arg);
                                
                                password_list.erase(password_list.begin());
                                break ;
                            } else {
                                logger(WARNING, "User limit reached");

                                reply_arg.push_back((*it2)->get_name());
                                _send_reply(fd, 471, reply_arg);
                                break ;
                            }
                        } else {
                            logger(INFO, "Channel is already exist, invalid password");
                            
                            reply_arg.push_back((*it2)->get_name());
                            _send_reply(fd, 475, reply_arg);
                            break ;
                        }
                    } else {

                        if ((int32_t)((*it2)->fetch_fds()->size() + 1) <= (*it2)->get_limits()) {
                            logger(INFO, "Channel is already exist, no expected password, joining channel...");

                            reply_arg.push_back(_users[fd]->get_prefix());
                            reply_arg.push_back((*it2)->get_name());
                            reply_arg.push_back((*it2)->get_topic());
                            (*it2)->fetch_fds()->push_back(fd);
                            
                            _send_welcome_message(fd, *it2, "JOIN", *it);
                            _send_reply(fd, 332, reply_arg);
                            break ;
                        } else {
                            logger(WARNING, "User limit reached");

                            reply_arg.push_back((*it2)->get_name());
                            _send_reply(fd, 471, reply_arg);
                            break ;
                        }
                    }
                } else {

                    if (find_fds_in_vec((*it2)->fetch_invite_fds(), fd)) {

                        if ((int32_t)((*it2)->fetch_fds()->size() + 1) <= (*it2)->get_limits()) {
                            logger(INFO, "Channel is Invite Only, client has been invited, joining channel...");
                            
                            reply_arg.push_back(_users[fd]->get_prefix());
                            reply_arg.push_back((*it2)->get_name());
                            reply_arg.push_back((*it2)->get_topic());
                            (*it2)->fetch_fds()->push_back(fd);
                            
                            _send_welcome_message(fd, *it2, "JOIN", *it);
                            _send_reply(fd, 332, reply_arg);
                        } else {
                            logger(WARNING, "User limit reached");

                            reply_arg.push_back((*it2)->get_name());
                            _send_reply(fd, 471, reply_arg);
                            break ;
                        }
                    } else {
                        logger(INFO, "Channel is Invite Only, client was not invited");

                        reply_arg.push_back((*it2)->get_name());
                        _send_reply(fd, 473, reply_arg);
                    }
                    break ;
                }
            }
        }

        if (!found) {
            logger(INFO, "Channel doesn't exist, creating channel...");

            if (!channel_name_is_valid(*it)) {
                logger(INFO, "Channel name is not valid");

                reply_arg.push_back(*it);
                _send_reply(fd, 476, reply_arg);
                continue ;
            }

            if (password_list.size()) {
                _channel.push_back(new Channel(*it, fd, password_list[0]));
                password_list.erase(password_list.begin());
            } else {
                _channel.push_back(new Channel(*it, fd));
            }

            reply_arg.push_back(_users[fd]->get_prefix());
            reply_arg.push_back(*it);
            reply_arg.push_back(_channel.back()->get_topic());

            _send_welcome_message(fd, _channel.back(), "JOIN", *it);
            _send_reply(fd, 332, reply_arg);
        }
    }
    DEBUG_PRINT_ALL_CHANNEL(_channel);
}

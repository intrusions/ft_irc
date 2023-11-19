/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_join.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:36:53 by xel               #+#    #+#             */
/*   Updated: 2023/11/19 13:19:09 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "utils.hpp"


/**
 * Irrsi put automatically a `#` at the beginning of the string.
 */
static bool  channel_name_is_valid(std::string c_name) {
    
    return ((c_name[0] == '#'));
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

                if (find_fds_in_vec((*it2)->fetch_banned_fds(), fd)) {
                    logger(INFO, "Client has been banned from this channel");

                    reply_arg.push_back((*it2)->get_name());
                    _send_reply(fd, 474, reply_arg);
                    break ;
                }

                if ((*it2)->get_password() != "") {

                    if (password_list.size() && (*it2)->get_password() == password_list[0]) {
                        logger(INFO, "This channel is already exist, valid password, joining channel...");
                        
                        reply_arg.push_back((*it2)->get_name());
                        reply_arg.push_back((*it2)->get_topic());
                        _send_reply(fd, 332, reply_arg);
                        (*it2)->fetch_fds()->push_back(fd);
                        password_list.erase(password_list.begin());
                        break ;
                    } else {
                        logger(INFO, "This channel is already exist, invalid password");
                        
                        reply_arg.push_back((*it2)->get_name());
                        _send_reply(fd, 475, reply_arg);
                        break ;
                    }
                } else {
                    logger(INFO, "This channel is already exist, no expected password, joining channel...");
                    
                    reply_arg.push_back((*it2)->get_name());
                    reply_arg.push_back((*it2)->get_topic());
                    _send_reply(fd, 332, reply_arg);
                    (*it2)->fetch_fds()->push_back(fd);
                    break ;
                }
            }
        }

        if (found == false) {
            logger(INFO, "This channel doesn't exist, creating channel...");

            if (!channel_name_is_valid(*it)) {
                logger(INFO, "This channel name is not valid");

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

            reply_arg.push_back(*it);
            reply_arg.push_back(_channel.back()->get_topic());
            _send_reply(fd, 332, reply_arg);
        }
    }
    DEBUG_PRINT_ALL_CHANNEL(_channel);
}

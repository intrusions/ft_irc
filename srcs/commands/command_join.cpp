/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_join.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:36:53 by xel               #+#    #+#             */
/*   Updated: 2023/11/27 19:29:57 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "utils.hpp"

// todo:
// check if the user is not banned when he want join a channel
// erase the first '#' in channel name if one is found
// delete the channel if the last client in leave it

void	Server::_command_join(std::vector<std::string> cmd, int32_t fd) {

    std::vector<std::string>    reply_arg;
    std::vector<std::string>    channel_list;
    std::vector<std::string>    password_list;
    bool                        found;

    if (cmd.size() == 1) {
        reply_arg.push_back(cmd[0]);
        _send_reply(fd, 461, reply_arg);
        return ;
    }

    channel_list = split(cmd[1], ',');
    
    if (cmd.size() >= 3)
        password_list = split(cmd[2], ',');

    vec_foreach(std::string, channel_list, it) {
        
        found = false;
        reply_arg.clear();

        vec_foreach(Channel *, _channel, it2) {
            
            if (*it == (*it2)->get_name()) {
                found = true;
                
                if ((*it2)->find_fds(fd)) {
                    logger(INFO, "Client are already in this channel");
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_join.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:36:53 by xel               #+#    #+#             */
/*   Updated: 2023/11/10 18:48:50 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "utils.hpp"

void	Server::_command_join(std::vector<std::string> cmd, int32_t fd) {

    std::vector<std::string>    err_param;
    std::vector<std::string>    channel_list;
    std::vector<std::string>    password_list;
    bool                        found;

    if (cmd.size() == 1) {
        err_param.push_back(cmd[0]);
        _send_reply(fd, 461, err_param);
        return ;
    }

    channel_list = split(cmd[1], ',');
    
    if (cmd.size() >= 3)
        password_list = split(cmd[2], ',');

    for (std::vector<std::string>::iterator it = channel_list.begin(); it != channel_list.end(); it++) {
        found = false;
        err_param.clear();

        for (std::vector<Channel *>::iterator it2 = _channel.begin(); it2 != _channel.end(); it2++) {
            
            if (*it == (*it2)->get_name()) {
                found = true;
                
                if ((*it2)->get_password() != "") {

                    if (password_list.size() && (*it2)->get_password() == password_list[0]) {
                        logger(INFO, "This channel is already exist, valid password, joining channel...");
                        
                        err_param.push_back((*it2)->get_name());
                        err_param.push_back("topic ???");
                        _send_reply(fd, 332, err_param);
                        (*it2)->fetch_fds()->push_back(fd);
                        password_list.erase(password_list.begin());
                        break ;
                    } else {
                        logger(INFO, "This channel is already exist, invalid password");
                        
                        err_param.push_back((*it2)->get_name());
                        _send_reply(fd, 475, err_param);
                        break ;
                    }
                } else {
                    logger(INFO, "This channel is already exist, no expected password, joining channel...");
                    
                    err_param.push_back((*it2)->get_name());
                    err_param.push_back("topic ???");
                    _send_reply(fd, 332, err_param);
                    (*it2)->fetch_fds()->push_back(fd);
                    break ;
                }
            }
        }

        if (found == false) {
            logger(INFO, "This channel doesn't exist, creating channel...");

            err_param.push_back(*it);
            err_param.push_back("No topic");
            _send_reply(fd, 332, err_param);

            if (password_list.size()) {
                _channel.push_back(new Channel(*it, fd, password_list[0]));
                password_list.erase(password_list.begin());
            } else {
                _channel.push_back(new Channel(*it, fd));
            }
        }
    }
    // DEBUG_PRINT_ALL_CHANNEL(_channel);
}

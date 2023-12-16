/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_operator_priv.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:50:23 by xel               #+#    #+#             */
/*   Updated: 2023/12/16 01:49:44 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Channel.hpp"
#include "utils.hpp"

static void     kick_operator(Channel *channel, int32_t fd) {
    
    for(std::vector<int32_t>::iterator it = channel->fetch_operator_fds()->begin(); it != channel->fetch_operator_fds()->end(); it++) {
        
        if (*it == fd) {
            channel->fetch_operator_fds()->erase(it);
            break;
        }
    }
}

static void     add_operator(Channel *channel, int32_t fd) {
    
    channel->fetch_operator_fds()->push_back(fd);
}


void    Server::_mode_operator_priv(Channel *channel, std::vector<std::string> &cmd, bool add_or_rm, int32_t fd) {

    std::string                 nickname;
    std::vector<std::string>    reply_arg;
    int32_t                     user_fd;

    if (cmd.size() < 4) {
        logger(WARNING, "Nickname missing");
        return ;
    }

    if (add_or_rm == REMOVE_MODE) {
        
        if ((user_fd = nickname_is_in_channel(_users, channel, cmd[3])) != false) { 
            
            if (find_fds_in_vec(channel->fetch_operator_fds(), user_fd)) {
                logger(INFO, "User successfully kicked from operator channel");
                
                kick_operator(channel, user_fd);
            } else {
                logger(INFO, "User is not a channel operator");
            }
        } else {
            logger(WARNING, "User is not in the channel");
            
            reply_arg.push_back(cmd[3]);
            reply_arg.push_back(cmd[1]);
            _send_reply(fd, 441, reply_arg);
        }
    
    } else if (add_or_rm == ADD_MODE) {
        
        nickname = cmd[3].substr(0, cmd[3].find(','));
        
        if ((user_fd = nickname_is_in_channel(_users, channel, nickname)) != false) {

            if (find_fds_in_vec(channel->fetch_operator_fds(), user_fd)) {
                logger(INFO, "User is already operator channel");
            } else {
                logger(INFO, "User is successfully added to operator channel");
                
                add_operator(channel, user_fd);
            }
        } else {
            logger(WARNING, "User is not in the channel");
        
            reply_arg.push_back(cmd[3]);
            reply_arg.push_back(cmd[1]);
            _send_reply(fd, 441, reply_arg);
        }
        cmd[3].erase(0, cmd[3].find(',') + 1);
    }
}

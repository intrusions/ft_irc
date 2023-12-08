/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_user_limit.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:50:23 by xel               #+#    #+#             */
/*   Updated: 2023/12/08 06:23:40 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Channel.hpp"
#include "utils.hpp"
#include <cstdlib>

//todo
static int32_t  limits_is_valid(std::string limits) {

    return (std::atoi(limits.c_str()));
}

void    Server::_mode_user_limit(Channel *channel, std::vector<std::string> cmd, bool add_or_rm, int32_t fd) {
    
    uint8_t                     nlimits;
    std::vector<std::string>    reply_arg;

    if (add_or_rm == REMOVE_MODE) {
        logger(INFO, "Mode -l set, user limit mode deleted on this channel");

        channel->set_mflags(channel->get_mflags() & ~CHANNEL_MODE_USER_LIMIT);
        channel->set_limits(CHANNEL_DEFAULT_LIMITS);

        reply_arg.push_back("-l");    
        _send_nmode_to_channel(channel, fd, reply_arg);
    
    } else if (add_or_rm == ADD_MODE) {
        
        if (cmd.size() >= 4) {
            
            if ((nlimits = limits_is_valid(cmd[3])) != false) {
                logger(INFO, "Mode +l set, new user limit on this channel");
                
                channel->set_mflags(channel->get_mflags() | CHANNEL_MODE_USER_LIMIT);
                channel->set_limits(nlimits);

                reply_arg.push_back("+l");    
                _send_nmode_to_channel(channel, fd, reply_arg);

            } else {
                logger(WARNING, "Invalid user limit");

                reply_arg.push_back(cmd[1]);
                reply_arg.push_back("+l");
                reply_arg.push_back(cmd[3]);
                reply_arg.push_back(":Invalid user limit");
                _send_reply(fd, 696, reply_arg);
            }
        } else {
            logger(WARNING, "Missing user limit");

            reply_arg.push_back(cmd[1]);
            reply_arg.push_back("+l");
            reply_arg.push_back("Missing user limit");
            reply_arg.push_back(":Missing user limit");
            _send_reply(fd, 696, reply_arg);
        }
    }
}

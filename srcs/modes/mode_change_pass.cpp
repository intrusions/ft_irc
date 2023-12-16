/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_change_pass.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:50:23 by xel               #+#    #+#             */
/*   Updated: 2023/12/16 01:46:02 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Channel.hpp"
#include "utils.hpp"

// todo
static bool     pass_is_valid(std::string pass) {
    
    (void)pass;
    return (true);
}

void    Server::_mode_change_pass(Channel *channel, std::vector<std::string> &cmd, bool add_or_rm, int32_t fd) {
    
    std::vector<std::string>    reply_arg;
    std::string                 password;

    if (add_or_rm == REMOVE_MODE) {
        logger(INFO, "Mode -k set, password deleted on this channel");

        channel->set_mflags(channel->get_mflags() & ~CHANNEL_MODE_CHANGE_PASS);
        channel->set_password("");

        reply_arg.push_back("-k");
        _send_nmode_to_channel(channel, fd, reply_arg);
    
    } else if (add_or_rm == ADD_MODE) {

        if (cmd.size() >= 4) {
            
            password = cmd[3].substr(0, cmd[3].find(','));
            
            if (pass_is_valid(password)) {
                logger(INFO, "Mode +k set, new password added");

                channel->set_mflags(channel->get_mflags() | CHANNEL_MODE_CHANGE_PASS);
                channel->set_password(password);

                reply_arg.push_back("+k");    
                _send_nmode_to_channel(channel, fd, reply_arg);
            
            } else {
                logger(WARNING, "Key is invalid");

                reply_arg.push_back(cmd[1]);
                reply_arg.push_back("+k");
                reply_arg.push_back(password);
                reply_arg.push_back(":Invalid pattern key");
                _send_reply(fd, 696, reply_arg);
            }
            cmd[3].erase(0, cmd[3].find(',') + 1);

        } else {
            logger(WARNING, "Missing key");

            reply_arg.push_back(cmd[1]);
            reply_arg.push_back("+k");
            reply_arg.push_back("Missing key");
            reply_arg.push_back(":Need a valid key");
            _send_reply(fd, 696, reply_arg);
        }
    }
}

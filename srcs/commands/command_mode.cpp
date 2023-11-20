/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_mode.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:55:28 by xel               #+#    #+#             */
/*   Updated: 2023/11/20 18:33:22 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "utils.hpp"
#include "assert.h"

void  Server::_handle_channel_mode(std::vector<std::string> cmd, int32_t fd) {
  
    std::vector<std::string>    reply_arg;
    Channel                     *channel = NULL;
    
  	for (std::vector<Channel *>::iterator it = _channel.begin(); it != _channel.end(); it++) {
    	
        if ((*it)->get_name() == cmd[1]) {
            channel = *it;
			break ;
        }
    }
	if (channel == NULL) {
        logger(WARNING, "Channel is not in the server");

        reply_arg.push_back(cmd[1]);
        _send_reply(fd, 403, reply_arg);
		return;
	}

	if (find_fds_in_vec(channel->fetch_operator_fds(), fd) == false) {
		logger(WARNING, "Client are not operator on this channel");
		
        reply_arg.push_back(cmd[1]);
        _send_reply(fd, 482, reply_arg);
		return;
	}

	std::string mode_string = cmd[2];
	switch (mode_string[0]) {
		case '+':
			// handle_add(&mode_string[1]);
		    logger(INFO, "+ Mode");
		break;
		case '-':
			// handle_remove(&mode_string[1]);
		    logger(INFO, "- Mode");
		break;
	}
}

void	Server::_command_mode(std::vector<std::string> cmd, int32_t fd) {

    std::vector<std::string>    reply_arg;

    if (cmd.size() < 3) {
        logger(WARNING, "No channel name or mode are given");

        reply_arg.push_back("No mode");
		_send_reply(fd, 221, reply_arg);
        return ;
    }
    
    
    if (cmd[1][0] == '#') {
        _handle_channel_mode(cmd, fd);
    } else {
        // handle_user_mode();
    }
}

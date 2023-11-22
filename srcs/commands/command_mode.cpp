/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_mode.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:55:28 by xel               #+#    #+#             */
/*   Updated: 2023/11/22 12:58:58 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "utils.hpp"
#include "assert.h"

static uint64_t mode_to_flag(const char mode) {
    
    switch (mode) {
        case 'i': return (CHANNEL_MODE_INVITE_ONLY);
        case 't': return (CHANNEL_MODE_TOPIC_MANAGE);
        case 'k': return (CHANNEL_MODE_CHANGE_PASS);
        case 'o': return (CHANNEL_MODE_OPERATOR_PRIV);
        case 'l': return (CHANNEL_MODE_USER_LIMIT);
        default:  return 0;
    }
}

void Server::_handle_add_mode(std::string modes, Channel *channel, std::vector<std::string> cmd, int32_t fd) {
    
    std::string                 message;
    std::vector<std::string>    reply_arg;
    
    for (uint8_t i = 0; modes[i]; i++) {
        
        uint64_t mode = mode_to_flag(modes[i]);
        if (mode) {
            
            switch (mode) {
                case (CHANNEL_MODE_INVITE_ONLY):    _mode_invite_only(channel, ADD_MODE);           break;
                case (CHANNEL_MODE_CHANGE_PASS):    _mode_change_pass(channel, cmd, ADD_MODE, fd);  break;
                case (CHANNEL_MODE_TOPIC_MANAGE):                                                   break;
                case (CHANNEL_MODE_OPERATOR_PRIV):                                                  break;
                case (CHANNEL_MODE_USER_LIMIT):                                                     break;
            }
        } else {
            logger(INFO, "Channel mode is not supported on this server");
            _send_reply(fd, 501, reply_arg);
        }
    }
}

void Server::_handle_remove_mode(std::string modes, Channel *channel, std::vector<std::string> cmd, int32_t fd) {
    
    std::string                 message;
    std::vector<std::string>    reply_arg;

    for (uint8_t i = 0; modes[i]; i++) {
        
        uint64_t mode = mode_to_flag(modes[i]);
        if (mode) {
            
            switch (mode) {
                case (CHANNEL_MODE_INVITE_ONLY):    _mode_invite_only(channel, REMOVE_MODE);            break;
                case (CHANNEL_MODE_CHANGE_PASS):    _mode_change_pass(channel, cmd, REMOVE_MODE, fd);   break;
                case (CHANNEL_MODE_TOPIC_MANAGE):                                                       break;
                case (CHANNEL_MODE_OPERATOR_PRIV):                                                      break;
                case (CHANNEL_MODE_USER_LIMIT):                                                         break;
            }
        } else {
            logger(INFO, "Channel mode is not supported on this server");
            _send_reply(fd, 501, reply_arg);
        }
    }
}

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
			_handle_add_mode(&mode_string[1], channel, cmd, fd);
		break;
		case '-':
			_handle_remove_mode(&mode_string[1], channel, cmd, fd);
		break;
	}

    DEBUG_PRINT_MODESTR(channel->get_mflags());
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_join.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:36:53 by xel               #+#    #+#             */
/*   Updated: 2023/11/08 23:42:11 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"
#include "../../includes/User.hpp"
#include "../../includes/Channel.hpp"
#include "../../includes/utils.hpp"

void	Server::_command_join(std::vector<std::string> cmd, int32_t fd) {

	std::vector<std::string>	err_param;

	if (cmd.size() == 1) {
		err_param.push_back(cmd[0]);
		_send_reply(fd, 461, err_param);
	}

	for (std::vector<Channel *>::iterator it = _channel.begin(); it != _channel.end(); it++) {
		if (cmd[1] == (*it)->get_name()) {
			logs("logs(this channel name is already exist, joining channel...)", 3);
			(*it)->get_fds().push_back(fd);
			DEBUG_PRINT_ALL_CHANNEL(_channel);
			return ;
		}
	}

	logs("logs(this channel name doesn't exist, creating channel...)", 3);
	_channel.push_back(new Channel(cmd[1], fd));
	DEBUG_PRINT_ALL_CHANNEL(_channel);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pass.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:36:53 by xel               #+#    #+#             */
/*   Updated: 2023/10/26 00:39:00 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"
#include "../../includes/User.hpp"

void	Server::_command_pass(std::vector<std::string> cmd, int32_t fd) {

	std::vector<std::string>	err_param;

	if (cmd.size() != 2) {
		err_param.push_back(cmd[0]);
		_send_reply(fd, 461, err_param);
		return ;
	}

	if (_users[fd]->get_nickname() != "GUEST") {
		_send_reply(fd, 462, err_param);
		return ;
	}

	if (_password != cmd[1]) {
		_send_reply(fd, 464, err_param);
		return ;		
	}

	_users[fd]->set_pass_is_valid(true);
}
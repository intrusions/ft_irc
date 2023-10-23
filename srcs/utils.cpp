/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:51:08 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/23 20:38:03 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.hpp"

/* basic */
std::vector<std::string>	split_space(std::string cmd) {
	
	std::vector<std::string>	tokens;
	std::istringstream			token_stream(cmd);
	std::string 				token;
	
	while (std::getline(token_stream, token, ' ')) {
		tokens.push_back(token);
	}
	return (tokens);
}

/* debug */
void	DEBUG_PRINT_CMD_VEC(User *user) {
	
	uint16_t i = 0;
	std::vector<std::string> *cmd = user->fetch_commands();
	
	for (std::vector<std::string>::iterator it = cmd->begin(); it != cmd->end(); it++) {
		std::cout << "_fd[" << user->get_fd() << "] | ";
		std::cout << "_commands[" << i << "] : " << *it << std::endl;
		i++;
	}
	std::cout << std::endl;
}

void	DEBUG_PRINT_CMD_SPLIT_VEC(std::vector<std::string> cmd, User *user) {
	
	uint16_t i = 0;
	
	for (std::vector<std::string>::iterator it = cmd.begin(); it != cmd.end(); it++) {
		std::cout << "_fd[" << user->get_fd() << "] | ";
		std::cout << "commands_split[" << i << "] : " << *it << std::endl;
		i++;
	}
	std::cout << std::endl;
}
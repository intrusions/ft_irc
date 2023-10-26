/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:51:08 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/26 17:54:05 by xel              ###   ########.fr       */
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

void logs(std::string str, uint8_t color) {

	std::string color_code;

	switch (color) {
		case 1: color_code = RED_TEXT;		break;
		case 2: color_code = GREEN_TEXT;	break;
		case 3: color_code = YELLOW_TEXT;	break;
		case 4: color_code = BLUE_TEXT;		break;
		case 5:	color_code = MAGENTA_TEXT;	break;
		case 6:	color_code = CYAN_TEXT;		break;
		default: color_code = RESET_COLOR;	break;
	}
	std::cout << color_code << str << RESET_COLOR << std::endl;
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
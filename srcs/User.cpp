/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:52:09 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/21 22:37:48 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"

/* constructor/destructor */
User::User(int32_t fd, struct sockaddr_in addr, Server *serv)
	: _fd(fd)
	, _server(serv)
	, _address(addr) {}

User::~User() {}


/* `User` function */
void	User::receive_client_input() {
	
	char			buff[512] = {};
	int64_t			bytes_read;
	uint8_t			delimiter_size;
	int32_t			pos_delimiter;
	std::string		copy_buff;

	bytes_read = recv(_fd, &buff, sizeof(buff), 0);
	
	if (bytes_read == -1) {
		return ;
	} else if (bytes_read == 512) {
		buff[510] = '\n';
		buff[511] = '\0';
	}

	copy_buff = buff; 

	while (copy_buff.length()){
	
		if ((pos_delimiter = copy_buff.find("\r\n")) != std::string::npos) {
			delimiter_size = 2;
		} else if ((pos_delimiter = copy_buff.find("\n")) != std::string::npos) {
			delimiter_size = 1;
		}

		_commands.push_back(copy_buff.substr(0, pos_delimiter));
		copy_buff.erase(0, pos_delimiter + delimiter_size);
	}
}

void	User::exec_client_commands() {

	for (std::vector<std::string>::iterator it = _commands.begin(); it != _commands.end(); ) {

		std::vector<std::string> cmd_splited = split_space(*it);

		if (cmd_splited.size()) {
			std::cout << "debug: " << cmd_splited[0] << std::endl;
		
			if (cmd_splited[0] == "/NICK" || cmd_splited[0] == "NICK") {
				std::cout << "nick function" << std::endl;
			} else if (cmd_splited[0] == "/TOPIC" || cmd_splited[0] == "TOPIC") {
				std::cout << "topic function" << std::endl;
			} else if (cmd_splited[0] == "/die" || cmd_splited[0] == "die") {
				std::cout << "die function" << std::endl;
			} else if (cmd_splited[0] == "/kill" || cmd_splited[0] == "kill") {
				std::cout << "kill function" << std::endl;
			} else if (cmd_splited[0] == "/OPER" || cmd_splited[0] == "OPER") {
				std::cout << "oper function" << std::endl;
			} else if (cmd_splited[0] == "/PASS" || cmd_splited[0] == "PASS") {
				std::cout << "pass function" << std::endl;
			} else if (cmd_splited[0] == "/USER" || cmd_splited[0] == "USER") {
				std::cout << "user function" << std::endl;
			} else if (cmd_splited[0] == "/QUIT" || cmd_splited[0] == "QUIT") {
				std::cout << "quit function" << std::endl;
			} else if (cmd_splited[0] == "/MODE" || cmd_splited[0] == "MODE") {
				std::cout << "mode function" << std::endl;
			} else if (cmd_splited[0] == "/PRIVMSG" || cmd_splited[0] == "PRIVMSG") {
				std::cout << "privmsg function" << std::endl;
			} else if (cmd_splited[0] == "/NOTICE" || cmd_splited[0] == "NOTICE") {
				std::cout << "notice function" << std::endl;
			} else if (cmd_splited[0] == "/JOIN" || cmd_splited[0] == "JOIN") {
				std::cout << "join function" << std::endl;
			} else if (cmd_splited[0] == "/LIST" || cmd_splited[0] == "LIST") {
				std::cout << "list function" << std::endl;
			} else if (cmd_splited[0] == "/INVITE" || cmd_splited[0] == "INVITE") {
				std::cout << "invite function" << std::endl;
			} else if (cmd_splited[0] == "/KICK" || cmd_splited[0] == "KICK") {
				std::cout << "kick function" << std::endl;
			} else if (cmd_splited[0] == "/PART" || cmd_splited[0] == "PART") {
				std::cout << "part function" << std::endl;
			} else if (cmd_splited[0] == "/PING" || cmd_splited[0] == "PING") {
				std::cout << "ping function" << std::endl;
			} else if (cmd_splited[0] == "/PONG" || cmd_splited[0] == "PONG") {
				std::cout << "pong function" << std::endl;
			}
		}
		it = _commands.erase(it);
	}
}


/* accessor */
int32_t	User::get_fd(void) { return (_fd); }

/* utils */
std::vector<std::string>	User::split_space(std::string cmd) {
	
	std::vector<std::string>	tokens;
	std::istringstream			token_stream(cmd);
	std::string 				token;
	
	while (std::getline(token_stream, token, ' ')) {
		tokens.push_back(token);
	}
	return (tokens);
}

/* debug */
void	User::DEBUG_PRINT_CMD_VEC(void) {
	
	uint16_t i = 0;
	
	for (std::vector<std::string>::iterator it = _commands.begin(); it != _commands.end(); it++) {
		std::cout << "_fd[" << _fd << "] | ";
		std::cout << "_commands[" << i << "] : " << *it << std::endl;
		i++;
	}
	std::cout << std::endl;
}

void	User::DEBUG_PRINT_CMD_SPLIT_VEC(std::vector<std::string> cmd) {
	
	uint16_t i = 0;
	
	for (std::vector<std::string>::iterator it = cmd.begin(); it != cmd.end(); it++) {
		std::cout << "_fd[" << _fd << "] | ";
		std::cout << "commands_split[" << i << "] : " << *it << std::endl;
		i++;
	}
	std::cout << std::endl;
}

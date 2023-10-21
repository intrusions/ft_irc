/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:52:09 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/21 18:08:50 by jucheval         ###   ########.fr       */
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


/* accessor */
int32_t	User::get_fd(void) { return (_fd); }

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

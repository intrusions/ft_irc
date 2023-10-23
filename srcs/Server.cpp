/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:13 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/21 21:24:13 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/User.hpp"
#include "../includes/utils.hpp"


/* constructor/destructor */
Server::Server(char *port, char *password) {
	
	_port = _check_port(port);
	_password = _check_password(password);
}

Server::~Server() {}

/* main argument's parsing */
uint16_t    Server::_check_port(char *port) {
	
	uint16_t	nPort = atoi(port);

	for (uint8_t i = 0; port[i]; i++) {
		if (!isdigit(port[i]))
			throw std::invalid_argument("`error`: invalid port");
	}

	if (nPort < 1024 || nPort > 49551)
		throw std::invalid_argument("`error`: invalid port");
	
	return (nPort);
}

std::string Server::_check_password(char *password) {
	
	std::string nPass(password);

	if (nPass.size() < 6)
		throw std::invalid_argument("`error`: invalid password");
	
	return (nPass);
}

/* server initialisation */
void		Server::server_initialisation() {

	int32_t	optsock = 1;
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (_sockfd == -1)
		throw Server::SocketInitialisationFailed();
	
	if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &optsock, sizeof(int32_t)) < 0)
		throw Server::SetSockOptFailed();

	memset(&_addr, 0, sizeof(_addr));

	_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(_port);

	if (bind(_sockfd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
		throw Server::BindFailed();

	if (listen(_sockfd, SOMAXCONN) == -1)
		throw Server::ListenFailed();

	_fds.push_back(pollfd());
	_fds.back().fd = _sockfd;
	_fds.back().events = (POLLIN | POLLHUP);
}

/* server loop */
void	Server::run() {

	if (poll(&_fds.front(), _fds.size(), -1) == -1)
		return ;		

	if (_fds.front().revents == POLLIN) {
		_accept_user();
	} else {
		
		for (std::vector<pollfd>::iterator it = _fds.begin() + 1; it != _fds.end(); it++) {
			if (it->revents == POLLIN) {
				_receive_client_input(_users[it->fd]);
				_exec_client_commands(_users[it->fd]);
			} else if ((it->revents & POLLRDHUP) == POLLRDHUP) {
				_delete_user(it->fd);
				break ;
			}
		}		
	}
}

/* receive command from client, parse, execute and return an output */
void	Server::_receive_client_input(User *user) {
	
	char			buff[512] = {};
	int64_t			bytes_read;
	uint8_t			delimiter_size;
	int32_t			pos_delimiter;
	std::string		copy_buff;

	bytes_read = recv(user->get_fd(), &buff, sizeof(buff), 0);
	
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

		user->fetch_commands()->push_back(copy_buff.substr(0, pos_delimiter));
		copy_buff.erase(0, pos_delimiter + delimiter_size);
	}
}

void	Server::_exec_client_commands(User *user) {

	std::vector<std::string> *cmd = user->fetch_commands();

	for (std::vector<std::string>::iterator it = cmd->begin(); it != cmd->end(); ) {

		std::vector<std::string> cmd_splited = split_space(*it);

		if (cmd_splited.size()) {
		
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
				// _server->_command_pass(cmd_splited, _fd);
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
		it = cmd->erase(it);
	}
}

/* user management (add && delete) */
void	Server::_accept_user() {
	
	struct sockaddr_in	addr;
	memset(&addr, 0, sizeof(addr));
	
	socklen_t sock_len = sizeof(addr);
	int32_t fd = accept(_sockfd, (struct sockaddr *)&addr, &sock_len);

	if (fd == -1) {
		std::cout << "error: `accept()` function failed" << std::endl;
		return ;
	}

	_users[fd] = new User(fd, addr, this);

	_fds.push_back(pollfd());
	_fds.back().fd = fd;
	_fds.back().events = (POLLIN | POLLRDHUP);
}

void	Server::_delete_user(int32_t fd) {
	
	close(fd);
	delete _users[fd];
	_users.erase(_users.find(fd));
	
	for (std::vector<pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it) {
		if (it->fd == fd) {
			_fds.erase(it);
			return ;
		}
	}
}

// void	Server::_command_pass(std::vector<std::string> cmd, int32_t fd) {

// 	if (cmd.size() != 2) {

// 		send_reply(fd, 461, )
// 	}
// }

// void	_send_reply(int32_t fd, int32_t err, std::vector<std::string> err_param) {

// }


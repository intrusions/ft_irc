/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:13 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/28 00:37:56 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/User.hpp"
#include "../includes/utils.hpp"


/* constructor/destructor */
Server::Server(char *port, char *password) {
	
	_port = _check_port(port);
	_password = _check_password(password);
	_networkname = "Porte de la chapelle";
	_servername = "Crackland";
	_version = "1";

	time_t	now = time(0);
    tm		*ltm = localtime(&now);
    char 	date[32];
    
	strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", ltm);
    
	_start_time = std::string(date);
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
		logs("logs(client socket created)", 2);
		_accept_user();
	} else {
		
		for (std::vector<pollfd>::iterator it = _fds.begin() + 1; it != _fds.end(); it++) {
			if (it->revents == POLLIN) {
				_receive_client_input(_users[it->fd]);
				_exec_client_commands(_users[it->fd]);
			} else if ((it->revents & POLLRDHUP) == POLLRDHUP) {
				logs("logs(client socket destroyed)", 1);
				_delete_user(it->fd);
				break ;
			}
		}		
	}
}


/* receive command from client, and fill `_commands` vector with string splited by '\n' or '\r\n' */
void	Server::_receive_client_input(User *user) {
	
	char			buff[512] = {};
	int64_t			bytes_read;
	uint8_t			delimiter_size = 0;
	uint64_t		pos_delimiter;
	std::string		copy_buff;

	bytes_read = recv(user->get_fd(), &buff, sizeof(buff), 0);
	
	if (bytes_read == -1) {
		return ;
	} else {
		buff[bytes_read] = 0;
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

/* execute one by one the command in `_commands`, and erase node after execution of it */
void	Server::_exec_client_commands(User *user) {

	std::vector<std::string> *cmd = user->fetch_commands();

	for (std::vector<std::string>::iterator it = cmd->begin(); it != cmd->end(); it = cmd->erase(it)) {

		std::vector<std::string> cmd_splited = split_space(*it);

		if (cmd_splited.size()) {

			if (cmd_splited[0] == "/PASS" || cmd_splited[0] == "PASS")				{ _command_pass(cmd_splited, user->get_fd()); } 
			else if (cmd_splited[0] == "/NICK" || cmd_splited[0] == "NICK") 		{ _command_nick(cmd_splited, user->get_fd()); } 
			else if (cmd_splited[0] == "/USER" || cmd_splited[0] == "USER") 		{ _command_user(*it, user->get_fd()); }
			else if (cmd_splited[0] == "/PING" || cmd_splited[0] == "PING")			{ _command_ping(user->get_fd()); }
			else if (cmd_splited[0] == "/die" || cmd_splited[0] == "die") 			{ std::cout << "die function" << std::endl;	}
			else if (cmd_splited[0] == "/kill" || cmd_splited[0] == "kill")			{ std::cout << "kill function" << std::endl; }
			else if (cmd_splited[0] == "/OPER" || cmd_splited[0] == "OPER")			{ std::cout << "oper function" << std::endl; }
			else if (cmd_splited[0] == "/TOPIC" || cmd_splited[0] == "TOPIC")		{ std::cout << "topic function" << std::endl; }
			else if (cmd_splited[0] == "/QUIT" || cmd_splited[0] == "QUIT")			{ std::cout << "quit function" << std::endl; }
			else if (cmd_splited[0] == "/MODE" || cmd_splited[0] == "MODE")			{ std::cout << "mode function" << std::endl; }
			else if (cmd_splited[0] == "/PRIVMSG" || cmd_splited[0] == "PRIVMSG")	{ std::cout << "privmsg function" << std::endl; }
			else if (cmd_splited[0] == "/NOTICE" || cmd_splited[0] == "NOTICE")		{ std::cout << "notice function" << std::endl; }
			else if (cmd_splited[0] == "/JOIN" || cmd_splited[0] == "JOIN")			{ std::cout << "join function" << std::endl; }
			else if (cmd_splited[0] == "/LIST" || cmd_splited[0] == "LIST")			{ std::cout << "list function" << std::endl; }
			else if (cmd_splited[0] == "/INVITE" || cmd_splited[0] == "INVITE")		{ std::cout << "invite function" << std::endl; }
			else if (cmd_splited[0] == "/KICK" || cmd_splited[0] == "KICK")			{ std::cout << "kick function" << std::endl; }
			else if (cmd_splited[0] == "/PART" || cmd_splited[0] == "PART")			{ std::cout << "part function" << std::endl; }
			else if (cmd_splited[0] == "/PONG" || cmd_splited[0] == "PONG")			{ std::cout << "pong function" << std::endl; }
		}
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
	
	for (std::vector<pollfd>::iterator it = _fds.begin() + 1; it != _fds.end(); it++) {
		if (it->fd == fd) {
			_fds.erase(it);
			return ;
		}
	}
}


/* reply management */
void	Server::_send_reply(int32_t fd, int32_t err, std::vector<std::string> err_param) {

	std::string reply;

	switch(err) {

		case 001: reply = RPL_WELCOME(_users[fd], _networkname, _servername);	break;
		case 002: reply = RPL_YOURHOST(_users[fd], _servername, _version);		break;
		case 003: reply = RPL_CREATED(_users[fd], _start_time, _servername);					break;
		case 004: reply = RPL_MYINFO(_users[fd], _servername, _version);		break;
		case 461: reply = ERR_NEEDMOREPARAMS(_users[fd], err_param);			break;
		case 462: reply = ERR_ALREADYREGISTERED(_users[fd]);					break;
		case 464: reply = ERR_PASSWDMISMATCH(_users[fd]);						break;
		case 431: reply = ERR_NONICKNAMEGIVEN(_users[fd]);						break;
		case 432: reply = ERR_ERRONEUSNICKNAME(_users[fd], err_param);			break;
		case 433: reply = ERR_NICKNAMEINUSE(_users[fd], err_param);				break;
		case 1001: reply = PER_NICKNAMECHANGE(err_param);						break;
	}

	if (send(fd, reply.c_str(), reply.length(), 0) == -1)
		return ;
}


/* accessor */
std::string Server::get_networkname()	{ return (_networkname); }
std::string Server::get_servername()	{ return (_servername); }
std::string Server::get_start_time()	{ return (_start_time); }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:13 by jucheval          #+#    #+#             */
/*   Updated: 2023/11/10 16:36:18 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "utils.hpp"

/* constructor/destructor */
Server::Server(const char *port, const char *password) {
	__abort_if_fail__(port);
	__abort_if_fail__(password);
	
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
uint16_t    Server::_check_port(const char *port) const {
	__abort_if_fail__(port);
	
	uint16_t	nPort = atoi(port);

	for (uint8_t i = 0; port[i]; i++) {
		if (!isdigit(port[i]))
			throw std::invalid_argument("`error`: invalid port");
	}

	if (nPort < 1024 || nPort > 49551)
		throw std::invalid_argument("`error`: invalid port");
	
	return (nPort);
}

std::string Server::_check_password(const char *password) const{
	
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
		logger(INFO, "client socket created");
		_accept_user();
	} else {
		
		for (std::vector<pollfd>::iterator it = _fds.begin() + 1; it != _fds.end(); it++) {
			if (it->revents == POLLIN) {
				_receive_client_input(_users[it->fd]);
				_exec_client_commands(_users[it->fd]);

#ifdef __linux__
			} else if ((it->revents & POLLRDHUP) == POLLRDHUP) {
#else
			} else if ((it->revents & POLLHUP) == POLLHUP) {
#endif

				logger(INFO, "client socket destroyed");
				_delete_user(it->fd);
				break ;
			}
		}		
	}
}


/* receive command from client, and fill `_commands` vector with string splited by '\n' or '\r\n' */
void	Server::_receive_client_input(User *user) {
	__abort_if_fail__(user);
	
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

t_command_type get_command_type_from_string(std::string &string)  {
	if (string[0] == '/') string.erase(0, 1);

	if (!string.compare(COMMAND_PASS_STR))
		return COMMAND_TYPE_PASS; 

	if (!string.compare(COMMAND_NICK_STR))
		return COMMAND_TYPE_NICK; 
	
	if (!string.compare(COMMAND_USER_STR))
		return COMMAND_TYPE_USER; 

	if (!string.compare(COMMAND_PING_STR))
		return COMMAND_TYPE_PING; 

	if (!string.compare(COMMAND_PONG_STR))
		return COMMAND_TYPE_PONG; 

	if (!string.compare(COMMAND_DIE_STR))
		return COMMAND_TYPE_DIE; 

	if (!string.compare(COMMAND_KILL_STR))
		return COMMAND_TYPE_KILL; 
	
	if (!string.compare(COMMAND_OPER_STR))
		return COMMAND_TYPE_OPER; 
	
	if (!string.compare(COMMAND_TOPIC_STR))
		return COMMAND_TYPE_TOPIC; 
	
	if (!string.compare(COMMAND_QUIT_STR))
		return COMMAND_TYPE_QUIT; 
	
	if (!string.compare(COMMAND_MODE_STR))
		return COMMAND_TYPE_MODE; 
	
	if (!string.compare(COMMAND_PRIVMSG_STR))
		return COMMAND_TYPE_PRIVMSG; 
	
	if (!string.compare(COMMAND_NOTICE_STR))
		return COMMAND_TYPE_NOTICE; 
	
	if (!string.compare(COMMAND_JOIN_STR))
		return COMMAND_TYPE_JOIN; 
	
	if (!string.compare(COMMAND_LIST_STR))
		return COMMAND_TYPE_LIST;
	
	if (!string.compare(COMMAND_INVITE_STR))
		return COMMAND_TYPE_USER; 
	
	if (!string.compare(COMMAND_KICK_STR))
		return COMMAND_TYPE_KICK; 
	
	if (!string.compare(COMMAND_PART_STR))
		return COMMAND_TYPE_PASS; 
	
	return COMMAND_TYPE_UNKNOWN;
}

/* execute one by one the command in `_commands`, and erase node after execution of it */
void	Server::_exec_client_commands(User *user) {
	__abort_if_fail__(user);

	//DEBUG_PRINT_CMD_VEC(user);
	std::vector<std::string> *cmd = user->fetch_commands();
	for (std::vector<std::string>::iterator it = cmd->begin(); it != cmd->end(); it = cmd->erase(it)) {

		Command command = Command(*it, user->get_fd());
	
		std::vector<std::string> cmd_splited = split(*it, ' ');
		//DEBUG_PRINT_CMD_SPLIT_VEC(cmd_splited, user);

		if (cmd_splited.size()) {
		
			t_command_type cmdtype = get_command_type_from_string(cmd_splited[0]);
			std::cout << cmdtype << std::endl;
			switch (cmdtype) {
				case COMMAND_TYPE_PASS: _command_pass(cmd_splited, user->get_fd());    break;
				case COMMAND_TYPE_NICK: _command_nick(cmd_splited, user->get_fd());    break;
				case COMMAND_TYPE_USER: _command_user(*it, user->get_fd());            break;
				case COMMAND_TYPE_PING: _command_ping(user->get_fd());                 break;
				case COMMAND_TYPE_PONG: _command_pong();                               break;
				case COMMAND_TYPE_JOIN: _command_join(cmd_splited, user->get_fd());    break;
				case COMMAND_TYPE_DIE:                                                 break;
				case COMMAND_TYPE_KILL:                                                break;
				case COMMAND_TYPE_OPER:                                                break;
				case COMMAND_TYPE_TOPIC:                                               break;
				case COMMAND_TYPE_QUIT:                                                break;
				case COMMAND_TYPE_MODE:                                                break;
				case COMMAND_TYPE_PRIVMSG:                                             break;
				case COMMAND_TYPE_NOTICE:                                              break;
				case COMMAND_TYPE_LIST:                                                break;
				case COMMAND_TYPE_INVITE:                                              break;
				case COMMAND_TYPE_KICK:                                                break;
				case COMMAND_TYPE_PART:                                                break;

				case COMMAND_TYPE_UNKNOWN:
				default: 
					logger(ERROR, "Unrecognized command: " + cmd_splited[0]);
			}
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

	_users[fd] = new User(fd /*, addr, this */);

	_fds.push_back(pollfd());
	_fds.back().fd = fd;

#ifdef __linux
	_fds.back().events = (POLLIN | POLLRDHUP);
#else
	_fds.back().events = (POLLIN | POLLHUP);
#endif

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
void	Server::_send_reply(int32_t fd, int32_t code, std::vector<std::string> &err_param) {

	std::string reply;

	switch(code) {

		case 001: reply = CREATE_RPL_WELCOME(_users[fd], _networkname, _servername);	break;
		case 002: reply = CREATE_RPL_YOURHOST(_users[fd], _servername, _version);		break;
		case 003: reply = CREATE_RPL_CREATED(_users[fd], _start_time, _servername);	break;
		case 004: reply = CREATE_RPL_MYINFO(_users[fd], _servername, _version);		break;
		case 332: reply = RPL_TOPIC(_users[fd], err_param);						break;
		case 461: reply = CREATE_ERR_NEEDMOREPARAMS(_users[fd], err_param);			break;
		case 462: reply = CREATE_ERR_ALREADYREGISTERED(_users[fd]);					break;
		case 464: reply = CREATE_ERR_PASSWDMISMATCH(_users[fd]);						break;
		case 431: reply = CREATE_ERR_NONICKNAMEGIVEN(_users[fd]);						break;
		case 432: reply = CREATE_ERR_ERRONEUSNICKNAME(_users[fd], err_param);			break;
		case 433: reply = CREATE_ERR_NICKNAMEINUSE(_users[fd], err_param);				break;
		case 475: reply = ERR_BADCHANNELKEY(_users[fd], err_param);				break;
		case 1001: reply = CREATE_PER_NICKNAMECHANGE(err_param);						break;
	}

	if (send(fd, reply.c_str(), reply.length(), 0) == -1)
		return ;
}


/* accessor */
std::string Server::get_networkname() const	{ return (_networkname); }
std::string Server::get_servername() const	{ return (_servername); }
std::string Server::get_start_time() const	{ return (_start_time); }

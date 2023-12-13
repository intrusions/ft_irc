/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:13 by jucheval          #+#    #+#             */
/*   Updated: 2023/12/13 21:22:22 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"
#include "utils.hpp"

/**
 * Constructor for the Server class.
 *
 * This constructor initializes a Server object with the provided port and password.
 * It checks and sets the port and password after validation. It also sets default
 * values for other server properties such as network name, server name, and version.
 * The constructor calculates and stores the server start time.
 */
Server::Server(const char *port, const char *password) {
    __abort_if_fail__(port);
    __abort_if_fail__(password);

    _port = _check_port(port);
    _password = _check_password(password);
    _networkname = "Porte de la chapelle";
    _servername = "Crackland";
    _version = "1";

    time_t  now = time(0);
    tm      *ltm = localtime(&now);
    char    date[32];

    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", ltm);

    _start_time = std::string(date);
}

Server::~Server() {}


/**
 * Check and convert a string to a valid port number.
 */
uint16_t    Server::_check_port(const char *port) const {
    __abort_if_fail__(port);
    
    uint16_t    nPort = atoi(port);

    for (uint8_t i = 0; port[i]; i++) {
        if (!isdigit(port[i]))
            throw std::invalid_argument("`error`: invalid port");
    }

    if (nPort < 1024 || nPort > 49551)
        throw std::invalid_argument("`error`: invalid port");
    
    return (nPort);
}

/**
 * Check and validate a password string.
 */
std::string Server::_check_password(const char *password) const{
    
    std::string nPass(password);

    if (nPass.size() < 6)
        throw std::invalid_argument("`error`: invalid password");
    
    return (nPass);
}


/**
 * Initialize the server by creating, configuring, and binding a socket,
 *        and set up for listening using the poll mechanism.
 *
 * This function performs socket creation, sets options for reuse, 
 * binds to a specified address and port, and sets up for listening.
 */
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


/**
 * Run the server, handling events using the poll mechanism.
 * 
 * This function uses the poll system call to wait for events on the registered
 * file descriptors. It handles the events for the server socket and client
 * sockets accordingly, calling relevant functions.
 *
 * - If the server socket has an event (POLLIN), it indicates a new connection
 *   request, and the `_accept_user` function is called to handle the new user.
 *
 * - For client sockets with events (POLLIN), the `_receive_client_input` function
 *   is called to receive input, and the `_exec_client_commands` function is
 *   called to execute client commands based on the received input.
 *
 * - On client socket events (POLLRDHUP or POLLHUP), indicating that the client
 *   has disconnected, the associated user is deleted, and the logger is informed.
 */
void	Server::run() {

    if (poll(&_fds.front(), _fds.size(), -1) == -1)
        return ;

    if (_fds.front().revents == POLLIN) {
        logger(INFO, "Client socket created");
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

                logger(INFO, "Client socket destroyed");
                _delete_user(it->fd);
                break ;
            }
        }		
    }
}


/**
 * Receive input from a client and process it.
 *
 * This function reads input from the specified client socket and processes it.
 * The received data is parsed based on newline characters ("\r\n" or "\n"), and
 * individual commands are added to the user's command queue for further processing.
 */
void	Server::_receive_client_input(User *user) {
    __abort_if_fail__(user);
    
    char            buff[512] = {};
    int64_t         bytes_read;
    uint8_t         delimiter_size = 0;
    uint64_t        pos_delimiter;
    std::string     copy_buff;

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

/**
 * Get the command type from a string representation.
 *
 * This function takes a string representation of a command and returns its
 * corresponding command type. It checks the provided string against predefined
 * command strings and returns the appropriate command type.
 */
uint8_t Server::_get_command_type_from_string(std::string &string) const {
    
    if (string[0] == '/')
        string.erase(0, 1);

    if (!string.compare(COMMAND_PASS_STR))      return (COMMAND_TYPE_PASS); 
    if (!string.compare(COMMAND_NICK_STR))      return (COMMAND_TYPE_NICK); 
    if (!string.compare(COMMAND_USER_STR))      return (COMMAND_TYPE_USER); 
    if (!string.compare(COMMAND_PING_STR))      return (COMMAND_TYPE_PING); 
    if (!string.compare(COMMAND_PONG_STR))      return (COMMAND_TYPE_PONG); 
    if (!string.compare(COMMAND_DIE_STR))       return (COMMAND_TYPE_DIE); 
    if (!string.compare(COMMAND_KILL_STR))      return (COMMAND_TYPE_KILL); 
    if (!string.compare(COMMAND_OPER_STR))      return (COMMAND_TYPE_OPER); 
    if (!string.compare(COMMAND_TOPIC_STR))     return (COMMAND_TYPE_TOPIC); 
    if (!string.compare(COMMAND_QUIT_STR))      return (COMMAND_TYPE_QUIT); 
    if (!string.compare(COMMAND_MODE_STR))      return (COMMAND_TYPE_MODE); 
    if (!string.compare(COMMAND_PRIVMSG_STR))   return (COMMAND_TYPE_PRIVMSG); 
    if (!string.compare(COMMAND_NOTICE_STR))    return (COMMAND_TYPE_NOTICE); 
    if (!string.compare(COMMAND_JOIN_STR))      return (COMMAND_TYPE_JOIN); 
    if (!string.compare(COMMAND_LIST_STR))      return (COMMAND_TYPE_LIST);
    if (!string.compare(COMMAND_INVITE_STR))    return (COMMAND_TYPE_INVITE); 
    if (!string.compare(COMMAND_KICK_STR))      return (COMMAND_TYPE_KICK); 
    if (!string.compare(COMMAND_PART_STR))      return (COMMAND_TYPE_PART); 
    
    return (COMMAND_TYPE_UNKNOWN);
}

/**
 * Execute commands from the user's command queue.
 *
 * This function processes commands from the user's command queue, where each
 * command is represented as a string. It iterates through the commands,
 * parses them, and invokes the corresponding functions based on the command type.
 * The function uses a switch statement to handle recognized command types,
 * and logs an error for unrecognized commands.
 *
 * The function modifies the user's command queue by erasing processed commands.
 */
void	Server::_exec_client_commands(User *user) {
    __abort_if_fail__(user);

    //DEBUG_PRINT_CMD_VEC(user);
    std::vector<std::string> *cmd = user->fetch_commands();
    for (std::vector<std::string>::iterator it = cmd->begin(); it != cmd->end(); it = cmd->erase(it)) {

        Command command = Command(*it, user->get_fd());
    
        std::vector<std::string> cmd_splited = split(*it, ' ');
        //DEBUG_PRINT_CMD_SPLIT_VEC(cmd_splited, user);

        if (cmd_splited.size()) {
        
            uint8_t cmdtype = _get_command_type_from_string(cmd_splited[0]);
            
            switch (cmdtype) {
                case COMMAND_TYPE_PASS:     _command_pass(cmd_splited, user->get_fd());     break;
                case COMMAND_TYPE_NICK:     _command_nick(cmd_splited, user->get_fd());     break;
                case COMMAND_TYPE_USER:     _command_user(*it, user->get_fd());             break;
                case COMMAND_TYPE_PING:     _command_ping(user->get_fd());                  break;
                case COMMAND_TYPE_PONG:     _command_pong();                                break;
                case COMMAND_TYPE_JOIN:     _command_join(cmd_splited, user->get_fd());     break;
                case COMMAND_TYPE_KICK:     _command_kick(cmd_splited, user->get_fd());     break;
                case COMMAND_TYPE_PRIVMSG:  _command_privmsg(*it, user->get_fd());          break;
                case COMMAND_TYPE_MODE:     _command_mode(cmd_splited, user->get_fd());     break;
                case COMMAND_TYPE_INVITE:   _command_invite(cmd_splited, user->get_fd());   break;
                case COMMAND_TYPE_TOPIC:    _command_topic(*it, user->get_fd());            break;
                case COMMAND_TYPE_PART:     _command_part(*it, user->get_fd());             break;
                case COMMAND_TYPE_DIE:                                                      break;
                case COMMAND_TYPE_KILL:                                                     break;
                case COMMAND_TYPE_OPER:                                                     break;
                case COMMAND_TYPE_QUIT:                                                     break;
                case COMMAND_TYPE_NOTICE:                                                   break;
                case COMMAND_TYPE_LIST:                                                     break;

                default: 
                    logger(ERROR, "Unrecognized command: '" + cmd_splited[0] + "'");
            }
        }
    }
}


/**
 * Accept a new user connection.
 *
 * This function accepts a new user connection by calling the `accept` function
 * on the server socket. If the connection is successful, it creates a new User
 * object to represent the client and adds the client's file descriptor to the
 * list of file descriptors monitored by the poll mechanism.
 *
 * The function sets up appropriate events for the poll mechanism based on
 * the operating system (Linux or non-Linux).
 */
void	Server::_accept_user() {
    
    struct sockaddr_in	addr;
    memset(&addr, 0, sizeof(addr));
    
    socklen_t sock_len = sizeof(addr);
    int32_t fd = accept(_sockfd, (struct sockaddr *)&addr, &sock_len);

    if (fd == -1) {
        std::cout << "error: `accept()` function failed" << std::endl;
        return ;
    }

    _users[fd] = new User(fd);

    _fds.push_back(pollfd());
    _fds.back().fd = fd;

#ifdef __linux
    _fds.back().events = (POLLIN | POLLRDHUP);
#else
    _fds.back().events = (POLLIN | POLLHUP);
#endif
}


/**
 * Delete a user and clean up resources.
 *
 * This function deletes a user by closing the user's file descriptor, freeing
 * the associated User object, and removing the user from the user map and the
 * list of file descriptors monitored by the poll mechanism.
 */
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


/**
 * Send a server reply to a specific user.
 *
 * This function sends a server reply to a user identified by their file descriptor.
 * The reply is selected based on the provided code, and additional parameters can
 * be passed to customize certain replies. The function constructs the reply message
 * and sends it to the user's file descriptor using the `send` function.
 *
 * @param fd The file descriptor of the target user.
 * @param code The code indicating the type of reply to send.
 * @param reply_arg Additional parameters for customizing certain replies.
 */
void	Server::_send_reply(int32_t fd, int32_t code, std::vector<std::string> &reply_arg) {

    std::string reply;

    switch(code) {

        case   1: reply = CREATE_RPL_WELCOME(_users[fd], _networkname, _servername);    break;
        case   2: reply = CREATE_RPL_YOURHOST(_users[fd], _servername, _version);       break;
        case   3: reply = CREATE_RPL_CREATED(_users[fd], _start_time, _servername);     break;
        case   4: reply = CREATE_RPL_MYINFO(_users[fd], _servername, _version);         break;
        case 221: reply = CREATE_RPL_UMODEIS(_users[fd], reply_arg);                    break;
        case 324: reply = CREATE_RPL_CHANNELMODEIS(reply_arg);                          break;
        case 332: reply = CREATE_RPL_TOPIC(_users[fd], reply_arg);                      break;
        case 341: reply = CREATE_RPL_INVITING(_users[fd], reply_arg);                   break;
        case 366: reply = CREATE_RPL_ENDOFNAMES(_users[fd], reply_arg);                 break;
        case 401: reply = CREATE_ERR_NOSUCHNICK(_users[fd], reply_arg);                 break;
        case 403: reply = CREATE_ERR_NOSUCHCHANNEL(_users[fd], reply_arg);              break;
        case 404: reply = CREATE_ERR_CANNOTSENDTOCHAN(_users[fd], reply_arg);           break;
        case 411: reply = CREATE_ERR_NORECIPIENT(_users[fd], reply_arg);                break;
        case 412: reply = CREATE_ERR_NOTEXTTOSEND(_users[fd]);                          break;
        case 441: reply = CREATE_ERR_USERNOTINCHANNEL(_users[fd], reply_arg);           break;
        case 442: reply = CREATE_ERR_NOTONCHANNEL(_users[fd], reply_arg);               break;
        case 443: reply = CREATE_ERR_USERONCHANNEL(_users[fd], reply_arg);              break;
        case 451: reply = CREATE_ERR_NOTREGISTERED(_users[fd]);                         break;
        case 461: reply = CREATE_ERR_NEEDMOREPARAMS(_users[fd], reply_arg);             break;
        case 462: reply = CREATE_ERR_ALREADYREGISTERED(_users[fd]);                     break;
        case 464: reply = CREATE_ERR_PASSWDMISMATCH(_users[fd]);                        break;
        case 431: reply = CREATE_ERR_NONICKNAMEGIVEN(_users[fd]);                       break;
        case 432: reply = CREATE_ERR_ERRONEUSNICKNAME(_users[fd], reply_arg);           break;
        case 433: reply = CREATE_ERR_NICKNAMEINUSE(_users[fd], reply_arg);              break;
        case 471: reply = CREATE_ERR_CHANNELISFULL(_users[fd], reply_arg);              break;
        case 475: reply = CREATE_ERR_BADCHANNELKEY(_users[fd], reply_arg);              break;
        case 482: reply = CREATE_ERR_CHANOPRIVSNEEDED(_users[fd], reply_arg);           break;
        case 473: reply = CREATE_ERR_INVITEONLYCHAN(_users[fd], reply_arg);             break;
        case 476: reply = CREATE_ERR_BADCHANMASK(reply_arg);                            break;
        case 501: reply = CREATE_ERR_UMODEUNKNOWNFLAG(_users[fd]);                      break;
        case 502: reply = CREATE_ERR_USERSDONTMATCH(_users[fd]);                        break;
        case 696: reply = CREATE_ERR_INVALIDMODEPARAM(_users[fd], reply_arg);           break;
        case 1001: reply = CREATE_PER_NICKNAMECHANGE(reply_arg);                        break;
        case 1002: reply = CREATE_PER_SENDMESSAGETOCHANNEL(reply_arg);                  break;
    }

    if (send(fd, reply.c_str(), reply.length(), 0) == -1)
        return ;
}


/* accessors */
std::string Server::get_networkname() const	{ return (_networkname); }
std::string Server::get_servername() const	{ return (_servername); }
std::string Server::get_start_time() const	{ return (_start_time); }

/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:05 by jucheval          #+#    #+#             */
/*   Updated: 2023/11/21 12:48:44 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#pragma once

#include "User.hpp"
#include "Channel.hpp"
#include "reply.hpp"
#include "Command.hpp"

#include <iostream>
#include <stdint.h>
#include <exception>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <vector>
#include <map>
#include <netinet/in.h>
#include <poll.h>
#include <cstring>
#include <unistd.h>
#include <signal.h>

class User;
class Channel;


class Server {
    
    private:
        uint16_t                _port;
        std::string             _password;
        std::string             _networkname;
        std::string             _servername;
        std::string             _start_time;
        std::string             _version;
        int32_t                 _sockfd;
        struct sockaddr_in      _addr;
        std::vector<pollfd>     _fds;
        std::map<int, User *>   _users;
        std::vector<Channel *>  _channel;


        uint16_t    _check_port(const char *port) const;
        std::string _check_password(const char *password) const;

        void        _accept_user(void);
        void        _delete_user(int32_t fd);

        void        _receive_client_input(User *user);
        void        _exec_client_commands(User *user);

        void        _command_pass(std::vector<std::string> cmd, int32_t fd);
        void        _command_nick(std::vector<std::string> cmd, int32_t fd);
        void        _command_user(std::string cmd, int32_t fd);
        void        _command_ping(uint32_t fd);
        void        _command_pong(void);
        void        _command_join(std::vector<std::string> cmd, int32_t fd);
        void        _command_kick(std::vector<std::string> cmd, int32_t fd);
        void        _command_privmsg(std::string cmd, int32_t fd);
        void        _command_invite(std::vector<std::string> cmd, int32_t fd);

        
        void        _command_mode(std::vector<std::string> cmd, int32_t fd);
        void        _handle_channel_mode(std::vector<std::string> cmd, int32_t fd);
        void        _handle_user_mode(std::vector<std::string> cmd, int32_t fd);
        void        _handle_remove_mode(std::string modes, Channel *channel, int32_t fd);
        void        _handle_add_mode(std::string modes, Channel *channel, int32_t fd);


        void        _send_reply(int32_t fd, int32_t code, std::vector<std::string> &reply_arg);
        void        _send_message_by_channel_name(std::string &c_name, std::string &message, int32_t fd);
        void        _send_message_by_nickname(std::string &nickname, std::string &message, int32_t fd);



        uint8_t     _get_command_type_from_string(std::string &string) const;


    public:
        Server(const char *port, const char *pass);
        ~Server();

        void	server_initialisation(void);
        void	run(void);

        std::string     get_networkname(void) const;
        std::string     get_servername(void) const;
        std::string     get_start_time(void) const;


        class SocketInitialisationFailed : public std::exception {
            public :
               virtual const char *what() const throw() {
                    return ("error: `socket()` function failed");
                } 
        };
        class SetSockOptFailed : public std::exception {
            public :
               virtual const char *what() const throw() {
                    return ("error: `setsockopt()` function failed");
                } 
        };
        class BindFailed : public std::exception {
            public :
               virtual const char *what() const throw() {
                    return ("error: `bind()` function failed");
                } 
        };
        class ListenFailed : public std::exception {
            public :
               virtual const char *what() const throw() {
                    return ("error: `listen()` function failed");
                } 
        };
};

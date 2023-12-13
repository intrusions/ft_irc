/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:05 by jucheval          #+#    #+#             */
/*   Updated: 2023/12/13 21:11:14 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// ========================================================================= //
//                                   Header                                  //
// ========================================================================= //

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


// ========================================================================= //
//                                   Define                                  //
// ========================================================================= //

#define ADD_MODE    1
#define REMOVE_MODE 0


// ========================================================================= //
//                                 Prototype                                 //
// ========================================================================= //

class User;
class Channel;


// ========================================================================= //
//                                   Class                                   //
// ========================================================================= //

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

        uint8_t     _get_command_type_from_string(std::string &string) const;

        void        _command_pass(std::vector<std::string> cmd, int32_t fd);
        void        _command_nick(std::vector<std::string> cmd, int32_t fd);
        void        _command_user(std::string cmd, int32_t fd);
        void        _command_ping(uint32_t fd);
        void        _command_pong(void);
        void        _command_kick(std::vector<std::string> cmd, int32_t fd);
        void        _command_invite(std::vector<std::string> cmd, int32_t fd);
        
        void        _command_join(std::vector<std::string> cmd, int32_t fd);
        void        _send_welcome_message(int32_t fd_sender, Channel *channel, std::string cmd, std::string cname);
        
        void        _command_privmsg(std::string cmd, int32_t fd);
        void        _send_message_by_channel_name(std::string &c_name, std::string &message, int32_t fd);
        void        _send_message_by_nickname(std::string &nickname, std::string &message, int32_t fd);
        
        void        _command_topic(std::string cmd, int32_t fd);
        void        _send_ntopic_to_channel(Channel *channel, std::string cname, int32_t sender_fd, std::vector<std::string> &reply_arg);
        
        void        _command_mode(std::vector<std::string> cmd, int32_t fd);
        void        _handle_channel_mode(std::vector<std::string> cmd, int32_t fd);
        void        _handle_remove_mode(std::string modes, Channel *channel, std::vector<std::string> cmd, int32_t fd);
        void        _handle_add_mode(std::string modes, Channel *channel, std::vector<std::string> cmd, int32_t fd);
        void        _send_nmode_to_channel(Channel *channel, int32_t sender_fd, std::vector<std::string> &reply_arg);

        void        _command_part(std::string cmd, int32_t fd);
        void        _send_part_message_by_channel_name(std::string &c_name, std::string &message, int32_t fd);


        void        _mode_invite_only(Channel *channel, bool add_or_rm, int32_t fd);
        void        _mode_topic_manage(Channel *channel, bool add_or_rm, int32_t fd);
        void        _mode_change_pass(Channel *channel, std::vector<std::string> cmd, bool add_or_rm, int32_t fd);
        void        _mode_user_limit(Channel *channel, std::vector<std::string> cmd, bool add_or_rm, int32_t fd);
        void        _mode_operator_priv(Channel *channel, std::vector<std::string> cmd, bool add_or_rm, int32_t fd);

        void        _send_reply(int32_t fd, int32_t code, std::vector<std::string> &reply_arg);

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

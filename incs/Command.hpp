/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:44:28 by xel               #+#    #+#             */
/*   Updated: 2023/11/10 17:01:11 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "reply.hpp"

#include <iostream>
#include <stdint.h>

#define COMMAND_PASS_STR     "PASS"
#define COMMAND_NICK_STR     "NICK"
#define COMMAND_USER_STR     "USER"
#define COMMAND_PING_STR     "PING"
#define COMMAND_PONG_STR     "PONG"
#define COMMAND_DIE_STR      "die"
#define COMMAND_KILL_STR     "kill"
#define COMMAND_OPER_STR     "OPER"
#define COMMAND_TOPIC_STR    "TOPIC"
#define COMMAND_QUIT_STR     "QUIT"
#define COMMAND_MODE_STR     "MODE"
#define COMMAND_PRIVMSG_STR  "PRIVMSG"
#define COMMAND_NOTICE_STR   "NOTICE"
#define COMMAND_JOIN_STR     "JOIN"
#define COMMAND_LIST_STR     "LIST"
#define COMMAND_INVITE_STR   "INVITE"
#define COMMAND_KICK_STR     "KICK"
#define COMMAND_PART_STR     "PART"

typedef enum {
    COMMAND_TYPE_PASS,
    COMMAND_TYPE_NICK,
    COMMAND_TYPE_USER,
    COMMAND_TYPE_PING,
    COMMAND_TYPE_PONG,
    COMMAND_TYPE_DIE,
    COMMAND_TYPE_KILL,
    COMMAND_TYPE_OPER,
    COMMAND_TYPE_TOPIC,
    COMMAND_TYPE_QUIT,
    COMMAND_TYPE_MODE,
    COMMAND_TYPE_PRIVMSG,
    COMMAND_TYPE_NOTICE,
    COMMAND_TYPE_JOIN,
    COMMAND_TYPE_LIST,
    COMMAND_TYPE_INVITE,
    COMMAND_TYPE_KICK,
    COMMAND_TYPE_PART,
    COMMAND_TYPE_UNKNOWN
}	t_command_type;

class Command {
    protected:
        std::string const   _command;
        int32_t             _user_fd;

    public:
        Command(std::string const &command, int32_t fd);
        virtual ~Command(void) { };

        int32_t             get_user_fd() const;
        std::string const   &get_command() const;
};

std::ostream &operator<<(std::ostream const &o, Command const &rhs);

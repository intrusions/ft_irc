/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:05 by jucheval          #+#    #+#             */
/*   Updated: 2023/11/12 09:04:04 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reply.hpp"

/* 001 */
std::string	CREATE_RPL_WELCOME(const User *user, const std::string &networkname, const std::string &servername) {

    return (
        ":" + servername + " 001 " + user->get_nickname() + " :Welcome to the " + networkname + " Network, "
        + user->get_nickname() + "[!" + user->get_username() + "@" + user->get_hostname() + "]\r\n"
    );
}

/* 002 */
std::string	CREATE_RPL_YOURHOST(const User *user, const std::string &servername, const std::string &version) {

    return (
        ":" + servername + " 002 " + user->get_nickname() + " :Your host is "
        + servername + ", running version " + version + "\r\n"
    );
}

/* 003 */
std::string	CREATE_RPL_CREATED(const User *user, const std::string &start_time, const std::string &servername) {

    return (
        ":" + servername + " 003 " + user->get_nickname()
        + " :This server was created " + start_time + "\r\n"
    );
}

/* 004 */
std::string	CREATE_RPL_MYINFO(const User *user, const std::string &servername, const std::string &version) {

    return (
        ":" + servername + " 004 " + user->get_nickname() + " "
        + servername + " " + version + " <available user modes> \n<available channel modes> [<channel modes with a parameter>]" + "\r\n"
    );
}

/* 332 */
std::string CREATE_RPL_TOPIC(const User *user, const std::vector<std::string> &reply_arg) {
    
    return (user->get_prefix() + " " + reply_arg[0] + " :" + reply_arg[1] + "\r\n");
}

/* 403 */
std::string	CREATE_ERR_NOSUCHCHANNEL(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " " + reply_arg[0] + " :No such channel\r\n");
}

/* 431 */
std::string	CREATE_ERR_NONICKNAMEGIVEN(const User *user) {

    return (user->get_prefix() + " :No nickname given\r\n");
}

/* 432 */
std::string	CREATE_ERR_ERRONEUSNICKNAME(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " " + reply_arg[0] + " :Erroneus nickname\r\n");
}

/* 433 */
std::string	CREATE_ERR_NICKNAMEINUSE(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " " + reply_arg[0] + " :Nickname is already in use\r\n");
}

/* 441 */
std::string	CREATE_ERR_USERNOTINCHANNEL(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " " + reply_arg[0] + " " + reply_arg[1] + " :They aren't on that channel\r\n");
}

/* 442 */
std::string	CREATE_ERR_NOTONCHANNEL(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " " + reply_arg[0] + " :You're not on that channel\r\n");
}

/* 461 */
std::string	CREATE_ERR_NEEDMOREPARAMS(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " " + reply_arg[0] + " :Not enough parameters\r\n");
}

/* 462 */
std::string	CREATE_ERR_ALREADYREGISTERED(const User *user) {

    return (user->get_prefix() + " :You may not reregister\r\n");
}

/* 464 */
std::string	CREATE_ERR_PASSWDMISMATCH(const User *user) {

    return (user->get_prefix() + " :Password incorrect\r\n");
}

/* 474 */
std::string	CREATE_ERR_BANNEDFROMCHAN(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " " + reply_arg[0] + " :Cannot join channel (+b)\r\n");
}

/* 475 */
std::string	CREATE_ERR_BADCHANNELKEY(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " " + reply_arg[0] + " :Cannot join channel (+k)\r\n");
}

/* 476 */
std::string	CREATE_ERR_BADCHANMASK(const std::vector<std::string> &reply_arg) {

    return (reply_arg[0] + " :Bad Channel Mask\r\n");
}

/* 1001 */
std::string	CREATE_PER_NICKNAMECHANGE(const std::vector<std::string> &reply_arg) {

    return (reply_arg[0] + " NICK " + reply_arg[1] + "\r\n");
}


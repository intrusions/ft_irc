/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:05 by jucheval          #+#    #+#             */
/*   Updated: 2023/12/18 19:20:43 by jucheval         ###   ########.fr       */
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
        + servername + " " + version + "\n[ -k -i -o -t -l ] [ -k -o -l ]" + "\r\n"
    );
}

/* 221 */
std::string CREATE_RPL_UMODEIS(const User *user, const std::vector<std::string> &reply_arg) {
    
    return (user->get_prefix() + " 221 " + reply_arg[0] + "\r\n");
}

/* 324 */
std::string CREATE_RPL_CHANNELMODEIS(const std::vector<std::string> &reply_arg) {
    return (reply_arg[1] + " " + reply_arg[2] + " " + reply_arg[0] + "\r\n");
}

/* 332 */
std::string CREATE_RPL_TOPIC(const User *user, const std::vector<std::string> &reply_arg) {
    
    return (":" + user->get_hostname() + " 332 " + user->get_nickname() + " " + reply_arg[1] + " :" + reply_arg[2] + "\r\n");
}

/* 341 */
std::string CREATE_RPL_INVITING(const User *user, const std::vector<std::string> &reply_arg) {
    
    return (user->get_prefix() + " 341 " + reply_arg[0] + " :" + reply_arg[1] + "\r\n");
}

/* 366 */
std::string	CREATE_RPL_ENDOFNAMES(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " 366 " + reply_arg[0] + " :End of /NAMES list\r\n");
}

/* 401 */
std::string	CREATE_ERR_NOSUCHNICK(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " 401 " + reply_arg[0] + " :No such nick/channel\r\n");
}

/* 403 */
std::string	CREATE_ERR_NOSUCHCHANNEL(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " 403 " + reply_arg[0] + " :No such channel\r\n");
}

/* 404 */
std::string	CREATE_ERR_CANNOTSENDTOCHAN(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " 404 " + reply_arg[0] + " :Cannot send to channel\r\n");
}

/* 411 */
std::string	CREATE_ERR_NORECIPIENT(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " 411 :No recipient given (" + reply_arg[0] + ")\r\n");
}

/* 412 */
std::string	CREATE_ERR_NOTEXTTOSEND(const User *user) {

    return (user->get_prefix() + " 412 :No text to send\r\n");
}

/* 431 */
std::string	CREATE_ERR_NONICKNAMEGIVEN(const User *user) {

    return (user->get_prefix() + " 431 :No nickname given\r\n");
}

/* 432 */
std::string	CREATE_ERR_ERRONEUSNICKNAME(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " 432 " + reply_arg[0] + " :Erroneus nickname\r\n");
}

/* 433 */
std::string	CREATE_ERR_NICKNAMEINUSE(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " 433 " + reply_arg[0] + " :Nickname is already in use\r\n");
}

/* 441 */
std::string	CREATE_ERR_USERNOTINCHANNEL(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " 441 " + reply_arg[0] + " " + reply_arg[1] + " :They aren't on that channel\r\n");
}

/* 442 */
std::string	CREATE_ERR_NOTONCHANNEL(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " 442 " + reply_arg[0] + " :You're not on that channel\r\n");
}

/* 443 */
std::string	CREATE_ERR_USERONCHANNEL(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " 443 " + reply_arg[0] + " " + reply_arg[1] + " :is already on channel\r\n");
}

/* 451 */
std::string	CREATE_ERR_NOTREGISTERED(const User *user) {

    return (user->get_prefix() + " 451 :You have not registered\r\n");
}

/* 461 */
std::string	CREATE_ERR_NEEDMOREPARAMS(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " 461 " + reply_arg[0] + " :Not enough parameters\r\n");
}

/* 462 */
std::string	CREATE_ERR_ALREADYREGISTERED(const User *user) {

    return (user->get_prefix() + " 462 :You may not reregister\r\n");
}

/* 464 */
std::string	CREATE_ERR_PASSWDMISMATCH(const User *user) {

    return (user->get_prefix() + " 464 :Password incorrect\r\n");
}

/* 471 */
std::string	CREATE_ERR_CHANNELISFULL(const User *user, const std::vector<std::string> &reply_arg) {

    return (":" + user->get_hostname() + " 471 " + user->get_nickname() + " " + reply_arg[0] + " :Cannot join channel (+l)\r\n");
}

/* 473 */
std::string	CREATE_ERR_INVITEONLYCHAN(const User *user, const std::vector<std::string> &reply_arg) {

    return (":" + user->get_hostname() + " 473 " + user->get_nickname() + " " + reply_arg[0] + " :Cannot join channel (+i)\r\n");
}

/* 474 */
std::string	CREATE_ERR_BANNEDFROMCHAN(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " 474 " + reply_arg[0] + " :Cannot join channel (+b)\r\n");
}

/* 475 */
std::string	CREATE_ERR_BADCHANNELKEY(const User *user, const std::vector<std::string> &reply_arg) {

    return (":" + user->get_hostname() + " 475 " + user->get_nickname() + " " + reply_arg[0] + " :Cannot join channel (+k)\r\n");
}

/* 476 */
std::string	CREATE_ERR_BADCHANMASK(const std::vector<std::string> &reply_arg) {

    return ("476 " + reply_arg[0] + " :Bad Channel Mask\r\n");
}

/* 482 */
std::string	CREATE_ERR_CHANOPRIVSNEEDED(const User *user, const std::vector<std::string> &reply_arg) {

    return (user->get_prefix() + " 482 " + reply_arg[0] + " :You're not channel operator\r\n");
}

/* 501 */
std::string	CREATE_ERR_UMODEUNKNOWNFLAG(const User *user) {

    return (user->get_prefix() + " 501 :Unknown MODE flag\r\n");
}

/* 502 */
std::string	CREATE_ERR_USERSDONTMATCH(const User *user) {

    return (user->get_prefix() + " 502 :Cant change mode for other users\r\n");
}

/* 696 */
std::string	CREATE_ERR_INVALIDMODEPARAM(const User *user, const std::vector<std::string> &reply_arg) {

    return (
        user->get_prefix() + " 696 " + reply_arg[0] + " " + reply_arg[1] + " "
        + reply_arg[2] + " " + reply_arg[3] + "\r\n"
    );
}

/* 1001 */
std::string	CREATE_PER_NICKNAMECHANGE(const std::vector<std::string> &reply_arg) {

    return (reply_arg[0] + " NICK " + reply_arg[1] + "\r\n");
}

/* 1002 */
std::string	CREATE_PER_SENDMESSAGETOCHANNEL(const std::vector<std::string> &reply_arg) {

    return (reply_arg[0] + " " + reply_arg[1] + " " + reply_arg[2] + " :" + reply_arg[3] + "\r\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:05 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/28 01:58:11 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/reply.hpp"

/* 001 */
std::string	RPL_WELCOME(User *user, std::string networkname, std::string servername) {

	return (":" + servername + " 001 " +  user->get_nickname() + " :Welcome to the " + networkname + " Network, " + user->get_nickname() + "[!" + user->get_username() + "@" + user->get_hostname() + "]\r\n");
}

/* 002 */
std::string	RPL_YOURHOST(User *user, std::string servername, std::string version) {

	return (":" + servername + " 002 " + user->get_nickname() + " :Your host is " + servername + ", running version " + version + "\r\n");
}

/* 003 */
std::string	RPL_CREATED(User *user, std::string start_time, std::string servername) {

	return (":" + servername + " 003 " + user->get_nickname() + " :This server was created " + start_time + "\r\n");
}

/* 004 */
std::string	RPL_MYINFO(User *user, std::string servername, std::string version) {

	return (":" + servername + " 004 " + user->get_nickname() + " " + servername + " " + version + " <available user modes> \n<available channel modes> [<channel modes with a parameter>]" + "\r\n");
}

/* 431 */
std::string	ERR_NONICKNAMEGIVEN(User *user) {

	return (user->get_prefix() + " :No nickname given\r\n");
}

/* 432 */
std::string	ERR_ERRONEUSNICKNAME(User *user, std::vector<std::string> err_param) {

	return (user->get_prefix() + " " + err_param[0] + " :Erroneus nickname\r\n");
}

/* 433 */
std::string	ERR_NICKNAMEINUSE(User *user, std::vector<std::string> err_param) {

	return (user->get_prefix() + " " + err_param[0] + " :Nickname is already in use\r\n");
}

/* 461 */
std::string	ERR_NEEDMOREPARAMS(User *user, std::vector<std::string> err_param) {

	return (user->get_prefix() + " " + err_param[0] + " :Not enough parameters\r\n");
}

/* 462 */
std::string	ERR_ALREADYREGISTERED(User *user) {

	return (user->get_prefix() + " :You may not reregister\r\n");
}

/* 464 */
std::string	ERR_PASSWDMISMATCH(User *user) {

	return (user->get_prefix() + " :Password incorrect\r\n");
}

/* 1001 */
std::string	PER_NICKNAMECHANGE(std::vector<std::string> err_param) {

	return (err_param[0] + " NICK " + err_param[1] + "\r\n");
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:05 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/24 03:32:48 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/reply.hpp"

/* 001 */
std::string	RPL_WELCOME(User *user, std::string networkname) {

	return (user->get_prefix() + " :Welcome to the " + networkname + " Network, " + user->get_nickname() + "[!" + user->get_username() + "@" + user->get_hostname() + "]\r\n");
}

/* 002 */
std::string	RPL_YOURHOST(User *user, std::string servername, std::string version) {

	return (user->get_prefix() + " :Your host is " + servername + ", running version " + version + "\r\n");
}

/* 003 */
std::string	RPL_CREATED(User *user, std::string start_time) {

	return (user->get_prefix() + " :This server was created " + start_time + "\r\n");
}

/* 004 */
std::string	RPL_MYINFO(User *user, std::string servername, std::string version) {

	return (user->get_prefix() + servername + " " + version + " <available user modes> \n<available channel modes> [<channel modes with a parameter>]" + "\r\n");
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
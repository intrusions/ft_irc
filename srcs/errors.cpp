/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:05 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/23 22:06:23 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/errors.hpp"

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
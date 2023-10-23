/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:05 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/23 20:56:18 by xel              ###   ########.fr       */
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
std::string	ERR_PASSWDMISMATCH (User *user) {

	return (user->get_prefix() + " :Password incorrect\r\n");
}
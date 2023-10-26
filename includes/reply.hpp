/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:05 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/27 00:29:22 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./User.hpp"

#include <string>
#include <stdint.h>
#include <vector>

class User;

std::string	RPL_WELCOME(User *user, std::string networkname);
std::string	RPL_YOURHOST(User *user, std::string servername, std::string version);
std::string	RPL_CREATED(User *user, std::string start_time);
std::string	RPL_MYINFO(User *user, std::string servername, std::string version);

std::string ERR_NEEDMOREPARAMS(User *user, std::vector<std::string> err_param);
std::string	ERR_ALREADYREGISTERED(User *user);
std::string	ERR_PASSWDMISMATCH(User *user);
std::string	ERR_NONICKNAMEGIVEN(User *user);
std::string	ERR_ERRONEUSNICKNAME(User *user, std::vector<std::string> err_param);
std::string	ERR_NICKNAMEINUSE(User *user, std::vector<std::string> err_param);

std::string	PER_NICKNAMECHANGE(std::vector<std::string> err_param);

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:33:05 by jucheval          #+#    #+#             */
/*   Updated: 2023/11/10 18:48:30 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"

#include <string>
#include <stdint.h>
#include <vector>

class User;

std::string CREATE_RPL_WELCOME(const User *user, const std::string &networkname, const std::string &servername);
std::string CREATE_RPL_YOURHOST(const User *user, const std::string &servername, const std::string &version);
std::string CREATE_RPL_CREATED(const User *user, const std::string &start_time, const std::string &servername);
std::string CREATE_RPL_MYINFO(const User *user, const std::string &servername, const std::string &version);
std::string RPL_TOPIC(User *user, std::vector<std::string> err_param);

std::string CREATE_ERR_NEEDMOREPARAMS(const User *user, const std::vector<std::string> &err_param);
std::string CREATE_ERR_ALREADYREGISTERED(const User *user);
std::string CREATE_ERR_PASSWDMISMATCH(const User *user);
std::string CREATE_ERR_NONICKNAMEGIVEN(const User *user);
std::string CREATE_ERR_ERRONEUSNICKNAME(const User *user, const std::vector<std::string> &err_param);
std::string CREATE_ERR_NICKNAMEINUSE(const User *user, const std::vector<std::string> &err_param);

std::string ERR_BADCHANNELKEY(User *user, std::vector<std::string> err_param);
std::string CREATE_PER_NICKNAMECHANGE(const std::vector<std::string> &err_param);

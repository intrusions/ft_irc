/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:51:08 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/29 18:23:14 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./User.hpp"

#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>

#define RESET_COLOR		"\033[0m"
#define RED_TEXT		"\033[31m"
#define GREEN_TEXT		"\033[32m"
#define YELLOW_TEXT		"\033[33m"
#define BLUE_TEXT		"\033[34m"
#define MAGENTA_TEXT	"\033[35m"
#define CYAN_TEXT		"\033[36m"


std::vector<std::string>	split_space(std::string cmd);
void						logs(std::string str, uint8_t color);

void	DEBUG_PRINT_CMD_VEC(User *user);
void	DEBUG_PRINT_CMD_SPLIT_VEC(std::vector<std::string> cmd, User *user);

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:51:08 by jucheval          #+#    #+#             */
/*   Updated: 2023/10/23 20:37:48 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./User.hpp"

#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>

std::vector<std::string>	split_space(std::string cmd);

void	DEBUG_PRINT_CMD_VEC(User *user);
void	DEBUG_PRINT_CMD_SPLIT_VEC(std::vector<std::string> cmd, User *user);

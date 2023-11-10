/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:51:08 by jucheval          #+#    #+#             */
/*   Updated: 2023/11/10 17:11:07 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./User.hpp"
#include "./Channel.hpp"


#include "color.hpp"
#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>

enum e_log_lvl {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

# define logger(level, str) \
    do { \
        const char* level_str; \
        switch (level) { \
            case    INFO: level_str = BLU    "INFO" CRESET; break; \
            case   DEBUG: level_str = YEL   "DEBUG" CRESET; break; \
            case WARNING: level_str = MAG "WARNING" CRESET; break; \
            case   ERROR: level_str = RED   "ERROR" CRESET; break; \
            default:      level_str =       "OTHER";        break; \
        } \
        std::cerr \
          << "[" << level_str \
          << "]: " << str \
          << std::endl; \
} while (0)

#if 0
#define __abort_if_fail__(expr) (void)expr
#else
#define __abort_if_fail__(expr) \
    do { \
        if (!(expr)) { \
            std::cerr \
              << "[" << __FILE__ \
              << ":" << __LINE__ \
              << "] Assertion failed: " \
              << #expr \
              << std::endl; \
            std::abort();   \
        } \
    } while (0)
#endif

std::vector<std::string>	split(std::string cmd, char delimiter);

void    DEBUG_PRINT_CMD_VEC(User *user);
void    DEBUG_PRINT_CMD_SPLIT_VEC(std::vector<std::string> cmd, User *user);
void    DEBUG_PRINT_ALL_CHANNEL(std::vector<Channel *> channel);


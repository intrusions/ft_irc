/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:51:08 by jucheval          #+#    #+#             */
/*   Updated: 2023/11/24 11:39:23 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#pragma once

#include "User.hpp"
#include "Channel.hpp"

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

# define logger(level, str)                                         \
    do {                                                            \
        const char* level_str;                                      \
                                                                    \
        switch (level) {                                            \
            case    INFO: level_str = BLU    "INFO" CRESET; break;  \
            case   DEBUG: level_str = YEL   "DEBUG" CRESET; break;  \
            case WARNING: level_str = MAG "WARNING" CRESET; break;  \
            case   ERROR: level_str = RED   "ERROR" CRESET; break;  \
            default:      level_str =       "OTHER";        break;  \
        }                                                           \
                                                                    \
        std::cerr                                                   \
            << "[" << level_str                                     \
            << "]: " << str                                         \
            << std::endl;                                           \
} while (0)

#if 0
    #define __abort_if_fail__(expr) (void)expr
#else
    #define __abort_if_fail__(expr)                         \
        do {                                                \
            if (!(expr)) {                                  \
                std::cerr                                   \
                    << "[" << __FILE__                      \
                    << ":" << __LINE__                      \
                    << "] Assertion failed: "               \
                    << #expr                                \
                    << std::endl;                           \
                std::abort();                               \
            }                                               \
        } while (0)
#endif

std::vector<std::string>    split(std::string cmd, char delimiter);

bool    find_fds_in_vec(std::vector<int32_t> *vec, const int32_t fd);

int32_t     nickname_is_in_channel(std::map<int, User *> &users, Channel *channel, std::string &nickname);
int32_t     search_fd_by_nickname(std::map<int, User *> &users, std::string &nickname);
Channel     *channel_is_existing(std::vector<Channel *> &c_list, std::string &c_name);



void    DEBUG_PRINT_CMD_VEC(User *user);
void    DEBUG_PRINT_CMD_SPLIT_VEC(std::vector<std::string> cmd, User *user);
void    DEBUG_PRINT_ALL_CHANNEL(std::vector<Channel *> channel);
void    DEBUG_PRINT_MODESTR(uint64_t flags);
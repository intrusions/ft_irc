/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:57:29 by jucheval          #+#    #+#             */
/*   Updated: 2023/11/20 21:35:11 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#pragma once

#include "Server.hpp"

#include <iostream>
#include <vector>
#include <stdint.h>
#include <netinet/in.h>

# define CHANNEL_MODE_INVITE_ONLY   0x1 << 1    
# define CHANNEL_MODE_USER_LIMIT    0x1 << 2
# define CHANNEL_MODE_CHANGE_PASS   0x1 << 3
# define CHANNEL_MODE_OPERATOR_PRIV 0x1 << 4
# define CHANNEL_MODE_TOPIC_MANAGE  0x1 << 5

class Channel {
    private:
        std::string             _name;
        std::string             _topic;
        std::string             _password;
        std::vector<int32_t>    _fds;
        std::vector<int32_t>    _banned_fds;
        std::vector<int32_t>    _operator_fds;
        uint64_t                _mflags; // mode flags
   
    public:
        Channel(std::string name, int32_t fd);
        Channel(std::string name, int32_t fd, std::string password);

        ~Channel();

        std::string             get_name(void) const;
        std::string             get_password(void) const;
        std::string             get_topic(void) const;

        std::vector<int32_t>    *fetch_fds(void);
        std::vector<int32_t>    *fetch_banned_fds(void);
        std::vector<int32_t>    *fetch_operator_fds(void);
        uint64_t                get_mflags(void);

        void                    set_mflags(uint64_t flag);
};

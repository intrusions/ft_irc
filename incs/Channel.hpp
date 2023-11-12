/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:57:29 by jucheval          #+#    #+#             */
/*   Updated: 2023/11/12 02:00:37 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"

#include <iostream>
#include <vector>
#include <stdint.h>
#include <netinet/in.h>

class Channel {
    private:
        std::string             _name;
        std::string             _topic;
        std::string             _password;
        std::vector<int32_t>    _fds;
        std::vector<int32_t>    _banned_fds;
        
    public:
        Channel(std::string name, int32_t fd);
        Channel(std::string name, int32_t fd, std::string password);

        ~Channel();

        std::string             get_name(void) const;
        std::string             get_password(void) const;
        std::string             get_topic(void) const;

        std::vector<int32_t>    *fetch_fds(void);
        std::vector<int32_t>    *fetch_banned_fds(void);

};

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:57:29 by jucheval          #+#    #+#             */
/*   Updated: 2023/11/11 19:50:08 by xel              ###   ########.fr       */
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
        
    public:
        Channel(std::string name, int32_t fd);
        Channel(std::string name, int32_t fd, std::string password);

        ~Channel();

        std::string             get_name(void) const;
        std::string             get_password(void) const;
        std::string             get_topic(void) const;

        std::vector<int32_t>    *fetch_fds(void);

        bool    find_fds(const int32_t fd);
};

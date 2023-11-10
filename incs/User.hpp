/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:51:08 by jucheval          #+#    #+#             */
/*   Updated: 2023/11/10 17:10:42 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"

#include <iostream>
#include <vector>
#include <stdint.h>
#include <netinet/in.h>

#define DEFAULT_INFO_VALUE "GUEST"

class Server;

class User {
    
    private:
        int32_t                     _fd;
        std::vector<std::string>    _commands;
        
        std::string                 _prefix;
        std::string                 _nickname;
        std::string                 _username;
        std::string                 _realname;
        std::string                 _hostname;

        bool                        _pass_is_valid;


    public:
        User(int32_t fd);
        ~User();
        
        int32_t         get_fd(void) const;
        std::string     get_prefix(void) const;
        std::string     get_nickname(void) const;
        std::string     get_username(void) const;
        std::string     get_realname(void) const;
        std::string     get_hostname(void) const;
        int32_t         get_pass_is_valid(void) const;

        void            set_prefix(void);
        void            set_nickname(const std::string &n);
        void            set_username(const std::string &n);
        void            set_realname(const std::string &n);
        void            set_hostname(const std::string &n);
        void            set_pass_is_valid(const bool n);
        
        std::vector<std::string>    *fetch_commands(void);
};


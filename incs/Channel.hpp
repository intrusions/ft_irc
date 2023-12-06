/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:57:29 by jucheval          #+#    #+#             */
/*   Updated: 2023/12/06 15:41:41 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#pragma once

// ========================================================================= //
//                                  Header                                   //
// ========================================================================= //

#include "Server.hpp"

#include <iostream>
#include <vector>
#include <stdint.h>
#include <netinet/in.h>


// ========================================================================= //
//                                   Define                                  //
// ========================================================================= //

# define CHANNEL_MODE_INVITE_ONLY   1U << 1
# define CHANNEL_MODE_USER_LIMIT    1U << 2
# define CHANNEL_MODE_CHANGE_PASS   1U << 3
# define CHANNEL_MODE_OPERATOR_PRIV 1U << 4
# define CHANNEL_MODE_TOPIC_MANAGE  1U << 5

# define CHANNEL_DEFAULT_LIMITS     12


// ========================================================================= //
//                                   Class                                   //
// ========================================================================= //

class Channel {
    private:
        std::string             _name;
        std::string             _topic;
        std::string             _password;
        int32_t                 _limits;
        
        std::vector<int32_t>    _fds;
        std::vector<int32_t>    _operator_fds;
        std::vector<int32_t>    _invite_fds;
        
        uint64_t                _mflags;
        bool                    _is_invite_only;
   
    public:
        Channel(std::string name, int32_t fd);
        Channel(std::string name, int32_t fd, std::string password);

        ~Channel();

        std::string             get_name(void) const;
        std::string             get_password(void) const;
        std::string             get_topic(void) const;
        int32_t                 get_limits(void) const;
        uint64_t                get_mflags(void);
        bool                    get_is_invite_only(void);
        
        void                    set_password(std::string npass);
        void                    set_topic(std::string ntopic);
        void                    set_limits(int32_t nlimits);
        void                    set_mflags(uint64_t flag);
        void                    set_is_invite_only(bool add_or_rm);
        
        std::vector<int32_t>    *fetch_fds(void);
        std::vector<int32_t>    *fetch_operator_fds(void);
        std::vector<int32_t>    *fetch_invite_fds(void);
};

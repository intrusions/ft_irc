/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_topic_manage.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:50:23 by xel               #+#    #+#             */
/*   Updated: 2023/12/08 06:33:43 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Channel.hpp"
#include "utils.hpp"

void    Server::_mode_topic_manage(Channel *channel, bool add_or_rm, int32_t fd) {
    
    std::vector<std::string>    reply_arg;

    if (add_or_rm == REMOVE_MODE) {
        channel->set_mflags(channel->get_mflags() & ~CHANNEL_MODE_TOPIC_MANAGE);

        reply_arg.push_back("-t");    
        _send_nmode_to_channel(channel, fd, reply_arg);

    } else {
        channel->set_mflags(channel->get_mflags() | CHANNEL_MODE_TOPIC_MANAGE);

        reply_arg.push_back("+t");    
        _send_nmode_to_channel(channel, fd, reply_arg);
    }

    channel->set_is_invite_only(add_or_rm);
}

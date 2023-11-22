/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_invite_only.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:50:23 by xel               #+#    #+#             */
/*   Updated: 2023/11/22 13:06:48 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Channel.hpp"
#include "utils.hpp"

void    Server::_mode_invite_only(Channel *channel, bool add_or_rm) {
    
    if (add_or_rm == ADD_MODE)  channel->set_mflags(channel->get_mflags() | CHANNEL_MODE_INVITE_ONLY);
    else                        channel->set_mflags(channel->get_mflags() & ~CHANNEL_MODE_INVITE_ONLY);

    channel->set_is_invite_only(add_or_rm);
}
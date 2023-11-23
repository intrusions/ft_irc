/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_topic_manage.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:50:23 by xel               #+#    #+#             */
/*   Updated: 2023/11/23 15:06:23 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Channel.hpp"
#include "utils.hpp"

void    Server::_mode_topic_manage(Channel *channel, bool add_or_rm) {
    
    if (add_or_rm == REMOVE_MODE)       channel->set_mflags(channel->get_mflags() & ~CHANNEL_MODE_TOPIC_MANAGE);
    else if (add_or_rm == ADD_MODE)     channel->set_mflags(channel->get_mflags() | CHANNEL_MODE_TOPIC_MANAGE);
}
/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_invite_only.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:50:23 by xel               #+#    #+#             */
/*   Updated: 2023/11/21 11:48:30 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Channel.hpp"
#include "utils.hpp"
#include "modes.hpp"

void    mode_invite_only(Channel *channel, bool add_or_rm) {
    
    channel->set_is_invite_only(add_or_rm);
}
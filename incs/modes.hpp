/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:05:42 by xel               #+#    #+#             */
/*   Updated: 2023/11/21 11:47:00 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#pragma once

#define ADD_MODE    1
#define REMOVE_MODE 0

void    mode_invite_only(Channel *channel, bool add_or_rm);
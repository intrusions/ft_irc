/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:57:29 by jucheval          #+#    #+#             */
/*   Updated: 2023/11/08 23:50:15 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./Server.hpp"

#include <iostream>
#include <vector>
#include <stdint.h>
#include <netinet/in.h>

class Channel {
	private:
		std::string				_name;
		std::vector<int32_t>	_fds;
		
	public:
		Channel(std::string name, int32_t fd);
		~Channel();

		std::string				get_name(void);
		std::vector<int32_t>	*fetch_fds(void);
};
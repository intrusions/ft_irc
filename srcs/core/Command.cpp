/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:49:36 by xel               #+#    #+#             */
/*   Updated: 2023/11/10 17:40:44 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "utils.hpp"

Command::Command(std::string const &command, int32_t fd)
    : _command(command)
    , _user_fd(fd) { logger(DEBUG, "got new command: " + command); }

int32_t             Command::get_user_fd() const	{ return (_user_fd); }
std::string const   &Command::get_command() const	{ return (_command); }

std::ostream    &operator<<(std::ostream &o, Command const &rhs) {
    
    o
    << "fd:" << rhs.get_user_fd() << ", "
    << "command:" << rhs.get_command()
    << std::endl;
    return (o);
}

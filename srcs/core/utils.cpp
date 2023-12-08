/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:51:08 by jucheval          #+#    #+#             */
/*   Updated: 2023/12/08 06:05:06 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "utils.hpp"
#include "color.hpp"

/* basic */
std::vector<std::string>	split(std::string cmd, char delimiter) {
    
    std::vector<std::string>    tokens;
    std::istringstream          token_stream(cmd);
    std::string                 token;
    
    while (std::getline(token_stream, token, delimiter)) {
        tokens.push_back(token);
    }
    return (tokens);
}

/* command utils */
bool    find_fds_in_vec(std::vector<int32_t> *vec, const int32_t fd) {

    for (std::vector<int32_t>::iterator it = vec->begin(); it != vec->end(); it++) {

        if (*it == fd)
            return (true);
    }
    return (false);
}

int32_t    nickname_is_in_channel(std::map<int, User *> &users, Channel *channel, std::string &nickname) {
    
    for (std::vector<int32_t>::iterator it = channel->fetch_fds()->begin(); it != channel->fetch_fds()->end(); it++) {
        if (users[*it]->get_nickname() == nickname) {
            return (*it);
        }
    }
    return (0);
}

int32_t    search_fd_by_nickname(std::map<int, User *> &users, std::string &nickname) {
    
    for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++) {
        if ((*it).second->get_nickname() == nickname) {
            return ((*it).second->get_fd());
        }
    }
    return (0);
}

Channel     *channel_is_existing(std::vector<Channel *> &c_list, std::string &c_name) {
    
    for (std::vector<Channel *>::iterator it = c_list.begin(); it != c_list.end(); it++) {
        if ((*it)->get_name() == c_name) {
            return (*it);
        }
    }
    return (NULL);
}

/* debug */
void	DEBUG_PRINT_CMD_VEC(User *user) {
    
    uint16_t i = 0;
    std::vector<std::string> *cmd = user->fetch_commands();
    
    for (std::vector<std::string>::iterator it = cmd->begin(); it != cmd->end(); it++) {
        std::cout << "_fd[" << user->get_fd() << "] | ";
        std::cout << "_commands[" << i << "] : " << *it << std::endl;
        i++;
    }
    std::cout << std::endl;
}

void	DEBUG_PRINT_CMD_SPLIT_VEC(std::vector<std::string> &cmd, User *user) {
    
    uint16_t i = 0;
    
    for (std::vector<std::string>::iterator it = cmd.begin(); it != cmd.end(); it++) {
        std::cout << "_fd[" << user->get_fd() << "] | ";
        std::cout << "commands_split[" << i << "] : " << *it << std::endl;
        i++;
    }
    std::cout << std::endl;
}

void	DEBUG_PRINT_ALL_CHANNEL(std::vector<Channel *> channel) {
    
    uint16_t i = 0;
    
    logger(DEBUG, "Channel list: [ [channel name] | ['fd' 'fd' ...] ]");
    
    for (std::vector<Channel *>::iterator it = channel.begin(); it != channel.end(); it++) {

        std::cout << "      Channel[" << i << "] : " << (*it)->get_name() << " | ";

        std::vector<int32_t>	*user_list = (*it)->fetch_fds();
        for (std::vector<int32_t>::iterator it2 = user_list->begin(); it2 != user_list->end(); it2++) {
            std::cout << "'" << *it2 << "'" << " ";
        }
        std::cout << std::endl;
        i++;
    }
}

void DEBUG_PRINT_MODESTR(uint64_t flags) {
    
    logger(DEBUG, "Channel flags: [ [flags name] [ (+flags) ] ]");

    if (flags & CHANNEL_MODE_INVITE_ONLY)   { std::cout << "      Invite Only (+i)" << std::endl; }
    if (flags & CHANNEL_MODE_USER_LIMIT)    { std::cout << "      User Limit (+l)" << std::endl; }
    if (flags & CHANNEL_MODE_CHANGE_PASS)   { std::cout << "      Change Password (+k)" << std::endl; }
    if (flags & CHANNEL_MODE_OPERATOR_PRIV) { std::cout << "      Operator Privileges (+o)" << std::endl; }
    if (flags & CHANNEL_MODE_TOPIC_MANAGE)  { std::cout << "      Topic Management (+t)" << std::endl; }
}

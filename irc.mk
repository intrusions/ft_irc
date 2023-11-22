NAME         := ircserv
CC           := c++
SRCS_DIR     := srcs
OBJS_DIR     := .objs
INCS_DIR     := incs
TEST_MAIN    := srcs/tests/__main__.cpp
MAIN         := srcs/main.cpp

CFLAGS :=                           \
    -std=c++98                      \
    -Wall                           \
    -Wextra                         \
    -Werror                         \
    -pedantic 

# export ASAN_OPTIONS="log_path=sanitizer.log"
# export ASAN_OPTIONS="detect_leaks=1"

CFLAGS_DBG :=                       \
    -g3                             \
    -O0                             \
    -fsanitize=address              \
    -fsanitize=undefined            \
    -fno-omit-frame-pointer         \
    -fstack-protector-strong        \
    -fno-optimize-sibling-calls 

SRCS :=                             \
    core/Server.cpp                 \
    core/User.cpp                   \
    core/utils.cpp                  \
    core/Channel.cpp                \
    reply/reply.cpp                 \
    core/Command.cpp                \
    commands/command_pass.cpp       \
    commands/command_nick.cpp       \
    commands/command_user.cpp       \
    commands/command_ping.cpp       \
    commands/command_pong.cpp       \
    commands/command_join.cpp       \
    commands/command_kick.cpp       \
    commands/command_privmsg.cpp    \
    commands/command_mode.cpp       \
    commands/command_invite.cpp     \
    modes/mode_invite_only.cpp      \
    modes/mode_change_pass.cpp      \
    modes/mode_user_limit.cpp       \
		tests/unit.cpp

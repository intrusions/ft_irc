NAME         := ircserv
CC           := c++
SRCS_DIR     := srcs
OBJS_DIR     := .objs
INCS_DIR     := incs

CFLAGS   := \
	-std=c++98 \
	-Wall     \
	-Wextra   \
	-Werror   \
	-pedantic 

# export ASAN_OPTIONS="log_path=sanitizer.log"
# export ASAN_OPTIONS="detect_leaks=1"

CFLAGS_DBG              := \
	-g3                      \
	-O0                      \
	-fsanitize=address       \
	-fsanitize=undefined     \
	-fno-omit-frame-pointer  \
	-fstack-protector-strong \
	-fno-optimize-sibling-calls 

SRCS := \
	main.cpp						\
	core/Server.cpp						\
	core/User.cpp						\
	core/utils.cpp						\
	errors/reply.cpp			\
	core/Command.cpp \
	commands/command_pass.cpp		\
	commands/command_nick.cpp		\
	commands/command_user.cpp		\
	commands/command_ping.cpp		\
	commands/command_pong.cpp
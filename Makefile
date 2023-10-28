SRCS		=	./main.cpp								\
				./srcs/Server.cpp						\
				./srcs/User.cpp							\
				./srcs/utils.cpp						\
				./srcs/reply.cpp						\
				./srcs/commands/command_pass.cpp		\
				./srcs/commands/command_nick.cpp		\
				./srcs/commands/command_user.cpp		\
				./srcs/commands/command_ping.cpp		\
				./srcs/commands/command_pong.cpp		\

OBJS		=	$(SRCS:.cpp=.o)

CC			=	c++

RM			=	rm -f

CFLAGS		= 	-I./includes

CPPFLAGS	= 	-std=c++98

NAME		=	ircserv

all:		$(NAME)

.cpp.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<


$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)	

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY:		all clean fclean re
NAME     = pipex
CFLAGS   = -Wall -Wextra -Werror -g -Ilibft
LDFLAGS  = -Llibft -lft
MAND     = pipex.c
BONUS    = pipex_bonus.c
SRCS     = die.c \
           ft_getenv.c \
           ft_execvpe.c \
           process.c
OBJS     = $(SRCS:.c=.o)
LIB_NAME = libft
LIB_PATH = ./$(LIB_NAME)/$(LIB_NAME).a

ifdef bonus
	SRCS += $(BONUS)
else
	SRCS += $(MAND)
endif

.PHONY: NAME all
all: $(NAME)

$(NAME): $(OBJS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

$(LIB_PATH):
	$(MAKE) -C $(LIB_NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(MAKE) -C $(LIB_NAME) clean
	$(RM) $(OBJS) pipex_bonus.o

.PHONY: fclean
fclean:
	$(MAKE) -C $(LIB_NAME) fclean
	$(RM) $(OBJS) pipex_bonus.o $(NAME)

.PHONY: re
re: fclean all

.PHONY: bonus
bonus:
		@make bonus=1 all

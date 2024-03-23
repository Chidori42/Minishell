CC = cc -g

CFLAGS = -Wall -Wextra -Werror 

NAME = minishell

SRCS = main.c ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putnbr_fd.c \
	ft_split.c \
	get_next_line.c \
	get_next_line_utils.c \
	set_param.c \
	ft_parcing.c \
	ft_substr.c \
	ft_strdup.c \
	builthing.c \
	ft_strcmp.c \
	ft_strncmp.c \
	ft_export.c \
	utils2.c \
	free.c \
	utils_export.c \
	ft_isalpha.c \
	ft_isalnum.c 
#ft_wildcard.c

OBJECTS = $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c -o $@ $<


$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -lreadline
clean:
	$(RM) $(OBJECTS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean $(NAME)


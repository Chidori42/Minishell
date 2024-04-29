
############################## varaibles section #######################

#Mandatory source files names.

SRCS                    =	minishell.c \
							ft_execute_cmd.c \
							ft_check_parse.c \
							ft_check_quotes.c \
							ft_inject_spaces.c \
							ft_remove_quotes.c \
							ft_execute_list.c \
							ft_create_list.c \
							ft_redirection.c \
							ft_create_tab.c \
							ft_check_red.c \
							ft_get_redir.c \
							ft_expander.c \
							ft_utils_1.c \
							ft_heredoc.c \
							ft_get_cmd.c \
							ft_signals.c \
							ft_export.c \
							utils_unset.c \
							builtins.c \
							pars_export.c \
							ft_update_env.c \
							utils_builtins.c \
							set_env.c


#Mandatory object files name.

OBJS                    = $(SRCS:%c=%o)

FLAGS                   = -Wall -Wextra -Werror #-g -fsanitize=address

NAME                    = minishell

LIBFT                   = ./libft/libft.a

LIBFT_H                 = ./libft/libft.h

LIBFT_SRCS              = 	./libft/ft_isalpha.c ./libft/ft_isdigit.c\
							./libft/ft_isalnum.c ./libft/ft_isascii.c\
							./libft/ft_isprint.c ./libft/ft_strlen.c \
							./libft/ft_memset.c ./libft/ft_bzero.c\
							./libft/ft_memcpy.c ./libft/ft_memmove.c\
							./libft/ft_strlcpy.c ./libft/ft_strlcat.c\
							./libft/ft_toupper.c ./libft/ft_tolower.c\
							./libft/ft_strchr.c ./libft/ft_strrchr.c\
							./libft/ft_strncmp.c ./libft/ft_memchr.c\
							./libft/ft_memcmp.c ./libft/ft_strnstr.c\
							./libft/ft_atoi.c ./libft/ft_calloc.c\
							./libft/ft_strdup.c ./libft/ft_substr.c\
							./libft/ft_strjoin.c ./libft/ft_strtrim.c\
							./libft/ft_split.c ./libft/ft_itoa.c\
							./libft/ft_strmapi.c ./libft/ft_striteri.c\
							./libft/ft_putchar_fd.c ./libft/ft_putstr_fd.c\
							./libft/ft_putendl_fd.c ./libft/ft_putnbr_fd.c\
							./libft/ft_lstnew.c ./libft/ft_lstadd_front.c \
							./libft/ft_lstsize.c ./libft/ft_lstlast.c\
							./libft/ft_lstadd_back.c ./libft/ft_lstdelone.c \
							./libft/ft_lstclear.c ./libft/ft_lstiter.c\
							./libft/ft_lstmap.c ./libft/get_next_line.c\
							./libft/ft_strllen.c ./libft/ft_strchar.c

#######################################################################

############################ Rules Section ############################

all                     : $(NAME)


%o                      : %c minishell.h $(LIBFT) $(LIBFT_H)
	cc  -c $(FLAGS) $< -o $@

$(LIBFT)                : $(LIBFT_SRCS) $(LIBFT_H)
	make -C ./libft

$(NAME)                 : $(LIBFT) $(OBJS)
	cc  $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

clean                   :
	rm -f *.o
	make clean -C ./libft

fclean                  : clean
	rm -f $(NAME)
	make fclean -C ./libft

re                      : fclean all

.PHONY                  : clean
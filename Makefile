
############################## varaibles section #######################

#Mandatory source files names.

SRCS                    =	minishell.c \
							./parser/ft_parse.c \
							./parser/ft_check_quotes.c \
							./parser/ft_inject_spaces.c \
							./parser/ft_create_tab.c \
							./parser/ft_check_red.c \
							./parser/ft_heredoc.c \
							./executer/ft_execute_cmd.c \
							./executer/ft_remove_quotes.c \
							./executer/ft_execute_list.c \
							./executer/ft_create_list.c \
							./executer/ft_redirection.c \
							./executer/ft_resplit_tok.c \
							./executer/ft_get_redir.c \
							./executer/ft_expander.c \
							./executer/ft_encapsule.c \
							./executer/ft_get_cmd.c \
							./builtins/utils_builtins.c \
							./builtins/utils_export.c \
							./builtins/ft_export.c \
							./builtins/ft_unset.c \
							./builtins/builtins.c \
							./builtins/ft_exit.c \
							./builtins/ft_cd.c \
							./shared/ft_update_env.c \
							./shared/ft_signals.c \
							./shared/ft_utils_1.c \
							./shared/ft_utils_2.c \
							./shared/ft_utils_3.c \
							./shared/set_env.c \

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
	gcc  -c $(FLAGS) $< -o $@

$(LIBFT)                : $(LIBFT_SRCS) $(LIBFT_H)
	make -C ./libft

$(NAME)                 : $(LIBFT) $(OBJS)
	gcc  $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

clean                   :
	rm -f *.o
	rm -f */*.o
	make clean -C ./libft

fclean                  : clean
	rm -f $(NAME)
	make fclean -C ./libft

re                      : fclean all

.PHONY                  : clean
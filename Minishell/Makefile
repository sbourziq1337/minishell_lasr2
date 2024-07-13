SOR = minishell.c ft_link_node.c ft_split.c ft_access.c ft_helper.c ft_creat_child.c \
ft_write_path.c ft_path_cmd.c ft_exc_cmd.c  tokenization/tokenization.c \
input_validation/input.c input_validation/handle_quotes.c ft_read_file.c biultin/bulitin.c biultin/check_is_buildin.c \
biultin/ft_export.c biultin/ft_setenv.c utils/utils_builtins.c utils/utils1.c utils/utils_tokens.c biultin/split_quote.c biultin/ft_unset.c
OBJC=$(SOR:.c=.o)
NAME = minishell
RM = rm -f
CC = cc -ggdb #-fsanitize=address
LDLIBS = -lreadline
#CFLAGS = -Wall -Wextra -Werror -fsanitize=address

all: $(NAME)

# libft\libft.a:
# 	make -C libft

$(NAME): $(OBJC) 
	$(CC) -o $(NAME) $^ $(LDLIBS)

clean:
	$(RM) $(OBJC)

fclean: clean
	$(RM) $(NAME)

re: fclean all

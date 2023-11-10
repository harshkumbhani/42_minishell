
# ---------------------------------- Config ---------------------------------- #
NAME				:= minishell
CC					:= cc
CFLAGS				:= -Wall -Wextra -Werror -MMD -MP -I./includes -g
LIBFT_DIR			:= libraries/myLib
LIBFT_LIB			:= $(LIBFT_DIR)/libft.a

# --------------------------- Program Source files --------------------------- #
OBJDIR				:= ./objs
VPATH				:= .:./src/:./src/signals/:./src/builtins/:./src/executor/:./src/lexer:./src/free/:./src/utils/:./src/parser:./src/expander/:

SRC					:= main.c
SRC_SIGNALS			:= signals.c
SRC_FREE			:= env_free.c
SRC_UTILS			:= env_utils.c
SRC_BUILTINS		:= cd.c pwd.c env.c echo.c unset.c exec_builtins.c exit.c export.c
SRC_EXECUTOR		:= executor.c pipex.c executor_utils.c handle_pipe.c handle_error.c \
						execute.c init.c
SRC_LEXER			:= lexer.c utils_lexer.c create_token.c create_token2.c
SRC_PARSER			:= parser.c parser_utils.c parser_utils2.c syntax_error.c
SRC_EXPANDER		:= expander.c

SRCS				:= $(SRC) $(SRC_SIGNALS) $(SRC_BUILTINS) $(SRC_EXECUTOR) \
						$(SRC_FREE) $(SRC_UTILS) $(SRC_LEXER) $(SRC_PARSER) \
						$(SRC_EXPANDER)
OBJS				:= $(addprefix $(OBJDIR)/, ${SRCS:%.c=%.o})

# ----------------------------------- Rules ---------------------------------- #
all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -L/usr/include -lreadline -o $@

$(OBJDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@rm -rf objs

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

norm: $(SRCS)
	$(shell norminette | grep Error)

re: fclean all

.PHONY: all clean fclean re $(LIBFT)

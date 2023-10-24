

# ---------------------------------- Config ---------------------------------- #
NAME                := minishell
CC                  := cc
CFLAGS              := -Wall -Wextra -Werror -MMD -MP -I./includes -g
LIBFT_DIR           := libraries/myLib
LIBFT_LIB           := $(LIBFT_DIR)/libft.a

# --------------------------- Program Source files --------------------------- #
OBJDIR              := ./objs
VPATH               := .:./src/:./src/signals/:./src/builtins/:./src/executor/:./src/free/:./src/utils/:

SRC                 := main.c
SRC_SIGNALS         := signals.c
SRC_FREE			:= env_free.c
SRC_UTILS			:= env_utils.c utils.c
SRC_BUILTINS		:= cd.c pwd.c env.c echo.c unset.c exec_builtins.c exit.c export.c
SRC_EXECUTOR		:= executor.c pipex.c executor_utils.c handle_pipe.c handle_error.c \
						execute.c init.c

SRCS                := $(SRC) $(SRC_SIGNALS) $(SRC_BUILTINS) $(SRC_EXECUTOR) \
						$(SRC_FREE) $(SRC_UTILS)

# ---------------------------------- Objects --------------------------------- #
OBJS                := $(addprefix $(OBJDIR)/, ${SRCS:%.c=%.o})

# ----------------------------------- Rules ---------------------------------- #
all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -lreadline -o $@

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

.PHONY: all clean fclean re $(LIBFT) init-submodule

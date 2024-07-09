################################################################################
###############                     CONFIG                        ##############
################################################################################

NAME := minishell
CC := cc
CFLAGS = -Wextra -Wall -Werror -MMD -MP $(addprefix -I, $(INC_DIRS))
LIBFT_DIR = ./libft
LIBFT_LIB = ./libft/libft.a

ifeq ($(shell uname), Darwin)
	LD_LIB = -L /usr/local/Cellar/readline/8.2.10/lib -lreadline
else ifeq ($(shell uname), Linux)
	LD_LIB = -L/usr/include -lreadline
endif

################################################################################
###############                 PRINT OPTIONS                     ##############
################################################################################

G := \033[32m
X := \033[0m
BO := $(shell tput bold)
LOG := printf "[$(BO)$(G)ⓘ INFO$(X)] %s\n"

################################################################################
###############                  DIRECTORIES                      ##############
################################################################################

OBJ_DIR := _obj
INC_DIRS := ./include ./libft/include \
			/usr/local/Cellar/readline/8.2.10/include
SRC_DIRS := ./src/ ./src/signals/ ./src/builtins/ ./src/executor/ \
						./src/lexer ./src/free/ ./src/utils/ ./src/parser \
						./src/expander/ ./src/error/

# Tell the Makefile where headers and source files are
vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

################################################################################
###############                  SOURCE FILES                     ##############
################################################################################

SRC_MAIN			:= main.c
SRC_SIGNALS			:= signals.c signal_utils.c exit_code.c
SRC_FREE			:= env_free.c
SRC_ERROR			:= error_msg.c
SRC_UTILS			:= env_utils.c utils.c env_utils2.c reset_fds.c
SRC_BUILTINS		:= cd.c pwd.c env.c echo.c unset.c exec_builtins.c exit.c export.c
SRC_EXECUTOR		:= executor.c handle_pipe.c command.c heredoc.c files.c command_utils.c
SRC_LEXER			:= lexer.c utils_lexer.c create_token.c
SRC_PARSER			:= parser.c parser_utils.c parser_utils2.c syntax_error.c parser_free.c \
						parser_putargs.c
SRC_EXPANDER		:= expander.c expander_utils.c

SRCS				:= $(SRC_MAIN) $(SRC_SIGNALS) $(SRC_BUILTINS) $(SRC_EXECUTOR) \
						$(SRC_FREE) $(SRC_UTILS) $(SRC_LEXER) $(SRC_ERROR) \
						$(SRC_EXPANDER) $(SRC_PARSER)

OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

################################################################################
########                         COMPILING                      ################
################################################################################

all: submodule ft_lib $(NAME)

$(NAME): $(OBJS)
	@$(LOG) "Linking object files to $@"
	@$(CC) $(CFLAGS) $(LIBFT_LIB) $(LD_LIB) $^ -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(LOG) "Compiling $(notdir $@)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@$(LOG) "Creating object directory."
	@mkdir -p $@

submodule:
	@git submodule update --init

ft_lib:
	@if [ ! -f $(LIBFT_LIB) ]; then \
		$(LOG) "Creating ft_lib"; \
		make -C $(LIBFT_DIR); \
	else \
		$(LOG) "ft_lib already created"; \
	fi

clean:
	@if [ -d "./libft/$(OBJ_DIR)" ]; then \
		$(LOG) "Cleaning ./libft/$(notdir $(OBJ_DIR))"; \
		rm -rf ./libft/$(OBJ_DIR); \
	else \
		$(LOG) "No objects to clean inside libft."; \
	fi
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(LOG) "Cleaning $(notdir $(OBJ_DIR))"; \
		rm -rf $(OBJ_DIR); \
	else \
		$(LOG) "No objects to clean."; \
	fi

fclean: clean
	@if [ -f $(LIBFT_LIB) ]; then \
		$(LOG) "Cleaning libft.a"; \
		rm -f $(LIBFT_LIB); \
	else \
		$(LOG) "No library to clean inside libft."; \
	fi
	@if [ -f "$(NAME)" ]; then \
		$(LOG) "Cleaning $(notdir $(NAME))"; \
		rm -f $(NAME); \
	else \
		$(LOG) "No library to clean."; \
	fi

re: fclean all

-include $(OBJS:$(OBJ_DIR)/%.o=$(OBJ_DIR)/%.d)

.PHONY: all fclean clean re

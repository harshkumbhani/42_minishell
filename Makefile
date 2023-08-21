# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 15:13:53 by hkumbhan          #+#    #+#              #
#    Updated: 2023/08/21 16:23:42 by cwenz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME 				:= minishell
CC					:= cc
CFLAGS 				:= -Wall -Wextra -Werror -MMD -MP -I./include -I./libraries/c-library/header -g
LIBFT_DIR			:= ./libraries/c-library
LIBFT_LIB 			:= $(LIBFT_DIR)/libft.a

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

OBJDIR				:= ./objs
VPATH 				:= .:./srcs/

SRC		 			:= parse.c indexing.c utils.c

################################################################################
#                                  Makefile  objs                              #
################################################################################

SRCS				:= $(SRC)
OBJS				:= $(addprefix $(OBJDIR)/, ${SRCS:%.c=%.o})

################################################################################
#                                 Makefile logic                               #
################################################################################

COM_COLOR   		:= \033[0;34m # Blue
OBJ_COLOR   		:= \033[0;36m # Cyan
ERROR_COLOR 		:= \033[0;31m # Red
WARN_COLOR  		:= \033[0;33m # Yellow
OK_COLOR    		:= \033[0;32m # Green
NO_COLOR    		:= \033[m # Default
COM_STRING   		:= "Compiling"

################################################################################
#                                 Makefile rules                             #
################################################################################

all: init-submodule $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	@echo "$(COM_COLOR)$(COM_STRING) $@ $(OBJ_COLOR)$(OBJS) $(NO_COLOR)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $@
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o program 

$(LIBFT_LIB):
	@make re -C $(LIBFT_DIR) > make_output.txt 2>&1; \
	if [ $$? -eq 0 ]; then \
		echo "$(OK_COLOR)LIBFT.A compilation successful.$(NO_COLOR)"; \
	else \
		echo "$(ERROR_COLOR)LIBFT.A compilation failed.$(NO_COLOR) Check make_output.txt for details."; \
		exit 1; \
	fi

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ 

init-submodule:
	@if [ -z "$(shell ls -A $(LIBFT_DIR))" ]; then \
		git submodule init $(LIBFT_DIR); \
		git submodule update $(LIBFT_DIR); \
	fi

clean:
	@echo
	@printf "%b" "$(COM_COLOR)Cleaning objects and dependency files...$(NO_COLOR)"
	@make clean -C $(LIBFT_DIR)
	@rm -rf objs program make_output.txt
	@echo

fclean: clean
	@printf "%b" "$(COM_COLOR)Cleaning libft library...$(NO_COLOR)"
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME) checker
	@echo

norm: $(SRCS)
	$(shell norminette | grep Error)

re: fclean all

.PHONY: all clean fclean re $(LIBFT) init-submodule
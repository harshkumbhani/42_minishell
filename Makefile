# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 15:13:53 by hkumbhan          #+#    #+#              #
#    Updated: 2023/08/21 17:04:56 by cwenz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME 				:= minishell
CC					:= cc
CFLAGS 				:= -Wall -Wextra -Werror -MMD -MP -I./includes -g
LIBFT_DIR			:= libraries/c-library
LIBFT_LIB 			:= $(LIBFT_DIR)/libft.a

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

OBJDIR				:= ./objs
VPATH 				:= .:./src/

SRC		 			:= main.c

################################################################################
#                                  Makefile  objs                              #
################################################################################

SRCS				:= $(SRC)
OBJS				:= $(addprefix $(OBJDIR)/, ${SRCS:%.c=%.o})

################################################################################
#                                 Makefile colours                             #
################################################################################

COM_COLOR   		:= \033[0;34m # Blue
OBJ_COLOR   		:= \033[0;36m # Cyan
ERROR_COLOR 		:= \033[0;31m # Red
WARN_COLOR  		:= \033[0;33m # Yellow
OK_COLOR    		:= \033[0;32m # Green
NO_COLOR    		:= \033[m # Default

################################################################################
#                                 Makefile rules                               #
################################################################################

all: init-submodule $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $@
	@echo "$(COM_COLOR)Compiling $@ $(OBJ_COLOR)$(OBJS) $(NO_COLOR)"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ 

# Initialize submodules
init-submodule:
	@if [ -z "$(shell ls -A $(LIBFT_DIR))" ]; then \
		git submodule init $(LIBFT_DIR); \
		git submodule update $(LIBFT_DIR); \
	fi

clean:
	@rm -rf objs

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

norm: $(SRCS)
	$(shell norminette | grep Error)

re: fclean all

.PHONY: all clean fclean re $(LIBFT) init-submodule

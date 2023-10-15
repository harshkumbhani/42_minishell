# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 15:13:53 by hkumbhan          #+#    #+#              #
#    Updated: 2023/10/15 17:05:28 by cwenz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME                := minishell
CC                  := cc
CFLAGS              := -Wall -Wextra -Werror -MMD -MP -I./includes -g
LIBFT_DIR           := libraries/c-library
LIBFT_LIB           := $(LIBFT_DIR)/libft.a

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

OBJDIR              := ./objs
VPATH               := .:./src/:./src/signals/:./src/builtins/

SRC                 := main.c
SRC_SIGNALS         := signals.c
SRC_BUILTINS		:= cd.c pwd.c

################################################################################
#                                  Makefile  objs                              #
################################################################################

SRCS                := $(SRC) $(SRC_SIGNALS) $(SRC_BUILTINS)
OBJS                := $(addprefix $(OBJDIR)/, ${SRCS:%.c=%.o})

################################################################################
#                                 Makefile rules                               #
################################################################################

all: init-submodule $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $@

$(OBJDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ 

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

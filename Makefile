# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 15:13:53 by hkumbhan          #+#    #+#              #
#    Updated: 2023/10/18 13:30:13 by hkumbhan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME                := minishell
CC                  := cc
CFLAGS              := -Wall -Wextra -Werror -MMD -MP -I./includes -g
LIBFT_DIR           := libraries/myLib
LIBFT_LIB           := $(LIBFT_DIR)/libft.a

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

OBJDIR              := ./objs
VPATH               := .:./src/:./src/signals/:./src/builtins/:./src/executor/

SRC                 := main.c
SRC_SIGNALS         := signals.c
SRC_BUILTINS		:= cd.c pwd.c env.c echo.c
SRC_EXECUTOR		:= executor.c pipex.c utils.c handle_pipe.c handle_error.c \
						execute.c init.c

################################################################################
#                                  Makefile  objs                              #
################################################################################

SRCS                := $(SRC) $(SRC_SIGNALS) $(SRC_BUILTINS) $(SRC_EXECUTOR)
OBJS                := $(addprefix $(OBJDIR)/, ${SRCS:%.c=%.o})

################################################################################
#                                 Makefile rules                               #
################################################################################

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -lreadline -o $@
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

.PHONY: all clean fclean re $(LIBFT)

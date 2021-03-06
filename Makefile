# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/17 15:44:28 by abeauvoi          #+#    #+#              #
#    Updated: 2018/05/23 03:31:59 by abeauvoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= ft_ls

#
# Dirs
#

SRCS_DIR	= src
OBJS_DIR	= obj
LIB_DIR		= libft
INC_DIRS	= $(addsuffix includes, ./ $(LIB_DIR)/)
VPATH		= $(SRCS_DIR)

#
# Sources
#

SRCS		= main.c print_err.c parse_argv.c core.c print_usage.c \
		  long_format.c short_format.c init.c utils.c list.c \
		  list2.c long_format2.c long_format3.c core2.c utils2.c \
		  utils3.c utils4.c colors.c

#
# Build
#

OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
CFLAGS		= -Wall -Werror -Wextra -O3 $(addprefix -I, $(INC_DIRS))
LFLAGS		= -L$(LIB_DIR) -lft
LIB		= libft.a
COMP		= $(CC) $(CFLAGS) -o $@ -c $<
LINK		= $(CC) $(LFLAGS) -o $@ $(filter-out $(LIB_DIR)/$(LIB), $^)

#
# Rules
#

all: $(LIB_DIR)/$(LIB) $(NAME)

debug: CFLAGS += -g3
debug: clean all

$(LIB_DIR)/$(LIB):
	@make -C $(LIB_DIR)

$(NAME): $(LIB_DIR)/$(LIB) $(OBJS)
	$(LINK)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(OBJS_DIR)
	$(COMP)

clean:
	@rm $(OBJS) 2> /dev/null || true
	@make -C $(LIB_DIR) $@
	@rm -rf $(OBJS_DIR)
	@echo "cleaned .o files"

fclean: clean
	@rm $(NAME) 2> /dev/null || true
	@make -C $(LIB_DIR) $@
	@echo "removed binary"

re: fclean all

.PHONY: all clean fclean re

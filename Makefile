# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/17 15:44:28 by abeauvoi          #+#    #+#              #
#    Updated: 2017/12/03 23:00:09 by abeauvoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_ls

SRC_NAME	= main.c no_arg.c print_err.c
SRC_PATH	= src

OBJ_NAME	= $(SRC_NAME:.c=.o)
OBJ_PATH	= obj

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CFLAGS		= -Wall -Werror -Wextra
INC_DIRS	= includes ft_printf/includes

LDLIBS		= -lftprintf
LIB_PATH	= ft_printf
LDFLAGS		= -L$(LIB_PATH) $(LDLIBS)

# MESSAGES
DO_MSG		= "[ok]"
CL_MSG		= "Removed $(NAME) object files"
LK_MSG		= "Linking"
BIN_MSG		= "$(NAME) was successfully created"
FCL_MSG		= "Removed $(NAME)"

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_PATH)
	@$(CC) $(LDFLAGS) $^ -o $@
	@echo $(BIN_MSG)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(addprefix -I,$(INC_DIRS)) -c $< -o $@
	@echo $(LK_MSG) [ $< ] $(DO_MSG)

clean:
	@make -C $(LIB_PATH) $@
	@$(RM) $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo $(CL_MSG)

fclean: clean
	@make -C $(LIB_PATH) $@
	@$(RM) $(NAME)
	@echo $(FCL_MSG)

re: fclean all

.PHONY: all, clean, fclean, re

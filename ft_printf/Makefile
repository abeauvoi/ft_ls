# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/17 15:44:28 by abeauvoi          #+#    #+#              #
#    Updated: 2017/09/28 19:03:25 by abeauvoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

SRC_NAME	= ft_printf.c ft_printf_core.c binary_spec.c \
			  char_spec.c fd_spec.c flags.c ft_max.c ft_min.c ft_wcslen.c \
			  get_precision.c get_value.c get_value_bis.c get_width.c \
			  group_flag.c hex_spec.c integer_spec.c non_printable_spec.c \
			  octal_spec.c parse_one_spec.c percent_spec.c pointer_spec.c\
			  size_mod.c string_spec.c unknown_form.c unsigned_spec.c \
			  utils.c atoi_skip.c buffer.c colors.c cvt_number.c \
			  safe_ft_strncpy.c ft_strstrn.c print_null.c ft_iswprint.c

SRC_PATH	= src

OBJ_NAME	= $(SRC_NAME:.c=.o)
OBJ_PATH	= obj

SRC			= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ			= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CFLAGS		= -Wall -Wextra -Werror
CPPFLAGS	= includes

LDLIBS		= -lft
LIB_PATH	= libft
LDFLAGS		= -L$(LIB_PATH)/ $(LDLIBS)

# MESSAGES
DO_MSG		= "[ok]"
CL_MSG		= "Removed $(NAME) object files"
LK_MSG		= "Linking"
BIN_MSG		= "$(NAME) was successfully created"
FCL_MSG		= "Removed $(NAME)"

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_PATH)
	@cp $(LIB_PATH)/libft.a $(NAME)
	@ar r $(NAME) $(OBJ)
	@echo $(BIN_MSG)
	@ranlib $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -I$(CPPFLAGS) -c $< -o $@
	@echo $(LK_MSG) [ $< ] $(DO_MSG)

clean:
	@make -C $(LIB_PATH) clean
	@$(RM) $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo $(CL_MSG)

fclean: clean
	@make -C $(LIB_PATH) fclean
	@$(RM) $(NAME)
	@echo $(FCL_MSG)

re: fclean all

norme:
	norminette $(SRC)
	norminette $(CPPFLAGS)/*.h

.PHONY: all, clean, fclean, re, norme

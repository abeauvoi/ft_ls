# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/11 18:23:33 by abeauvoi          #+#    #+#              #
#    Updated: 2017/11/16 14:38:55 by abeauvoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

SRC_NAME	= ft_abs.c ft_atoi.c ft_atoi_skip.c ft_bzero.c \
			  ft_digittoint.c ft_delcontent.c ft_error.c ft_isalnum.c \
			  ft_isalpha.c ft_isascii.c ft_isdigit.c ft_islower.c ft_isprint.c \
			  ft_isspace.c ft_isupper.c ft_itoa.c ft_isxdigit.c ft_lstadd.c \
			  ft_lstdel.c ft_lstdelone.c ft_lstnew.c ft_lstiter.c ft_lstmap.c \
			  ft_lstsize.c ft_lststrsplit.c ft_lstpush.c ft_memalloc.c \
			  ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c \
			  ft_memmove.c ft_memset.c ft_pow.c ft_putchar.c ft_putchar_fd.c \
			  ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_base.c \
			  ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_revstr.c \
			  ft_strcat.c ft_strchr.c ft_strchrnul.c ft_strclr.c ft_strcpy.c \
			  ft_strcmp.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c \
			  ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c \
			  ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncmp_no_case.c \
			  ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c \
			  ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c \
			  ft_toupper.c get_next_line.c ft_print_int_tab_base.c \
			  ft_lstprint_base.c ft_strchrset.c ft_round.c \
			  ft_min.c ft_max.c ft_strrchr2.c ft_noccur.c ft_gen_swap.c

## VARIABLES ###################################################################

SRC_PATH	= src
INC_DIR		= includes
CPPFLAGS	= $(addprefix -I, $(INC_DIR))

CFLAGS		= -Wall -Werror -Wextra

OBJ_NAME	= $(SRC_NAME:.c=.o)
OBJ_PATH	= obj

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

## MESSAGES ####################################################################

DO_MSG		= "[ok]"
CL_MSG		= "Removed $(NAME) object files"
LK_MSG		= "Linking"
LIB_MSG		= "$(NAME) was successfully created"
FCL_MSG		= "Removed $(NAME)"

## RULES #######################################################################

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $^
	@echo $(LIB_MSG)
	@ranlib $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo $(LK_MSG) [ $< ] $(DO_MSG)

clean:
	@$(RM) $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo $(CL_MSG)

fclean: clean
	@$(RM) $(NAME)
	@echo $(FCL_MSG)

re: fclean all

.SILENT: $(OBJS)

.PHONY: all clean fclean re

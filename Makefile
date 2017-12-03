# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/17 15:44:28 by abeauvoi          #+#    #+#              #
#    Updated: 2017/12/03 23:18:52 by abeauvoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
VPATH = $(SRC_DIR)

SRC_DIR	= src/
OBJ_DIR	= obj/
SRC	= $(addprefix $(SRC_DIR), main.c no_arg.c print_err.c)

OBJ = $(addprefix $(OBJ_DIR), $(notdir $(SRC:.c=.o)))


CFLAGS = -Wall -Werror -Wextra
INC_DIR = includes ft_printf/includes
INC = $(addprefix -I, $(INC_DIR))

LIB = ftprintf
LIB_DIR	= ft_printf
LINK = $(addprefix -L,$(LIB_DIR)) $(addprefix -l,$(LIB))

## OUTPUT ######################################################################

GREEN		= \033[32m
RED			= \033[31m
LBLUE		= \033[36m
NC			= \033[0m

OK_COLOR=\x1b[32;01m
ERROR_COLOR=\x1b[31;01m
WARN_COLOR=\x1b[33;01m
OK_STRING=$(OK_COLOR)[OK]$(NC)
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NC)
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NC)


## RULES #######################################################################

all: obj_dir $(NAME)
	@true

$(NAME): msg $(OBJS)
	@echo "\r\033[J └── $(NAME) [$(GREEN)OK$(NC)]"


$(OBJ_DIR)%.o: %.c
	@echo "\r\033[J └── $(NAME)[\\] > $<\c"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "\r\033[J └── $(NAME)[/] > $@\c"

msg:
	@echo "Creating:"

obj_dir:
	@mkdir -p $(OBJ_DIR)
	
clean:
	@echo "$(LIB)\n └── \c"
	@make -C $(LIB_DIR) $@ &> /dev/null || true
	@echo "$(RED)rm ./obj $(NC)[$(GREEN)OK$(NC)]"
	@echo "$(NAME)\n └── \c"
	@$(RM) $(OBJS)
	@echo "$(RED)rm ./obj $(NC)[$(GREEN)OK$(NC)]"
	@rmdir $(OBJ_DIR) 2> /dev/null || true

fclean: clean
	@make -C $(LIB_DIR) $@ &> /dev/null || true
	@$(RM) $(NAME)
	@echo " └── \c"
	@echo "$(RED)rm $(NAME) $(NC)[$(GREEN)OK$(NC)]"

re: fclean all

nr:
	@echo "$(LBLUE)==== norminette ====$(NC)"
	@echo "norme for $(NAME)"
	@$	norminette $(SRC) > n.log
	@cat n.log | grep -B 1 'Error' | sed 's/--/  │└── end file /g' \
		| sed 's/Norme:/  ├┬─ NORME:/g' | sed 's/Error:/  │├── File :/g' \
		| sed 's/Error/  │├──/g' > enorm.log
	@echo "norm\t\t\c"
	@if test ! -s enorm.log; then echo "\t$(OK_STRING)"; \
		else echo "$(ERROR_STRING)" && cat enorm.log \
		&& echo "  │└── end file\n  └── end NORME"; fi;
	@$ rm -f n.log enorm.errors enorm.log

.PHONY: all clean fclean re msg obj_dir

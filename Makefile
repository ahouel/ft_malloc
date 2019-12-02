# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahouel <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/16 10:03:32 by ahouel            #+#    #+#              #
#    Updated: 2019/11/08 18:28:18 by ahouel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################# NAMES ########################################

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CC			= clang
CFLAGS		= -g -Wall -Wextra -Werror
LDFLAGS		= -shared
NAME		= libft_malloc.so
HOSTLIB		= libft_malloc_$(HOSTTYPE).so
NORME		= norminette
NORME_FULL	= norminette-full

TEST_FILES	= test.c

SRC_PATH	= ./srcs/
OBJ_PATH	= ./objs/
INC_PATH	= ./includes/
LIB_PATH	= ./libft/
LIB_INC		= $(LIB_PATH)includes

SRC_FILES =	free.c				\
			malloc.c			\
			realloc.c			\
			reallocf.c			\
			calloc.c			\
			is_block_valid.c	\
			which_area.c		\
			show_alloc_mem.c	\
			ft_align.c			\
			mmap_errors.c

INC_FILES = malloc.h	\
			malloc_struct.h
LIB_FILES = libft.a
LIB = $(addprefix $(LIB_PATH), $(LIB_FILES))

OBJ_NAMES = $(SRC_FILES:.c=.o)
OBJ_FILES = $(addprefix $(OBJ_PATH), $(OBJ_NAMES))

DEP = $(OBJ_FILES:.o=.d)

################################ COLORS #######################################

NORMAL = "\033[0m"
BOLD = "\033[1m"
YELLOW = "\033[0;33m"
RED = "\033[0;31m"
GREEN = "\033[0;32m"
BLUE = "\033[0;34m"
CYAN = "\033[0;36m"
MAGENTA = "\033[0;35m"
UP = "\033[A"
CUT = "\033[K"

################################ RULES ########################################

all: $(NAME)

-include $(DEP)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null || true

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -MMD -c $< -o $@ -I $(INC_PATH) -I $(LIB_INC)
	@echo $(BLUE)Compilation of $(BOLD)$(notdir $<)$(BLUE) done.$(NORMAL)

$(LIB):
	@echo $(GREEN)Compilation of $(BOLD)$(LIB_FILES)$(GREEN) ...$(NORMAL)
	@make -C $(LIB_PATH)
	@echo $(UP)$(CUT)$(UP)$(CUT)$(UP)
	@echo $(GREEN)Compilation of $(BOLD)$(LIB_FILES)$(GREEN) done.$(NORMAL)

$(NAME): $(HOSTLIB)
	@ln -fs $(HOSTLIB) $(NAME)
	@echo $(YELLOW)Link $(BOLD)$(NAME)$(YELLOW) to $(BOLD)$(HOSTLIB)$(YELLOW) created.$(NORMAL)

$(HOSTLIB): $(LIB) $(OBJ_PATH) $(OBJ_FILES) $(addprefix $(INC_PATH), $(INC_FILES))
	@$(CC) $(LDFLAGS) $(OBJ_FILES) $(LIB) -o $(HOSTLIB) -I $(INC_PATH) -I $(LIB_PATH)includes
	@echo $(GREEN)Library $(BOLD)$(notdir $(HOSTLIB))$(GREEN) created.$(NORMAL)

$(NORME):
	@echo $(MAGENTA)Norminette, GO !!!$(NORMAL)
	@$(NORME) $(SRC_PATH) $(INC_PATH)

$(NORME_FULL): $(NORME)
	@$(NORME) $(LIB_PATH)/srcs $(LIB_PATH)/includes

test: $(NAME) $(TEST_FILES)
	@$(CC) libft_malloc.so -I $(INC_PATH) -I $(LIB_INC) $(LIB) $(TEST_FILES) -o test

clean:
ifeq ("$(shell test -e $(OBJ_PATH) && echo titi)", "titi")
ifneq ($(SRC_PATH), $(OBJ_PATH))
	@rm -rf $(OBJ_PATH)
	@echo $(RED)Objects files of $(BOLD)$(notdir $(HOSTLIB))$(RED) removed.$(NORMAL)
else
	@echo $(RED)SRC_PATH and OBJ_PATH shouldn\'t be the same, please change it !$(NORMAL)
endif
	@make -C $(LIB_PATH) clean
else
	@echo $(RED)Objects files of $(BOLD)$(notdir $(HOSTLIB))$(RED) not found.$(NORMAL)
endif

fclean: clean
	@rm -f test_sh
	@rm -f test
ifeq ("$(shell test -e $(LIB) && echo toto)", "toto")
	@rm $(LIB)
endif
ifeq ("$(shell test -e $(NAME) && echo toto)", "toto")
	@rm $(NAME)
	@echo $(RED)Link $(BOLD)$(notdir $(NAME))$(RED) removed.$(NORMAL)
else
	@echo $(RED)Link $(BOLD)$(notdir $(HOSTLIB))$(RED) not found.$(NORMAL)
endif
ifeq ("$(shell test -e $(HOSTLIB) && echo toto)", "toto")
	@rm $(HOSTLIB)
	@echo $(RED)Library $(BOLD)$(notdir $(HOSTLIB))$(RED) removed.$(NORMAL)
else
	@echo $(RED)Library $(BOLD)$(notdir $(HOSTLIB))$(RED) not found.$(NORMAL)
endif

re: fclean all

.PHONY: all, clean, fclean, re

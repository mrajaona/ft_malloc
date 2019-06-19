ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

DIR_INC		=	./inc/
DIR_SRC		=	./src/
DIR_LIB		=	./lib/

NAME		=	$(addprefix $(DIR_LIB), libft_malloc_$(HOSTTYPE).so)
LNNAME		=	$(addprefix $(DIR_LIB), libft_malloc.so)

DIR_FREE	=	free/
SRC_FREE	=	free.c
SRCS_FREE	=	$(addprefix $(DIR_FREE), $(SRC_FREE))

DIR_MALLOC	=	malloc/
SRC_MALLOC	=	malloc.c
SRCS_MALLOC	=	$(addprefix $(DIR_MALLOC), $(SRC_MALLOC))

DIR_REALLOC		=	realloc/
SRC_REALLOC		=	realloc.c \
					ft_memcpy.c
SRCS_REALLOC	=	$(addprefix $(DIR_REALLOC), $(SRC_REALLOC))

DIR_SHOW	=	show/
SRC_SHOW	=	show_alloc_mem.c
SRCS_SHOW	=	$(addprefix $(DIR_SHOW), $(SRC_SHOW))

MORE_INC	=	memory.h

SRC			=	$(SRCS_MALLOC) \
				$(SRCS_FREE) \
				$(SRCS_REALLOC) \
				$(SRCS_SHOW)
INC			=	$(SRC:.c=.h) $(MORE_INC)

INCS		=	$(addprefix $(DIR_INC), $(INC))
SRCS		=	$(addprefix $(DIR_SRC), $(SRC))

DIRS		=	$(DIR_FREE) $(DIR_MALLOC) $(DIR_REALLOC) $(DIR_SHOW)
DIRS_INC	=	$(addprefix -I$(DIR_INC), $(DIRS))

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror -fpic $(DIRS_INC) -c

CC			=	/usr/bin/gcc
RM			=	/bin/rm -f
ECHO		=	/usr/bin/printf
LIB			=	/usr/bin/ar rc
LN			=	/bin/ln -s
MKDIR		=	/bin/mkdir -p

all			:	$(NAME)

$(OBJS) 	:	$(INCS)

$(NAME) 	:	$(INCS) $(SRCS) $(OBJS)
				$(MKDIR) $(DIR_LIB)
				$(CC) -shared -o $(NAME) $(OBJS)
				$(RM) $(LNNAME)
				$(LN) $(NAME) $(LNNAME)
				@$(ECHO) "\033[32m> Executable compiled\033[0m\n"

clean		:
				@$(RM) $(OBJS)
				@$(ECHO) "\033[31m> Directory cleaned\033[0m\n"

fclean		:	clean
				@$(RM) -r $(DIR_LIB)
				@$(ECHO) "\033[31m> Removed executable\033[0m\n"

re			:	fclean all

.PHONY		:	all clean fclean re

.DEFAULT_GOAL	:=	all
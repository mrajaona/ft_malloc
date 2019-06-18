ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME			=	libft_malloc_$(HOSTTYPE).so

DIR_INC		=	./inc/
DIR_SRC		=	./src/

DIR_MALLOC	=	malloc/
SRC_MALLOC	=	malloc.c
SRCS_MALLOC	=	$(addprefix	$(DIR_MALLOC), $(SRC_MALLOC))

DIR_FREE	=	free/
SRC_FREE	=	free.c
SRCS_FREE	=	$(addprefix	$(DIR_FREE), $(SRC_FREE))

DIR_REALLOC		=	realloc/
SRC_REALLOC		=	realloc.c \
					ft_memcpy.c
SRCS_REALLOC	=	$(addprefix	$(DIR_REALLOC), $(SRC_REALLOC))

SRC			=	$(SRCS_MALLOC) \
				$(SRC_FREE) \
				$(SRC_REALLOC)
INC			=	$(SRC:.c=.h)

INCS		=	$(addprefix $(DIR_INC), $(INC))
SRCS		=	$(addprefix $(DIR_SRC), $(SRC))

DIRS		=	$(DIR_MAIN)
DIRS_INC	=	$(addprefix -I$(DIR_INC), $(DIRS))

OBJS			=	$(SRCS:.c=.o)

CFLAGS			=	-Wall -Wextra -Werror -I $(INCLUDE) -c

CC				=	/usr/bin/gcc
RM				=	/bin/rm -f
ECHO			=	/usr/bin/printf
LIB				=	/usr/bin/ar rc

all				:	$(NAME)

$(OBJS) :		$(INCS)

$(NAME) :		$(INCS) $(SRCS) $(INCLUDE) $(OBJS)
				$(CC) $(CFLAGS) $(OBJS)
				$(LIB) $(NAME) $(OBJS)
				@$(ECHO) "\033[32m> Executable compiled\033[0m\n"

clean	:
				@$(RM) $(OBJS)
				@$(ECHO) "\033[31m> Directory cleaned\033[0m\n"

fclean	:				clean
				@$(RM) $(NAME)
				@$(ECHO) "\033[31m> Removed executable\033[0m\n"

re		:		fclean all

.PHONY	:		all clean fclean re

.DEFAULT_GOAL	:=	all
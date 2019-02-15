ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME			=	libft_malloc_$(HOSTTYPE).so
LNAME			=	libft_malloc.so
INCLUDE		 	=	./inc/

INC				=	ft_malloc.h ft_malloc_util.h ft_malloc_print.h
INCS			=	$(addprefix $(INCLUDE), $(INC))

DIR_FREE		=	./src/free/
SRC_FREE		=	free.c
SRCS_FREE		=	$(addprefix $(DIR_FREE), $(SRC_FREE))

DIR_MALLOC		=	./src/malloc/
SRC_MALLOC		=	malloc.c \
					zone.c
SRCS_MALLOC		=	$(addprefix $(DIR_MALLOC), $(SRC_MALLOC))

DIR_REALLOC		=	./src/realloc/
SRC_REALLOC		=	realloc.c \
					ft_memcpy.c
SRCS_REALLOC	=	$(addprefix $(DIR_REALLOC), $(SRC_REALLOC))

DIR_SHOW		=	./src/show/
SRC_SHOW		=	show_mem_alloc.c \
					print_tools.c \
					ft_print.c \
					print_blocks.c \
					ft_nbr.c
SRCS_SHOW		=	$(addprefix $(DIR_SHOW), $(SRC_SHOW))

DIR_UTIL		=	./src/util/
SRC_UTIL		=	util.c \
					align.c \
					chunk.c
SRCS_UTIL		=	$(addprefix $(DIR_UTIL), $(SRC_UTIL))

SRCS			=	$(SRCS_FREE) \
					$(SRCS_MALLOC) \
					$(SRCS_REALLOC) \
					$(SRCS_SHOW) \
					$(SRCS_UTIL)

OBJS			=	$(SRCS:.c=.o)

CFLAGS			=	-Wall -Wextra -Werror -fpic -I $(INCLUDE) -c

CC				=	/usr/bin/gcc
RM				=	/bin/rm -f
ECHO			=	/usr/bin/printf
LN				=	/bin/ln

all				:	$(NAME)

$(OBJS) :		$(INCS)

$(NAME) :		$(INCS) $(SRCS) $(INCLUDE) $(OBJS)
				$(CC) -shared -o $(NAME) $(OBJS)
				$(RM) $(LNAME)
				$(LN) -s $(NAME) $(LNAME)
				@$(ECHO) "\033[32m> Executable compiled\033[0m\n"

clean	:
				@$(RM) $(OBJS)
				@$(ECHO) "\033[31m> Directory cleaned\033[0m\n"

fclean	:		clean
				@$(RM) $(NAME) $(LNAME)
				@$(ECHO) "\033[31m> Removed executable\033[0m\n"

re		:		fclean all

.PHONY	:		all clean fclean re

.DEFAULT_GOAL	:=	all
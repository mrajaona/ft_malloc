ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

DIR_INC		=	./inc/
DIR_SRC		=	./src/

NAME		=	libft_malloc_$(HOSTTYPE).so
LNNAME		=	libft_malloc.so

DIR_FREE	=	free/
SRC_FREE	=	free.c
SRCS_FREE	=	$(addprefix $(DIR_FREE), $(SRC_FREE))

DIR_MALLOC	=	malloc/
SRC_MALLOC	=	malloc.c \
				malloc_large.c \
				malloc_other.c
SRCS_MALLOC	=	$(addprefix $(DIR_MALLOC), $(SRC_MALLOC))

DIR_REALLOC		=	realloc/
SRC_REALLOC		=	realloc.c \
					ft_memcpy.c
SRCS_REALLOC	=	$(addprefix $(DIR_REALLOC), $(SRC_REALLOC))

DIR_SHOW	=	show/
SRC_SHOW	=	show_alloc_mem.c \
				show_type.c \
				show_item.c
SRCS_SHOW	=	$(addprefix $(DIR_SHOW), $(SRC_SHOW))

DIR_GLOBAL	=	global/
SRC_GLOBAL	=	global.c
SRCS_GLOBAL	=	$(addprefix $(DIR_GLOBAL), $(SRC_GLOBAL))

DIR_UTIL	=	util/
SRC_UTIL	=	identify.c \
				merge.c \
				split.c \
				get_type.c
SRCS_UTIL	=	$(addprefix $(DIR_UTIL), $(SRC_UTIL))

DIR_MORE	=	./
MORE_INC	=	memory.h

SRC			=	$(SRCS_MALLOC) \
				$(SRCS_FREE) \
				$(SRCS_REALLOC) \
				$(SRCS_SHOW) \
				$(SRCS_GLOBAL) \
				$(SRCS_UTIL)
INC			=	$(SRC:.c=.h) $(MORE_INC)

INCS		=	$(addprefix $(DIR_INC), $(INC))
SRCS		=	$(addprefix $(DIR_SRC), $(SRC))

DIRS		=	$(DIR_FREE) $(DIR_MALLOC) $(DIR_REALLOC) \
				$(DIR_SHOW) $(DIR_GLOBAL) $(DIR_UTIL) $(DIR_MORE)
DIRS_INC	=	$(addprefix -I$(DIR_INC), $(DIRS)) -I./ft_printf/inc

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror -fPIC \
				$(DIRS_INC) -c

CC			=	/usr/bin/gcc
RM			=	/bin/rm -f
LN			=	/bin/ln -s
ECHO		=	/usr/bin/printf

MAKE		=	/usr/bin/make -C

all			:	$(NAME)

$(OBJS) 	:	$(INCS)

libs		:
				$(MAKE) ./ft_printf

$(NAME) 	:	$(INCS) $(SRCS) $(OBJS)
				$(MAKE) ./ft_printf
				$(CC) -shared -o $(NAME) $(OBJS) ./ft_printf/libftprintf.a 
				$(RM) $(LNNAME)
				$(LN) $(NAME) $(LNNAME)
				@$(ECHO) "\033[32m> Executable compiled\033[0m\n"

clean		:
				@$(RM) $(OBJS)
				$(MAKE) ./ft_printf clean
				@$(ECHO) "\033[31m> Directory cleaned\033[0m\n"

fclean		:	clean
				@$(RM) $(NAME) $(LNAME)
				$(MAKE) ./ft_printf fclean
				@$(ECHO) "\033[31m> Removed executable\033[0m\n"

re			:	fclean all

.PHONY		:	all clean fclean re

.DEFAULT_GOAL	:=	all
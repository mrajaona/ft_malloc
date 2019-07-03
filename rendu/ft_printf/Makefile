NAME		=	libftprintf.a

INCLUDE		=	./inc/
INC			=	ft_printf.h

DIR_PRINTF	=	./src/ft_printf/
SRC_PRINTF	=	ft_printf.c
SRCS_PRINTF	=	$(addprefix	$(DIR_PRINTF), $(SRC_PRINTF))

DIR_BUF		=	./src/buf/
SRC_BUF		=	buf.c \
				ft_putstr.c \
				ft_putchar.c \
				ft_putaddr.c \
				ft_print_nbr.c \
				ft_putnbr.c \
				ft_putunbr_base.c \
				ft_print_double.c \
				ft_putdouble.c \
				ft_strlen.c
SRCS_BUF	=	$(addprefix	$(DIR_BUF), $(SRC_BUF))

DIR_CONV	=	./src/conversion/
SRC_CONV	=	init.c \
				init_prec_fw.c \
				init_type.c \
				convert.c \
				conv_str.c \
				conv_ptr.c \
				conv_uchar.c \
				conv_int.c \
				conv_uint.c \
				conv_double.c

SRCS_CONV	=	$(addprefix	$(DIR_CONV), $(SRC_CONV))


INCS		=	$(addprefix $(INCLUDE), $(INC))
SRCS		=	$(SRCS_PRINTF) $(SRCS_BUF) $(SRCS_CONV)

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror \
				-fPIC -I $(INCLUDE)

CC			=	/usr/bin/gcc
LIB			=	ar rc
RM			=	/bin/rm -f
ECHO		=	/usr/bin/printf

all		:		$(NAME)

$(OBJS)	:		$(INCS)

$(NAME)	:		$(INCS) $(SRCS) $(INCLUDE) $(OBJS)
				$(LIB) $(NAME) $(OBJS)
				@$(ECHO) "\033[32m> Executable compiled\033[0m\n"

clean	:
				@$(RM) $(OBJS)
				@$(ECHO) "\033[31m> Directory cleaned\033[0m\n"

fclean	:		clean
				@$(RM) $(NAME)
				@$(ECHO) "\033[31m> Removed executable\033[0m\n"

re		:		fclean all

.PHONY	:		all clean fclean re

.DEFAULT_GOAL	:=	all

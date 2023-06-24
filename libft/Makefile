NAME		= libft.a

SRCS1	= ft_atoi.c		\
		ft_bzero.c		\
		ft_isalnum.c	\
		ft_isalpha.c	\
		ft_isascii.c	\
		ft_isdigit.c	\
		ft_isprint.c	\
		ft_memchr.c		\
		ft_memcmp.c		\
		ft_memcpy.c		\
		ft_memmove.c	\
		ft_memset.c		\
		ft_strchr.c		\
		ft_strlcat.c	\
		ft_strlcpy.c	\
		ft_strlen.c		\
		ft_strncmp.c	\
		ft_strnstr.c	\
		ft_strrchr.c	\
		ft_tolower.c	\
		ft_toupper.c	\
		ft_strdup.c		\
		ft_calloc.c		\
		ft_substr.c		\
		ft_strjoin.c	\
		ft_strtrim.c	\
		ft_itoa.c		\
		ft_split.c		\
		ft_strmapi.c	\
		ft_striteri.c	\
		ft_striteri.c	\
		ft_putchar_fd.c	\
		ft_putstr_fd.c	\
		ft_putendl_fd.c	\
		ft_putnbr_fd.c	\

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

INCLUDE		= -I include

OBJDIR		= objs

SRCS		= $(SRCS1)

OBJS		=	$(SRCS:%.c=$(OBJDIR)/%.o)

all:	$(NAME)

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

$(OBJDIR)/%.o:%.c
			@mkdir -p $(@D)
			$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

clean:	
		@$(RM) -r $(OBJDIR)

fclean:	clean
		@$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re

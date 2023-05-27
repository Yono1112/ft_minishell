NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline
# RLDIR = `brew --prefix readline`
RM = rm -rf
SRCS =	src/main.c	\
		src/free.c	\
		src/lexer/tokenize.c	\
		src/lexer/blank.c		\
		src/lexer/operator.c	\
		src/lexer/word.c		\
		src/lexer/add_token_to_argv.c	\
		src/output_error/output_error.c	\
		src/expansion/expand.c	\
		src/expansion/remove_quote.c	\
		src/expansion/expand_variable.c	\
		src/expansion/expand_heredoc_line.c	\
		src/expansion/split_word.c	\
		src/parser/parse.c	\
		src/redirection/redirect.c	\
		src/pipeline/pipe.c

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

INC = -I include

DEBUG_FLAG = -fsanitize=address

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: CFLAGS += $(DEBUG_FLAG)
debug: re

test: re
	./test.sh

.PHONY: all clean fclean re test debug

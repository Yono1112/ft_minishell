NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -L$(LIBFTDIR) -lft
ifeq ($(shell uname -s), Linux)
else
RLDIR = $(shell brew --prefix readline)
LDFLAGS += -L$(RLDIR)/lib
endif
RM = rm -rf
SRCS =	src/main.c	\
		src/free/free.c	\
		src/lexer/tokenize.c	\
		src/lexer/blank.c		\
		src/lexer/operator.c	\
		src/lexer/word.c		\
		src/lexer/add_token_to_argv.c	\
		src/output_error/output_error.c	\
		src/expansion/expand.c	\
		src/expansion/remove_quote/remove_quote.c	\
		src/expansion/expand_variable/expand_variable.c	\
		src/expansion/expand_variable/expand_heredoc_line.c	\
		src/expansion/expand_variable/append_quote.c	\
		src/expansion/expand_variable/expand_parameter_str.c	\
		src/expansion/expand_variable/expand_variable_str.c	\
		src/expansion/expand_variable/expand_variable_token.c	\
		src/expansion/is_utils.c	\
		src/expansion/remove_quote/remove_quote_token.c	\
		src/expansion/remove_quote/remove_single_double_quote.c	\
		src/expansion/expand_variable/append_char.c	\
		src/parser/parse.c	\
		src/parser/pipeline.c	\
		src/parser/add_operator_to_node.c	\
		src/parser/add_token_to_node.c	\
		src/parser/create_new_redirect.c	\
		src/parser/parse_utils.c	\
		src/parser/simple_command.c	\
		src/redirection/do_redirect.c	\
		src/redirection/is_redirect.c	\
		src/redirection/open_redirect_file.c	\
		src/redirection/read_heredoc.c	\
		src/redirection/reset_redirect.c	\
		src/redirection/stashfd.c	\
		src/pipeline/pipe.c	\
		src/execution/exec.c	\
		src/execution/check_cmd_path.c	\
		src/execution/check_is_filename.c	\
		src/execution/exec_simple_cmd.c	\
		src/execution/wait_pipeline.c	\
		src/signal/signal.c	\
		src/builtin/is_builtin.c	\
		src/builtin/exec_builtin_cmd.c	\
		src/builtin/exec_builtin_exit.c	\
		src/builtin/exec_builtin_echo.c	\
		src/builtin/exec_builtin_cd.c	\
		src/builtin/exec_builtin_pwd.c	\
		src/builtin/exec_builtin_utils.c	\
		src/environ/env_utils.c	\
		src/environ/ft_getenv.c	\
		src/environ/init_env_list.c	\
		src/environ/set_env_list.c	\
		src/builtin/exec_builtin_export.c	\
		src/builtin/exec_builtin_unset.c	\
		src/environ/unset_env_list.c	\
		src/builtin/exec_builtin_env.c	\
		src/environ/update_value_to_env.c	\
		src/environ/add_key_value_to_env.c

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

INC =   -I include -I $(RLDIR)/include 

DEBUG_FLAG = -fsanitize=address
# DEBUG_FLAG = -fsanitize=address,leak

all: $(NAME)

LIBFTDIR	= libft

LIBFT = $(LIBFTDIR)/libft.a

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBS) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFTDIR)

re: fclean all

debug: CFLAGS += $(DEBUG_FLAG)
debug: re

test: re
	./test.sh

set-env:
	echo "minishell\nset echo-control-characters Off" >> ~/.inputrc

unset-env:
	echo "minishell\nset echo-control-characters On" >> ~/.inputrc 

norm:
	norminette include src libft
	nm -u $(NAME) | grep -v -E "_(readline|rl_clear_history|rl_on_new_line|\
	rl_replace_line|rl_redisplay|add_history|printf|malloc|free|write|\
	access|open|read|close|fork|wait|waitpid|wait3|wait4|signal|\
	sigaction|sigemptyset|sigaddset|kill|exit|getcwd|chdir|stat|lstat|\
	fstat|unlink|execve|dup|dup2|pipe|opendir|readdir|closedir|\
	strerror|perror|isatty|ttyname|ttyslot|ioctl|getenv|tcsetattr|\
	tcgetattr|tgetent|tgetflag|tgetnum|tgetstr|tgoto|tputs)"

.PHONY: all clean fclean re test debug

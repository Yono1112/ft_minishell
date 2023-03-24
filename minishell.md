# minishell
## flow
1. input from readline
1. lexer(tokenizer) and parser
	1. lexer
	1. parser
1. expand
1. exec cmd

- step.1 Readline Loop
- step.2 Build and Test
- step.3 Exec Path
	- fork
	- execve
	- wait
- step.4 Exec Filename
	- 環境変数PATHとは？
		- https://otomosa.com/linux/envpath/

Todo
- exec filenameでstrdupしたのをまだfreeしてない
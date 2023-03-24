# minishell
## Flow
1. input from readline
1. lexer(tokenizer) and parser
	1. lexer
	1. parser
1. expand
1. exec cmd

## Note for each step
- step.1 Readline Loop
	- readline
- step.2 Build and Test
- step.3 Exec Path
	- fork
	- execve
	- wait
- step.4 Exec Filename
	- access
		- int access(const char *pathname, int mode)
		- 呼び出し元プロセスがファイル pathname にアクセスできるかどうかをチェックする
		- mode はチェックを行うアクセス権を指定するもので、F_OK はファイルが存在するかどうかのみを,R_OK, W_OK, X_OK は、ファイルが存在して、それぞれ読み込み、書き込み、実行の許可があるか を検査する。
	- 環境変数PATHとは？
		- https://otomosa.com/linux/envpath/

## Todo
- exec filenameでstrdupしたのをまだfreeしてない
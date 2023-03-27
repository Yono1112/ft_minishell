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
		- `char *readline(const char str*);`
		- strを出力し、プロンプトを開いて標準入力で文字列を入力します。改行(Enter)を受け取ると、今まで入力された文字列を返します。
		- ubuntu上で`apt install -y libreadline-dev`
	- add_history
		- `int add_history(const char *);`
		- 引数に入れた文字列をhistoryとして保存します。プロンプトが開いている状態でキーボードの方向キー上下で今までプロンプトに入力した文字列を呼び出すことができます。
- step.2 Build and Test
- step.3 Exec Path
	- fork
	- wait
	- execve
- step.4 Exec Filename
	- access
		- `int access(const char *pathname, int mode);`
		- 呼び出し元プロセスがファイル pathname にアクセスできるかどうかをチェックする
		- mode はチェックを行うアクセス権を指定するもので、F_OK はファイルが存在するかどうかのみを,R_OK, W_OK, X_OK は、ファイルが存在して、それぞれ読み込み、書き込み、実行の許可があるか を検査する。
	- [環境変数PATHとは？](https://otomosa.com/linux/envpath/)

## Todo
- exec filenameでstrdupしたのをまだfreeしてない
- ~~ubuntuで動かすとreadlineのヘッダファイルが無いとerrorが出る~~
- 標準ライブラリをlibftにする

##doc
- [readlineとsignal by 42soul](https://intrepidgeeks.com/tutorial/minishell-readline)
- [minishellの概要 by 42soul](https://techdebt.tistory.com/33?category=833728)
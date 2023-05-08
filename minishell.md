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
		- プロセスを複製するコマンド
	- wait
		- 特定のプロセスが終了するまで呼び出し元のプロセスを停止するコマンド
	- execve
		- 指定したコマンドを呼び出し元のプロセスで実行するコマンド
- step.4 Exec Filename
	- access
		- `int access(const char *pathname, int mode);`
		- 呼び出し元プロセスがファイル pathname にアクセスできるかどうかをチェックする
		- mode はチェックを行うアクセス権を指定するもので、F_OK はファイルが存在するかどうかのみを,R_OK, W_OK, X_OK は、ファイルが存在して、それぞれ読み込み、書き込み、実行の許可があるか を検査する。
	- PATHについて
		- [環境変数PATHとは？](https://otomosa.com/linux/envpath/)
- step.5 tokenizer
	- tokenizer(lexer)とは
		- テキストをトークン(最小限に分割された単語)に分割すること
	- operator(制御演算子)
		- 制御演算子とはシェルにおいてプログラムの制御フローを制御するために用いられる特別な文字列で、一般的にシェルが特別な意味を持つ文字列を検出すると、それに応じた動作を実行する。
		- || (or)：左側のコマンドが失敗した場合にのみ、右側のコマンドを実行します。
		- & (background)：コマンドをバックグラウンドで実行します。バックグラウンドで実行されたコマンドは、現在のシェルの制御を返します。
		- && (and)：左側のコマンドが成功した場合にのみ、右側のコマンドを実行します。
		- ; (separator)：左側のコマンドを実行し、その後右側のコマンドを実行します。
		- ;; (end of command)：case文で使用され、現在のパターンに一致するコマンドを実行し、case文を終了します。
		- ( と ) (parentheses)：コマンドをサブシェル内で実行します。サブシェルは現在のシェルとは異なる環境で実行されます。
		- | (pipe)：左側のコマンドの出力を、右側のコマンドの入力に渡します。
		- \n (newline)：コマンドラインを終了し、実行可能なコマンドとして解釈します。
	- metacharcter(メタ文字)
		- コマンドやシェルスクリプト内で特別な意味を持つ文字のことで、ワードの区切りや引用符の扱い、リダイレクションの指定などに使われる。
	- メタ文字は文字列の解釈に関わる特別な意味を持つ文字であり、オペレータはシェルコマンドや構文の構成要素となる記号やキーワードであるという違いがある。
- step.9 redirection
	- dup2
		- `int dup2(int oldfd, int newfd)`
		- 
	- openのフラグとパーミッション
		- O_CREAT
			- ファイルが存在しない場合は新しく作成します。存在する場合は、他のフラグに従って開きます。
		- O_WRONLY
			- ファイルを書き込み専用モードで開きます。これにより、ファイルへの読み取りアクセスは許可されません。
		- O_TRUNC
			- ファイルを開く際に、そのサイズを0に切り詰めます。これは、新しいデータを書き込む前に、既存のデータを消去するために使用されます。
		- 0644(パーミッション)
			- 所有者に対して読み書きの権限を、グループおよび他のユーザーに対しては読み取りのみの権限を与えることを意味します。

## Todo
- exec filenameでstrdupしたのをまだfreeしてない
- ~~ubuntuで動かすとreadlineのヘッダファイルが無いとerrorが出る~~
	- done
		- readlineのリンクを一番後ろにすると解決した。順序があるっぽい。
- 標準ライブラリをlibftにする
- ~~cat fileでsegvする(usashellはしない)~~
	- done.だけど最後の行にプロンプトが表示されてしまう
- ~~echo にスペースだけだとsegvする(usahsellはしない)~~
	- tokenizerでスペースをwordと認識されているのが原因、usashellはwordと認識されてない
	- done!
		- tokenizerのblankとoperator以下のif文を別々に分けていたがelse ifで全ての条件式を一つにしたら解決した。
- ~~redirect outputが複数個の時にファイルが一つしか開かない~~
	- done
		- parserでtokenのポインタが正しく動いていなかったのが原因だった
- reset_redirectを自作する(現状usashellのをコピペしている)
- redirect inputでcat < fileをするも`cat: stdin: Bad file descriptor`と表示され読み込めない


##doc
- [readlineとsignal by 42soul](https://intrepidgeeks.com/tutorial/minishell-readline)
- [minishellの概要 by 42soul](https://techdebt.tistory.com/33?category=833728)
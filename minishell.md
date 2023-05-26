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
		- `pid_t wait(int *wstatus)`
		- 呼び出し元プロセスの子プロセスの状態変化を待ちます。子プロセスの状態変化がすでに発生していた場合は、wait関数はすぐに復帰します。それ以外の場合は、子プロセスの状態変化が起こるか、シグナルハンドラによりシステムコールが中断されるまで呼び出し元プロセスは停止します。
		- *statusは子プロセスからの終了ステータスを格納する変数を指定します。
		- 返り値は成功すると、終了した子プロセスのプロセスID を返す。 エラーの場合 -1 を返す。 
		- WEXITSATUS
			- 子プロセスの終了ステータスを返す。
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
		- O_APPEND
			- 既存のデータが上書きされず、新しいデータがファイルの末尾に追加されることが保証されます。
		- 0644(パーミッション)
			- 所有者に対して読み書きの権限を、グループおよび他のユーザーに対しては読み取りのみの権限を与えることを意味します。
- step10 pipe
- step11 expand
	- 展開 (expansion) とは変数などの中身をそれが使われてる場所に入れ込むこと。
	- 今回は変数展開(環境変数使用時に必要？)とパラメータ展開の$?を実装する。
	- $は展開したいときにしか使用しない。そのためexportやdeclareなどの変数宣言時には不必要。
	- $?(special parametar)
		- 最後に実行されたフォアグラウンドのパイプラインの 終了ステータスに展開されます。 
	- heredoc時のexpand
		- delimiter(cat << EOFでいうとEOFがdelimiter)がquoteに囲まれていた場合は、heredoc時に入力されるlineに変数($から始まる変数)が入ったとしても展開されない
		- 逆にdelimiterがquoteに囲まれていなかったら、変数はexpandされる

| 名前 | 展開・置換の意味 |
| --- | ------------- |
| ブレース展開 |  {1..10} を展開すること |
| チルダ展開 |  ~/.bash_profile の ~ を展開すること |
| パラメータ展開 |  $?、$@、$1、${1:-word} 等を展開すること |
| 変数展開 | 上記とほぼ同じだが展開対象が変数名の場合 |
| コマンド置換 |  $(cmd) を置換すること |
| 算術式展開 |  $((var + 1)) を展開すること |
| パス名展開 |  *.txt を展開すること |
| クォート削除 | "test.txt"の"を表示しない |
- step12 signal
- step13 environ
- step14 builtin


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
- ~~redirect inputでcat < fileをするも`cat: stdin: Bad file descriptor`と表示され読み込めない~~
	- done
		- create_new_redirect_inのt_node_kindがND_REDIR_OUTになっていたのが原因だった
- ~~pipeを実装したらredirect_inputとredirect_heredocを実行してもfcntlでerrorになってしまう~~
	- done
		- なぜかpushしたら上手くいくようになった。原因不明


##doc
- minishell
	- [man bash](https://linuxjm.osdn.jp/html/GNU_bash/man1/bash.1.html)
	- [minishellの作り方(usami-sanのminishell解説)](https://usatie.notion.site/minishell-29921d3ea13447ad897349acd5733d5e)
	- [minishellの作り方で出てくるコード例のrepository](https://github.com/usatie/minishell_v2/tree/livecoding)
	- [readlineとsignal by 42soul](https://intrepidgeeks.com/tutorial/minishell-readline)
	- [minishellの概要 by 42soul](https://techdebt.tistory.com/33?category=833728)
	- [シェルスクリプトの $ は･･･変数の接頭辞ではなく展開するときの記号(expand解説)](https://qiita.com/ko1nksm/items/1864aa2db8ce7bcf332d)
- git
	- [個人開発でGithubのissue,プルリクを活用する方法](https://qiita.com/usayamadausako/items/375bdae07e381745e6eb)
	- [git clone の際に submodule の clone を忘れたときの対処法](https://qiita.com/kentarosasaki/items/3e670567c0512b9d411e)
	- [git reset 解説](https://qiita.com/forest1/items/f7c821565a7a7d64d60f)
	- [DiscordのチャンネルにGitHubの通知を送るには？](https://mekurun.com/tips/discord-github/)
	- [［GitHub］一人開発でもissueベース/セルフプルリクエストを使って開発する](https://qiita.com/braveryk7/items/5208263cd06a8878f0c2)
